#define _XOPEN_SOURCE 1000 // or any bigger number
#include <stdio.h>
#include <stdlib.h>
#include "strutil.h"
#include "pila.h"
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define FACTOR_REDIMENSION 2


bool redimensionar_arr(int* vector, size_t tam_nuevo) {
    int* datos_nuevo = realloc(vector, (tam_nuevo*FACTOR_REDIMENSION) * sizeof(int));
    if (tam_nuevo > 0 && datos_nuevo == NULL) {
        return false;
    }
    vector = datos_nuevo;
    return true;
}


bool isNumber(char number[]){
    int i = 0;
    if (number[0] == '-' && number[1] == '\0'){
        return false;
    }
    i = 1;
    for (; number[i] != 0; i++){
        if (!isdigit(number[i])) return false;
    }
    return true;
}


int suma (pila_t* pila, int* arreglo,size_t j){
    if(pila_cantidad(pila) < 2){
        return -1;
    }
    int a ,b;
    a = *(int*)pila_desapilar(pila);
    b = *(int*)pila_desapilar(pila);
    arreglo[j] = a + b;
    pila_apilar(pila,&arreglo[j]);
    return 0;
}


int resta (pila_t* pila, int* arreglo,size_t j){
    if(pila_cantidad(pila) < 2){
        return -1;
    }
    int a ,b;
    a = *(int*)pila_desapilar(pila);
    b = *(int*)pila_desapilar(pila);
    arreglo[j] = a - b;
    pila_apilar(pila,&arreglo[j]);
    return 0;
}


int multiplicacion (pila_t* pila, int* arreglo,size_t j){
    if(pila_cantidad(pila) < 2){
        return -1;
    }
    int a ,b;
    a = *(int*)pila_desapilar(pila);
    b = *(int*)pila_desapilar(pila);
    arreglo[j] = a * b;
    pila_apilar(pila,&arreglo[j]);
    return 0;
}


int division(pila_t* pila, int* arreglo,size_t j){
    if(pila_cantidad(pila) < 2){
        return -1;
    }
    int a ,b;
    a = *(int*)pila_desapilar(pila);
    b = *(int*)pila_desapilar(pila);
    if(b == 0){
        return -1;
    }
    arreglo[j] = a / b;
    pila_apilar(pila,&arreglo[j]);
    return 0;
}


int calculo_potencia(int a, int b){
    if(b == 0){
        return 1;
    }else if (b <= 1){
        return a;
    }else if ((b % 2) == 0){
        return calculo_potencia(a*a, b/2);
    }else{
        return a * calculo_potencia(a*a, (b-1)/2);
    }
    return -1;
}


int potencia(pila_t* pila, int* arreglo,size_t j){
    if(pila_cantidad(pila) < 2){
        return -1;
    }
    int a ,b;
    a = *(int*)pila_desapilar(pila);
    b = *(int*)pila_desapilar(pila);
    if(b < 0){
        return -1;
    }
    arreglo[j] = calculo_potencia(a,b);
    pila_apilar(pila,&arreglo[j]);
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
        return -1;
    }
    int a;
    a = *(int*)pila_desapilar(pila);
    if(a < 0){
        return -1;
    }
    arreglo[j] = calculo_raiz(a,0,a);
    pila_apilar(pila,&arreglo[j]);
    return 0;
}


int calculo_logartimo(int a, int b){
    if (a > (b-1)){
        return 1+calculo_logartimo(a/b,b);
    }
    return 0;
}


int logaritmo(pila_t* pila, int* arreglo,size_t j){
    if(pila_cantidad(pila) < 2){
        return -1;
    }
    int a ,b;
    a = *(int*)pila_desapilar(pila);
    b = *(int*)pila_desapilar(pila);
    if(b <= 1){
        return -1;
    }
    arreglo[j] = calculo_logartimo(a,b);
    pila_apilar(pila,&arreglo[j]);
    return 0;
}


