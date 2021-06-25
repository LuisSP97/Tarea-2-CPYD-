#include "registro.h"

string detDate(string date){
    char dateAux[MAX];
    for(long unsigned int i = 0; i < date.size(); i++){
        if(i == 10){
            break;
        }
        else{
            dateAux[i] = date.at(i);
        }
    }
    string onlyDate = dateAux;
    return onlyDate;
};

string detHour(string date){
    char hourAux[MAX];
    for(long unsigned int i = 11; i < date.size(); i++){
        hourAux[i-11] = date[i];
    }
    string onlyHour = hourAux;
    return onlyHour;
}

long detSubtotal(long quant, long amnt){
    long subt = quant * amnt;
    return subt;
}