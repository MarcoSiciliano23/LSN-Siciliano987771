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

class FunzioneBase {

public:
		virtual double Valuta(double x) const = 0;
		virtual ~FunzioneBase() { ; };
};


class G : public FunzioneBase {
public:
		double Valuta(double x) const override;
};

class P : public FunzioneBase {
public:
		double Valuta(double x) const override;
};



// function to calculate squared distance
double sq_Distance(vector<vector<int>>& percorso);
double sq_Distance(vector<vector<double>>& percorso);

void SaveOnTo(const string& Filename, double dato, double errore);
void SaveOnTo(const string& Filename, double dato);

// Functions to calculate error
double Error(vector<double> Av, vector<double> Av2, int N);
double Error(double Av, double Av2, int N);

//Functions for progressive averages
void MediaProgressiva(const vector<double>& dati, int N, int L, const string& Filename);
void MediaProgressiva_last(const vector<double>& dati, int N, int L, const string& Filename);
void sq_MediaProgressiva_last(const vector<double>& dati, int N, int L, const string& Filename);






#endif // FILE_H

