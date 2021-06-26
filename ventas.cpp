#include "ventas.h"


//Funcion que determina el total de un solo dia y lo almacena en un vector de tipo Venta
vector<Venta> detTotal(vector<Registro> data){
    long total = 0;
    string date;
    vector<Venta> newData;      //Se crea el vector para retornar los resultados.
    Venta reg(date, total);
    for(unsigned int i = 0; i < data.size()-1; i++){        //Se recorre el vector de registro
        if(data.at(i).getDate() == data.at(i+1).getDate()){     //Se compara la fecha del registro actual con la siguiente 
            total = total + data.at(i).getSubtotal();       //Si son iguales se suman los subtotales de los registros
        }
        else{                                               //Si no lo son, se suma el subtotal del registro actual
            total = total + data.at(i).getSubtotal();       //Se guarda la fecha del registro actual
            date = data.at(i).getDate();                    //Se asignan a un registro de tipo venta y despues se agregan al vector newData de tipo Venta
            reg.setTotal(total);
            reg.setFecha(date);
            newData.push_back(reg);
            total = 0;                                      //Se reinicia la suma del total por dia
        }
    }
    long count = data.size()-1;                             //Una vez termina el ciclo for el ultimo push queda sin ejecutarse por la logica del codigo
    total = total + data.at(count).getSubtotal();           //Por lo que se realiza la misma logica del else pero fuera de este.
    date = data.at(count).getDate();
    reg.setTotal(total);
    reg.setFecha(date);
    newData.push_back(reg);
    return newData;     //Se retorna un vector con las fechas y sus totales de ventas por dia.
}