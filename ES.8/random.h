#ifndef __Random__
#define __Random__


#include"function.h"
// This class contains functions for generating random numbers using the RANNYU algorithm
class Random {

private:
	int m1,m2,m3,m4,l1,l2,l3,l4,n1,n2,n3,n4;

protected:

public:
	// Default constructor
	Random();
	// Destructor
	~Random();
	// Method to set the seed for the RNG
	void SetRandom(int * , int, int);
	// Method to save the seed to a file
	void SaveSeed();
	// Method to generate a random number in the range [0,1)
	double Rannyu(void);
	// Method to generate a random number in the range [min,max)
	double Rannyu(double min, double max);
	// Method to generate a random number with a Gaussian distribution
	double Gauss(double mean, double sigma);
	// Method to generate a random number with a Exponential distribution
	double Dist_Exp(double lambda);
	// Method to generate a random number with a Lorentzian distribution
	double Lorentzian(double mu, double Gamma);

	// Funzione per eseguire un singolo passo Metropolis
	double Metropolis(Trial_wave_function &psi, double x0, double step_size);

	// Funzione per stimare il rapporto di accettazione per una data dimensione del passo
	double stima_stepSize(Energia &H, Trial_wave_function &psi, int num_steps, double step_size);

	// Funzione per integrare utilizzando l'algoritmo Metropolis
	double Integra_metropolis(Energia &H, Trial_wave_function &psi, int num_steps, double step_size);

	// Funzione per calcolare medie progressive ed errori utilizzando l'algoritmo Metropolis
	pair<double, double> MediaProg_Metropolis(Energia &H, Trial_wave_function &psi, int num_steps, double step_size, 
	 int nblocks);


};

#endif // __Random__
