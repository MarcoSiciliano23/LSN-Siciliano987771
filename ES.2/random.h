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

	double integraMedia(double xmin, double xmax, FunzioneBase &f, int punti);
	double AR (FunzioneBase &f, double xmin, double xmax, double ymax);

	// random walk discreto
	vector<vector<int>> Rnd_Walk (int passi, int a);
	//random walk continuo
	vector<vector<double>> Rnd_Walk (int passi, double a);
	


};


#endif // __Random__
