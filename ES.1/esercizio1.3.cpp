
#include "random.h"
#include "function.h"


using namespace std;

int main(int argc, char *argv[]) {
		// Inizializzazione del generatore di numeri casuali
		Random rnd;

		// Parametri dell'esperimento
		double L = 4.0;  // Lunghezza dell'ago
		double d = 7.0;  // Distanza tra le linee del piano
		double pi = 0.0; // Stima di pi

		// Variabili per le coordinate dei punti e il coefficiente angolare
		double x = 0.0;
		double x1 = 0.0;
		double x2 = 0.0;
		double y1 = 0.0;
		double y2 = 0.0;
		double m = 0.0;

		// Parametri della simulazione
		int M = 1000000;   // Lanci totali
		int N = 100;      // Numero di blocchi
		int N_th = M / L;  // Lanci nel blocco
		int N_hit = 0;     // Numero di volte che l'ago colpisce una linea

		// Variabili per la stima progressiva di pi
		double sum = 0.0;
		double sum2 = 0.0;
		double Mean = 0.0;
		double Mean2 = 0.0;
		double err_prog = 0.0;


		// Ciclo sui blocchi
		for (int i = 0; i < N; i++) {
				N_hit = 0;

				// Ciclo sui lanci nel blocco
				for (int j = 0; j < N_th; j++) {
						// Generazione di un punto casuale
						x = rnd.Rannyu(0, d);

						// Generazione di punti per calcolare il coefficiente angolare
						x1 = rnd.Rannyu();
						x2 = rnd.Rannyu();
						y1 = rnd.Rannyu();
						y2 = rnd.Rannyu();



						// Calcolo del coefficiente angolare della retta
						m = (y2 - y1) / (x2 - x1);

						// Calcolo degli estremi dell'ago e controllo se il punto è stato colpito
						if (x - (L / 2 * 1 / sqrt(1 + m * m)) <= 0 || x + (L / 2 * 1 / sqrt(1 + m * m) ) >= d) {
								N_hit++;
						}
				}

				// Calcolo della stima di pi
				pi = (2 * L * double(N_th)) / (d * double(N_hit));

				// Aggiornamento della somma
				sum += pi;
				sum2 += pi*pi;

				// Calcolo della media progressiva e della media al quadrato
				Mean = sum / (i + 1);
				Mean2 = sum2 /(1+i);



				// Calcolo dell'errore progressivo
				err_prog = Error(Mean, Mean2, i);

			//cout << Mean<< err_prog<<endl;


			//li scrivo su file
			SaveOnTo("pi.out", Mean, err_prog);	
			
			}


		return 0;
}