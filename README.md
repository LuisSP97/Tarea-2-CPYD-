# Tarea-2-CPYD-
Programa que calcula diferentes modelos matematicos de prediccion para un conjunto de datos perteneciente a una tienda de retail. Como resultado se muestra el modelo(Ecuacion) que predice el total de ventas de un dia segun su fecha.

## Como ejecutar 🚀
Las siguientes instrucciones te permitiran obtener una copia del programa, y asi poder ejecutarlo.

### Pre-requisitos 📋
```
 - Compilador de C/C++
 - Make (Builder)
 - Archivo con formato necesario
```
### Formato archivo 📋
Es necesario contar con un archivo llamado "datos.csv", el cual tiene que contener su informacion distribuida de la siguiente manera en distintas columnas:

  1. created (Fecha y hora de creacion del registro 2020-08-14 14:05:05.229)
  2. sku (Codigo del producto)
  3. quantity (Cantidad del producto del registro)
  4. amount (Precio unitario del producto)
  5. name (Nombre del producto)

Tambien sus datos deben encontrarse entre comillas dobles ("dato") y deben estar separados por punto y coma ("dato1";"dato2").
### Instalación 🔧

1. Clonar el proyecto a tu PC

_Para esto puedes descargarlo directo desde GitHub o clonarlo desde un terminal._

```
git clone https://github.com/LuisSP97/Tarea-2-CPYD-
```

2. Construccion del proyecto

_Para esto se utilizara la herramienta mencionada anteriormente, Make. Para esto debes ejecutar el siguiente comando en un terminal:_

```
make
```

## Ejecucion del proyecto ⚙️
_Dependiendo del entorno en cual lo ejecutes, debes llamar al archivo "main", que es el que iniciara el programa. A la vez debes ingresar el parametro, todo esto desde el terminal. Un ejemplo en linux/Mac OS seria:_
```
./main /ruta/al/archivo/datos.csv
```

## Informacion del proyecto

### Construido con 🛠️

* C++ - Lenguaje de programacion utilizado
* Make - Utilizado para compilar la aplicacion de C++
* [Visual Studio Code](https://code.visualstudio.com/) - Usado para crear el codigo

### Autores ✒️

* **Ariel Painenao Pincheira** - [barsinsor](https://github.com/barsinsor)
* **Luis Salinas Poblete** - [LuisSP97](https://github.com/LuisSP97)
* **Cristobal Sanchez Orellana** - [CristobalSanchezOrellana](https://github.com/CristobalSanchezOrellana)
