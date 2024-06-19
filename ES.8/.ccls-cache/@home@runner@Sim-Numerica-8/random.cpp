#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>
#include "random.h"


using namespace std;

Random :: Random(){
	int seed[4];
	 int p1, p2;
	 ifstream Primes("Primes");
	 if (Primes.is_open()){
			Primes >> p1 >> p2 ;
	 } else cerr << "PROBLEM: Unable to open Primes" << endl;
	 Primes.close();

	 ifstream input("seed.in");
	 string property;

	 if (input.is_open()){
			while ( !input.eof() ){
				 input >> property;
				 if( property == "RANDOMSEED" ){
						input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
						SetRandom(seed,p1,p2);
				 }
			}
			input.close();
	 } else cerr << "PROBLEM: Unable to open seed.in" << endl;


	 SaveSeed();

}

// Default constructor, does not perform any action

Random :: ~Random(){}
// Default destructor, does not perform any action

void Random :: SaveSeed(){
	 // This function saves the current state of the random number generator to a file "seed.out"
	 ofstream WriteSeed;
	 WriteSeed.open("seed.out");
	 if (WriteSeed.is_open()){
			WriteSeed << "RANDOMSEED	" << l1 << " " << l2 << " " << l3 << " " << l4 << endl;;
	 } else cerr << "PROBLEM: Unable to open random.out" << endl;
	WriteSeed.close();
	return;
}

double Random :: Gauss(double mean, double sigma) {
	 // This function generates a random number from a Gaussian distribution with given mean and sigma
	 double s=Rannyu();
	 double t=Rannyu();
	 double x=sqrt(-2.*log(1.-s))*cos(2.*M_PI*t);
	 return mean + x * sigma;
}

double Random :: Dist_Exp(double lambda){
		double x = -1./lambda * log(1.-Rannyu());

		return x;
}

double Random :: Lorentzian(double mu, double Gamma){
	double x = Gamma * tan(M_PI * (Rannyu() - 0.5)) + mu;

	return x;
}


double Random :: Rannyu(double min, double max){
	 // This function generates a random number in the range [min, max)
	 return min+(max-min)*Rannyu();
}

double Random :: Rannyu(void){
	// This function generates a random number in the range [0,1)
	const double twom12=0.000244140625;
	int i1,i2,i3,i4;
	double r;

	i1 = l1*m4 + l2*m3 + l3*m2 + l4*m1 + n1;
	i2 = l2*m4 + l3*m3 + l4*m2 + n2;
	i3 = l3*m4 + l4*m3 + n3;
	i4 = l4*m4 + n4;
	l4 = i4%4096;
	i3 = i3 + i4/4096;
	l3 = i3%4096;
	i2 = i2 + i3/4096;
	l2 = i2%4096;
	l1 = (i1 + i2/4096)%4096;
	r=twom12*(l1+twom12*(l2+twom12*(l3+twom12*(l4))));

	return r;
}

void Random :: SetRandom(int * s, int p1, int p2){
	// This function sets the seed and parameters of the random number generator
	m1 = 502;
	m2 = 1521;
	m3 = 4071;
	m4 = 2107;
	l1 = s[0];
	l2 = s[1];
	l3 = s[2];
	l4 = s[3];
	n1 = 0;
	n2 = 0;
	n3 = p1;
	n4 = p2;

	return;
}


 double Random:: stima_stepSize (Energia H, Trial_wave_function psi, int num_steps, double step_size){

	double x = 0.;
	
	double integral_sum = 0.;
	int accepted = 0;


	for(int i=0; i<num_steps; i++){

		double x_new = Rannyu(x - step_size, x + step_size);
		
		double a = Rannyu(0, 1);
		
		if (a < psi.Acceptance_ratio(x_new, x)) {
		
			x = x_new;
			accepted++;
		}

		integral_sum += H.Valuta(x);
	}
	 return double(accepted)/num_steps;
 }
	 
double Random::Integra_metropolis(Energia H, Trial_wave_function psi, int num_steps, double step_size, double &var) {
	double x = 0.;
	double integral_sum = 0.;
	double integral_sum_sq = 0.;

	for (int i = 0; i < num_steps; i++) {
			double x_new = Rannyu(x - step_size, x + step_size);
			double a = Rannyu();

			if (a < psi.Acceptance_ratio(x_new, x)) x = x_new;

			double h_val = H.Valuta(x);
			integral_sum += h_val;
			integral_sum_sq += h_val * h_val;
	}

	double integral = integral_sum / num_steps;
	double integral2 = integral_sum_sq / num_steps;
	
	var = Error(integral, integral2, num_steps);

	return integral;
}

void Random::SimulatedAnnealing(double &mu, double &sigma, double T_0, int num_steps, double step_size) {
	
	double T = T_0;
	double T_min = 0.001;
	double a = 0.999;
	double new_sigma = 0.006;

	double new_energy, current_energy, var_curr, var_new, err_curr, err_new;
	int k = 0;

	while (T > T_min) {
			Energia H(mu, sigma);
			Trial_wave_function psi(mu, sigma);

			current_energy = Integra_metropolis(H, psi, num_steps, step_size, var_curr);
			err_curr = var_curr;

			double new_mu = mu + Rannyu(-0.1, 0.1) * T;

			if (sigma > 0.005) new_sigma = sigma + Rannyu(-0.1, 0.1) * T;

			Energia new_H(new_mu, new_sigma);
			Trial_wave_function new_psi(new_mu, new_sigma);

			new_energy = Integra_metropolis(new_H, new_psi, num_steps, step_size, var_new);
			err_new = var_new;

			double dE = new_energy - current_energy;

			if (dE < 0 || Rannyu(0., 1.) < exp(-dE / T)) {
					mu = new_mu;
					sigma = new_sigma;
					current_energy = new_energy;
					err_curr = err_new;
			}

			SaveOnTo("SA.dat", current_energy, err_curr);

			T = T_0 * pow(a, k);
			k++;
	}
}