int ternario(pila_t* pila, int* arreglo, size_t j){
    if(pila_cantidad(pila) < 3){
        return -1;
    }
    int a ,b, c;
    a = *(int*)pila_desapilar(pila);
    b = *(int*)pila_desapilar(pila);
    c = *(int*)pila_desapilar(pila);
    if (a == 0){
        arreglo[j] = c;
    }else{
        arreglo[j] = b;
    }
    pila_apilar(pila,&arreglo[j]);
    return 0;
}


bool ops (pila_t* pila, char* signo, char** operadores, int* arreglo, size_t j){
    size_t longitud = strlen(signo)-1;
    if(strncmp(operadores[0],signo,longitud) == 0){
        if (suma(pila,arreglo,j) == -1){
            return false;
        }
        return true;
    }else if(strncmp(operadores[1],signo,longitud) == 0){
        if (resta(pila,arreglo,j) == -1){
            return false;
        }
        return true;
    }else if(strncmp(operadores[2],signo,longitud) == 0){
        if(multiplicacion(pila,arreglo,j) == -1){
            return false;
        }
        return true;
    }else if(strncmp(operadores[3],signo,longitud) == 0){
        if(division(pila,arreglo,j) == -1){
            return false;
        }
        return true;
    }else if(longitud == 4 && strncmp(operadores[4],signo,longitud) == 0){
        if (raiz(pila,arreglo,j) == -1){
            return false;
        }
        return true;
    }else if(strncmp(operadores[5],signo,longitud) == 0){
        if (potencia(pila,arreglo,j) == -1){
            return false;
        }
        return true;
    }else if(strncmp(operadores[6],signo,longitud) == 0){
        if (ternario(pila,arreglo,j) == -1){
            return false;
        }
        return true;
    }else if(longitud == 3 && strncmp(operadores[7],signo,longitud) == 0){
        if (logaritmo(pila,arreglo,j) == -1){
            return false;
        }
        return true;
    }else{
        return false;
    }
}


bool calculadora_l(char** operadores, char* linea, size_t long_linea){
    pila_t* pila = pila_crear();
    if(pila == NULL){
        return false;
    }

    int* guarda_numeros = calloc(long_linea,sizeof(int));
    if (guarda_numeros == NULL){
        pila_destruir(pila);
        return false;
    }

    size_t tam = long_linea;
    int j = 0;
    char** entrada = split(linea,' ');
    bool error_stop = false;
    for(int i = 0; entrada[i] != NULL; i++){
        if (strcmp(entrada[i],"\0") != 0){
            if(isNumber(entrada[i])){
                guarda_numeros[j] = atoi(entrada[i]);
                pila_apilar(pila,&guarda_numeros[j]);
                j++;
            }else{
                if(ops(pila,entrada[i],operadores,guarda_numeros,j) == false){
                    error_stop = true;
                    break;
                }
                j++;
            }
            if(j == tam){
                if(redimensionar_arr(guarda_numeros,tam) == false){
                    error_stop = true;
                    break;
                }
                tam = tam*FACTOR_REDIMENSION;
            }
        }
    }
    if(pila_cantidad(pila) != 1){
        error_stop = true;
    }
    if(!error_stop){
        fprintf(stdout,"%d\n",*(int*)pila_desapilar(pila));
    }
    pila_destruir(pila);
    free(guarda_numeros);
    free_strv(entrada);
    return error_stop;
}


int calculadora_entrada(void){
    char** operators = split("+ - * / sqrt ^ ? log",' ');
    char *line_buffer = NULL;
    size_t line_buffer_size = 0;
    ssize_t line_size;
    line_size = getline(&line_buffer, &line_buffer_size, stdin);
    while(line_size > 1){
        if (calculadora_l(operators,line_buffer,line_buffer_size) == true){
            fprintf(stdout, "ERROR\n");
        }
        line_size = getline(&line_buffer, &line_buffer_size, stdin);
    }
    free(line_buffer);
    free_strv(operators);
    return 0;
}


int main(void){
    calculadora_entrada();
    return 0;
}
