#define _XOPEN_SOURCE 700 // or any bigger number
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


int calculadora(void){
    pila_t* pila = pila_crear();
    if(pila == NULL){
        return 0;
    }
    printf("post pila\n");
    char** operators = split("+ - * / sqrt ^ ? log",' ');
    char *line_buffer = NULL;
    size_t line_buffer_size = 0;
    getline(&line_buffer, &line_buffer_size, stdin);
    char** entrada = split(line_buffer,' ');

    char a;
    char b;
    int aa;
    int bb;

    for(int i = 0; entrada[i] != NULL; i++){
        if(isNumber(entrada[i])){
            //printf("%ls\n",entrada[i]);
            pila_apilar(pila,entrada[i]);
            printf("apila numero\n");
        }else{
            printf("es operador\n");
            //
            // TODO: desapilar numeros dependiendo de la operacion.
            //
            switch ((int)*(char*)entrada[i]) {
                case '+':
                    a = *(char*)pila_desapilar(pila);
                    b = *(char*)pila_desapilar(pila);
                    aa = a -'0';
                    bb = b -'0';
                    printf("suma d1 %d, d2 %d\n",aa,bb);
                    printf("%d\n",aa+bb);
                    break;
                case '-':
                    printf("resta\n");
                    break;
                case '*':
                    printf("multipl\n");
                    break;
                case '/':
                    printf("div\n");
                case '^':
                    printf("pot\n");
                    break;
                case '?':
                    printf("ternario\n");
                    break;
                /*
                case 'sqrt':
                    printf("raiz\n");
                    break;
                case 'log':
                    printf("log\n");
                    break;
                */
            }
        }
    }
    free_strv(operators);
    free(line_buffer);
    printf("salida\n");
    return 0;
}



int main(void){
    calculadora();
    return 0;
}
