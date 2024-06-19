#include "ingiro.h"
#include <unordered_set>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;

// Implementazione della classe City
City::City() {
		c.resize(2); // Inizializza il vettore c per contenere 2 elementi (coordinate x e y)
}

City::~City() {}

double City::Get_Coord(int i) {
		return c[i]; // Ritorna la coordinata richiesta (0 per x, 1 per y)
}

void City::Set_city(Random& rnd) {
	
		/*/ Imposta la città su una circonferenza
		double R = 1; // Raggio della circonferenza
		double x = rnd.Rannyu(-1, 1); // Genera un numero casuale tra -1 e 1 per la coordinata x
		c[0] = x;

		if (rnd.Rannyu() < 0.5) {
				c[1] = -sqrt(R - x * x); // Calcola la coordinata y in modo che sia sulla circonferenza
		} else {
				c[1] = sqrt(R - x * x); // Calcola la coordinata y in modo che sia sulla circonferenza
		}
		/*/
	
		// Codice alternativo per impostare le coordinate su un quadrato
		//
		double x = rnd.Rannyu(-1, 1);
		double y = rnd.Rannyu(-1, 1);
		c[0] = x;
		c[1] = y;
		//
}

void City::Set(double x, double y) {
		c[0] = x; // Imposta la coordinata x
		c[1] = y; // Imposta la coordinata y
}

// Implementazione della classe Mappa

Mappa::Mappa(int ncity, Random& rnd) : _ncity(ncity) {
		Map.resize(ncity); // Ridimensiona il vettore Map per contenere ncity elementi

		// Inizializza ciascuna città nella mappa con coordinate casuali
		for (int i = 0; i < _ncity; i++) {
				Map[i].Set_city(rnd);
		}

		// Codice alternativo per ordinare le città in maniera regolare lungo una circonferenza
		/*
		for (int i = 0; i < _ncity; i++) {
				Map[i].Set(cos(i * 2 * M_PI / _ncity), sin(i * 2 * M_PI / _ncity));
		}
		*/
}

Mappa::~Mappa() {}

City& Mappa::GetCity(int index) {
		if (index >= 0 && index < _ncity) {
				return Map[index]; // Ritorna la città alla posizione index
		} else {
				throw out_of_range("Index out of range"); // Lancia un'eccezione se l'indice è fuori dai limiti
		}
}

double Mappa::Get_length(vector<int> p) {
		double length = 0.0;

		// Calcola la lunghezza totale del percorso
		for (int i = 0; i < _ncity - 1; i++) {
				City& current_city = GetCity(p[i]);
				City& next_city = GetCity(p[i + 1]);

				// Calcola la distanza euclidea tra due città
				length += sqrt(pow(current_city.Get_Coord(0) - next_city.Get_Coord(0), 2) +
											 pow(current_city.Get_Coord(1) - next_city.Get_Coord(1), 2));
		}

		// Aggiungi la distanza tra l'ultima città e la prima per chiudere il ciclo
		City& first_city = GetCity(p[0]);
		City& last_city = GetCity(p[_ncity - 1]);
		length += sqrt(pow(first_city.Get_Coord(0) - last_city.Get_Coord(0), 2) +
									 pow(first_city.Get_Coord(1) - last_city.Get_Coord(1), 2));

		return length;
}

double Mappa::Get_distance(vector<int> p, int i, int j) {
		double distance = 0.0;

		City& current_city = GetCity(p[i]);
		City& next_city = GetCity(p[j]);

		// Calcola la distanza euclidea tra due città
		distance = sqrt(pow(current_city.Get_Coord(0) - next_city.Get_Coord(0), 2) +
										pow(current_city.Get_Coord(1) - next_city.Get_Coord(1), 2));

		return distance;
}

// Implementazione della classe Genetica

Genetica::Genetica(int ncity) : Map(ncity, rnd), _ncity(ncity) {
		percorso.resize(_ncity);
		for (int i = 0; i < _ncity; ++i) {
				percorso[i] = i; // Inizializza il percorso con la sequenza di città
		}
		cout << endl;
}

Genetica::~Genetica() {}

