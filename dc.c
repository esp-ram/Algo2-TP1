#define _XOPEN_SOURCE 1000 // or any bigger number
#include <stdio.h>
#include <stdlib.h>
#include "strutil.h"
#include "pila.h"
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define MAX_LIMIT 20


bool isNumber(char number[]){
    int i = 0;
    if (number[0] == '-') i = 1;
    for (; number[i] != 0; i++){
        if (!isdigit(number[i])) return false;
    }
    return true;
}


bool isOperator_1(char* posible, char** operadores){
    for(int i = 0;i<8;i++){
        if(strcmp(posible,operadores[i]) == 0){
            return true;
        }
    }
    return false;
}

int suma (pila_t* pila, int* arreglo,size_t j){
    if(pila_capacidad(pila) < 2){
        fprintf(stderr, "ERROR FALTAN ELEMENTOS\n");
        return -1;
    }
    int a ,b;
    a = *(int*)pila_desapilar(pila);
    b = *(int*)pila_desapilar(pila);
    arreglo[j+1] = a + b;
    pila_apilar(pila,&arreglo[j+1]);
    return 0;
}

int resta (pila_t* pila, int* arreglo,size_t j){
    if(pila_capacidad(pila) < 2){
        fprintf(stderr, "ERROR FALTAN ELEMENTOS\n");
        return -1;
    }
    int a ,b;
    a = *(int*)pila_desapilar(pila);
    b = *(int*)pila_desapilar(pila);
    arreglo[j+1] = a - b;
    pila_apilar(pila,&arreglo[j+1]);
    return 0;
}

int multiplicacion (pila_t* pila, int* arreglo,size_t j){
    if(pila_capacidad(pila) < 2){
        fprintf(stderr, "ERROR FALTAN ELEMENTOS\n");
        return -1;
    }
    int a ,b;
    a = *(int*)pila_desapilar(pila);
    b = *(int*)pila_desapilar(pila);
    arreglo[j+1] = a * b;
    pila_apilar(pila,&arreglo[j+1]);
    return 0;
}


int calculo_potencia(int a, int b){
    if(b = 0){
        return 1;
    }else if (b == 1){
        return a;
    }else if ((a % 2) == 0){
        return calculo_potencia(a*a, b/2);
    }else{
        return a * calculo_potencia(a*a, (b-1)/2);
    }
    return NULL;
}

int division(pila_t* pila, int* arreglo,size_t j){
    if(pila_capacidad(pila) < 2){
        fprintf(stderr, "ERROR FALTAN ELEMENTOS\n");
        return -1;
    }
    int a ,b;
    // REVIEW: caso b = 0 se apila a?
    a = *(int*)pila_desapilar(pila);
    b = *(int*)pila_desapilar(pila);
    arreglo[j+1] = a / b;
    pila_apilar(pila,&arreglo[j+1]);
    return 0;
}

int potencia(pila_t* pila, int* arreglo,size_t j){
    if(pila_capacidad(pila) < 2){
        fprintf(stderr, "ERROR FALTAN ELEMENTOS\n");
        return -1;
    }
    // REVIEW: agregar comprobacion b = 0.
    int a ,b;
    a = *(int*)pila_desapilar(pila);
    b = *(int*)pila_desapilar(pila);
    arreglo[j+1] = calculo_potencia(a,b);
    pila_apilar(pila,&arreglo[j+1]);
    return 0;
}


int calculo_raiz(int a, int min, int max){
    if(max<min){
        return NULL;
    }
    int medio = (min+max)/2;
    if(medio*medio > a){
        return calculo_raiz(a,min,medio-1);
    }
    if(medio*medio <= a && (medio+1)*(medio+1) > a){
        return medio;
        }
    return calculo_raiz(a,medio+1,max);
}


int raiz(pila_t* pila, int* arreglo,size_t j){
    if(pila_capacidad(pila) < 1){
        fprintf(stderr, "ERROR FALTAN ELEMENTOS\n");
        return -1;
    }
    // REVIEW: agregar comprobacion b = 0.
    int a;
    a = *(int*)pila_desapilar(pila);
    arreglo[j+1] = calculo_raiz(a,1,a/2);
    pila_apilar(pila,&arreglo[j+1]);
    return 0;
}


void ops (pila_t* pila, char* signo, char** operadores, int* arreglo, size_t j){
    if(strstr(signo,operadores[0]) != NULL){
        return(suma(pila,arreglo,j));
        printf("suma\n");
    }else if(strstr(signo,operadores[1]) != NULL){
        return(resta(pila,arreglo,j));
        printf("resta\n");
    }else if(strstr(signo,operadores[2]) != NULL){
        return(multiplicacion(pila,arreglo,j));
        printf("multipl\n");
    }else if(strstr(signo,operadores[3]) != NULL){
        return(division(pila,arreglo,j));
        printf("div\n");
    }else if(strstr(signo,operadores[4]) != NULL){
        printf("raiz\n");
    }else if(strstr(signo,operadores[5]) != NULL){
        printf("pot\n");
    }else if(strstr(signo,operadores[6]) != NULL){
        printf("ternario\n");
    }else if(strstr(signo,operadores[7]) != NULL){
        printf("log\n");
    }else{
        printf("no es un operador\n");
    }
}

/*
int calculadora(void){
    pila_t* pila = pila_crear();
    if(pila == NULL){
        return 0;
    }
    char** operators = split("+ - * / sqrt ^ ? log",' ');
    char *line_buffer = NULL;
    size_t line_buffer_size = 0;
    getline(&line_buffer, &line_buffer_size, stdin);
    char** entrada = split(line_buffer,' ');
    for(int i = 0; entrada[i] != NULL; i++){
        if(isNumber(entrada[i])){
            pila_apilar(pila,(entrada[i]));
            printf("apila numero\n");
        }else{
            printf("no es numero\n");
            ops(pila,entrada[i],operators);
        }
    }
    free_strv(entrada);
    free_strv(operators);
    free(line_buffer);
    pila_destruir(pila);
    printf("salida\n");
    return 0;
}
*/



int calculadora_1(void){
    pila_t* pila = pila_crear();
    if(pila == NULL){
        return 0;
    }
    char** operators = split("+ - * / sqrt ^ ? log",' ');
    char *line_buffer = NULL;
    size_t line_buffer_size = 0;
    getline(&line_buffer, &line_buffer_size, stdin);
    // TODO: comprobacion memoria calloc.
    int* guarda_numeros = calloc(line_buffer_size,sizeof(int));
    char** entrada = split(line_buffer,' ');
    int j = 0;
    for(int i = 0; entrada[i] != NULL; i++){
        if(isNumber(entrada[i])){
            guarda_numeros[j] = atoi(entrada[i]);
            pila_apilar(pila,&guarda_numeros[j]);
            printf("apila numero\n");
            j++;
        }else{
            printf("no es numero\n");
            ops(pila,entrada[i],operators,guarda_numeros,j){
            }
        }
    }
    printf("%d\n",*(int*)pila_desapilar(pila));

    pila_destruir(pila);
    return 0;
}


int main(void){
    calculadora_1();
    return 0;
}
