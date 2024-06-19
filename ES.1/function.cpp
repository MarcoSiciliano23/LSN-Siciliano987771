#include"function.h"

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

void SaveOnTo(const string& Filename, double dato) {
		ofstream outputFile(Filename, ios::app);  // ios::app consente di aggiungere al file esistente

		if (outputFile.is_open()) {
				outputFile << dato << endl;
				outputFile.close();

		} else {
				cout << "Errore: Impossibile aprire il file " << Filename << endl;
		}
}

void SaveOnTo(const string& Filename, vector<double> dato) {
	// Apertura del file in modalità append
	ofstream out(Filename.c_str(), ios::app);

	// Scrittura dei valori nel file
	if (out) {
		for(int i = 0; i < dato.size(); i++) out << dato[i] << endl;
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

double Error(double Av, double Av2, int N) {

	if (N==0){
		return 0;
	}

	else{
		return sqrt((Av2 - Av*Av)/N);
	}
}


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