#include"random.h"

int main(){

	string Filename1 = "walk_discreto.out";
	string Filename2 = "walk_continuo.out";
	
	Random rnd;
	
	int N = 100;
	int L = 100;
	int passi = 100;
	int a = 1;
	double b = 1.;
	
	
	vector<double> values_Disc(N*L, 0.0);
	vector<double> values_Cont(N*L, 0.0);// CASO CONTINUO
	

	for (int j = 1; j <= passi; j++)	{
		
		for(int i = 0; i < N*L; i++){

			// CASO DISCRETO 
			auto percorso_discreto = rnd.Rnd_Walk(j, a);
		  values_Disc[i] = sq_Distance(percorso_discreto);

			// CASO CONTINUO
			auto percorso_continuo = rnd.Rnd_Walk(j, b);
			values_Cont[i] = sq_Distance(percorso_continuo);
		}


		sq_MediaProgressiva_last(values_Disc, N, L, Filename1);
		for_each(values_Disc.begin(), values_Disc.end(), [](double& k){k = 0;});

		sq_MediaProgressiva_last(values_Cont, N, L, Filename2);
		for_each(values_Cont.begin(), values_Cont.end(), [](double& k){k = 0;});
	}
	

	return 0;
}