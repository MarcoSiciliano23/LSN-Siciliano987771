#include "random.h"
#include "function.h"

int main(){

	Random rnd;
	int M = 10000; //lanci totali
	int N = 100;// num. blocchi
	int L = int(M/N);//lanci nel blocco

	//primo punto
	
	double sum = 0;
	 double Mean = 0;//vector<double> Mean(N);
	 double Mean2 = 0; //vector<double> Mean2(N);
	 double err_prog = 0;


	 double Sum_Prog = 0; //vector<double> Sum_Prog(N);
	 double Sum2_Prog = 0; //vector<double> Sum2_Prog(N);
	 double Av = 0;
	 double Av2 = 0;

	for(int i = 0; i <N; i++){ //i blocchi

		sum = 0;

		for(int j = 0; j < L; j++){ // i lanci in un blocco
			sum += rnd.Rannyu();
		}


		Mean = sum/L;
		Mean2 = Mean*Mean; // media al quadrato

		Sum_Prog += Mean;
		Sum2_Prog += Mean2;

		Av = Sum_Prog / (i+1);
		Av2 = Sum2_Prog / (i+1);

		err_prog = Error(Av, Av2, i);

		//li scrivo su file
		SaveOnTo("Mean.out", Av, err_prog);	

	}

	
	// seconod punto
	sum = 0;
	Mean = 0;
	Mean2 = 0; 
	err_prog = 0;


	Sum_Prog = 0; 
	Sum2_Prog = 0; 
	Av = 0;
	Av2 = 0;

	for(int i = 0; i <N; i++){ //i blocchi

		sum = 0;

		for(int j = 0; j < L; j++){ // i lanci in un blocco
			sum += pow(rnd.Rannyu()-0.5,2);
		}


		Mean = sum/L;
		Mean2 = Mean*Mean; // media al quadrato

		Sum_Prog += Mean;
		Sum2_Prog += Mean2;

		Av = Sum_Prog / (i+1);
		Av2 = Sum2_Prog / (i+1);

		err_prog = Error(Av, Av2, i);

		//li scrivo su file
		SaveOnTo("scarti.out", Av, err_prog);	

	}

	//terzo punto

	M = 100;
	N = 10000;
	int expected = int (N/M);
	vector<double> chi_values;
	vector<int> observed(M, 0);
	
	double chi2 = 0.;

	for (int j = 0; j < 100; j++ ){

		for (int i = 0; i < N; ++i) {
				int interval = static_cast<int>(rnd.Rannyu(0, M));
				observed[interval]++;
		}

		for (int i = 0; i < M; i++){
			
			chi2 += ((observed[i] - expected) * (observed[i] - expected)) / double(expected);
		}
			
			chi_values.push_back(chi2);
			
			chi2 = 0;
		
		fill(observed.begin(), observed.end(), 0); //inizializzo a zero
		}

	SaveOnTo("Chi2_j.out", chi_values);

	return 0;
}