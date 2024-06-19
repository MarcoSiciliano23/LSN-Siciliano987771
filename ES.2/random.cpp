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

//AGGIUNTE DA ME
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


double Random :: integraMedia(double xmin, double xmax, FunzioneBase &f, int punti) {
	double sum = 0;


	for (int n = 0; n < punti; n++) {

		double x = Rannyu(xmin, xmax);
		double ff = f.Valuta(x);

		sum += ff;
	}

	double I = sum / punti * (xmax - xmin);

	return I;
	};

double Random::AR(FunzioneBase& f, double xmin, double xmax, double ymax) {
		double x;
		double y;
		double fx;

		do {
				double s = Rannyu();
				double t = Rannyu();
				x = xmin + (xmax - xmin) * s;
				y = ymax * t;

				fx = f.Valuta(x);

				// Restituisci x subito se y è minore o uguale a fx
				if (y <= fx) {
						return x;
				}

				// Altrimenti, continua il ciclo
		} while (true); // Aggiunto un ciclo while(true) per garantire che il loop termini solo quando viene restituito un valore valido
}

vector<vector<int>> Random :: Rnd_Walk (int passi, int a){

	
	vector<int> posizione(3, 0);
	vector<int> incremento(3, 0);
	
	vector<vector<int>> percorso(1, posizione);

	//vector<double> posizione_finale(3, 0);

	for (int i = 0; i < passi; i++){

		//ogni numero indica un spostamento (avanti(+1) o indietro(-1)) in ciascuna direzione
		//(0,1) x, (2,3) y, (4,5) z
		int decision = static_cast<int>(Rannyu(0.,6.));

		if (decision == 0) incremento[0] = a;
		if (decision == 1) incremento[0] = -a;

		if (decision == 2) incremento[1] = a;
		if (decision == 3) incremento[1] = -a;

		if (decision == 4) incremento[2] = a;
		if (decision == 5) incremento[2] = -a;

		posizione[0] += incremento[0];
		posizione[1] += incremento[1];
		posizione[2] += incremento[2];

		percorso.push_back(posizione);

		
	}
	
	return percorso;		
};


vector<vector<double>> Random::  Rnd_Walk (int passi, double b){


		vector<double> posizione(3, 0.);
		vector<double> incremento(3, 0.);

		vector<vector<double>> percorso(1, posizione);

		//vector<double> posizione_finale(3, 0);

		for (int i = 0; i < passi; i++){

			
			double phi = Rannyu(0., 2* M_PI); //angolo azimutale
			double theta = acos(1- 2* Rannyu()); //angolo polare; ho invertito la cumulativa

			incremento[0] = b * sin(theta) * cos(phi);
			incremento[1] = b * sin(theta) * sin(phi);
			incremento[2] = b * cos(theta);
			
			posizione[0] += incremento[0];
			posizione[1] += incremento[1];
			posizione[2] += incremento[2];

			percorso.push_back(posizione);

			
		}

		return percorso;		
	}

