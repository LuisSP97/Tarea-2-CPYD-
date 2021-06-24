#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#define MAX 1024

using namespace std;

class Registro {
    public:
        //Metodo constructor
        Registro(string created, string sku, long quantity, long amount, string name, string date, string hour){};
        //Metodos SET
        void setCreated(string datetime){created = datetime;}
        void setSku(string identifier){sku = identifier;}
        void setQuantity(long quant){quantity = quant;}
        void setAmount(long amnt){amount = amnt;}
        void setName(string desc){name = desc;}
        void setDate(string real_date){date = real_date;}
        void setHour(string real_hour){hour = real_hour;}
        //Metodos GET
        const string getCreated(){return created;}
        const string getSku(){return sku;}
        const long getQuantity(){return quantity;}
        const long getAmount(){return amount;}
        const string getName(){return name;}
        const string getDate(){return date;}
        const string getHour(){return hour;}
    private:
        string created;
        string sku;
        long quantity;
        long amount;
        string name;
        string date;
        string hour;
};

string detDate(string date);
string detHour(string date);

#endif //REGISTRO_H