#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "registro.h"

using namespace std;

string split(string word);
vector<Registro> process_file(vector<Registro> data, string route);

#endif //FUNCIONES_H