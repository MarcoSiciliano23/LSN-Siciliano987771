#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "random.h"

using namespace std;

void metro (int num_steps, double sigma, double mu, double step_size);
double acceptance_ratio(double x_new, double x, double sigma, double mu);
double trial_wave_function(double x, double sigma, double mu);

double potential (double x);
double kinetic(double x, double sigma, double mu);
double local_energy(double x, double sigma, double mu);


void SaveOnTo(const string& Filename, double dato, double errore);
double Error(vector<double> Av, vector<double> Av2, int N);
void MediaProgressiva(const vector<double>& dati, int N, int L, const string& Filename);
