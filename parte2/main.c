#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamaño_prueba 10
//Creamos la estrucutra de la tabla hash y las listas enlazadas
typedef struct lista_enlazada{
    int paginavirtual;
    int marcos_de_pagina;
    struct lista_enlazada *siguiente;
}lista_enlazada;

typedef struct
{
    lista_enlazada *Lista[tamaño_prueba];
}tabla_hash;

//Funcion hash utilizada para ubicar las paginas dentro de la tabla hash
int funcion_hash(int pagina){
    int numero = pagina % tamaño_prueba;
    return numero;
}
//Imprime el estado actual de la tabla hash
void imprimir_tabla_hash(tabla_hash *tabla) {
    printf("Estado actual de la tabla hash:\n");
    for (int i = 0; i < tamaño_prueba; i++) {
        printf("Índice %d: ", i);
        lista_enlazada *actual = tabla->Lista[i];
        if (actual == NULL) {
            printf("vacío\n");
        } else {
            while (actual != NULL) {
                printf("[Página: %d, Marco: %d] -> ", actual->paginavirtual, actual->marcos_de_pagina);
                actual = actual->siguiente;
            }
            printf("NULL\n");
        }
    }
    printf("\n");
}
//Añade las pagina dentro de la tabla hash
int Añadir_pagina(tabla_hash *tabla,int pagina,int marco){
    //Si donde deberia estar la pagina, no hay nada se añade sin mas
    if (tabla->Lista[funcion_hash(pagina)] == NULL) {
        tabla->Lista[funcion_hash(pagina)] = malloc(sizeof(lista_enlazada));
        if (tabla->Lista[funcion_hash(pagina)] == NULL) {
            printf("Error al asignar memoria\n");
            exit(1);
        }
        tabla->Lista[funcion_hash(pagina)]->marcos_de_pagina = marco;
        tabla->Lista[funcion_hash(pagina)]->paginavirtual = pagina;
        tabla->Lista[funcion_hash(pagina)]->siguiente = NULL;
    }
    //Se busca hasta el final de la lista enlazada, para agregar la pagina
    else{
        
        lista_enlazada *Actual = tabla->Lista[funcion_hash(pagina)];
        if(Actual->siguiente == NULL){
            
            Actual->siguiente = malloc(sizeof(lista_enlazada));
            Actual->siguiente->marcos_de_pagina = marco;
            Actual->siguiente->paginavirtual = pagina;
            
        }
        else{
            while(Actual->siguiente != NULL){
            Actual = Actual->siguiente;
                }
            Actual->siguiente = malloc(sizeof(lista_enlazada)); 
            if (Actual->siguiente == NULL) {
                printf("Error al asignar memoria\n");
                exit(1);
                }
            Actual->siguiente->marcos_de_pagina = marco;
            Actual->siguiente->paginavirtual = pagina;
            
                }
    }
    
    
    return 0;
}
//Quita la pagina que se requiere de la tabla hash
int remover_pagina(tabla_hash *tabla,int pagina)
{
    int marco;
    //Guardaremos la la lista anterior y actual a la seleccionada
    lista_enlazada *Actual = tabla->Lista[funcion_hash(pagina)];
    lista_enlazada *Anterior = NULL;
    //Buscamos si es que la pagina que buscamos existe dentro de la lista enlazada
    while(Actual != NULL && Actual->paginavirtual != pagina){
        Anterior = Actual;
        Actual = Actual->siguiente;
    }
    marco = Actual->marcos_de_pagina;
    //Si existe la pagina que queremos eliminar, entonces 
    if(Actual != NULL){
        
        if (Anterior == NULL) {
            tabla->Lista[funcion_hash(pagina)] = Actual->siguiente;
        } 
        else {
            Anterior->siguiente = Actual->siguiente;
        }
        free(Actual);
    }
    //Ya que algunos algoritmos necesitan del marco, se lo daremos al eliminar la pagina
    return marco;
}
// Se encuentra la pagina  que no sera referenciada por el tiempo mas largo
int buscar_pagina(int paginas[],int pagina,int posicion_de_inicio,int cantidad_de_paginas){
    int numero = 0,i;
    for(i = posicion_de_inicio +1;i<cantidad_de_paginas;i++){
        if(paginas[i] == pagina){
            return numero;
        }
        numero ++;
    }
    return -1;
}
//Busca si la pagina se encuentra dentro de la tabla hash, en caso de estarlo es un HIT
void buscar_pagina_esta(tabla_hash *tabla,int paginas[],int i,int *verificador){
    lista_enlazada *actual;
    if(tabla->Lista[funcion_hash(paginas[i])]->paginavirtual == paginas[i]){
        printf("HIT\n");
        *verificador = 1;
    }
    actual = tabla->Lista[funcion_hash(paginas[i])];
    while(actual->siguiente != NULL){
        actual = actual->siguiente;
        if(actual->paginavirtual == paginas[i]){
            printf("HIT\n");
            *verificador = 1;
            break;
        }
                
    }
}
//Encuenta la posicion del numero mayor
int posicion_mayor(int arreglo[],int tamaño){
    int posicion_mayor = 0;
    for (int i = 1; i < tamaño; i++) {
        if (arreglo[i] > arreglo[posicion_mayor]) {
            posicion_mayor = i;
            }
            }

    return posicion_mayor;
}
//Aumenta 1 segundo
int aumentar_tiempo(int arreglo[],int numero_marco){
    int i;
    for(i = 0;i<numero_marco;i++){
        arreglo[i] = arreglo[i] + 1;
    }
    return 0;
}
int FIFO(tabla_hash *tabla,int paginas[],int marcos[],int cantidad_paginas,int numero_de_marcos){
    int contador = 0,fallos_de_pagina = 0;
    int i = 0,j = 0,verificador = 0;
    int contador2 = 0;
    lista_enlazada *actual;
    
    for(i = 0;i<cantidad_paginas;i++){
        printf("Se intentara añadir la pagina %d\n",paginas[i]);
        verificador = 0;
        if(contador2>=numero_de_marcos){
            contador2 = 0;
        }
        if(contador>=numero_de_marcos){
            
            //Buscamos si es que la pagina ya se encuentra asignada
            if(tabla->Lista[funcion_hash(paginas[i])] != NULL){
                buscar_pagina_esta(tabla,paginas,i,&verificador);
            }
            if(verificador == 1){
                imprimir_tabla_hash(tabla);
                continue;
            }
            //En caso de no estarlo se reemplazara la pagina mas antigua por la que se quiere asignar actualmente
            
            for(j = 0;j<tamaño_prueba;j++){
                
                if(tabla->Lista[j] == NULL){
                    continue;
                }
                
                actual = tabla->Lista[j];
                if(tabla->Lista[j]->marcos_de_pagina == marcos[contador2]){
                    int pagina = tabla->Lista[j]->paginavirtual;
                    remover_pagina(tabla,pagina);
                    Añadir_pagina(tabla,paginas[i],marcos[contador2]);
                    actual = tabla->Lista[funcion_hash(paginas[i])];
                    fallos_de_pagina ++;
                    printf("MISS\n");
                    contador2 ++;
                    break;
                }
                
                while(actual->siguiente != NULL){
                    if(actual->marcos_de_pagina == marcos[contador2]){
                        remover_pagina(tabla,actual->paginavirtual);
                        Añadir_pagina(tabla,paginas[i],actual->marcos_de_pagina);
                        fallos_de_pagina ++;
                        printf("MISS\n");
                        contador2 ++;
                        break;
                    }
                    actual = actual->siguiente;
                }
            }
            imprimir_tabla_hash(tabla);
        }
        else{
            
            Añadir_pagina(tabla,paginas[i],marcos[i]);
            imprimir_tabla_hash(tabla);
            fallos_de_pagina++;
        }
        contador++;
    }
    return fallos_de_pagina;
}

