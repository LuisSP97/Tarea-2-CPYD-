#include <iostream>
#include <vector>
#include <stdlib.h>
#include "funciones.h"

using namespace std;

int main(int argc, char *argv[]){
    if(argc < 2){
        cout << "=== Integrantes ===" << endl;
        cout << "Luis Salinas Poblete" << endl;
        cout << "Cristobal Sanchez Orellana" << endl;
        cout << "Ariel Painenao Pincheira" << endl;
    }
    else if(argc >= 3){
        cout << "Al parecer ingresaste parametros extras, intentelo nuevamente." << endl;
    }
    else{
        //Variables de validacion de formato y parametros
        string route = argv[1];     //Corresponde al argumento entregado por la linea de comandos/Terminal
        bool isCSV = false;
        isCSV = validar_formato(route, isCSV);
        if(isCSV == true){
            //Variables y funcion para medir tiempo de ejecucion
            unsigned t0, t1;
            t0 = clock();
            vector<Registro> data;      //Vector para almacenar lo que se leera desde el archivo
            vector<Venta> newData;      //Vector para almacenar los totales de ventas por dia
            cout << "Procesando archivo..." << endl;
            data = process_file(data, route);
            cout << "Determinando total de cada dia..." << endl;
            newData = detTotal(data);
            varianza_total(newData);
            regresion_exponencial(newData);
            regresion_lineal(newData);
            regresion_polinomica(newData);
            
            //Se finaliza el tiempo de ejecucion
            t1 = clock();
            double time = (double(t1-t0)/CLOCKS_PER_SEC);
            cout << "Tiempo de ejecucion:" << time << endl;
        }
        else{
            cout << "El formato del archivo ingresado no es compatible con el programa." << endl;
        }
    }
    return 0;
};