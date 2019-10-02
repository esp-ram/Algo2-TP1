#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/*
//malloc tamaño n o maximo de str ?
char *substr(const char *str, size_t n){
    char* nuevo_string = malloc(sizeof(char) * n+1);
    if (nuevo_string == NULL){
        return NULL;
    }
    size_t count = 0;
    while (count < n){
        if (count <= strlen(str)){
            nuevo_string[count] = str[count];
        }else{
            nuevo_string[count] = '\0';
        }
        count += 1;
    }
    return nuevo_string;
}
*/



char* substr(const char* str, size_t n){
    char* nuevo_string = malloc(sizeof(char) * n+1);
    if (nuevo_string == NULL){
        return NULL;
    }
    strncpy(nuevo_string,str,n);
    nuevo_string[n] = '\0';
    return nuevo_string;
}




char **split(const char *str, char sep){
    int count = 0;
    size_t i = 0;
    while (str[i] != '\0'){
        if (str[i] == sep){
            count += 1;
        }
        i++;
    }
    char **strv = malloc(sizeof(char*) * (count+2));
    if (strv == NULL){
        return NULL;
    }
    i=0;
    int inicio = 0;
    int fin = 0;
    int posicion = 0;
    while(str[i] != '\0'){
        if (str[i] != sep){
            fin++;
            i++;
        }else{
            char* temporal = substr(str+inicio,fin-inicio);
            if (temporal == NULL){
                return NULL;
            }
            strv[posicion] = temporal;
            posicion++;
            inicio = fin+1;
            fin++;
            i++;
        }
    }
    char* temporal = substr(str+inicio,fin-inicio);
    if (temporal == NULL){
        return NULL;
    }
    strv[posicion] = temporal;
    strv[posicion+1] = NULL;
    return strv;
}



char *join(char **strv, char sep){
    int count = 0;
    size_t letras = 0;
    while (strv[count] != NULL){
        letras += strlen(strv[count]);
        count++;
    }
    char* cadena_unida = malloc(sizeof(char) * (letras+count));
    //char* cadena_unida = calloc((letras+count),sizeof(char));
    if (cadena_unida == NULL){
        return NULL;
    }
    letras = 0;
    cadena_unida[0] = '\0';
    for (int i = 0; i<count;i++){
        size_t cantidad = strlen(strv[i]);
        strcat(cadena_unida,strv[i]);
        printf("%d\n",i);
        letras += cantidad;
        if (i != count-1){
            //NULL;
            cadena_unida[letras] = sep;
            letras++;
            cadena_unida[letras] = '\0';
            //strcpy(cadena_unida,sep);
        }
    }
    return cadena_unida;
}
