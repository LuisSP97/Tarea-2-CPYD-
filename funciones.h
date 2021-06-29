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
long covarianza(vector<long> totales, vector<long> fechas);
vector<long> crear_totales(vector<Venta> newData);
vector<long> codificar_fechas(vector<Venta> newData);
long calcular_promedio(vector<long> data);
long varianza(vector<long> data);
long coef_determinacion_r_lineal(long covar_xy, long var_x, long var_y);
#endif //FUNCIONES_H