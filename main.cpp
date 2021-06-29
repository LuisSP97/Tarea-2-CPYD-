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

            cout << "-----=====------=====----" << endl;

            vector<long> arr_total, arr_fechas;
            long varianza_totales = 0, varianza_fechas = 0, covarianza_totales_fechas = 0;
            long double coef_determinacion = 0;
            arr_total = crear_totales(newData);
            arr_fechas = codificar_fechas(newData);
            cout << arr_total.size() << endl;
            varianza_totales = varianza(arr_total);
            varianza_fechas = varianza(arr_fechas);
            covarianza_totales_fechas = covarianza(arr_total, arr_fechas);
            coef_determinacion = coef_determinacion_r_lineal(covarianza_totales_fechas, varianza_totales, varianza_fechas);
            cout << "totales = " << varianza_totales << endl;
            cout << "fechas = " << varianza_fechas << endl;
            cout << "covarianza = " << covarianza_totales_fechas << endl;
            cout << "r^2 = " << coef_determinacion << endl;
            cout << "-----=====------=====----" << endl;

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