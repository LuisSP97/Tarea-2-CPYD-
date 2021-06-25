#include <iostream>
#include <vector>
#include <stdlib.h>
#include "funciones.h"

using namespace std;

int main(int argc, char *argv[]){
    vector<Registro> data;
    string route = argv[1];
    cout << route << endl;
    data = process_file(data, route);




    cout << "SKU:" << data[1].getSku() << endl;
    cout << "Name:" << data[1].getName() << endl;
    cout << "Amount:" << data[1].getAmount() << endl;
    cout << "Quantity:" << data[1].getQuantity() << endl;
    cout << "Subtotal:" << data[1].getSubtotal() << endl;
    cout << "Date-Time:" << data[1].getCreated() << endl;
    cout << "Date:" << data[1].getDate() << endl;
    cout << "Hour:" << data[1].getHour() << endl;
};