# Sistemas Operativos - Proyecto 2
Integrantes del grupo: Benjamín Eduardo Martínez Quijada, Luis Ignacio Martínez Neira, Mario Andrés Salgado Jaque, Santiago Alexander Díaz Barra

## Instrucciones para compilación
El proyecto se desarrolló utilizando CLion, pero es posible compilarlo en cualquier instalación de Linux utilizando CMake y make.

Es recomendable clonar el repositorio, abrir una terminal en la carpeta local de cada parte de la tarea e ingresar los siguientes comandos:
```
mkdir build
cd build
cmake ..
make
```

Se construirá un solo archivo, ```./simulapc``` en caso de la parte 1 y ```./mvirtual``` en caso de la parte 2.

## Instrucciones de uso
### Parte 1
Se recibirá como parámetro de entrada el número de productores (-p), número de consumidores (-c), tamaño inicial de cola (-s), y tiempo de espera máxima de consumidores en segundos (-t).
Ejemplo de ejecución:
```
./simulapc -p 10 -c 5 -s 50 -t 1
```
### Parte 2
Se recibirá como parámetros de entrada el número de marcos iniciales (-m), algoritmo de reemplazo (-a), y un archivo con referencias a memoria dadas en número de página virtual (-f). Ejemplo de ejecución:
```
 ./mvirtual -m 3 -a FIFO -f referencias.txt
```
Donde ```referencias.txt``` contiene ```0 1 3 4 1 2 5 1 2 3 4```

Para el argumento del algoritmo de reemplazamiento se debe utilizar en mayúsculas uno de los siguientes nombres: FIFO, LRU, OPTIMO, RELOJ_SIMPLE. 
