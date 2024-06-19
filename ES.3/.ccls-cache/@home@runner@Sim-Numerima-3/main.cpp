
#include "Function.h"
#include "Random.h"
#include <algorithm>

int main() {
	int M = 100000;
	int N = 100;
	int L = int(M/N);
	
	double S0 = 100.;
	double K = 100.;
	double T = 1.;
	double r = 0.1;
	double sigma = 0.25;
	double t=0;

	Random rnd;
	
	GBM S (r, sigma, rnd);
	vector<double> Val_call;
	vector<double> Val_put;
	double m = 0;

	for (int i = 0; i < M; i++){

		//cout << "Valuta: " << S.Valuta(T) << endl;
		
		m = max(0.,S.Valuta(T, S0)-K);
		Val_call.push_back( exp(-r*T) * m );

		m = max(0.,K-S.Valuta(T, S0));
		Val_put.push_back( exp(-r*T) * m );
		
	}

	 MediaProgressiva(Val_call, N, L, "Call.out");
	 MediaProgressiva(Val_put, N, L, "Put.out");


	return 0;
}