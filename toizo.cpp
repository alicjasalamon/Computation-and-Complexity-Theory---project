#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

	///////////////////////////
	//      strukturki       //
	///////////////////////////

struct Punkt{
	int x;
	int y;
	Punkt(int x, int y):x(x), y(y) {};
};

struct Przesuniecie{
	int x;
	int y;
	Przesuniecie(int x, int y):x(x), y(y) {};
};

struct Trasa{
	Punkt poczatek;
	Przesuniecie zmiana;
	Trasa(Punkt a, Przesuniecie b):poczatek(a), zmiana(b){};
};

struct Agent{
	Punkt poczatek;
	Punkt koniec;
	Agent(Punkt a, Punkt b):poczatek(a), koniec(b){};
};

	///////////////////////////
	//    zmienne globalne   //
	///////////////////////////

//rozmiar planszy
int x;
int y;

//dane wejsciowe o agentach
vector<Agent> tablicaAgentow;

//dane wyjsciowe - punkty i przesuniecia
vector<Trasa> wynik;

int glebokosc=-1;
int nrAgenta=-1;

	///////////////////////////
	//   szalone funkcje     //
	///////////////////////////
	
int arystoteles(Punkt a, Punkt b)
{
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
	
bool brakKolizji(Punkt a)
{
	Punkt p(0,0); //tu mi kazalo dac cos
	for(int i=0; i<wynik.size(); i++)
	{
		p = wynik[i].poczatek;
		if(p.x == a.x && p.y == a.x)
			return false;
	}
	return true;
}

Punkt porownanie(0,0); //kazalo
/*
bool sort(const Trasa& a, const Trasa& b)
{
	return arystoteles(a.poczatek, porownanie) < arystoteles(b.poczatek, porownanie);
}*/

Przesuniecie polnoc = 	Przesuniecie(1,0);
Przesuniecie poludnie = Przesuniecie(-1,0);
Przesuniecie wschod = 	Przesuniecie(0,1);
Przesuniecie zachod = 	Przesuniecie(0,-1);	
	
vector<Przesuniecie> szukajRuchow(Punkt a, Punkt b)
{
	//wybieramy mozliwe wektory
	vector<Trasa> mozliwosci;
	if((a.x -1)>0 && brakKolizji(Punkt(a.x-1, a.y))) 
		mozliwosci.push_back(Trasa(a,poludnie));
	if((a.x +1)<=x && brakKolizji(Punkt(a.x+1, a.y)))
		mozliwosci.push_back(Trasa(a, polnoc));
	if((a.y -1)>0 && brakKolizji(Punkt(a.x, a.y-1)))
		mozliwosci.push_back(Trasa(a, zachod));
	if((a.y +1)<=y && brakKolizji(Punkt(a.x, a.y+1))) 
		mozliwosci.push_back(Trasa(a, wschod));
	
	//i sortujemy je
	porownanie = b;
	//sort(mozliwosci.begin(), mozliwosci.end(), sort);
	
	//przepisujemy
	vector<Przesuniecie> rezultat;
	/*for(int i=0; i<mozliwosci.size(); i++)
	{
		rezultat.push_back(mozliwosci[i].zmiana);
	}*/
	return rezultat;
}

void szukaj_drogi(Punkt a, Punkt b)
{
	if(a.x==b.x && a.y==b.y)
	{
		nrAgenta++;
		Agent nastepnyAgent = tablicaAgentow[nrAgenta];
		if(nastepnyAgent.poczatek.x ==0 )
		{
			wypisz();
			exit(EXIT_SUCCESS);
		}
		else
		{
			szukaj_drogi(nastepnyAgent.poczatek, nastepnyAgent.koniec);
		}
		nrAgenta--;
	}
	else
	{
		vector<Przesuniecie> mozliweRuchy;
		mozliweRuchy = szukajRuchow(a,b);
		for(int i=0; i<mozliweRuchy.size(); i++)
		{
			glebokosc++;
			Przesuniecie w = mozliweRuchy[i];
			wynik[glebokosc]=Trasa(a,w);
			szukaj_drogi(Punkt(a.x+w.x, b.x+w.x), b);
			glebokosc--;
		}
	}

}

void wypisz()
{
	cout << wynik.size() << endl;
	for(int i=0; i<wynik.size(); i++)
	{
		cout << wynik[i].poczatek.x << " "  << wynik[i].poczatek.y << " " ;
		cout << wynik[i].zmiana.x << " "  << wynik[i].zmiana.y << endl;	
	}
	
}
	///////////////////////////
	//   	    main         //
	///////////////////////////
	
int main()
{
	//a teraz wczytam
	cin >> x >> y;
	
	int ile, a,b,c,d;
	cin >> ile;
	
	for(int i=0; i<ile; i++)
	{
		cin >> a >> b >> c >> d;
		tablicaAgentow.push_back(Agent(Punkt(a,b), Punkt(c,d)));
	}
	
	Agent agent = tablicaAgentow[0];
	//szukaj_drogi(agent.poczatek, agent.koniec);

	cout << "dzialam " << endl;
	
	wynik.push_back(Trasa(Punkt(3,2), Przesuniecie(1,0)));
	wynik.push_back(Trasa(Punkt(5,6), Przesuniecie(0,1)));
	wynik.push_back(Trasa(Punkt(1,2), Przesuniecie(-1,0)));

	wypisz();
 
    return 0;
}
