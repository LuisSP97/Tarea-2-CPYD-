#ifndef VENTAS_H
#define VENTAS_H

#include <string>
#include <iostream>
#include <vector>
#include "registro.h"

using namespace std;

class Venta{
    public:
        Venta(string fecha, long total){};

        void setFecha(string date){fecha = date;}
        void setTotal(long num){total = num;}

        const string getFecha(){return fecha;}
        const long getTotal(){return total;}

    private:
        string fecha;
        long total;
};

vector<Venta> detTotal(vector<Registro> data);
vector<Venta> promMes(vector<Venta> data);
vector<Venta> moda(vector<Venta> data);

#endif //VENTAS_H