vector<vector<int>> Genetica::Prima_generazione(int N) {
		_N = N;
		vector<vector<int>> generazione;

		int i = 0;
		while (i < _N) {
				int j = static_cast<int>(rnd.Rannyu(1, _ncity));
				int k = static_cast<int>(rnd.Rannyu(1, _ncity));

				// Assicura che k sia diverso da j
				while (k == j) {
						k = static_cast<int>(rnd.Rannyu(1, _ncity));
				}

				swap(percorso[k], percorso[j]); // Scambia due città nel percorso
				generazione.push_back(percorso); // Aggiunge il percorso modificato alla generazione
				i++;
		}
		return generazione;
}

void Genetica::sort_by_length(vector<vector<int>>& generazione) {
		sort(generazione.begin(), generazione.end(), [this](vector<int>& a, vector<int>& b) { // Usa Map per calcolare la lunghezza
				return Map.Get_length(a) < Map.Get_length(b); // Ordina i percorsi per lunghezza crescente
		});
}

bool Genetica::check_percorso(const vector<int>& p) {
		if (p[0] != 1) return false; // Verifica che il percorso inizi con la città 1
		vector<bool> visited(_ncity, false); // Inizializza un vettore per tracciare le città visitate

		for (int i = 0; i < _ncity; ++i) {
				int city = p[i];
				if (city < 1 || city > _ncity || visited[city - 1]) {
						return false; // Verifica unicità e validità delle città nel percorso
				}
				visited[city - 1] = true; // Marca la città come visitata
		}

		return true; // Se tutte le verifiche sono superate, il percorso è valido
}

vector<int> Genetica::selection(const vector<vector<int>>& generazione) {
		double r = rnd.Rannyu();
		int j = static_cast<int>(fmod(generazione.size() * r * r, generazione.size())); // Selezione non lineare
		return generazione[j];
}

void Genetica::pair_perm(vector<int>& p) {
		int j = static_cast<int>(rnd.Rannyu(1, _ncity));
		int k = static_cast<int>(rnd.Rannyu(1, _ncity));

		// Assicura che k sia diverso da j
		while (k == j) {
				k = static_cast<int>(rnd.Rannyu(1, _ncity));
		}

		swap(p[k], p[j]); // Scambia due città nel percorso
}

void Genetica::shift(vector<int>& p) {
		int j = static_cast<int>(rnd.Rannyu(1, _ncity - 1)); // Calcola un indice casuale per lo shift
		rotate(p.begin() + 1, p.begin() + j, p.end()); // Esegue lo shift del percorso
}

void Genetica::m_perm(vector<int>& p) {
		int j = static_cast<int>(rnd.Rannyu(1, _ncity - 1)); // Indice di inizio
		int m = static_cast<int>(rnd.Rannyu(1, (_ncity - j) / 2)); // Numero di città da spostare
		int z = static_cast<int>(rnd.Rannyu(j + m + 1, (_ncity - 1 - m))); // Inizio dell'altro range

		swap_ranges(p.begin() + j, p.begin() + j + m, p.begin() + z); // Scambia i segmenti di città
}

void Genetica::m_inverse(vector<int>& p) {
		int j = static_cast<int>(rnd.Rannyu(1, _ncity - 1)); // Indice di inizio
		int m = static_cast<int>(rnd.Rannyu(j, _ncity)); // Indice di fine

		reverse(p.begin() + j, p.begin() + m); // Inverte il segmento di città
}

pair<vector<int>, vector<int>> Genetica::crossover(vector<int>& parent1, vector<int>& parent2) {
		if (parent1.size() != parent2.size()) throw std::invalid_argument("Parents must be of the same size");

		int j = static_cast<int>(rnd.Rannyu(1, _ncity - 1)); // Punto di crossover
		vector<int> child1(_ncity, -1); // Inizializza con -1 per rappresentare le posizioni non ancora assegnate
		vector<int> child2(_ncity, -1);

		// Copia la prima parte del percorso dal genitore
		for (int i = 0; i <= j; ++i) {
				child1[i] = parent1[i];
				child2[i] = parent2[i];
		}

		// Set per tenere traccia delle città già incluse nel percorso
		unordered_set<int> included1(child1.begin(), child1.begin() + j + 1);
		unordered_set<int> included2(child2.begin(), child2.begin() + j + 1);

		// Completare i percorsi con le città mancanti nell'ordine in cui appaiono nel consorte
		int current_index1 = j + 1;
		int current_index2 = j + 1;

		for (int i = 0; i < _ncity; ++i) {
				if (included1.find(parent2[i]) == included1.end()) {
						child1[current_index1++] = parent2[i];
						included1.insert(parent2[i]);
				}
				if (included2.find(parent1[i]) == included2.end()) {
						child2[current_index2++] = parent1[i];
						included2.insert(parent1[i]);
				}
		}

		if (!check_percorso(child1)) {
				child1 = parent1; // Se il percorso non è valido, ritorna al genitore
		}
		if (!check_percorso(child2)) {
				child2 = parent2; // Se il percorso non è valido, ritorna al genitore
		}

		return {child1, child2};
}

