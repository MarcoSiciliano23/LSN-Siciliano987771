#include "Function.h"
#include "Random.h"


Gaussiana::Gaussiana(double mu, double sigma) : m_mu(mu), m_sigma(sigma) {}

double Gaussiana::Valuta(double x) const {
		return 1. / (m_sigma * sqrt(2. * M_PI)) *
					 pow(M_E, -pow(x - m_mu, 2) / (2. * pow(m_sigma, 2)));
}

double Seno::Valuta(double x) const {
		return sin(x);
}

double G::Valuta(double x) const {
		return M_PI_2 * cos(M_PI_2 * x);
}

double P::Valuta(double x) const {
		return (1. / 15. * -17. / 10. * x * x + 3. / 2.);
}

double G1::Valuta(double x) const {
		return (M_PI_2 * cos(M_PI_2 * x)) /((7./6.)*(-x*x +3/2)); //(14. / 15. * -17. / 10. * x * x + 3. / 2.);
}

/////////////////////////









void SaveOnTo(const string& Filename, double dato, double errore) {
		// Apertura del file in modalità append
		ofstream out(Filename.c_str(), ios::app);

		// Scrittura dei valori nel file
		if (out) {
				out << dato << "\t" << errore << endl;
		}

		// Chiusura del file
		out.close();
}

double Error(vector<double> Av, vector<double> Av2, int N) {
		if (N == 0) {
				return 0;
		}
		return sqrt((Av2[N] - Av[N] * Av[N]) / N);
}

//N no. di blocchi L no. di lanci in un blocco Filename il file dove salvare i dati
void MediaProgressiva(const vector<double>& dati, int N, int L, const string& Filename) {
		// Dichiarazione dei vettori per le medie progressive
		vector<double> ave(N, 0.0);
		vector<double> av2(N, 0.0);
		vector<double> sum_prog(N, 0.0);
		vector<double> su2_prog(N, 0.0);
		vector<double> err_prog(N, 0.0);

		// Calcolo delle medie progressive
		for (int i = 0; i < N; i++) {
				double sum1 = 0.0;

				for (int j = 0; j < L; j++) {
						int k = j + i * L;
						sum1 += dati[k];
				}

				ave[i] = sum1 / L;       // r_i 
				av2[i] = pow(ave[i], 2);  // (r_i)^2
		}

		// Calcolo delle medie progressive cumulative
		for (int i = 0; i < N; i++) {
				for (int j = 0; j <= i; j++) {
						sum_prog[i] += ave[j]; // SUM_{j=0,i} r_j
						su2_prog[i] += av2[j]; // SUM_{j=0,i} (r_j)^2
				}

				sum_prog[i] /= (i + 1); // Cumulative average
				su2_prog[i] /= (i + 1); // Cumulative square average
				err_prog[i] = Error(sum_prog, su2_prog, i);

			SaveOnTo(Filename, sum_prog[i], err_prog[i]);
		}

			//cout << sum_prog[N] << "\t" << err_prog[N] << endl;
}

