#ifndef __ingiro_h__
#define __ingiro_h__

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include "random.h"

using namespace std;

class City {
private:
		vector<double> c;  // Coordinate della città
		Random rnd;        // Oggetto per generare numeri casuali

public:
		City();
		~City();

		double Get_Coord(int i);             // Ottiene la coordinata i-esima della città
		void Set_city(Random& rnd);          // Imposta la città con coordinate casuali
		void Set(double x, double y);        // Imposta le coordinate della città
};



class Mappa {
private:
		int _ncity;             // Numero di città
		vector<City> Map;       // Vettore di città

public:
		Mappa(int ncity, Random& rnd); // costruttore per città random
		Mappa (int ncity, const string& filename); //costruttore per citta caricate da file
		~Mappa();

		City& GetCity(int index);             // Ottiene la città all'indice specificato
		double Get_length(vector<int> p);     // Calcola la lunghezza del percorso p
		double Get_distance(vector<int> p, int i, int j);  // Calcola la distanza tra due città nel percorso p
};



class Genetica {
private:
		Random rnd;                    // Oggetto per generare numeri casuali
		Mappa Map;                     // Mappa di città
		vector<int> percorso;          // Percorso corrente
		int _ncity;                    // Numero di città
		int _N;                        // Numero di individui nella popolazione

public:
		Genetica(int ncity);
		Genetica(int ncity, const string& filename);
		~Genetica();

		vector<vector<int>> Prima_generazione(int N);  // Genera la prima generazione di percorsi
		void sort_by_length(vector<vector<int>>& generazione);  // Ordina i percorsi per lunghezza
		bool check_percorso(const vector<int>& p);  // Verifica la validità del percorso
		vector<int> selection(const vector<vector<int>>& generazione);  // Seleziona un percorso dalla generazione

		// Mutazioni
		void pair_perm(vector<int>& p);           // Permutazione di coppie
		void shift(vector<int>& p);               // Shift delle città
		void m_perm(vector<int>& p);              // Permutazione multipla
		void m_inverse(vector<int>& p);           // Inversione di una sottosequenza
		pair<vector<int>, vector<int>> crossover(vector<int>& parent1, vector<int>& parent2);  // Crossover tra due percorsi

		vector<int> Evoluzione(int _N, const string& filename);  // Evoluzione della popolazione
};

#endif
