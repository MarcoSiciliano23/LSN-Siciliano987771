#include "function.h"
#include "Random.h"
#include <algorithm>

int main() {
  int M = 10000;
  int N = 100;
  int L = int(M / N);

  double S0 = 100.;
  double K = 100.;
  double T = 1.;
  double r = 0.1;
  double sigma = 0.25;
  double t = 0;

  Random rnd;

  GBM S(r, sigma, rnd);
  vector<double> Val_call_discr;
  vector<double> Val_put_discr;
  double m = 0;

  double prima = 0;
  double ora = 0;
  double Si = S0;

  for (int i = 0; i < M; i++) {

    for (int j = 0; j <= 100; j++) {

      Si = S.Valuta_discr(ora, prima, Si);
			
			prima = ora;
			ora = j * 0.01;
		}
		
    m = max(0., Si - K);
    Val_call_discr.push_back(exp(-r * T) * m);

    m = max(0., K - Si);
    Val_put_discr.push_back(exp(-r * T) * m);
    
		Si = S0;
		prima = 0;
		ora = 0;

   
  }
  
  MediaProgressiva(Val_call_discr, N, L, "Call_discr1.out");
  MediaProgressiva(Val_put_discr, N, L, "Put_discr1.out");

  return 0;
}