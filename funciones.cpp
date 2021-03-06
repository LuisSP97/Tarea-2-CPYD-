#include "funciones.h"
#include<iomanip>
#include<cmath>

using namespace std;

//Funcion que elimina las comillas dobles utilizando la funcion erase.
string split(string word){
    word.erase(remove(word.begin(), word.end(), '"'), word.end());
    return word;
}

//Funcion que procesa los datos del archivo recibido por la linea de comandos/ Terminal
vector<Registro> process_file(vector<Registro> data, string route){
    ifstream file(route);
    string line;
    char delimiter = ';';
    if(file.is_open()){
        cout << "Se abrio el archivo con exito!" << endl;
        cout << "Procesando el archivo..." << endl;
        while(getline(file, line)){
            stringstream stream(line);
            //Variables para almacenar datos del archivo
            string date, identifier, quant, amnt, desc;
            //Variables para almacenar datos del archivo en vector
            string v_date, v_hour, v_identifier, v_desc, v_real_date, v_real_hour;
            long v_quant = 0, v_amnt = 0, v_subt = 0;
            //Se obtiene una linea y se separan los datos en las variables a medida que encuentra el delimiter
            getline(stream, date, delimiter);
            getline(stream, identifier, delimiter);
            getline(stream, quant, delimiter);
            getline(stream, amnt, delimiter);
            getline(stream, desc, delimiter);
            //Se eliminan comillas dobles de las variables y se transforman a sus tipos de variables correspondientes
            v_desc = split(desc);
            v_date = split(date);
            v_quant = atol(split(quant).c_str());
            v_amnt = atol(split(amnt).c_str());
            v_identifier = split(identifier);
            v_real_date = detDate(split(date));
            v_real_hour = detHour(split(date));
            v_subt = detSubtotal(v_quant, v_amnt);
            //Se crea un reg de tipo Registro y se le setean los valores obtenidos ya limpios
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

//Funcion para validar que el formato del archivo sea CSV
bool validar_formato(string ruta, bool isCSV){
    int tamano = ruta.size()-1;
    int aux = ruta.size()-4;
    string formato;
    for(int i = tamano; i > aux; i--){      //Ciclo inverso que extrae los ultimos 3 caracteres, correspondientes al formato csv
        formato.push_back(ruta[i]);
        ruta.pop_back();
    }
    if(formato == "vsc"){           //Como el ciclo es inverso, el string formato lo almacenara al reves
        return true;
    }
    return false;
}

//Funcion que determina un modelo de regresion exponencial con el conjunto de datos
void regresion_exponencial(vector<Venta> newData){
    int n,i;
    long double a,b,A;
    n=newData.size()-1;
    long x[n],y[n],sumx=0;
    long double Y[n],sumy=0,sumxy=0,sumx2=0;
    for(i=1;i<=n;i++){                                      //se designan x e y para definir el modelo de regresion 
        x[i]=i;                                             // x es la codificacion de la fecha del 1 a n
        y[i]=newData[i].getTotal();                         // y es el monto total vendido en esa fecha
    }  
    for(i=1;i<=n;i++)
    {   
        Y[i]=log(y[i]);                                     //se calcula el logaritmo del monto total por dia

    }
    for(i=1;i<=n;i++)                                       // se calculan las respectivas sumatorias
    {
        sumx=sumx +x[i];                                    //sumatoria de x
        sumx2=sumx2 +x[i]*x[i];                             //sumatoria de x??
        sumy=sumy +Y[i];                                    // sumatoria de Y que es el logaritmo de y
        sumxy=sumxy +x[i]*Y[i];                             // sumatoria de x * y 
        
    }
    A=((sumx2*sumy -sumx*sumxy)/(n*sumx2-sumx*sumx));           //calculo de a y b para luego obtener el valor exponencial de a
    b=((n*sumxy-sumx*sumy)/(n*sumx2-sumx*sumx));
    a=exp(A);                                                       //valor exponecial de A
    cout<<"\n               Modelo exponencial:"<<endl;
    cout<<"La ecuacion de la recta para predecir las ventas de un dia en una fecha x es:\n VentaTotalDia= "<< a <<"e"<<"^"<<b<<"*FechaDia"<<endl;
}

//Funcion que determina un modelo de regresion lineal con el conjunto de datos
void regresion_lineal(vector<Venta> newData){
    int n,i;
    n=newData.size()-1;
    long x[n],y[n],sumx=0;
    long double a,b,sumy=0,sumxy=0,sumx2=0;
    for(i=1;i<=n;i++){                                    //se designan x e y para definir el modelo de regresion 
        x[i]=i;                                          // x es la codificacion de la fecha del 1 a n                             
        y[i]=newData[i].getTotal();                     // y es el monto total vendido en esa fecha
    }  
    for(i=1;i<=n;i++)                                // Se calcula las respectivas sumatorias
    {
        sumx = sumx + x[i];
        sumx2 = sumx2 + x[i]*x[i];
        sumy = sumy + y[i];
        sumxy = sumxy + x[i]*y[i];
    }
        b = (n*sumxy-sumx*sumy)/(n*sumx2-sumx*sumx);                //calculo de a y b 
        a = (sumy - b*sumx)/n;

    cout<<"\n              Modelo de regresion lineal:"<<endl;                  //mostrando el resultado de la regresion lineal
    cout<<"La ecuacion de la recta para predecir las ventas de un dia en una fecha x es: \n VentaTotalDia= "<< a <<" + "<< b<<"*FechaDia"<<endl;
}

//Funcion que determina un modelo de regresion polinomica con el conjunto de datos
void regresion_polinomica(vector<Venta> newData){
    int i,j,k,n,N;
    cout.precision(4);                        //designa la precicsion
    cout.setf(ios::fixed);
    N=newData.size()-1;
    n=2;                                       //n es el grado del polinomio
    double x[N],y[N];
    for(i=1;i<=N;i++){
        x[i]=i+1;
        y[i]=newData[i].getTotal();
    }
    double X[2*n+1];                        //array que guardara los valores de sigma (xi), sigma (xi ^ 2), sigma (xi ^ 3) .... sigma (xi ^ 2n)
    for (i=0;i<2*n+1;i++)
    {
        X[i]=0;
        for (j=0;j<N;j++)
            X[i]=X[i]+pow(x[j],i);        //posiciones que almacenaran N y los sigma
    }
    double B[n+1][n+2],a[n+1];            //B es la matriz que almacenaran las ecuaciones y a guaradara los coeficientes finales
    for (i=0;i<=n;i++)
        for (j=0;j<=n;j++)
            B[i][j]=X[i+j];            //Se crea la matriz normal que guardara sus coeficientes en sus posicion correspondientes a excepcion de la ultima columna
    double Y[n+1];                    //arra que guardara los sigma pero de Y 
    for (i=0;i<n+1;i++)
    {    
        Y[i]=0;
        for (j=0;j<N;j++)
        Y[i]=Y[i]+pow(x[j],i)*y[j];        //las posiciones se guardan en orden del su grado exponencial de menor a mayor
    }
    for (i=0;i<=n;i++)
        B[i][n+1]=Y[i];                //cargar en la ultima columna de B los valores de Y
    n=n+1;                //n se hace n + 1 porque la parte de eliminaci??n de Gauss a continuaci??n fue para n ecuaciones, pero aqu?? n es el grado de polinomio y para n grado obtenemos n + 1 ecuaciones  
   
    for (i=0;i<n;i++)                    //A partir de ahora comienza la Eliminaci??n Gaussiana para resolver el conjunto de ecuaciones lineales (Pivotizaci??n)
        for (k=i+1;k<n;k++)
            if (B[i][i]<B[k][i])
                for (j=0;j<=n;j++)
                {
                    double temp=B[i][j];
                    B[i][j]=B[k][j];
                    B[k][j]=temp;
                }
     
    for (i=0;i<n-1;i++)            //loop para hacer la eliminacion de Gauss
        for (k=i+1;k<n;k++)
            {
                double t=B[k][i]/B[i][i];
                for (j=0;j<=n;j++)
                    B[k][j]=B[k][j]-t*B[i][j];    //hacer que los elementos debajo de los elementos pivote sean iguales a cero o eliminar las variables
            }
    for (i=n-1;i>=0;i--)                //sustitucion hacia atras
    {                        //x es una matriz cuyos valores corresponden a los valores de x, y, z ..
        a[i]=B[i][n];                //hacer que la variable a calcular sea igual a la derecha de la ??ltima ecuaci??n
        for (j=0;j<n;j++)
            if (j!=i)            //luego reste todos los valores de lhs excepto el coeficiente de la variable cuyo valor esta siendo calculado
                a[i]=a[i]-B[i][j]*a[j];
        a[i]=a[i]/B[i][i];            //finalmente dividi el rhs por el coeficiente de la variable a calcular
    }  
    cout<<"\n               Modelo de regresion polinomica:"<<endl;
    cout<<"La ecuacion de la recta en grado 2 para predecir las ventas de un dia para una fecha x es: \n  VentaTotalDia= ";
    for (i=0;i<n;i++)
        cout<<" + ("<<a[i]<<")"<<"*FechaDia^"<<i;
    cout<<"\n";
}


//Funcion que retorna un vector con todos los totales del vector de clase Venta
vector<long> crear_totales(vector<Venta> newData){
    vector<long> arr;
    for(unsigned int i = 1; i < newData.size(); i++){
        arr.push_back(newData.at(i).getTotal());
    }
    return arr;
}

//Funcion que codifica las fechas, asignandoles un numero a partir del 2 en la posicion 0
vector<long> codificar_fechas(vector<Venta> newData){
    long num = 0;
    vector<long> arr;
    for(unsigned int i = 1; i < newData.size(); i++){
        num = i + 1;
        arr.push_back(num);
    }
    return arr;
}

//Funcion que calcula el promedio de todos los datos de un vector
long calcular_promedio(vector<long> data){
    long promedio = 0, suma = 0;
    for(unsigned int i = 0; i < data.size(); i++){
        suma = suma + data.at(i);
    }
    promedio = suma/data.size();
    return promedio;
}

//Funcion que calcula la varianza de una poblacion de datos
long varianza(vector<long> data){
    vector<long> arr;
    long promedio = 0, count = 0, suma = 0;
    promedio = calcular_promedio(data);
    for(unsigned int i = 0; i < data.size(); i++){
        arr.push_back(pow(data.at(i) - promedio, 2));
        suma = suma + arr.at(i);
        count++;
    }
    promedio = suma/count;
    return promedio;
}


//Funcion para calcular la covarianza de las variables fecha y total del vector de tipo Venta
long covarianza(vector<long> totales, vector<long> fechas){
    long prom_total = 0, prom_fecha = 0, suma = 0, n = totales.size();
    long double covariance = 0;
    vector<long> arr_total, arr_fecha, arr_producto;
    prom_total = calcular_promedio(totales);
    prom_fecha = calcular_promedio(fechas);
    for(unsigned int i = 0; i < totales.size(); i++){
        arr_total.push_back(totales.at(i) - prom_total);
        arr_fecha.push_back(fechas.at(i) - prom_fecha);
        arr_producto.push_back(arr_total.at(i) * arr_fecha.at(i));
    }
    for(unsigned int i = 0; i < arr_producto.size(); i++){
        suma = suma + arr_producto.at(i);
    }
    covariance = suma/n;
    return covariance;
}

//Funcion que determina el coeficiente de determinacion para la regresion lineal, utilizando la el coeficiente de relacion de Pearson.
//======== LA FUNCION PRESENTA PROBLEMAS AL MULTIPLICAR DE FORMA ERRONEA LOS DATOS AL SER DEMASIADO GRANDES===========
long coef_determinacion_r_lineal(long covar_xy, long var_x, long var_y){
    long double r_cuadrado = 0, covar;
    covar = pow(covar_xy, 2);
    r_cuadrado = covar/(var_x * var_y);
    cout << "R^2 = " <<r_cuadrado << endl;
    return r_cuadrado;
}