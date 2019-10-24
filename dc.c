#define _XOPEN_SOURCE 1000 // or any bigger number
#include <stdio.h>
#include <stdlib.h>
#include "strutil.h"
#include "pila.h"
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>


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
    if(pila_cantidad(pila) < 2){
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
    if(pila_cantidad(pila) < 2){
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
    if(pila_cantidad(pila) < 2){
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


int division(pila_t* pila, int* arreglo,size_t j){
    if(pila_cantidad(pila) < 2){
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


int calculo_potencia(int a, int b){
    if(b == 0){
        return 1;
    }else if (b == 1){
        return a;
    }else if ((a % 2) == 0){
        return calculo_potencia(a*a, b/2);
    }else{
        return a * calculo_potencia(a*a, (b-1)/2);
    }
    return -1;
}


int potencia(pila_t* pila, int* arreglo,size_t j){
    if(pila_cantidad(pila) < 2){
        fprintf(stderr, "ERROR FALTAN ELEMENTOS\n");
        return -1;
    }
    // REVIEW: agregar comprobacion b < 0.
    int a ,b;
    a = *(int*)pila_desapilar(pila);
    b = *(int*)pila_desapilar(pila);
    arreglo[j+1] = calculo_potencia(a,b);
    pila_apilar(pila,&arreglo[j+1]);
    return 0;
}


int calculo_raiz(int a, int min, int max){
    if(max<min){
        return -1;
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
    if(pila_cantidad(pila) < 1){
        fprintf(stderr, "ERROR FALTAN ELEMENTOS\n");
        return -1;
    }
    // REVIEW: agregar comprobacion a > 0.
    int a;
    a = *(int*)pila_desapilar(pila);
    arreglo[j+1] = calculo_raiz(a,1,a/2);
    pila_apilar(pila,&arreglo[j+1]);
    return 0;
}


int calculo_logartimo(int a, int b){
    if (a < b-1){
        return 0;
    }
    return 1+calculo_logartimo(a/b,b);
}


int logaritmo(pila_t* pila, int* arreglo,size_t j){
    if(pila_cantidad(pila) < 2){
        fprintf(stderr, "ERROR FALTAN ELEMENTOS\n");
        return -1;
    }
    // REVIEW: agregar comprobacion b > 1.
    int a ,b;
    a = *(int*)pila_desapilar(pila);
    b = *(int*)pila_desapilar(pila);
    arreglo[j+1] = calculo_logartimo(a,b);
    pila_apilar(pila,&arreglo[j+1]);
    return 0;
}


int ternario(pila_t* pila, int* arreglo, size_t j){
    if(pila_cantidad(pila) < 3){
        fprintf(stderr, "ERROR FALTAN ELEMENTOS\n");
        return -1;
    }
    int a ,b, c;
    a = *(int*)pila_desapilar(pila);
    b = *(int*)pila_desapilar(pila);
    c = *(int*)pila_desapilar(pila);
    if (a == 0){
        arreglo[j+1] = c;
    }else{
        arreglo[j+1] = b;
    }
    pila_apilar(pila,&arreglo[j+1]);
    return 0;
}


void ops (pila_t* pila, char* signo, char** operadores, int* arreglo, size_t j){
    if(strstr(signo,operadores[0]) != NULL){
        suma(pila,arreglo,j);
        // printf("suma\n");
    }else if(strstr(signo,operadores[1]) != NULL){
        resta(pila,arreglo,j);
        // printf("resta\n");
    }else if(strstr(signo,operadores[2]) != NULL){
        multiplicacion(pila,arreglo,j);
        // printf("multipl\n");
    }else if(strstr(signo,operadores[3]) != NULL){
        division(pila,arreglo,j);
        // printf("div\n");
    }else if(strstr(signo,operadores[4]) != NULL){
        raiz(pila,arreglo,j);
        // printf("raiz\n");
    }else if(strstr(signo,operadores[5]) != NULL){
        potencia(pila,arreglo,j);
        // printf("pot\n");
    }else if(strstr(signo,operadores[6]) != NULL){
        ternario(pila,arreglo,j);
        // printf("ternario\n");
    }else if(strstr(signo,operadores[7]) != NULL){
        logaritmo(pila,arreglo,j);
        // printf("log\n");
    }else{
        printf("no es un operador\n");
    }
}


int calculadora(void){
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
            ops(pila,entrada[i],operators,guarda_numeros,j);
        }
    }
    printf("%d\n",*(int*)pila_desapilar(pila));
    pila_destruir(pila);
    free(guarda_numeros);
    free_strv(entrada);
    return 0;
}


int main(void){
    calculadora();
    return 0;
}
