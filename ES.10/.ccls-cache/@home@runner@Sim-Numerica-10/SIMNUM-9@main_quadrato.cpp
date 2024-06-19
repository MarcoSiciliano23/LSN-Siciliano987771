
#include <TApplication.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TF1.h>
#include <TBox.h> 
#include <iostream>
#include "ingiro.h"
using namespace std ;
//
// assicurarsi che la funzione Set_City sia impostat sulla configurazione corretta
//
int main() {
		int n_city = 34;
		Random rnd;

		Mappa Map(n_city, rnd);

		Genetica gene(n_city);

	 vector<int> best_solution = gene.Evoluzione(1000, "length_quad.dat");

		// salvataggio su file e grafico
		vector<double> x ;
		vector<double> y;

		for (int i = 0; i < n_city; i++) {
				x.push_back(Map.GetCity(i).Get_Coord(0));
				y.push_back(Map.GetCity(i).Get_Coord(1));
		}



		// Apertura del file in modalità scrittura
	ofstream outFile("coord_quad.dat");

		// Verifica se il file è stato aperto correttamente
		if (!outFile.is_open()) {
				cerr << "Errore nell'apertura del file: " << "coord_quad.dat" <<  endl;
				return 1;
		}

		// Controllo che i due vettori abbiano la stessa dimensione
		if (x.size() != x.size()) {
			cerr << "I vettori non hanno la stessa dimensione." <<  endl;
				return 1;
		}

		// Scrittura dei dati dei vettori nel file
		for (size_t i = 0; i < x.size(); ++i) {
				outFile << x[i] << "  " << y[i] <<  endl;
		}

		// Chiusura del file
		outFile.close();

	cout << "Dati salvati correttamente nel file: " <<"coord_quad.dat" <<  endl;

	ofstream openFile("percorso_quad.dat");

		// Verifica se il file è stato aperto correttamente
		if (!openFile.is_open()) {
			cerr << "Errore nell'apertura del file: " << "percorso_quad.dat" <<  endl;
				return 1;
		}

		// Scrittura dei dati del vettore nel file
		for (size_t i = 0; i < best_solution.size(); ++i) {
				openFile << best_solution[i] <<  endl;
		}

		// Chiusura del file
		openFile.close();

	cout << "Dati salvati correttamente nel file: " << "percorso_quad.dat" <<  endl;


// Crea un canvas per disegnare
		TCanvas *c1 = new TCanvas("c1", "percorso", 1000, 1000);
		TGraph *gr = new TGraph();    // Inizializza il grafico per le città
		TGraph *percorso = new TGraph(); // Inizializza il grafico per il percorso


		// Imposta le coordinate per il grafico delle città
		for (int i = 0; i < n_city; i++) {
			 gr->SetPoint(i, Map.GetCity(i).Get_Coord(0), Map.GetCity(i).Get_Coord(1));
		}

		// Imposta le coordinate per il grafico del percorso migliore
		for (int i = 0; i < n_city; i++) {
				percorso->SetPoint(i, Map.GetCity(best_solution[i]).Get_Coord(0), Map.GetCity(best_solution[i]).Get_Coord(1));
		}

		// Aggiungi un punto per collegare l'ultimo punto al primo nel percorso
		percorso->SetPoint(n_city, Map.GetCity(best_solution[0]).Get_Coord(0), Map.GetCity(best_solution[0]).Get_Coord(1));

		// Imposta lo stile del grafico per le città
		gr->SetMarkerStyle(20);     // Cerchi pieni
		gr->SetMarkerSize(1.0);     // Dimensione dei punti
		gr->SetMarkerColor(kBlue);  // Colore blu

		// Imposta il colore del grafico per il percorso
		percorso->SetMarkerColor(kGreen);

		// Disegna il grafico per le città
		gr->Draw("AP");

		// Disegna il grafico per il percorso
		percorso->Draw("L");

		
	// Disegna il quadrato
		TBox *square = new TBox(-1, -1, 1, 1);  // Coordinate (x1, y1, x2, y2)
		square->SetLineColor(kBlue);  // Colore blu
		square->SetLineWidth(2);      // Spessore della linea
		square->SetFillStyle(0);      // Nessun riempimento
		square->Draw("same");

		c1->Update();
		
	
		//Mostra il canvas
		c1->Draw();
		c1->SaveAs("grafico_quad.png");

		return 0;
}