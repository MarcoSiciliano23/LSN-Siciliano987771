#include "random.h"
#include "function.h"

int main (){

	Random rnd;
	int M = 10000;

	double Std_Dice = 0;
	double Exp_Dice = 0;
	double Lor_Dice = 0;
	vector<int> tries = {1,2,10,100};


	for (unsigned k = 0; k < tries.size(); k++){
		for (int i = 0; i < M; i++){

			Std_Dice = 0;
			Exp_Dice = 0;
			Lor_Dice = 0;

			for (int j = 0; j < tries[k]; j++){
			Std_Dice += rnd.Rannyu();
			Exp_Dice += rnd.Dist_Exp(1);
			Lor_Dice += rnd.Lorentzian(0,1);
			}

		Std_Dice /= tries[k];
		Exp_Dice /= tries[k];
		Lor_Dice /= tries[k];

		string numeroLanci = to_string(tries[k]);
		SaveOnTo("Unif"+ numeroLanci + ".out", Std_Dice);	
		SaveOnTo("Exp"+ numeroLanci + ".out", Exp_Dice);
		SaveOnTo("Lor"+ numeroLanci + ".out", Lor_Dice);
		}
	}


	return 0;
}