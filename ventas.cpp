#include "ventas.h"

vector<Venta> detTotal(vector<Registro> data){
    long total = 0;
    string date;
    vector<Venta> newData;
    Venta reg(date, total);
    for(unsigned int i = 0; i < data.size()-1; i++){
        if(data.at(i).getDate() == data.at(i+1).getDate()){
            total = total + data.at(i).getSubtotal();
        }
        else{
            total = total + data.at(i).getSubtotal();
            date = data.at(i).getDate();
            reg.setTotal(total);
            reg.setFecha(date);
            newData.push_back(reg);
            total = 0;
        }
    }
    long count = data.size()-1;
    total = total + data.at(count).getSubtotal();
    date = data.at(count).getDate();
    reg.setTotal(total);
    reg.setFecha(date);
    newData.push_back(reg);
    return newData;
}