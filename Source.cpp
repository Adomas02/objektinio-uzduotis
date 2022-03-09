#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include <boost/algorithm/algorithm.hpp>


using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using std::setw;
using std::string;

//const int kiek = 15;

struct Mokinys
{
	string vardas, pavarde;
	int* paz= new int[];
	int egz;
	double rezult = 0;
};

void ivestis(std::vector<Mokinys> &mok,int kiek);
void isvestis(std::vector<Mokinys> &mok,int kiek);
double skaiciavimas(double a, std::vector<Mokinys> &mok, int i);
double skaiciavimasVid(std::vector<Mokinys> &mok, int a,int kiek);
void rikiavimas(std::vector<Mokinys> &mok, int a,int kiek);
double skaiciavimasMed(std::vector<Mokinys> &mok, int i,int kiek);
void pazymiuIvestis(std::vector<Mokinys> &mok, int a,int kiek);
void bufer_nusk(std::string read_vardas, std::string write_vardas);
std::vector<std::string> split(std::string str, char delimiter);
std::vector<Mokinys> sortabc(std::vector<Mokinys> mok);

int main()
{
	srand(time(NULL));
	std::vector<Mokinys> mok;
	//Mokinys a;
	//ivestis(mok);
	bufer_nusk("studentai.txt", "kursiokai.txt");
}
void ivestis(std::vector<Mokinys> &mok,int kiek)
{
	int i = 0;
	char y;
	while (1)
	{
		cout << "Ar norite ivesti mokini? y/n" << endl;
		cin >> y;
		if (y == 'y')
		{
			cout << "Iveskite mokinio varda ";
			mok.push_back(Mokinys());
			string vardas;
			cin >> vardas;
			mok[i].vardas = vardas;
			cout << "Iveskite mokinio pavarde ";
			string pavarde;
			cin >> pavarde;
			mok[i].pavarde = pavarde;
			cout << "Iveskite egzamino pazymi ";
			mok[i].egz = rand() % 10 + 1;
			cout << mok[i].egz << endl;
			pazymiuIvestis(mok, i,kiek);
			rikiavimas(mok, i,kiek);
			i++;
		}
		else
		{
			break;
		}
	}
	//isvestis(mok, i);
}
void isvestis(std::vector<Mokinys> &mok,int kiek)
{
	cout << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
	cout << "----------------------------------------------------------" << endl;
	int i=0;
	sortabc(mok);
	for (Mokinys &m : mok)
		{
			rikiavimas(mok, i,kiek);
			cout << mok[i].vardas << setw(20) << mok[i].pavarde << setw(15) << fixed << setprecision(2) << skaiciavimasVid(mok, i,kiek) << setw(15) << fixed << setprecision(2) << skaiciavimasMed(mok, i,kiek) << endl;
			i++;
		}

}
double skaiciavimasVid(std::vector<Mokinys> &mok, int a,int kiek)
{
	double sum = 0, vid; //pazymiu suma, vidurkis
	for (int i = 0; i < kiek; i++)
	{
		sum += mok[a].paz[i];
	}
	vid = sum / kiek;
	mok[a].rezult = skaiciavimas(vid, mok, a);
	return mok[a].rezult;
}
void rikiavimas(std::vector<Mokinys> &mok, int a, int kiek)
{
	int laikinas;
	for (int i = 0; i < kiek; i++)
		for (int j = i + 1; j < kiek; j++)
		{
			if (mok[a].paz[i] > mok[a].paz[j])
			{
				laikinas = mok[a].paz[i];
				mok[a].paz[i] = mok[a].paz[j];
				mok[a].paz[j] = laikinas;
			}
		}
}
double skaiciavimas(double a, std::vector<Mokinys> &mok, int i)
{
	mok[i].rezult = 0.4 * a + 0.6 * mok[i].egz;
	return mok[i].rezult;
}
double skaiciavimasMed(std::vector<Mokinys> &mok, int i, int kiek)
{
	if (kiek % 2 == 0)
	{
		double laikMed;
		laikMed = ((mok[i].paz[kiek / 2] + mok[i].paz[kiek / 2 - 1]) / 2.0);
		mok[i].rezult = skaiciavimas(laikMed, mok, i);
		return mok[i].rezult;
	}
	else
	{
		mok[i].rezult = skaiciavimas(mok[i].paz[kiek / 2], mok, i);
		return mok[i].rezult;
	}
}
void pazymiuIvestis(std::vector<Mokinys> &mok, int a,int kiek)
{
	int i = 0;
	for (int j = 0; j < kiek; j++)
	{
		cout << "Iveskite namu darbu pazymi ";

		int pazLaik; //laikinas pazimys
		pazLaik = rand() % 10 + 1;
		cout << pazLaik << endl;
		mok[a].paz[i] = pazLaik;
		i++;
	}
}
void bufer_nusk(std::string read_vardas, std::string write_vardas)
{
	std::vector<std::string> splited;
	std::string eil,tmp;
	std::stringstream my_buffer;
	

	//nuskaitymas i bufferi
	std::ifstream open_f(read_vardas);
	my_buffer << open_f.rdbuf();
	open_f.close();
	std::getline(my_buffer, tmp);
	std::vector<std::string> tmpeilDalys = split(tmp,' ');
	int kiek=0;
	for (std::string &a : tmpeilDalys)
	{
		kiek++;
	}
	//cout<<kiek;
	std::vector<Mokinys> mokiniai;

	//bufferio padalijimas i eiluciu vektoriu
	while (my_buffer)
	{
		if (!my_buffer.eof())
		{
			std::getline(my_buffer, eil);

			std::vector<std::string> eilDalys = split(eil,' ');

			

			Mokinys mok=Mokinys();
			mok.vardas = eilDalys[0];
			mok.pavarde = eilDalys[1];
			
			mok.paz = new int[kiek];
			for(int i=0;i<kiek-3;i++)
			{
				mok.paz[i]=std::stoi(eilDalys[2+i]);
			}

			mok.egz = std::stod(eilDalys[kiek-1]);
			

			mokiniai.push_back(mok);
    		//cout<<mokiniai.vardas;
			splited.push_back(eil);

		}
		else
			break;

	}

	isvestis(mokiniai,kiek);

	//vektroiaus konvertavimas i viena eilute
	std::string outputas = "";
	for (std::string &a : splited)
		(a.compare(*splited.rbegin()) != 0) ? outputas += a + "\n" : outputas += a;
	splited.clear();

	//Failo isvedimas per viena eilute
	std::ofstream out_f(write_vardas);
	out_f << outputas;
	out_f.close();
}
std::vector<std::string> split(std::string str, char delimiter)
{
	std::vector<std::string> result;
    size_t start;
    size_t end = 0;
 
    while ((start = str.find_first_not_of(delimiter, end)) != std::string::npos)
    {
        end = str.find(delimiter, start);
        result.push_back(str.substr(start, end - start));
    }

	return result;
}
std::vector<Mokinys> sortabc(std::vector<Mokinys> mok)
{
	Mokinys laikinas;
	for (Mokinys &m : mok)
	 for(Mokinys &n : mok)
	 if(m.vardas>n.vardas)
	 {
		laikinas= m;
		m=n;
		n=m;
	 }

	return mok;
}

