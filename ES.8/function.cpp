#include "function.h"

// Implementazione del costruttore della classe Trial_wave_function
Trial_wave_function::Trial_wave_function(double mu, double sigma) : _mu(mu), _sigma(sigma) {}

// Implementazione del metodo per valutare la funzione d'onda di prova in un punto x
double Trial_wave_function::Valuta(double x) const {
    // Calcola il valore della funzione d'onda di prova
    return exp(-0.5 * pow((x - _mu) / _sigma, 2)) + exp(-0.5 * pow((x + _mu) / _sigma, 2));
}

// Implementazione del metodo per calcolare il rapporto di accettazione nell'algoritmo Metropolis
double Trial_wave_function::Acceptance_ratio(double xnew, double x) {
    // Calcola il rapporto di accettazione
    double ratio = (Valuta(xnew) * Valuta(xnew)) / (Valuta(x) * Valuta(x));
    // Restituisce il rapporto limitato a 1.0
    return min(1.0, ratio);
}

// Implementazione del costruttore della classe Energia
Energia::Energia(double mu, double sigma) : psi(mu, sigma), _mu(mu), _sigma(sigma) {}

// Implementazione del metodo per valutare l'energia in un punto x
double Energia::Valuta(double x) const {
    // Calcola il potenziale
    double potential = pow(x, 4) - 5.0 / 2.0 * x * x;

    // Calcola il termine cinetico
    double kinetic = -0.5 / (pow(_sigma, 4)) * (_mu * _mu - _sigma * _sigma + x * x - 2 * x * _mu * tanh((_mu * x) / (_sigma * _sigma)));

    // Restituisce il valore dell'energia totale
    return potential + kinetic;
}




void SaveOnTo(const string& Filename, double dato) {
		ofstream outputFile(Filename, ios::app);
		if (outputFile.is_open()) {
				outputFile << dato << endl;
				outputFile.close();
		} else {
				cout << "Errore: Impossibile aprire il file " << Filename << endl;
		}
}


void SaveOnTo(const string& Filename, double dato, double errore) {
		ofstream out(Filename.c_str(), ios::app);
		if (out) {
				out << dato << "  " << errore << endl;
		}
		out.close();
}



double Error(vector<double> Av, vector<double> Av2, int N) {
		if (N == 0) {
				return 0;
		}
		return sqrt((Av2[N] - Av[N] * Av[N]) / N);
}

double Error(double Av, double Av2, int N) {
		if (N == 0) {
				return 0;
		}
		return sqrt((Av2 - Av * Av) / N);
}



void MediaProgressiva(const vector<double>& dati, int N, int L, const string& Filename) {
	//N numero di blocchi
	//L numero di lanci per blocco
	vector<double> ave(N, 0.0);
		vector<double> av2(N, 0.0);
		vector<double> sum_prog(N, 0.0);
		vector<double> su2_prog(N, 0.0);
		vector<double> err_prog(N, 0.0);

		for (int i = 0; i < N; i++) {
				double sum1 = 0.0;
				for (int j = 0; j < L; j++) {
						int k = j + i * L;
						sum1 += dati[k];
				}
				ave[i] = sum1 / L;
				av2[i] = pow(ave[i], 2);
		}

		for (int i = 0; i < N; i++) {
				for (int j = 0; j <= i; j++) {
						sum_prog[i] += ave[j];
						su2_prog[i] += av2[j];
				}
				sum_prog[i] /= (i + 1);
				su2_prog[i] /= (i + 1);
				err_prog[i] = Error(sum_prog, su2_prog, i);

				SaveOnTo(Filename, sum_prog[i], err_prog[i]);
		}
}


void MediaProgressiva_last(const vector<double>& dati, int N, int L, const string& Filename) {
		vector<double> ave(N, 0.0);
		vector<double> av2(N, 0.0);
		vector<double> sum_prog(N, 0.0);
		vector<double> su2_prog(N, 0.0);
		vector<double> err_prog(N, 0.0);

		for (int i = 0; i < N; i++) {
				double sum1 = 0.0;
				for (int j = 0; j < L; j++) {
						int k = j + i * L;
						sum1 += dati[k];
				}
				ave[i] = sum1 / L;
				av2[i] = pow(ave[i], 2);
		}

		for (int i = 0; i < N; i++) {
				for (int j = 0; j <= i; j++) {
						sum_prog[i] += ave[j];
						su2_prog[i] += av2[j];
				}
				sum_prog[i] /= (i + 1);
				su2_prog[i] /= (i + 1);
				err_prog[i] = Error(sum_prog, su2_prog, i);
		}

		SaveOnTo(Filename, sum_prog.back(), err_prog.back());
}


void sq_MediaProgressiva_last(const vector<double>& dati, int N, int L, const string& Filename) {
		vector<double> ave(N, 0.0);
		vector<double> av2(N, 0.0);
		vector<double> sum_prog(N, 0.0);
		vector<double> su2_prog(N, 0.0);
		vector<double> err_prog(N, 0.0);

		for (int i = 0; i < N; i++) {
				double sum1 = 0.0;
				for (int j = 0; j < L; j++) {
						int k = j + i * L;
						sum1 += dati[k];
				}
				ave[i] = sum1 / L;
				av2[i] = pow(ave[i], 2);
		}

		for (int i = 0; i < N; i++) {
				for (int j = 0; j <= i; j++) {
						sum_prog[i] += ave[j];
						su2_prog[i] += av2[j];
				}
				sum_prog[i] /= (i + 1);
				su2_prog[i] /= (i + 1);
				err_prog[i] = Error(sum_prog, su2_prog, i);
		}

		double sq = sqrt(sum_prog.back());
		double err = 0.5 * err_prog.back() / sq; // errore propagato

		SaveOnTo(Filename, sq, err);
}


