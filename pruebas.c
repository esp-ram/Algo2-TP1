#include "strutil.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void joi(){
    char** cont = split(",", ',');
    char* ret = join(cont,',');
    printf("%s\n",ret);
    free(cont[0]);
    free(cont[1]);
    free(cont[2]);
    free(cont);
    free(ret);
}

void spl(){
    char** cont = split("abc,def,ghi", ',');
    printf("%c\n",*(char*)cont[0]);
    printf("%c\n",*(char*)cont[1]);
    printf("%ld\n",strlen(cont[2]));
    printf("%d\n", cont[3] == NULL);
    //printf("%s\n",cont[3]);
    free(cont[0]);
    free(cont[1]);
    free(cont[2]);
    free(cont);
}



void sub(){
    //const char* ejemplo = "Ejemplo";
    char* test = substr("abc,def,ghi"+4,3);
    printf("%s\n",test);
    free(test);
}

int main(){
    //sub();
    //spl();
    joi();
    return 0;
}
