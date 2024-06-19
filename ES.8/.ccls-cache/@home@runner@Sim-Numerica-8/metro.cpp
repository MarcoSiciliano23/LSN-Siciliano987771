#include "metro.h"

double trial_wave_function(double x, double sigma, double mu) {
		return exp(-0.5 * pow((x - mu) / sigma, 2)) + exp(-0.5 * pow((x + mu) / sigma, 2));
};


double acceptance_ratio(double x_new, double x, double sigma, double mu) {
		double ratio = pow(trial_wave_function(x_new, sigma, mu), 2) / pow(trial_wave_function(x, sigma, mu), 2);

	if (ratio > 1) {
		return 1.;
	} else {
		return ratio;
	} 
};


double potential (double x) {
	return pow(x, 4) - 5./2. * x*x;
}

double kinetic(double x, double sigma, double mu){
	/////
 double term1 = exp(-pow(x - mu, 2) / (2 * pow(sigma, 2))) * (1 - pow(x - mu, 2) / pow(sigma, 2));
	double term2 = exp(-pow(x + mu, 2) / (2 * pow(sigma, 2))) * (1 - pow(x + mu, 2) / pow(sigma, 2));
	double second_deriv = (term1 + term2) / pow(sigma, 2);
	/////

	return -0.5 * second_deriv / trial_wave_function(x, sigma, mu);
}

double local_energy(double x, double sigma, double mu) {
		double ke = kinetic(x, sigma, mu); // Kinetic energy
		double pe = potential(x); // Potential energy
		return ke + pe; // Total local energy
}


void metro (int num_steps, double sigma, double mu, double step_size){

	double x = 0.;
	double x_new = 0.;
	double a = 0.;
	double integral_sum = 0.;
	

	for(int i=0; i<num_steps; i++){

		x_new = rnd.Rannyu(x - step_size, x + step_size);

		a = rnd.Rannyu(0, 1);
		if (a < acceptance_ratio(x_new, x, sigma, mu)) x = x_new;

		integral_sum += trial_wave_function(x, sigma, mu);

	}


};






/*
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
*/