vector<int> Genetica::Evoluzione(int _N, int gen_stop) {
		auto generazione = Prima_generazione(_N);

		sort_by_length(generazione);
		int i = 0;
		//int no_improvement = 0;

		//ofstream outFile(filename); // Crea un file di output per salvare i risultati

		while (i <gen_stop) { 
				vector<vector<int>> new_generation = {generazione[0]}; // Mantiene il miglior percorso

				while (new_generation.size() < _N) {
						vector<int> parent1 = selection(generazione);
						vector<int> parent2 = selection(generazione);

						if (rnd.Rannyu() < 0.9) {
								auto crossover_result = crossover(parent1, parent2);

								new_generation.push_back(crossover_result.first);
								new_generation.push_back(crossover_result.second);
						} else {
								new_generation.push_back(parent1);
								new_generation.push_back(parent2);
						}
				}

				for (int j = 0; j < _N ; ++j) {
					
						int k = static_cast<int>(rnd.Rannyu(0., _N));

						if (rnd.Rannyu() < 0.075)  m_inverse(new_generation[k]);

						if (rnd.Rannyu() < 0.1)  shift(new_generation[k]);
					
						if (rnd.Rannyu() < 0.1) m_perm(new_generation[k]);
						
						if (rnd.Rannyu() < 0.05) pair_perm(new_generation[k]);
						
				}

				sort_by_length(new_generation);
/*
				if (Map.Get_length(new_generation[0]) < Map.Get_length(generazione[0])) {
						no_improvement = 0; // Resetta il contatore se c'è miglioramento
				} else {
						no_improvement++;
				}
*/
				generazione = new_generation;
		
		i++;
			}
		return generazione[0];
}

vector<int> Genetica::RESTART(int _N, int gen_stop, vector<int> &old_best) {
	
	vector<vector<int>> generazione={old_best};

	int i = 0;
	while (i < _N-1) {
			int j = static_cast<int>(rnd.Rannyu(1, _ncity));
			int k = static_cast<int>(rnd.Rannyu(1, _ncity));

			// Assicura che k sia diverso da j
			while (k == j) {
					k = static_cast<int>(rnd.Rannyu(1, _ncity));
			}

			swap(old_best[k], old_best[j]); // Scambia due città nel percorso
			generazione.push_back(old_best); // Aggiunge il percorso modificato alla generazione
			i++;
	}
	
	sort_by_length(generazione);
	
	int j = 0;
	//int no_improvement = 0;

	//ofstream outFile(filename); // Crea un file di output per salvare i risultati

	while (j <gen_stop) { 
			vector<vector<int>> new_generation = {generazione[0]}; // Mantiene il miglior percorso

			while (new_generation.size() < _N) {
					vector<int> parent1 = selection(generazione);
					vector<int> parent2 = selection(generazione);

					if (rnd.Rannyu() < 0.9) {
							auto crossover_result = crossover(parent1, parent2);

							new_generation.push_back(crossover_result.first);
							new_generation.push_back(crossover_result.second);
					} else {
							new_generation.push_back(parent1);
							new_generation.push_back(parent2);
					}
			}

			for (int j = 0; j < _N ; ++j) {

					int k = static_cast<int>(rnd.Rannyu(0., _N));

					if (rnd.Rannyu() < 0.075)  m_inverse(new_generation[k]);

					if (rnd.Rannyu() < 0.1)  shift(new_generation[k]);

					if (rnd.Rannyu() < 0.1) m_perm(new_generation[k]);

					if (rnd.Rannyu() < 0.05) pair_perm(new_generation[k]);

			}

			sort_by_length(new_generation);
/*
			if (Map.Get_length(new_generation[0]) < Map.Get_length(generazione[0])) {
					no_improvement = 0; // Resetta il contatore se c'è miglioramento
			} else {
					no_improvement++;
			}
*/
			generazione = new_generation;

	j++;
		}
	return generazione[0];
}
