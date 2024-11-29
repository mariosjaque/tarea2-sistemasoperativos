# Sistemas Operativos - Proyecto 2 - Parte 1
Integrantes del grupo: Benjamín Eduardo Martínez Quijada, Luis Ignacio Martínez Neira, Mario Andrés Salgado Jaque, Santiago Alexander Díaz Barra

## Instrucciones para compilación
El proyecto se desarrolló utilizando CLion, pero es posible compilarlo en cualquier instalación de Linux utilizando CMake y make.

Es recomendable clonar el repositorio, abrir una terminal en la carpeta local de este e ingresar los siguientes comandos:
```
mkdir build
cd build
cmake ..
make
```
Se construirá un solo archivo, el cual se puede ejecutar de la siguiente forma:
```
./simulapc
```

## Instrucciones de uso
Se recibirá como parámetro de entrada el número de productores, número de consumidores, tamaño inicial de cola y tiempo de espera máxima de consumidores en segundos.
Ejemplo de ejecución:
```
./simulapc -p 10 -c 5 -s 50 -t 1
```
