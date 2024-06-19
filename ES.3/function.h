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

// Funzione per calcolare la distanza quadratica, versione per matrici di interi
double sq_Distance(vector<vector<int>>& percorso);

// Funzione per calcolare la distanza quadratica, versione per matrici di double
double sq_Distance(vector<vector<double>>& percorso);

// Funzione per salvare su file un dato con il suo errore associato
void SaveOnTo(const string& Filename, double dato, double errore);

// Funzione per salvare su file un dato singolo
void SaveOnTo(const string& Filename, double dato);

// Funzione per calcolare l'errore, versione per vettori di medie e vettori di quadrati delle medie
double Error(vector<double> Av, vector<double> Av2, int N);

// Funzione per calcolare l'errore, versione per due medie e il numero di misure N
double Error(double Av, double Av2, int N);

// Funzione per calcolare medie progressive e salvarle su file
void MediaProgressiva(const vector<double>& dati, int N, int L, const string& Filename);

// Funzione per calcolare l'ultima media progressiva e salvarla su file
void MediaProgressiva_last(const vector<double>& dati, int N, int L, const string& Filename);

// Funzione per calcolare l'ultima media progressiva quadrata e salvarla su file
void sq_MediaProgressiva_last(const vector<double>& dati, int N, int L, const string& Filename);

// Fine del file di intestazione "function.h"
#endif // FILE_H
