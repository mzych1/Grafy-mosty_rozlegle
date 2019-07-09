#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

class Graf
{
private:
	int n;//liczba wierzcholkow
	bool **tab;//tablica dwuwymiarowa
public:
	Graf()//konstruktor, ze wczytywaniem danych
	{
		int a, b;
		cin >> n;//blad jak podana nie liczba lub liczba ujemna
		if(cin.fail() || n<0)
			throw logic_error("niepoprawna liczba wierzcholkow"); 

		if (n != 0)
		{
			tab = new bool*[n];
			for (int i = 0; i < n; ++i)
			{
				tab[i] = new bool[n];
				for (int j = 0; j < n; ++j)
					tab[i][j] = false;
			}

			while (true)
			{
				cin >> a;//musi byc z zakresu od 0 do n-1
				if (!cin) 
					break;
				if (a < 0 || a >= n)
					throw logic_error("niepoprawny poczatek krawedzi");
				cin >> b;//blad jak nie liczba, musi byc z zakresu od 0 do n-1, nie moze byc rowna a
				if (cin.fail() || b < 0 || b >= n || a == b)
					throw logic_error("niepoprawny koniec krawedzi");
				tab[a][b] = true;
				tab[b][a] = true;
			}
		}
		if (!czySpojny())
			throw logic_error("wprowadzony graf nie jest spojny");
	}

	Graf(Graf &inny)//konstruktor kopiujacy
	{
		n = inny.n;
		if (n != 0)
		{
			tab = new bool*[n];
			for (int i = 0; i < n; ++i)
			{
				tab[i] = new bool[n];
				for (int j = 0; j < n; ++j)
					tab[i][j] = inny.tab[i][j];
			}
		}
	}

	~Graf()//destruktor
	{
		if (n != 0)
		{
			for (int i = 0; i < n; ++i)
				delete tab[i];
			delete tab;
		}
	}

	bool czySpojny(int a = -1, int b = -1)//przejscie grafu w glab i okreslenie czy jest spojny
	{
		int pocz = 0;//numer wierzcholka od ktorego bedziemy rozpoczynac przejscie grafu
		bool *odwiedzone = new bool[n]; // Tablica odwiedzin
		for (int i = 0; i < n; ++i)
			odwiedzone[i] = false;//na poczatku zaden wierzcholek nie jest odwiedzony
		int iloscOdwiedzonych = 0;

		//nie mozna zaczac przejscia grafu od wierzcholka a/b
		while (pocz == a || pocz == b)
			++pocz;
		DFS(pocz, iloscOdwiedzonych, odwiedzone);

		delete odwiedzone;
		if (a >= 0)
			iloscOdwiedzonych += 2;//dodaje wierzcholki ktore staly sie izolowane bo sa chwilowo usuniete
		if (iloscOdwiedzonych == n)
			return true;
		return false;
	}

	void DFS(int v, int& iloscOdw, bool *odw)
	{
		odw[v] = true;//oznaczam wierzcholek jako odwiedzony
		++iloscOdw;

		for (int i = 0; i < n; i++) //rekurencyjne odwiedzanie nieodwiedzonych sasiadow
			if (tab[v][i] && !odw[i]) //wywolujemy DFS dla i jesli wierzcholek i jest sasiadem v oraz nie byl odwiedzony
				DFS(i, iloscOdw, odw);
	}

	void wypiszMostyRozlegle()//sprawdza wszystkie krawedzie po kolei
	{
		if (n <= 2)//brak krawedzi lub 1 krawedz => brak mostow rozleglych
			return;

		Graf *tmp = new Graf(*this);//kopia grafu wejsciowego ktora bedziemy modyfikowac
		for (int i = 0; i < n; ++i)
		{
			for (int j = i; j < n; ++j)
			{
				if (tab[i][j])
				{
					tmp->usunKrawedz(i, j);
					if (!tmp->czySpojny(i, j))
						cout << i << " " << j << endl;
					tmp->dodajKrawedz(*this, i, j);
				}
			}

		}
		delete tmp;
	}

	void usunKrawedz(int a, int b)
	{
		if (a >= n || b >= n || tab[a][b] == false || tab[b][a] == false)
			throw logic_error("logic_error");  //sprawdzenie poprawnosci danych

		for (int i = 0; i < n; ++i)
		{
			tab[a][i] = false;
			tab[b][i] = false;
			tab[i][a] = false;
			tab[i][b] = false;
		}
	}

	void dodajKrawedz(Graf &bazowy, int a, int b)
	{
		if (a >= n || b >= n)
			throw logic_error("logic_error");  //sprawdzenie poprawnosci danych

		for (int i = 0; i <n; ++i)
		{
			tab[a][i] = bazowy.tab[a][i];
			tab[b][i] = bazowy.tab[b][i];
			tab[i][a] = bazowy.tab[i][a];
			tab[i][b] = bazowy.tab[i][b];
		}
	}
};
