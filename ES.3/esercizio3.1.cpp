#include "function.h"
#include "Random.h"
#include <algorithm>

int main() {

		// Definisce i parametri di simulazione
		int M = 100000; // Numero totale di simulazioni
		int N = 100;    // Numero di blocchi
		int L = int(M / N); // Numero di simulazioni per blocco

		// Parametri dell'opzione
		double S0 = 100.;  // Prezzo iniziale dell'asset
		double K = 100.;   // Prezzo di esercizio
		double T = 1.;     // Tempo alla scadenza
		double r = 0.1;    // Tasso di interesse privo di rischio
		double sigma = 0.25; // Volatilità
		

		
		// Oggetto per il modello di moto browniano geometrico
		
		GBM S(r, sigma);
		
		// Vettori per memorizzare i valori delle opzioni
		vector<double> Val_call;
		vector<double> Val_put;
		vector<double> Val_call_discr;
		vector<double> Val_put_discr;

		double m = 0;
		double prima = 0.;
		double ora = 0.;
		double Si = S0;
		

		for (int i = 0; i < M; i++) {

			// Simulazione continua
			m = max(0., S.Valuta(T, S0) - K);
			Val_call.push_back(exp(-r * T) * m);

			m = max(0., K - S.Valuta(T, S0));
			Val_put.push_back(exp(-r * T) * m);
		
		
	
			// Simulazione discreta
			for (int j = 1; j <= 100; j++) {
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

		// Calcola la media progressiva e scrive i risultati su file
		MediaProgressiva(Val_call, N, L, "Call.out");
		MediaProgressiva(Val_put, N, L, "Put.out");

		MediaProgressiva(Val_call_discr, N, L, "Call_discr.out");
		MediaProgressiva(Val_put_discr, N, L, "Put_discr.out");

	return 0;
}
