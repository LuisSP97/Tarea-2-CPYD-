#include "registro.h"

//Funcion que determina la fecha del registro, separandola de la hora.
string detDate(string date){
    char dateAux[2048];
    for(unsigned int i = 0; i < date.size(); i++){
        if(date.at(i)!=32){
            dateAux[i] = date.at(i);
        }
        else{}
    }
    string onlyDate = dateAux;
    return onlyDate;
};

//Funcion que determina la hora del registro, separandola de la fecha.
string detHour(string date){
    char hourAux[1024];
    for(long unsigned int i = 11; i < date.size(); i++){
        hourAux[i-11] = date[i];
    }
    string onlyHour = hourAux;
    return onlyHour;
}

//Funcion que determina el subtotal de un registro con fecha y hora.
long detSubtotal(long quant, long amnt){
    long subt = quant * amnt;
    return subt;
}