int Optimo(tabla_hash *tabla,int paginas[],int marcos[],int cantidad_paginas,int numero_de_marcos){
    int fallos_de_pagina = 0,i,contador = 0,verificador = 0,j,cantidad_paginas_quedan,pagina_mayor,marco;
    //Se guardara el estado actual de las paginas con un marco asignado con un arreglo
    int paginas_asignadas[numero_de_marcos];
    int arreglo[numero_de_marcos];
    for(i = 0;i<cantidad_paginas;i++){
        printf("Se intentara añadir la pagina %d\n",paginas[i]);
        verificador = 0;
        if(contador >= numero_de_marcos){

            //Se busca si es que la pagina ya se encuentra asignadad
            if(tabla->Lista[funcion_hash(paginas[i])] != NULL){
                buscar_pagina_esta(tabla,paginas,i,&verificador);
            }
            if(verificador == 1){
                imprimir_tabla_hash(tabla);
                continue;
            }
            //En caso de no estarlo se aplicara el algoritmo de reemplazamiento Optimo
            printf("MISS\n");
            fallos_de_pagina ++;
            for(j = 0;j<numero_de_marcos;j++){
                arreglo[j] = buscar_pagina(paginas,paginas_asignadas[j],i,cantidad_paginas);
                if(arreglo[j] == -1){
                    marco = remover_pagina(tabla,paginas_asignadas[j]);
                    Añadir_pagina(tabla,paginas[i],marco);
                    paginas_asignadas[j] = paginas[i];
                    imprimir_tabla_hash(tabla);
                    verificador = 1;
                    break;
                }
            }
            if(verificador == 1){
                continue;
            }
            
            pagina_mayor = posicion_mayor(arreglo,numero_de_marcos);
            marco = remover_pagina(tabla,paginas_asignadas[pagina_mayor]);
            Añadir_pagina(tabla,paginas[i],marco);
            paginas_asignadas[pagina_mayor] = paginas[i];
            imprimir_tabla_hash(tabla);
        }

        else{
            printf("MISS\n");
            Añadir_pagina(tabla,paginas[i],marcos[i]);
            contador++;
            paginas_asignadas[i] = paginas[i];
            imprimir_tabla_hash(tabla);
            fallos_de_pagina ++;
        }
    }
    return fallos_de_pagina;
}

