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
#include<utility>


using namespace std;

// Classe base astratta per definire una funzione
class FunzioneBase {
public:
    // Metodo virtuale puro per valutare la funzione in un punto x
    virtual double Valuta(double x) const = 0;
    // Distruttore virtuale per permettere la distruzione polimorfica
    virtual ~FunzioneBase() { ; };
};

// Classe che rappresenta una funzione d'onda di prova derivata da FunzioneBase
class Trial_wave_function : public FunzioneBase {
private:
    double _mu, _sigma;  // Parametri della funzione d'onda di prova

public:
    // Costruttore che inizializza la funzione d'onda di prova con sigma e mu dati
    Trial_wave_function(double sigma, double mu);
    // Distruttore per la classe Trial_wave_function
    ~Trial_wave_function() { ; };

    // Metodo per valutare la funzione d'onda di prova in un punto x
    double Valuta(double x) const override;

    // Metodo per calcolare il rapporto di accettazione nell'algoritmo Metropolis
    double Acceptance_ratio(double x_new, double x);
};

// Classe che rappresenta una funzione energia derivata da FunzioneBase
class Energia : public FunzioneBase {
private:
    Trial_wave_function psi;  // Funzione d'onda di prova associata all'energia
    double _mu, _sigma;  // Parametri dell'energia

public:
    // Costruttore che inizializza l'energia con sigma e mu dati
    Energia(double sigma, double mu);
    // Distruttore per la classe Energia
    ~Energia() { ; };

    // Metodo per valutare l'energia in un punto x
    double Valuta(double x) const override;
};





// Funzioni per salvare su file
void SaveOnTo(const string& Filename, double dato, double errore);
void SaveOnTo(const string& Filename, double dato);

// Funzioni per calcolare l'errore
double Error(vector<double> Av, vector<double> Av2, int N);
double Error(double Av, double Av2, int N);

// Funzioni per medie progressive
void MediaProgressiva(const vector<double>& dati, int N, int L, const string& Filename);
void MediaProgressiva_last(const vector<double>& dati, int N, int L, const string& Filename);
void sq_MediaProgressiva_last(const vector<double>& dati, int N, int L, const string& Filename);




#endif // FILE_H

