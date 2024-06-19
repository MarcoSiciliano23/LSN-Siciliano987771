
#include <TApplication.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TF1.h>
#include <TBox.h> 
#include <iostream>
#include "ingiro.h"
using namespace std ;

int main() {
		int n_city = 34;
		Random rnd;

		string quadrato = "quadrato";

		Mappa Mapa(n_city, rnd, quadrato);

		Genetica geni(n_city, quadrato);

	 vector<int> bestsolution = geni.Evoluzione(1000, "length_quad.dat");

		// salvataggio su file e grafico
		vector<double> xQ ;
		vector<double> yQ;

		for (int i = 0; i < n_city; i++) {
				xQ.push_back(Mapa.GetCity(i).Get_Coord(0));
				yQ.push_back(Mapa.GetCity(i).Get_Coord(1));
		}



		// Apertura del file in modalità scrittura
	ofstream outFileQ("coord_quad.dat");

		// Verifica se il file è stato aperto correttamente
		if (!outFileQ.is_open()) {
				cerr << "Errore nell'apertura del file: " << "coord_quad.dat" <<  endl;
				return 1;
		}

		// Controllo che i due vettori abbiano la stessa dimensione
		if (xQ.size() != xQ.size()) {
			cerr << "I vettori non hanno la stessa dimensione." <<  endl;
				return 1;
		}

		// Scrittura dei dati dei vettori nel file
		for (size_t i = 0; i < xQ.size(); ++i) {
				outFileQ << xQ[i] << "  " << yQ[i] <<  endl;
		}

		// Chiusura del file
		outFileQ.close();

	cout << "Dati salvati correttamente nel file: " <<"coord_quad.dat" <<  endl;

	ofstream openFileQ("percorso_quad.dat");

		// Verifica se il file è stato aperto correttamente
		if (!openFileQ.is_open()) {
			cerr << "Errore nell'apertura del file: " << "percorso_quad.dat" <<  endl;
				return 1;
		}

		// Scrittura dei dati del vettore nel file
		for (size_t i = 0; i < bestsolution.size(); ++i) {
				openFileQ << bestsolution[i] <<  endl;
		}

		// Chiusura del file
		openFileQ.close();

	cout << "Dati salvati correttamente nel file: " << "percorso_quad.dat" <<  endl;


// Crea un canvas per disegnare
		TCanvas *c2 = new TCanvas("c2", "percorso2", 1000, 1000);
		TGraph *gr2 = new TGraph();    // Inizializza il grafico per le città
		TGraph *percorso2 = new TGraph(); // Inizializza il grafico per il percorso2


		// Imposta le coordinate per il grafico delle città
		for (int i = 0; i < n_city; i++) {
			 gr2->SetPoint(i, Mapa.GetCity(i).Get_Coord(0), Mapa.GetCity(i).Get_Coord(1));
		}

		// Imposta le coordinate per il grafico del percorso2 migliore
		for (int i = 0; i < n_city; i++) {
				percorso2->SetPoint(i, Mapa.GetCity(bestsolution[i]).Get_Coord(0), Mapa.GetCity(bestsolution[i]).Get_Coord(1));
		}

		// Aggiungi un punto per collegare l'ultimo punto al primo nel percorso2
		percorso2->SetPoint(n_city, Mapa.GetCity(bestsolution[0]).Get_Coord(0), Mapa.GetCity(bestsolution[0]).Get_Coord(1));

		// Imposta lo stile del grafico per le città
		gr2->SetMarkerStyle(20);     // Cerchi pieni
		gr2->SetMarkerSize(1.0);     // Dimensione dei punti
		gr2->SetMarkerColor(kBlue);  // Colore blu

		// Imposta il colore del grafico per il percorso2
		

		// Disegna il grafico per le città
		gr2->Draw("AP");

		// Disegna il grafico per il percorso2
		percorso2->Draw("L");

		
	// Disegna il quadrato
		TBox *square = new TBox(-1, -1, 1, 1);  // Coordinate (xQ1, y1, xQ2, y2)
		square->SetLineColor(kBlue);  // Colore blu
		square->SetLineWidth(2);      // Spessore della linea
		square->SetFillStyle(0);      // Nessun riempimento
		square->Draw("same");

		c2->Update();
		
	
		//Mostra il canvas
		c2->Draw();
		c2->SaveAs("grafico_quad.png");

		return 0;
}