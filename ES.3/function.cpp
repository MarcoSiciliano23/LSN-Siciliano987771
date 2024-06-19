#include "function.h"

// Implementazione del metodo per valutare la funzione G(x)
double G::Valuta(double x) const {
    return M_PI_2 * cos(M_PI_2 * x);  // Valuta la funzione G(x) = π/2 * cos(π/2 * x)
}

// Implementazione del metodo per valutare la funzione P(x)
double P::Valuta(double x) const {
    return (-1.5*x*x + 1.5);  // Valuta la funzione P(x) = -1.5 * x^2 + 1.5
}

// Funzione per calcolare la distanza quadratica per una matrice di interi
double sq_Distance(vector<vector<int>>& percorso) {
    double distance = 0;

    double xi = percorso[0][0];
    double yi = percorso[0][1];
    double zi = percorso[0][2];

    double xf = percorso[percorso.size() - 1][0];
    double yf = percorso[percorso.size() - 1][1];
    double zf = percorso[percorso.size() - 1][2];

    distance = pow(xi - xf, 2) + pow(yi - yf, 2) + pow(zi - zf, 2);  // Calcola la distanza quadratica

    return distance;
}

// Funzione per calcolare la distanza quadratica per una matrice di double
double sq_Distance(vector<vector<double>>& percorso) {
    double distance = 0;

    double xi = percorso[0][0];
    double yi = percorso[0][1];
    double zi = percorso[0][2];

    double xf = percorso[percorso.size() - 1][0];
    double yf = percorso[percorso.size() - 1][1];
    double zf = percorso[percorso.size() - 1][2];

    distance = pow(xi - xf, 2) + pow(yi - yf, 2) + pow(zi - zf, 2);  // Calcola la distanza quadratica

    return distance;
}

// Funzione per salvare su file un singolo dato
void SaveOnTo(const string& Filename, double dato) {
    ofstream outputFile(Filename, ios::app);
    if (outputFile.is_open()) {
        outputFile << dato << endl;  // Salva il dato nel file
        outputFile.close();
    } else {
        cout << "Errore: Impossibile aprire il file " << Filename << endl;  // Messaggio di errore se non è possibile aprire il file
    }
}

// Funzione per salvare su file un dato e il suo errore associato
void SaveOnTo(const string& Filename, double dato, double errore) {
    ofstream out(Filename.c_str(), ios::app);
    if (out) {
        out << dato << "\t" << errore << endl;  // Salva il dato e il suo errore nel file
    }
    out.close();
}

// Funzione per calcolare l'errore dati vettori di medie e vettori di quadrati delle medie
double Error(vector<double> Av, vector<double> Av2, int N) {
    if (N == 0) {
        return 0;
    }
    return sqrt((Av2[N] - Av[N] * Av[N]) / N);  // Calcola l'errore
}

// Funzione per calcolare l'errore dati due medie e il numero di misure N
double Error(double Av, double Av2, int N) {
    if (N == 0) {
        return 0;
    }
    return sqrt((Av2 - Av * Av) / N);  // Calcola l'errore
}

// Funzione per calcolare medie progressive e salvarle su file
void MediaProgressiva(const vector<double>& dati, int N, int L, const string& Filename) {
    vector<double> ave(N, 0.0);
    vector<double> av2(N, 0.0);
    vector<double> sum_prog(N, 0.0);
    vector<double> su2_prog(N, 0.0);
    vector<double> err_prog(N, 0.0);

    for (int i = 0; i < N; i++) {
        double sum1 = 0.0;
        for (int j = 0; j < L; j++) {
            int k = j + i * L;
            sum1 += dati[k];
        }
        ave[i] = sum1 / L;  // Calcola la media progressiva
        av2[i] = pow(ave[i], 2);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            sum_prog[i] += ave[j];
            su2_prog[i] += av2[j];
        }
        sum_prog[i] /= (i + 1);
        su2_prog[i] /= (i + 1);
        err_prog[i] = Error(sum_prog, su2_prog, i);  // Calcola l'errore progressivo

        SaveOnTo(Filename, sum_prog[i], err_prog[i]);  // Salva la media progressiva e il suo errore nel file
    }
}

// Funzione per calcolare solo l'ultima media progressiva e salvarla su file
void MediaProgressiva_last(const vector<double>& dati, int N, int L, const string& Filename) {
    vector<double> ave(N, 0.0);
    vector<double> av2(N, 0.0);
    vector<double> sum_prog(N, 0.0);
    vector<double> su2_prog(N, 0.0);
    vector<double> err_prog(N, 0.0);

    for (int i = 0; i < N; i++) {
        double sum1 = 0.0;
        for (int j = 0; j < L; j++) {
            int k = j + i * L;
            sum1 += dati[k];
        }
        ave[i] = sum1 / L;  // Calcola la media progressiva
        av2[i] = pow(ave[i], 2);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            sum_prog[i] += ave[j];
            su2_prog[i] += av2[j];
        }
        sum_prog[i] /= (i + 1);
        su2_prog[i] /= (i + 1);
        err_prog[i] = Error(sum_prog, su2_prog, i);  // Calcola l'errore progressivo
    }

    SaveOnTo(Filename, sum_prog.back(), err_prog.back());  // Salva solo l'ultima media progressiva e il suo errore nel file
}

// Funzione per calcolare la radice quadrata dell'ultima media progressiva e salvarla su file
void sq_MediaProgressiva_last(const vector<double>& dati, int N, int L, const string& Filename) {
    vector<double> ave(N, 0.0);
    vector<double> av2(N, 0.0);
    vector<double> sum_prog(N, 0.0);
    vector<double> su2_prog(N, 0.0);
    vector<double> err_prog(N, 0.0);

    for (int i = 0; i < N; i++) {
        double sum1 = 0.0;
        for (int j = 0; j < L; j++) {
            int k = j + i * L;
            sum1 += dati[k];
        }
        ave[i] = sum1 / L;  // Calcola la media progressiva
        av2[i] = pow(ave[i], 2);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            sum_prog[i] += ave[j];
            su2_prog[i] += av2[j];
        }
        sum_prog[i] /= (i + 1);
        su2_prog[i] /= (i + 1);
        err_prog[i] = Error(sum_prog, su2_prog, i);  // Calcola l'errore progressivo
    }

    double sq = sqrt(sum_prog.back());  // Calcola la radice quadrata dell'ultima media progressiva
    double err = 0.5 * err_prog.back() / sq;

    SaveOnTo(Filename, sq, err);  // Salva la radice quadrata dell'ultima media progressiva e il suo errore nel file
}
