#include "funciones.h"
#include<iomanip>
#include<cmath>

using namespace std;

//Funcion que elimina las comillas dobles utilizando la funcion erase.
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
    for(int i = tamano; i > aux; i--){
        formato.push_back(ruta[i]);
        ruta.pop_back();
    }
    if(formato == "vsc"){
        return true;
    }
    return false;
}

void regresion_exponencial(vector<Venta> newData){
    int n,i;
    long double a,b,A;
    n=199;
    long x[n],y[n],sumx=0;
    long double Y[n],sumy=0,sumxy=0,sumx2=0;
    for(i=1;i<=n;i++){                                      //se designan x e y para definir el modelo de regresion 
        x[i]=i;
        y[i]=newData[i].getTotal();
    }  
    for(i=1;i<=n;i++)
    {   
        Y[i]=log(y[i]);                                     //se calcula el logaritmo del monto total por dia

    }
    for(i=1;i<=n;i++)                                       // se calculan las respectivas sumatorias
    {
        sumx=sumx +x[i];
        sumx2=sumx2 +x[i]*x[i];
        sumy=sumy +Y[i];
        sumxy=sumxy +x[i]*Y[i];
        
    }
    A=((sumx2*sumy -sumx*sumxy)/(n*sumx2-sumx*sumx));           //calculo de a y b para luego obtener el valor exponencial de a
    b=((n*sumxy-sumx*sumy)/(n*sumx2-sumx*sumx));
    a=exp(A);
    cout<<"\n               Modelo exponencial:"<<endl;
    cout<<"La ecuacion de la recta es y= "<< a <<"e"<<"^"<<b<<"x"<<endl;
}

void regresion_lineal(vector<Venta> newData){
    int n,i;
    n=newData.size();
    long x[n-1],y[n-1],sumx=0;
    long double a,b,sumy=0,sumxy=0,sumx2=0;
    for(i=1;i<n;i++){
        x[i]=i+1;
        y[i]=newData[i].getTotal();
    }  
    for(i=1;i<n;i++)                                // Se calcula las respectivas sumatorias
    {
        sumx = sumx + x[i];
        sumx2 = sumx2 + x[i]*x[i];
        sumy = sumy + y[i];
        sumxy = sumxy + x[i]*y[i];
    }
        b = (n*sumxy-sumx*sumy)/(n*sumx2-sumx*sumx);                //calculo de a y b 
        a = (sumy - b*sumx)/n;

 cout<<"\n              Modelo de regresion lineal:"<<endl;                  //mostrando el resultado de la regresion lineal
 cout<<"La ecuacion de la recta es: y = "<< a <<" + "<< b<<"x"<<endl;
}

void regresion_polinomica(vector<Venta> newData){
    int i,j,k,n,N;
    cout.precision(4);                        //designa la precicsion
    cout.setf(ios::fixed);
    N=199;
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
    n=n+1;                //n se hace n + 1 porque la parte de eliminación de Gauss a continuación fue para n ecuaciones, pero aquí n es el grado de polinomio y para n grado obtenemos n + 1 ecuaciones  
   
    for (i=0;i<n;i++)                    //A partir de ahora comienza la Eliminación Gaussiana para resolver el conjunto de ecuaciones lineales (Pivotización)
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
        a[i]=B[i][n];                //hacer que la variable a calcular sea igual a la derecha de la última ecuación
        for (j=0;j<n;j++)
            if (j!=i)            //luego reste todos los valores de lhs excepto el coeficiente de la variable cuyo valor esta siendo calculado
                a[i]=a[i]-B[i][j]*a[j];
        a[i]=a[i]/B[i][i];            //finalmente dividi el rhs por el coeficiente de la variable a calcular
    }  
    cout<<"\n               Modelo de regresion polinomica:"<<endl;
    cout<<"La ecuacion de la recta en grado 2 es:  y=";
    for (i=0;i<n;i++)
        cout<<" + ("<<a[i]<<")"<<"x^"<<i;
    cout<<"\n";
}