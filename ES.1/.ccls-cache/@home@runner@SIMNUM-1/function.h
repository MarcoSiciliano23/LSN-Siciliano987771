#ifndef FILE_H
#define FILE_H


#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void SaveOnTo(const string& Filename, double dato, double errore);
void SaveOnTo(const string& Filename, double dato);
void SaveOnTo(const string& Filename, vector<double> dato);

double Error(vector<double> Av, vector<double> Av2, int N);
double Error(double Av, double Av2, int N);

void MediaProgressiva(const vector<double>& dati, int N, int L, const string& Filename);

#endif // FILE_H
