#define _XOPEN_SOURCE 700 // or any bigger number
#include <stdio.h>
#include <stdlib.h>
#include "strutil.h"
#include "lista.h"
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


bool comprobacion(char* linea_leida, char* buscada){
    char** contenido = split(linea_leida, ' ');
    for(size_t i = 0; contenido[i] != NULL; i++){
        if (contenido[i] != NULL && strlen(contenido[i]) >= strlen(buscada) && strstr(contenido[i], buscada) != NULL){
            free_strv(contenido);
            return true;
        }
    }
    free_strv(contenido);
    return false;
}


void agregar_linea(char* linea, lista_t* lista, size_t n){
    char* add_line;
    add_line = malloc(sizeof(char) * strlen(linea)+1);
    strcpy(add_line,linea);
    lista_insertar_ultimo(lista,add_line);
    if(lista_largo(lista) > (size_t)(n+1)){
        free(lista_borrar_primero(lista));
    }
}

void mostrar_anteriores(lista_t* lista){
    while(!lista_esta_vacia(lista)){
        void* linea_print = lista_borrar_primero(lista);
        fprintf(stdout, "%s", (char*)linea_print);
        free(linea_print);
    }
}


void desde_entrada(char* palabra, size_t n){
    lista_t* lista_lineas = lista_crear();
    if(n != 0){
        lista_destruir(lista_lineas);
    }
    char *line_buffer = NULL;
    size_t line_buffer_size = 0;
    ssize_t line_size;
    line_size = getline(&line_buffer, &line_buffer_size, stdin);
    while(line_size > 1){
        if(n != 0){
            agregar_linea(line_buffer,lista_lineas,n);
            if(comprobacion(line_buffer, palabra)){
                fprintf(stdout, "\ncoincidencia encontrada\n");
                mostrar_anteriores(lista_lineas);
            }
        }else{
            if(comprobacion(line_buffer, palabra)){
                fprintf(stdout, "\ncoincidencia encontrada: %s\n", line_buffer);
            }
        }
        line_size = getline(&line_buffer, &line_buffer_size, stdin);
    }
    free(line_buffer);
    line_buffer = NULL;
    if(n != 0){
        lista_destruir(lista_lineas,free);
    }
}


void desde_archivo(char* palabra, size_t n, char* archivo){
    lista_t* lista_lineas = lista_crear();
    if(n != 0){
        lista_destruir(lista_lineas);
    }
    char *line_buffer = NULL;
    size_t line_buffer_size = 0;
    ssize_t line_size;
    FILE *fp = fopen(archivo, "r");
    line_size = getline(&line_buffer, &line_buffer_size, fp);
    while(line_size >= 0){
        if(n != 0){
            agregar_linea(line_buffer,lista_lineas,n);
            if(comprobacion(line_buffer, palabra)){
                fprintf(stdout, "\ncoincidencia encontrada\n");
                mostrar_anteriores(lista_lineas);
            }
        }else{
            if(comprobacion(line_buffer, palabra)){
                fprintf(stdout, "%s\n", line_buffer);
            }
        }
        line_size = getline(&line_buffer, &line_buffer_size, fp);
    }
    free(line_buffer);
    line_buffer = NULL;
    fclose(fp);
    if(n != 0){
        lista_destruir(lista_lineas,free);
    }
}



int main(int argc, char* argv[]){
    if (argc < 3) {
        fprintf(stderr, "%s\n","Cantidad erronea de parametros");
        return 0;
    } else if (argc == 3) {
        printf("caso == 3\n");
        if(!isNumber(argv[2]) || atoi(argv[2]) < 0){
            fprintf(stderr,"%s\n","no es un numero");
            return 0;
        }
        desde_entrada(argv[1],atoi(argv[2]));
        return 0;
    }else if (argc == 4){
        printf("caso == 4\n");
        printf("%d\n",atoi(argv[2]));
        if(!isNumber(argv[2])){
            fprintf(stderr,"%s\n","no es un numero");
            return 0;
        }
        if(access(argv[3], R_OK ) == -1 ) {
            fprintf(stderr, "%s\n","No se pudo leer el archivo indicado");
            return 0;
        }
        desde_archivo(argv[1],atoi(argv[2]),argv[3]);
        return 0;
    }else{
        fprintf(stderr, "%s\n","Cantidad erronea de parametros");
        return 0;
    }
}
