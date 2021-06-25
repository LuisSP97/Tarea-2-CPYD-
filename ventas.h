#ifndef VENTAS_H
#define VENTAS_H

#include <string>
#include <iostream>
#include <vector>
#include "registro.h"

using namespace std;

class Venta: public Registro{
    public:
        Venta(string fecha, int total);

        void setFecha(string date){fecha = date;}
        void setTotal(int num){total = num;}

        const string getFecha(){return fecha;}
        const int getTotal(){return total;}

    private:
        string fecha;
        int total;
};

vector<Venta> promDia(vector<Venta> data);
vector<Venta> moda(vector<Venta> data);

#endif //VENTAS_H