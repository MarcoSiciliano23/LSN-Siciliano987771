#include "function.h"
#include "random.h"

int main() {

    //PRIMO PUNTO//
    Random rnd;
    int M = 10000; // Numero totale di lanci
    int N = 100;   // Numero di blocchi
    int n = 500;   // Lanci per la stima dell'integrale
    int L = int(M / N); // Numero di lanci in un blocco

    G g; // Funzione integranda

    double val = 0;
    vector<double> integrali;

    // Stima dell'integrale usando la media semplice
    for (int i = 0; i < M; i++) {
        val = rnd.integraMedia(0.0, 1.0, g, n);
        integrali.push_back(val);
    }

    // Calcolo e salvataggio della media progressiva per il campionamento uniforme
    MediaProgressiva(integrali, N, L, "unif_sampl.out");



    //SECONDO PUNTO//
   
    P p; // Distribuzione di probabilità p

    double x = 0.0;
    double s = 0;
    vector<double> I;

    // Stima dell'integrale usando l'importance sampling
    for (int i = 0; i < M; i++) {
        s = 0.0; // Reset della somma per ogni valore dell'integrale

        for (int j = 0; j < n; j++) {
            x = rnd.AR(p, 0.0, 1.0, 1.5); // Campionamento da p(x) usando il metodo accept-reject
            s += g.Valuta(x) / p.Valuta(x); // Accumulo del valore pesato
        }

        I.push_back(s / n); // Media dei valori dell'integrale
    }

    // Calcolo e salvataggio della media progressiva per l'importance sampling
    MediaProgressiva(I, N, L, "imp_sampl.out");

    return 0;
}
