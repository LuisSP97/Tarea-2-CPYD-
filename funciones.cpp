#include "funciones.h"

using namespace std;

string split(string word){
    word.erase(remove(word.begin(), word.end(), '"'), word.end());
    return word;
}

vector<Registro> process_file(vector<Registro> data, string route){
    ifstream file(route);
    string line;
    char delimiter = ';';
    if(file.is_open()){
        cout << "Se abrio el archivo con exito!" << endl;
        while(getline(file, line)){
            stringstream stream(line);
            //Variables para almacenar datos del archivo
            string date, identifier, quant, amnt, desc;
            //Variables para almacenar datos del archivo en vector
            string v_date, v_identifier, v_desc, v_real_date, v_real_hour;
            long v_quant = 0, v_amnt = 0, v_subt = 0;

            getline(stream, date, delimiter);
            getline(stream, identifier, delimiter);
            getline(stream, quant, delimiter);
            getline(stream, amnt, delimiter);
            getline(stream, desc, delimiter);

            v_desc = split(desc);
            v_quant = atol(split(quant).c_str());
            v_amnt = atol(split(amnt).c_str());
            v_date = split(date);
            v_identifier = split(identifier);
            v_real_date = detDate(v_date);
            v_real_hour = detHour(v_date);
            v_subt = detSubtotal(v_quant, v_amnt);


            Registro reg(v_date, v_identifier, v_quant, v_amnt, v_desc, v_real_date, v_real_hour, v_subt);
            reg.setCreated(v_date);
            reg.setSku(v_identifier);
            reg.setQuantity(v_quant);
            reg.setAmount(v_amnt);
            reg.setName(v_desc);
            reg.setDate(v_real_date);
            reg.setHour(v_real_hour);
            reg.setSubtotal(v_subt);
            data.push_back(reg);
        }
        file.close();
    }
    else{
        cout << "Ups!, el archivo no se pudo abrir :c" << endl;
    }
    return data;
}