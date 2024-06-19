#include"random.h"

int main() {
    // Nomi dei file di output per i risultati delle simulazioni
    string Filename1 = "walk_discreto.out";
    string Filename2 = "walk_continuo.out";
    
    // Oggetto Random per generare numeri casuali
    Random rnd;
    
    // Parametri per le simulazioni
    int N = 100;        // Numero di blocchi
    int L = 100;        // Numero di passi per ogni blocco
    int passi = 100;    // Numero di iterazioni per aumentare il numero di passi
    int a = 1;          // Passo per il caso discreto
    double b = 1.0;     // Passo per il caso continuo
    
    // Vettori per memorizzare le distanze quadrate finali
    vector<double> values_Disc(N * L, 0.0);    // Caso discreto
    vector<double> values_Cont(N * L, 0.0);    // Caso continuo

    // Ciclo principale per aumentare il numero di passi nella simulazione
    for (int j = 1; j <= passi; j++) {
        
        // Loop per eseguire le simulazioni per il numero corrente di passi j
        for (int i = 0; i < N * L; i++) {
            
            // Simulazione del percorso nel caso discreto 
            auto percorso_discreto = rnd.Rnd_Walk(j, a);
            values_Disc[i] = sq_Distance(percorso_discreto); // Calcola la distanza quadrata finale e la memorizza
            
            // Simulazione del percorso nel caso continuo 
            auto percorso_continuo = rnd.Rnd_Walk(j, b);
            values_Cont[i] = sq_Distance(percorso_continuo); // Calcola la distanza quadrata finale e la memorizza
        }

        // Calcola e salva l'ultima media progressiva delle distanze quadrate finali per il caso discreto
        sq_MediaProgressiva_last(values_Disc, N, L, Filename1);

        // Azzera il vettore values_Disc per prepararlo per la prossima iterazione
        for_each(values_Disc.begin(), values_Disc.end(), [](double &k) { k = 0; });

        // Calcola e salva l'ultima media progressiva delle distanze quadrate finali per il caso continuo
        sq_MediaProgressiva_last(values_Cont, N, L, Filename2);
		
        // Azzera il vettore values_Cont per prepararlo per la prossima iterazione
        for_each(values_Cont.begin(), values_Cont.end(), [](double &k) { k = 0; });
    }

    return 0;
}
