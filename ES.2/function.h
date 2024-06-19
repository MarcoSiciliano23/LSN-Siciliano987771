#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>
#include<cstdlib>


using namespace std;

// Classe base astratta per definire una funzione generica
class FunzioneBase {
public:
    // Metodo virtuale puro per valutare la funzione in un punto x
    virtual double Valuta(double x) const = 0;
    // Distruttore virtuale per permettere la distruzione polimorfica
    virtual ~FunzioneBase() { ; };
};

// Classe concreta che eredita da FunzioneBase e definisce una funzione specifica G(x)
class G : public FunzioneBase {
public:
    // Implementazione del metodo per valutare la funzione G(x)
    double Valuta(double x) const override;
};

// Classe concreta che eredita da FunzioneBase e definisce una funzione specifica P(x)
class P : public FunzioneBase {
public:
    // Implementazione del metodo per valutare la funzione P(x)
    double Valuta(double x) const override;
};


// funzioni per calcolare la distanza al quadrato
double sq_Distance(vector<vector<int>>& percorso);
double sq_Distance(vector<vector<double>>& percorso);

void SaveOnTo(const string& Filename, double dato, double errore);
void SaveOnTo(const string& Filename, double dato);

// funzioni per calcolare gli errori
double Error(vector<double> Av, vector<double> Av2, int N);
double Error(double Av, double Av2, int N);

//funzioni per le medie progressive
void MediaProgressiva(const vector<double>& dati, int N, int L, const string& Filename);
void MediaProgressiva_last(const vector<double>& dati, int N, int L, const string& Filename);
void sq_MediaProgressiva_last(const vector<double>& dati, int N, int L, const string& Filename);






#endif // FILE_H

