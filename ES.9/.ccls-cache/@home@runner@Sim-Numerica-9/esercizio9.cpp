#include <TAxis.h>
#include <TApplication.h>
#include <TBox.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TF1.h>
#include <iostream>
#include "ingiro.h"
using namespace std ;

int main() {
    
    int n_city = 34;
    
    Random rnd_C;
    Random rnd_Q;

    string cerchio = "cerchio";
    string quadrato = "quadrato";
    
    Mappa MapC(n_city, rnd_C, cerchio);
    Genetica geneC(n_city, cerchio);
    vector<int> best_solutionC = geneC.Evoluzione(1000, "lenght_cerchio.dat");

    
    Mappa Mapa(n_city, rnd_Q, quadrato);
    Genetica geni(n_city, quadrato);
    vector<int> bestsolution = geni.Evoluzione(1000, "length_quad.dat");


    
    // Salvataggio su file
    
    //cerchio
    vector<double> xC, yC;
    for (int i = 0; i < n_city; i++) {
        xC.push_back(MapC.GetCity(i).Get_Coord(0));
        yC.push_back(MapC.GetCity(i).Get_Coord(1));
    }

    // Apertura del file in modalità scrittura
    ofstream outFile("coord_cerc.dat");
    if (!outFile.is_open()) {
        cerr << "Errore nell'apertura del file: coord_cerc.dat" << endl;
        return 1;
    }

    // Scrittura dei dati dei vettori nel file
    for (size_t i = 0; i < xC.size(); ++i) {
        outFile << xC[i] << "  " << yC[i] << endl;
    }
    
    outFile.close();
    cout << "Dati salvati correttamente nel file: coord_cerc.dat" << endl;

    ofstream openFile("percorso_cerc.dat");
    if (!openFile.is_open()) {
        cerr << "Errore nell'apertura del file: percorso_cerc.dat" << endl;
        return 1;
    }
    for (size_t i = 0; i < best_solutionC.size(); ++i) {
        openFile << best_solutionC[i] << endl;
    }
    openFile.close();
    cout << "Dati salvati correttamente nel file: percorso_cerc.dat" << endl;


    
    //quadrato
    vector<double> xQ, yQ;
    for (int i = 0; i < n_city; i++) {
        xQ.push_back(Mapa.GetCity(i).Get_Coord(0));
        yQ.push_back(Mapa.GetCity(i).Get_Coord(1));
    }

    ofstream outFileQ("coord_quad.dat");
    if (!outFileQ.is_open()) {
        cerr << "Errore nell'apertura del file: coord_quad.dat" << endl;
        return 1;
    }
    for (size_t i = 0; i < xQ.size(); ++i) {
        outFileQ << xQ[i] << "  " << yQ[i] << endl;
    }
    outFileQ.close();
    cout << "Dati salvati correttamente nel file: coord_quad.dat" << endl;

    ofstream openFileQ("percorso2_quad.dat");
    if (!openFileQ.is_open()) {
        cerr << "Errore nell'apertura del file: percorso2_quad.dat" << endl;
        return 1;
    }
    for (size_t i = 0; i < bestsolution.size(); ++i) {
        openFileQ << bestsolution[i] << endl;
    }
    openFileQ.close();
    cout << "Dati salvati correttamente nel file: percorso2_quad.dat" << endl;
    
    /////////////////////////////////////////////////////////////////////////////


    /*/ Crea un canvas per disegnare

    //cerchio
    TCanvas *c1 = new TCanvas("c1", "percorso", 1000, 1000);
    TGraph *gr = new TGraph();    // Inizializza il grafico per le città
    TGraph *percorso = new TGraph(); // Inizializza il grafico per il percorso

    // Imposta le coordinate per il grafico delle città
    for (int i = 0; i < n_city; i++) {
        gr->SetPoint(i, xC[i], yC[i]);
    }

    // Imposta le coordinate per il grafico del percorso migliore
    for (int i = 0; i < n_city; i++) {
        percorso->SetPoint(i, xC[best_solutionC[i]], yC[best_solutionC[i]]);
    }

    // Aggiungi un punto per collegare l'ultimo punto al primo nel percorso
    percorso->SetPoint(n_city, xC[best_solutionC[0]], yC[best_solutionC[0]]);

    // Imposta lo stile del grafico per le città
    gr->SetMarkerStyle(20);     // Cerchi pieni
    gr->SetMarkerSize(1.0);     // Dimensione dei punti
    gr->SetMarkerColor(kBlue);  // Colore blu

    // Disegna il grafico per le città
    gr->Draw("AP");

    // Disegna il grafico per il percorso
    percorso->Draw("L");

    // Disegna la circonferenza
    TF1 *circle_upper = new TF1("circle_upper", "sqrt(1 - x*x)", -1, 1);
    circle_upper->SetLineColor(kRed);  // Colore rosso
    circle_upper->SetLineWidth(2);     // Spessore della linea
    circle_upper->Draw("same");

    TF1 *circle_lower = new TF1("circle_lower", "-sqrt(1 - x*x)", -1, 1);
    circle_lower->SetLineColor(kRed);  // Colore rosso
    circle_lower->SetLineWidth(2);     // Spessore della linea
    circle_lower->Draw("same");

    // Mostra il canvas
    c1->Draw();
    c1->SaveAs("grafico_cerchio.png");


    
    // quadrato
    TCanvas *c2 = new TCanvas("c2", "percorso2", 1000, 1000);
    TGraph *gr2 = new TGraph();    // Inizializza il grafico per le città
    TGraph *percorso2 = new TGraph(); // Inizializza il grafico per il percorso2

    // Imposta le coordinate per il grafico delle città
    for (int i = 0; i < n_city; i++) {
        gr2->SetPoint(i, xQ[i], yQ[i]);
    }

    // Imposta le coordinate per il grafico del percorso2 migliore
    for (int i = 0; i < n_city; i++) {
        percorso2->SetPoint(i, xQ[bestsolution[i]], yQ[bestsolution[i]]);
    }

    // Aggiungi un punto per collegare l'ultimo punto al primo nel percorso2
    percorso2->SetPoint(n_city, xQ[bestsolution[0]], yQ[bestsolution[0]]);

    // Imposta lo stile del grafico per le città
    gr2->SetMarkerStyle(20);     // Cerchi pieni
    gr2->SetMarkerSize(1.0);     // Dimensione dei punti
    gr2->SetMarkerColor(kBlue);  // Colore blu
 

    // Disegna il grafico per le città
    gr2->Draw("AP");

    // Disegna il grafico per il percorso2
    percorso2->Draw("L");

    // Disegna il quadrato
    TBox *square = new TBox(-1, -1, 1, 1);  // Coordinate (x1, y1, x2, y2)
    square->SetLineColor(kBlue);  // Colore blu
    square->SetLineWidth(2);      // Spessore della linea
    square->SetFillStyle(0);      // Nessun riempimento
    square->Draw("same");

    c2->Update();

    // Mostra il canvas
    c2->Draw();
    c2->SaveAs("grafico_quad.png");
    /*/
    
    return 0;
}
