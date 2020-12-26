//POP_2018_01_15_projekt_2_Sobczuk_Wojciech_AIR_3_172128.cpp srodowisko: Dev-C++ 5.11 kompilator: TDM-GCC 4.9.2 64-bit System operacyjny: Windows 8.1 64-bit

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iomanip>

using namespace std;

const unsigned short int MAX_ELEM_BAZA=20; //maksymalna ilosc elementow w bazie
const unsigned short int MAX_DL_JEDN=2; //maksymalna dlugosc jednostki

struct pomiar
{
	int ID;
	string IP;
	int dolnyZakres;
	int gornyZakres;
	char jednostka[MAX_DL_JEDN];
	int roz;
	char status;
};

void inicjalizacja(pomiar p[], int &i)
{
	fstream urzadzenia("urzadzenia.txt");
	while(!urzadzenia.eof())
	{
		urzadzenia >> p[i].ID;
		urzadzenia >> p[i].IP;
		urzadzenia >> p[i].dolnyZakres;
		urzadzenia >> p[i].gornyZakres;
		urzadzenia >> p[i].jednostka;
		urzadzenia >> p[i].roz;
		urzadzenia >> p[i].status;
		i++;
	}
	i--;
}

void pisz_menu()
{
	cout << "MENU GLOWNE" << endl;
	cout << "----------------" << endl;
	cout << "Wybierz opcje: " << endl;
	cout << "1. Dodanie urzadzenia do bazy" << endl;
	cout << "2. Wypisanie urzadzen z bazy" << endl;
	cout << "3. Przetworzenie pomiarow" << endl;
	cout << "-------------------------------" << endl;
	cout << "0. Wyjscie" << endl;
}

void wyswietlanie(pomiar p[], int wariant, int elem)
{
	if(wariant==1) 
	{
		for(int i=0; i<elem; i++)
		{
			if(p[i].status=='t') cout << p[i].ID << " " << p[i].IP << " " << p[i].dolnyZakres << " " << p[i].gornyZakres << " " << p[i].jednostka << " " << p[i].roz << " " << p[i].status << endl;
		}
	}
	else if(wariant==2)
	{
		for(int i=0; i<elem; i++)
		{
			if(p[i].status!='t') cout << p[i].ID << " " << p[i].IP << " " << p[i].dolnyZakres << " " << p[i].gornyZakres << " " << p[i].jednostka << " " << p[i].roz << " " << p[i].status << endl;
		}
	}
	else cout << "Zly numer wariantu!" << endl;
}

void dodanie(pomiar p[], int &elem)
{
	fstream urzadzenia("urzadzenia.txt");
	cout << "Podaj IP urzadzenia ";
	cin >> p[elem].IP;
	cout << "Podaj dolny zakres pomiaru urzadzenia ";
	cin >> p[elem].dolnyZakres;
	cout << "Podaj gorny zakres pomiaru urzadzenia ";
	cin >> p[elem].gornyZakres;
	do
	{
		cout << "Podaj jednostke pomiaru ";
		cin >> p[elem].jednostka;
	}while(strlen(p[elem].jednostka)>MAX_DL_JEDN);
	cout << "Podaj rozdzielczosc urzadzenia ";
	cin >> p[elem].roz;
	cout << "Podaj status urzadzenia ";
	cin >> p[elem].status;
	p[elem].ID=elem;
	elem++;
	for(int i=0; i<elem; i++) urzadzenia << p[i].ID << " " << p[i].IP << " " << p[i].dolnyZakres << " " << p[i].gornyZakres << " " << p[i].jednostka << " " << p[i].roz << " " << p[i].status << endl;
}

void pomiary(pomiar p[])
{
	fstream pom("pomiary.txt");
	int id, wartosc, i;
	float wynik;
	do
	{
		i=0;
		pom >> id >> wartosc;
		while(id!=p[i].ID) i++;
		if(p[i].status=='t')
		{
			wynik=((wartosc/(pow(2,p[i].roz)-1))*((p[i].gornyZakres-p[i].dolnyZakres))) + p[i].dolnyZakres;
			cout << setprecision(3) << wynik << " " << p[i].jednostka << ", czujnik " << id << endl;
		}	
	}while(!pom.eof());
}

void menu_glowne(pomiar p[], int &elem)
{
	int n,w;
	fstream urzadzenia("urzadzenia.txt");
	do
	{
		pisz_menu();
		cout << "Wybierz opcje: ";
		cin >> n;
		switch(n)
		{
			case 1:
				if(elem==MAX_ELEM_BAZA) 
				{
					cout << "Baza pelna" << endl;
					break;
				}
				else
				{
					dodanie(p,elem);
					break;
				}
			case 2: 
				cout << "Podaj wariant" << endl;
				cout << "-------------" << endl;
				cout << "1. Aktywne urzadzenia" << endl;
				cout << "2. Nieaktywne urzadzenia" << endl << ">";
				cin >> w;
				wyswietlanie(p, w, elem);
				break;
			case 3:
				pomiary(p);
				break;
			case 0: cout << "Wyjscie" << endl; break;
			default: cout << "Nie ma takiej opcji" << endl; break;
		}
	}while(n!=0);
}


int main()
{
	pomiar pomiary[MAX_ELEM_BAZA];
	int ilElem=0;
	fstream urzadzenia("urzadzenia.txt");
	if(!urzadzenia) cout << "Plik urzadzenia.txt nie zostal otwarty!" << endl;
	else cout << "Plik urzadzenia.txt otwarty pomyslnie " << endl;
	inicjalizacja(pomiary, ilElem);
	menu_glowne(pomiary, ilElem);
	urzadzenia.close();
	system("Pause");
	return 0;
}

