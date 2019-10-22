#define _XOPEN_SOURCE 700 // or any bigger number
#include <stdio.h>
#include <stdlib.h>
#include "strutil.h"
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define ANSI_COLOR_LGH_RED	   "\x1b[1m\x1b[31m"
#define ANSI_COLOR_LGH_GREEN   "\x1b[1m\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define LONG_ANSI 23


bool isNumber(char number[]){
    int i = 0;
    if (number[0] == '-') i = 1;
    for (; number[i] != 0; i++){
        if (!isdigit(number[i])) return false;
    }
    return true;
}


void desde_entrada(char* palabra, size_t n){
    char* linea = NULL;
    size_t capacidad = 0;
    ssize_t leidos = getline(&linea, &capacidad, stdin);
    printf("%s, chars=%06zd\n", linea, leidos);
    free(linea);
}

/*
void desde_archivo(char* palabra, size_t n ,char* archivo){
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;
    char *ret;
    FILE *fp = fopen(archivo, "r");
    line_size = getline(&line_buf, &line_buf_size, fp);
    while (line_size >= 0){
        //printf("line: chars=%06zd, buf size=%06zu, contenido: %s", line_size, line_buf_size, line_buf);
        char** contenido = split(line_buf, ' ');
        for(size_t i = 0; contenido[i] != NULL; i++){
            if (contenido[i] != NULL && strlen(contenido[i]) >= strlen(palabra)){
                ret = strstr(contenido[i], palabra);
                if(ret != NULL){
                    char* modif_str = calloc(LONG_ANSI + strlen(palabra),sizeof(char));
                    strcat(modif_str,substr(contenido[i],strlen(contenido[i])-strlen(ret)));
                    strcat(modif_str,ANSI_COLOR_LGH_RED);
                    strcat(modif_str,substr(ret,strlen(palabra)));
                    strcat(modif_str,ANSI_COLOR_RESET);
                    strcat(modif_str,(ret+strlen(palabra)));
                    free(contenido[i]);
                    contenido[i]=modif_str;
                }
            }
        }
        char* resultado = join(contenido,' ');
        free_strv(contenido);
        fprintf(stdout,"%s\n", resultado);
        free(resultado);
        line_size = getline(&line_buf, &line_buf_size, fp);
    }
    free(line_buf);
    line_buf = NULL;
    fclose(fp);
}
*/


void comprobacion(char* linea_leida, char* buscada){
    char** contenido = split(linea_leida, ' ');
    for(size_t i = 0; contenido[i] != NULL; i++){
        if (contenido[i] != NULL && strlen(contenido[i]) >= strlen(buscada) && strstr(contenido[i], buscada) != NULL){
            fprintf(stdout,"%s\n", linea_leida);
            break;
        }
    }
    free_strv(contenido);
}


void desde_archivo_1(char* palabra, size_t n ,char* archivo){
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;
    FILE *fp = fopen(archivo, "r");
    line_size = getline(&line_buf, &line_buf_size, fp);
    while (line_size >= 0){
        comprobacion(line_buf, palabra);
        line_size = getline(&line_buf, &line_buf_size, fp);
    }
    free(line_buf);
    line_buf = NULL;
    fclose(fp);
}



int main(int argc, char* argv[]){
    if (argc < 3) {
        fprintf(stderr, "%s\n","Cantidad erronea de parametros");
        return 0;
    } else if (argc == 3) {
        printf("caso == 3\n");
        if(!isNumber(argv[2]) || argv[2] < 0){
            fprintf(stderr,"%s\n","no es un numero");
            return 0;
        }
        desde_entrada(argv[1],(size_t)argv[2]);
        return 0;
    }else if (argc == 4){
        printf("caso == 4\n");
        if(!isNumber(argv[2])){
            fprintf(stderr,"%s\n","no es un numero");
            return 0;
        }
        if(access(argv[3], R_OK ) == -1 ) {
            fprintf(stderr, "%s\n","No se pudo leer el archivo indicado");
            return 0;
        }
        desde_archivo_1(argv[1],(size_t)argv[2],argv[3]);
        return 0;
    }else{
        fprintf(stderr, "%s\n","Cantidad erronea de parametros");
        return 0;
    }


}
