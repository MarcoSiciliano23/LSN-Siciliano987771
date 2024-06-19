#include"random.h"
#include <utility>


int main() {
	
	double sigma = 0.5;
	double mu = 1.;
	
//	int nthrows = 10000; // lanci in un blocco
	int nblocks = 100;
	int n = 1000; //lanci per la stima dell'integrale
	
	Random rnd;
	
	Energia H(mu, sigma);
	Trial_wave_function psi(mu, sigma);

	/*/ TROVA LA GRANDEZZA DELLO STEP DA ESEGUIRE, AFFINCH
	double step_size = 0.01;
	double acceptance = 0.;
	
	while(acceptance <= 0.47|| acceptance >= 0.55){
		
		acceptance = rnd.stima_stepSize(H, psi, n, step_size);
		
		step_size += 0.01; 
	}

	cout << "Acceptance: " << acceptance << endl;
	cout << "Step Size: " << step_size << endl;
/*/


	
	double T0 = 1.;
	
	ra.SimulatedAnnealing(mu, sigma, T0, n, step_size);

	cout << "mu: " << mu << endl;
	cout << "sigma: " << sigma << endl;
		
return 0;
}