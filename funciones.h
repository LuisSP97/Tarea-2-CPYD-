#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "registro.h"
#include "ventas.h"

using namespace std;

string split(string word);
vector<Registro> process_file(vector<Registro> data, string route);
bool validar_formato(string ruta, bool isCSV);
void regresion_exponencial(vector<Venta> newData);
void regresion_lineal(vector<Venta> newData);
void regresion_polinomica(vector<Venta> newData);
long varianza_total(vector<Venta> newData);

#endif //FUNCIONES_H