#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char* substr(const char* str, size_t n){
    char* nuevo_string = malloc(sizeof(char) * n+1);
    if (nuevo_string == NULL){
        return NULL;
    }
    strncpy(nuevo_string,str,n);
    nuevo_string[n] = '\0';
    return nuevo_string;
}


char* asignar_str(const char* str, int inicio, int final){
    char* temporal = substr(str+inicio,final-inicio);
    if (temporal == NULL){
        return NULL;
    }
    return temporal;
}


char **split(const char *str, char sep){
    int count = 0;
    for(int i = 0; str[i] != '\0'; i++){
        if (str[i] == sep){
            count += 1;
        }
    }

    char **strv = malloc(sizeof(char*) * (count+2));
    if (strv == NULL){
        return NULL;
    }

    int inicio = 0;
    int fin = 0;
    int posicion = 0;
    for(int j = 0; j < strlen(str);j++){
        if (str[j] != sep){
            fin++;
        }else{
            strv[posicion] = asignar_str(str,inicio,fin);
            posicion++;
            fin++;
            inicio = fin;
        }
    }
    strv[posicion] = asignar_str(str,inicio,fin);
    strv[posicion+1] = NULL;
    return strv;
}


char *join(char **strv, char sep){
    if(strv[0] == NULL){
        char* cadena_vacia = calloc(1,sizeof(char));
        if(!cadena_vacia){
            return NULL;
        }
        strcpy(cadena_vacia,"");
        return cadena_vacia;
    }

    char chequeo_separador[1];
    *chequeo_separador = sep;
    int separador_nulo = strcmp(chequeo_separador,"\0");
    int count = 0;
    size_t letras = 0;

    while (strv[count] != NULL){
        letras += strlen(strv[count]);
        count++;
    }

    if (separador_nulo == 0) letras -= (count-1);

    char* cadena_unida = calloc((letras+count),sizeof(char));
    if (cadena_unida == NULL){
        return NULL;
    }
    char* cadena_devolver = &cadena_unida[0];

    for(int i = 0; i<count;i++){
        letras = 0;
        size_t cantidad = strlen(strv[i]);
        strcpy(cadena_unida,strv[i]);
        if(separador_nulo != 0 && i<count-1){
            *(cadena_unida+cantidad) = sep;
            letras += 1;
        }
        letras += cantidad;
        cadena_unida+=letras;
    }
    return cadena_devolver;
}


void free_strv(char *strv[]){
	size_t cantidad = 0;
	while(strv[cantidad] != NULL){
		free(strv[cantidad]);
		cantidad += 1;
	}
	free(strv);
}
