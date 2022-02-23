#include<iomanip>
#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::setw;
using std::fixed;
using std::setprecision;

struct Mokinys {
	string vardas, pavarde;
	int* paz;
	int egz, kiek;
	double rezult = 0;
};
void ivestis(Mokinys mok[],int i);
void isvestis(Mokinys mok[],int i);
double skaiciavimas(double a, Mokinys mok[], int i);
double skaiciavimasVid(Mokinys mok[], int i);
void rikiavimas(Mokinys mok[],int n);
double skaiciavimasMed(Mokinys mok[], int i);
void pazymiuIvestis(Mokinys mok[],int i);
void ivestisDidejantisMasyvas(Mokinys mok[], int i, int did);
Mokinys* didintMasyva(Mokinys mok[], int did);

int main()
{
	
	int did = 1;
	Mokinys* A;
	A = new Mokinys[did];

	int i = 0;
	
	ivestisDidejantisMasyvas(A,i,did);
}
void ivestis(Mokinys mok[],int i)
{
	cout << "Iveskite mokinio varda ";
	cin >> mok[i].vardas;
	cout << "Iveskite mokinio pavarde ";
	cin >> mok[i].pavarde;
	mok[i].paz = new int[100];
	pazymiuIvestis(mok,i);
	cout << "Iveskite egzamino pazymi ";
	cin >> mok[i].egz;
}
void isvestis(Mokinys mok[], int i)
{
	cout << "Vardas" << setw(10) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) <<"Galutinis (Med.)" << endl;
	cout << "----------------------------------------------------------" << endl;
	for (int j = 0;j < i;j++)
	{
		cout << mok[j].vardas << setw(10) << mok[j].pavarde << setw(15) << fixed << setprecision(2) << skaiciavimasVid(mok, j) << setw(15) << fixed << setprecision(2) << skaiciavimasMed(mok, j) << endl;
	}
}
double skaiciavimasVid(Mokinys mok[], int n)
{
	double sum = 0, vid;//pazymiu suma, vidurkis
	for (int i = 0;i < mok[i].kiek;i++)
	{
		sum += mok[n].paz[i];
	}
	vid = sum / mok[n].kiek;
	mok[n].rezult=skaiciavimas(vid,mok,n);
	return mok[n].rezult;
}
void rikiavimas(Mokinys mok[], int n)
{
	int laikinas;
	for (int i = 0;i < mok[n].kiek; i++)
		for (int j = i + 1;j < mok[n].kiek;j++)
		{
			if (mok[n].paz[i] > mok[n].paz[j])
			{
				laikinas = mok[n].paz[i];
				mok[n].paz[i] = mok[n].paz[j];
				mok[n].paz[j] = laikinas;
			}

		}
}
double skaiciavimas(double a, Mokinys mok[],int i)
{
	mok[i].rezult = 0.4 * a + 0.6 * mok[i].egz;
	return mok[i].rezult;
}
double skaiciavimasMed(Mokinys mok[],int i)
{
	if (mok[i].kiek % 2 == 0)
	{
		double laikMed;
		laikMed =( (mok[i].paz[mok[i].kiek / 2] + mok[i].paz[mok[i].kiek / 2 - 1]) / 2.0);
		mok[i].rezult = skaiciavimas(laikMed, mok,i);
		return mok[i].rezult;
	}
	else
	{
		mok[i].rezult = skaiciavimas(mok[i].paz[mok[i].kiek/2], mok,i);
		return mok[i].rezult;
	}
}
void pazymiuIvestis(Mokinys mok[],int n)
{
	char yesNo;
	int i = 0;
	while (1)
	{
		cout << "Ar norite ivesti namu darbu pazymi? (y/n) ";
		cin >> yesNo;
		if (yesNo == 'y')
		{
			cin >> mok[n].paz[i];
			i++;
			mok[n].kiek = i;
		}
		else
		{
			break;
		}
	}
}
void ivestisDidejantisMasyvas(Mokinys mok[],int i, int did)
{
	char yes;
	while (1)
	{
		cout << "Ar norite ivesti mokini? (y/n) ";
		cin >> yes;
		if (yes == 'y')
		{
			if (i == did-1)
			{
				ivestis(mok, i);
				rikiavimas(mok, i);
				i++;
				ivestisDidejantisMasyvas(didintMasyva(mok, did), i, did + 5);
			}
			else
			{
				ivestis(mok, i);
				rikiavimas(mok, i);
				i++;
			}
		
		}
		else
		{
			break;
		}
	}
	isvestis(mok, i);
}
Mokinys* didintMasyva(Mokinys mok[],int did)
{
	 Mokinys* tempMas;
	 tempMas = new Mokinys[did + 5];
	 for (int i = 0;i < did;i++)
	 {
		 tempMas[i] = mok[i];
	 }
	 return tempMas;
}