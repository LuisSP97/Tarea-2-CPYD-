#include <iostream>
#include <vector>
#include <stdlib.h>
#include "funciones.h"

using namespace std;

int main(int argc, char *argv[]){
    vector<Registro> data;
    vector<Venta> newData;
    string route = argv[1];
    cout << "Procesando archivo..." << endl;
    data = process_file(data, route);
    cout << "Determinando total de cada dia..." << endl;
    newData = detTotal(data);
    /*for(unsigned int i = 1; i < newData.size(); i++){
        cout << i << "." <<"Fecha:" << newData[i].getFecha()<< "//Total del dia:" << newData[i].getTotal() << endl;
    }*/
    regresion_exponencial(newData);
    regresion_lineal(newData);
    regresion_polinomica(newData);

};