int LRU(tabla_hash *tabla,int paginas[],int marcos[],int cantidad_paginas,int numero_de_marcos){
    int fallos_de_pagina = 0,i,contador = 0,verificador = 0,j,tiempo_mayor,marco;
    int paginas_asignadas[numero_de_marcos];
    int tiempo[numero_de_marcos];
    //Se inicializa todo en el arreglo tiempo, a el numero de tamaño del marco, ya que esto solo sera utilizado si es que, los marcos no bastan, para el tamaño de paginas
    for(i = 0;i<numero_de_marcos;i++){
        tiempo[i] = 0;
    }
    for(i = 0;i<cantidad_paginas;i++){
        printf("Se intentara añadir la pagina %d\n",paginas[i]);
        verificador = 0;
        if(contador >= numero_de_marcos){
            if(tabla->Lista[funcion_hash(paginas[i])] != NULL){
                buscar_pagina_esta(tabla,paginas,i,&verificador);
            }
            if(verificador == 1){
                aumentar_tiempo(tiempo,numero_de_marcos);
                for(j = 0;j<numero_de_marcos;j++){
                    if(paginas_asignadas[j] == paginas[i]){
                        tiempo[j] = 0;
                        break;
                    }
                }
                imprimir_tabla_hash(tabla);
                continue;
            }
            printf("MISS\n");
            fallos_de_pagina ++;
            tiempo_mayor = posicion_mayor(tiempo,numero_de_marcos);
            marco = remover_pagina(tabla,paginas_asignadas[tiempo_mayor]);
            Añadir_pagina(tabla,paginas[i],marco);
            paginas_asignadas[tiempo_mayor] = paginas[i];
            aumentar_tiempo(tiempo,numero_de_marcos);
            tiempo[tiempo_mayor] = 0;
            imprimir_tabla_hash(tabla);
        }


        else{
            printf("MISS\n");
            Añadir_pagina(tabla,paginas[i],marcos[i]);
            contador++;
            paginas_asignadas[i] = paginas[i];
            imprimir_tabla_hash(tabla);
            fallos_de_pagina ++;
        }
    }
    return fallos_de_pagina;
}
int Reloj_simple(tabla_hash *tabla,int paginas[],int marcos[],int cantidad_paginas,int numero_de_marcos){
    int fallos_de_pagina = 0,i,contador = 0,verificador = 0,j,marco;
    int paginas_asignadas[numero_de_marcos];
    int bits[numero_de_marcos];
    for(i = 0;i<numero_de_marcos;i++){
        bits[i] = 1;
    }
    for(i = 0;i<cantidad_paginas;i++){
        printf("Se intentara añadir la pagina %d\n",paginas[i]);
        verificador = 0;
        if(contador >= numero_de_marcos){
            if(tabla->Lista[funcion_hash(paginas[i])] != NULL){
                buscar_pagina_esta(tabla,paginas,i,&verificador);
            }
            if(verificador == 1){
                imprimir_tabla_hash(tabla);
                continue;
            }
            printf("MISS\n");
            fallos_de_pagina ++;
            j = 0;
            while(1){
                if(bits[j] == 0){
                    break;
                }
                bits[j] = 0;
                j++;
                if(j>=numero_de_marcos){
                    j = 0;
                }
            }
            
            marco = remover_pagina(tabla,paginas_asignadas[j]);
            Añadir_pagina(tabla,paginas[i],marco);
            bits[j] = 1;
            paginas_asignadas[j] = paginas[i];
            printf("Estado actual de los bits:");
            for(int z=0;z<numero_de_marcos;z++){
                printf("%d ",bits[z]);
            }
            printf("\n");
            imprimir_tabla_hash(tabla);
            }

        else{
            printf("MISS\n");
            Añadir_pagina(tabla,paginas[i],marcos[i]);
            contador++;
            paginas_asignadas[i] = paginas[i];
            imprimir_tabla_hash(tabla);
            fallos_de_pagina ++;
        }
    }
    return fallos_de_pagina;
}
int main(int argc,char *argv[])
{
    FILE *referencias;
    int i = 0,cantidad_paginas = 0,numero,fallos_de_pagina;
    int paginas[100];
    //Dejamos todos los numeros del arreglo paginas en -1
    for(i=0;i<100;i++){
        paginas[i] =-1;
    }
    printf("Usted selecciono los siguientes argumentos: \n");
    for(i=0;i<argc;i++)
    {
        printf("%s\n",argv[i]);
    }
    int numero_de_marcos = atoi(argv[2]);
    printf("Numero de marcos es %d\n",numero_de_marcos);
    int marcos[numero_de_marcos];
    for(i = 0;i<numero_de_marcos;i++){
        marcos[i] = i;
    }

    referencias = fopen(argv[6],"r");
    if(referencias == NULL)
    {
        printf("Error al abrir el archivo de texto");
        exit(1);
    }
    //Guardar las referencias en el arreglo paginas
    
    while (fscanf(referencias, "%d", &numero) == 1) {
        paginas[cantidad_paginas] = numero;
        printf("%d ", paginas[cantidad_paginas]);
        cantidad_paginas++;
    }
    fclose(referencias);
    //Creamos la respectiva tabla hash con un tamaño constante de 10
    printf("\n");
    
    tabla_hash *tabla = malloc(sizeof(tabla_hash));
    
    if (tabla == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
        }
    
    for(i=0;i<tamaño_prueba;i++){
        tabla->Lista[i] = NULL;
    }
    
    if(strcmp("FIFO",argv[4]) == 0){
        printf("Fallos de pagina: %d",FIFO(tabla,paginas,marcos,cantidad_paginas,numero_de_marcos));
    }
    else if(strcmp("OPTIMO",argv[4]) == 0){
        printf("Fallos de pagina: %d",Optimo(tabla,paginas,marcos,cantidad_paginas,numero_de_marcos));
    }
    else if(strcmp("LRU",argv[4]) == 0){
        printf("Fallos de pagina: %d",LRU(tabla,paginas,marcos,cantidad_paginas,numero_de_marcos));
    }
    else if(strcmp("RELOJ_SIMPLE",argv[4]) == 0){
        printf("Fallos de pagina: %d",Reloj_simple(tabla,paginas,marcos,cantidad_paginas,numero_de_marcos));
    }
    else{
        printf("No se selecciono ningun algoritmo de reemplazamiento");
    }
    // Liberar memoria
    for (i = 0; i < tamaño_prueba; i++) {
        if (tabla->Lista[i] != NULL) {
            free(tabla->Lista[i]);
        }
    }
    free(tabla);
    return 0;
}