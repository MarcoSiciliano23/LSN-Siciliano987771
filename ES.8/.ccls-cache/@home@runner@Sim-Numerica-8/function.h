#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>
#include<cstdlib>
#include<utility>


using namespace std;

class FunzioneBase {

public:
		virtual double Valuta(double x) const = 0;
		virtual ~FunzioneBase() { ; };
};



class Trial_wave_function : public FunzioneBase{
private: double _mu, _sigma;

public:
	Trial_wave_function (double sigma, double mu);
	~Trial_wave_function() { ; };

	double Valuta(double x) const override;
	double Acceptance_ratio(double x_new, double x);
};


class Energia : public FunzioneBase{
private:

Trial_wave_function psi;
double _mu, _sigma;

public:
	Energia (double sigma, double mu);
	~Energia() { ; };

	double Valuta(double x) const override;
};







// function to calculate squared distance

void SaveOnTo(const string& Filename, double dato, double errore);
void SaveOnTo(const string& Filename, double dato);


// Functions to calculate error
double Error(vector<double> Av, vector<double> Av2, int N);
double Error(double Av, double Av2, int N);

//Functions for progressive averages
void MediaProgressiva(const vector<double>& dati, int N, int L, const string& Filename);
void MediaProgressiva_last(const vector<double>& dati, int N, int L, const string& Filename);
void sq_MediaProgressiva_last(const vector<double>& dati, int N, int L, const string& Filename);






#endif // FILE_H

