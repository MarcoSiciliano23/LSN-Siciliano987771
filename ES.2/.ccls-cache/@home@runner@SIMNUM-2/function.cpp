#include"function.h"


double G::Valuta(double x) const {
		return M_PI_2 * cos(M_PI_2 * x);
}

double P::Valuta(double x) const {
		return (-1.5*x*x + 1.5);
}



double sq_Distance(vector<vector<int>>& percorso){
		double distance = 0;

		double xi = percorso[0][0];
		double yi = percorso[0][1];
		double zi = percorso[0][2];

		double xf = percorso[percorso.size() - 1][0];
		double yf = percorso[percorso.size() - 1][1];
		double zf = percorso[percorso.size() - 1][2];

		distance = pow(xi - xf, 2) + pow(yi - yf, 2) + pow(zi - zf, 2);

		return distance;
}

double sq_Distance(vector<vector<double>>& percorso){
		double distance = 0;

		double xi = percorso[0][0];
		double yi = percorso[0][1];
		double zi = percorso[0][2];

		double xf = percorso[percorso.size() - 1][0];
		double yf = percorso[percorso.size() - 1][1];
		double zf = percorso[percorso.size() - 1][2];

		distance = pow(xi - xf, 2) + pow(yi - yf, 2) + pow(zi - zf, 2);

		return distance;
}



// Function to save a single data to a file
void SaveOnTo(const string& Filename, double dato) {
		ofstream outputFile(Filename, ios::app);
		if (outputFile.is_open()) {
				outputFile << dato << endl;
				outputFile.close();
		} else {
				cout << "Errore: Impossibile aprire il file " << Filename << endl;
		}
}

// Function to save data and error to a file
void SaveOnTo(const string& Filename, double dato, double errore) {
		ofstream out(Filename.c_str(), ios::app);
		if (out) {
				out << dato << "\t" << errore << endl;
		}
		out.close();
}



// Function to calculate error given vectors
double Error(vector<double> Av, vector<double> Av2, int N) {
		if (N == 0) {
				return 0;
		}
		return sqrt((Av2[N] - Av[N] * Av[N]) / N);
}

// Function to calculate error given two doubles
double Error(double Av, double Av2, int N) {
		if (N == 0) {
				return 0;
		}
		return sqrt((Av2 - Av * Av) / N);
}



//function to calculate progressive averages
void MediaProgressiva(const vector<double>& dati, int N, int L, const string& Filename) {
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

//function to save only the last progressive average
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

// function to save the square root of the last progressive average
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
		double err = 0.5 * err_prog.back() / sq;

		SaveOnTo(Filename, sq, err);
}


