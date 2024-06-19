#include"random.h"
#include <utility>


int main() {
	
	double sigma = 0.5;
	double mu = 1.;
	
	int nblocks = 100;
	int n = 1000; //lanci per la stima dell'integrale
	
	Random rnd;
	
	/*/ TROVA LA GRANDEZZA DELLO STEP DA ESEGUIRE, AFFICHÉ L'ACCETTAZA DEL METROPOLIS SIA AL 50% CIRCA'
	
	Energia H(mu, sigma);
	Trial_wave_function psi(mu, sigma);
	
	double step_size = 0.01;
	double acceptance = 0.;
	
	while(acceptance <= 0.47|| acceptance >= 0.55){
		
		acceptance = rnd.stima_stepSize(H, psi, n, step_size);
		
		step_size += 0.01; 
	}

	cout << "Acceptance: " << acceptance << endl;
	cout << "Step Size: " << step_size << endl;
/*/

	//SIMULATED ANNEALING/////////////
	
		double step_size = 0.99;
		double T = 1.0; //temperatura iniziale
		double T_min = 0.01; 
		double a = 0.999; //parametro della legge di decrescita della temperatura
		double new_sigma;

		double new_energy, current_energy, curr_err, new_err; //variabili di appoggio

		int k = 0; //iteratore 
	
		while (T > T_min) {
				Energia H(mu, sigma);
				Trial_wave_function psi(mu, sigma);

				//si calcola l'autovalore iniziale
				auto Old = rnd.MediaProg_Metropolis(H, psi, n, step_size, nblocks);
				current_energy = Old.first;
				curr_err = Old.second;

				//si muovono i parametri
				double new_mu = mu + rnd.Rannyu(-0.1, 0.1) * T;
				if (sigma > 0.005) new_sigma = sigma + rnd.Rannyu(-0.1, 0.1) * T;

				// si propone un nuovo stato
				Energia new_H(new_mu, new_sigma);
				Trial_wave_function new_psi(new_mu, new_sigma);

				//si calcola l'autovalore del nuovo stato
				auto New = rnd.MediaProg_Metropolis(new_H, new_psi, n, step_size, nblocks);
				new_energy = New.first;
				new_err = New.second;

				double dE = new_energy - current_energy;

				// si controlla se si accetta o meno
				if (dE < 0 || rnd.Rannyu(0., 1.) < exp(-dE / T)) {
						mu = new_mu;
						sigma = new_sigma;
						current_energy = new_energy;
						curr_err = new_err;
				}

				SaveOnTo("SA.dat", current_energy, curr_err);

				T = pow(a,k); // si raffredda il sistema
				k++;
		}

		cout << "mu: " << mu << endl;
		cout << "sigma: " << sigma << endl;


	//media progressiava per la stima di <H> con i parametri che minimizzano//////////////
	
	//nuovo stato con i parametri trovati
	Energia H(mu, sigma);
	Trial_wave_function psi(mu, sigma);
	
	vector<double> ave(nblocks, 0.0);
		vector<double> av2(nblocks, 0.0);
		vector<double> sum_prog(nblocks, 0.0);
		vector<double> su2_prog(nblocks, 0.0);
		vector<double> err_prog(nblocks, 0.0);

		for (int i = 0; i < nblocks; i++) {

				ave[i] = rnd.Integra_metropolis(H, psi, n, step_size);
				av2[i] = pow(ave[i], 2);
		}

		for (int i = 0; i < nblocks; i++) {
				for (int j = 0; j <= i; j++) {
						sum_prog[i] += ave[j];
						su2_prog[i] += av2[j];
				}
				sum_prog[i] /= (i + 1);
				su2_prog[i] /= (i + 1);
				err_prog[i] = Error(sum_prog, su2_prog, i);

			 SaveOnTo("energie.dat",sum_prog[i], err_prog[i]);
		}

		//Sampling del modulo quadro di psi
		ofstream out_psi{"psi.dat",ios::out};
		double x = 0.;
	
		for (int i = 0; i < 100000; i++){
				x = rnd.Metropolis(psi, x, step_size);
			 out_psi  << x << endl;
		}
		out_psi.close();

		return 0;
}