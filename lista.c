#include "lista.h"
#include <stdlib.h>



typedef struct nodo {
    void* dato;
    struct nodo* proximo;
} nodo_t;

struct lista{
    nodo_t* primero;
    nodo_t* ultimo;
    size_t largo;
};


struct lista_iter{
    lista_t* lista;
    nodo_t* actual;
    nodo_t* anterior;
};


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


nodo_t* nodo_crear(void* valor){
    nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
    if (nodo_nuevo == NULL){
        return NULL;
    }
    nodo_nuevo->dato = valor;
    nodo_nuevo->proximo = NULL;
    return nodo_nuevo;
}


lista_t* lista_crear(void){
    lista_t* lista_nueva = malloc(sizeof(lista_t));
    if (lista_nueva == NULL){
        return NULL;
    }
    lista_nueva->primero = NULL;
    lista_nueva->ultimo = NULL;
    lista_nueva->largo = 0;
    return lista_nueva;
}


bool lista_esta_vacia(const lista_t* lista){
    return(lista->primero == NULL);
}


bool lista_insertar_ultimo(lista_t* lista, void* dato){
    nodo_t* nodo_agregar = nodo_crear(dato);
    if (nodo_agregar == NULL){
        return false;
    }
    if (lista_esta_vacia(lista)){
        lista->primero = nodo_agregar;
    }else{
        lista->ultimo->proximo = nodo_agregar;
    }
    lista->ultimo = nodo_agregar;
    lista->largo += 1;
    return true;
}


bool lista_insertar_primero(lista_t* lista, void* dato){
    nodo_t* nodo_agregar = nodo_crear(dato);
    if (nodo_agregar == NULL){
        return false;
    }
    if (lista_esta_vacia(lista)){
        lista->ultimo = nodo_agregar;
    }else{
        nodo_agregar->proximo = lista->primero;
    }
    lista->primero = nodo_agregar;
    lista->largo += 1;
    return true;
}


void* lista_ver_primero(const lista_t* lista){
    return lista_esta_vacia(lista) ? NULL : lista->primero->dato;
}

void* lista_ver_ultimo(const lista_t* lista){
    return lista_esta_vacia(lista) ? NULL : lista->ultimo->dato;
}

size_t lista_largo (const lista_t* lista){
    return (lista->largo);
}


void* lista_borrar_primero(lista_t* lista){
    if (lista_esta_vacia(lista)){
        return NULL;
    }
    void* dato_devolver = lista_ver_primero(lista);
    nodo_t* nodo_borrar = lista->primero;
    lista->primero = lista->primero->proximo;
    free(nodo_borrar);
    lista->largo -= 1;
    if (lista_esta_vacia(lista)){
        lista->ultimo = NULL;
    }
    return(dato_devolver);
}

void lista_destruir(lista_t* lista, void destruir_dato(void*)){
    while(!lista_esta_vacia(lista)){
        void* dato_eliminar = lista_borrar_primero(lista);
        if (destruir_dato != NULL){
            destruir_dato(dato_eliminar);
        }
    }
    free(lista);
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////




lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t* nuevo = malloc(sizeof(lista_iter_t));
    if (nuevo == NULL){
        return NULL;
    }
    nuevo->lista = lista;
    nuevo->actual = lista->primero;
    nuevo->anterior = NULL;
    return nuevo;
}


bool lista_iter_avanzar(lista_iter_t *iter){
    if (iter->actual == NULL){
        return false;
    }
    iter->anterior = iter->actual;
    iter->actual = iter->actual->proximo;
    return true;
}


void *lista_iter_ver_actual(const lista_iter_t *iter){
    if (iter->actual != NULL){
        return (iter->actual->dato);
    }
    return NULL;
}


bool lista_iter_al_final(const lista_iter_t *iter){
    return (iter->actual == NULL);
}


void *lista_iter_borrar(lista_iter_t *iter){
    if (iter->actual == NULL){
        return NULL;
    }
    void* dato_devolver = iter->actual->dato;
    nodo_t* nodo_a_borrar = iter->actual;
    if (iter->anterior == NULL && iter->actual->proximo == NULL){
        iter->lista->primero = NULL;
        iter->lista->ultimo = NULL;
    }else if (iter->anterior == NULL){
        iter->lista->primero = iter->actual->proximo;
    }else if (iter->actual->proximo == NULL){
        iter->anterior->proximo = iter->actual->proximo;
        iter->lista->ultimo = iter->anterior;
    }else{
        iter->anterior->proximo = iter->actual->proximo;
    }
    iter->actual = iter->actual->proximo;
    iter->lista->largo -= 1;
    free(nodo_a_borrar);
    return dato_devolver;
}


bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    nodo_t* a_insertar = nodo_crear(dato);
    if (a_insertar == NULL){
        return false;
    }
    if (iter->anterior == NULL && iter->actual == NULL){
        iter->lista->primero = a_insertar;
        iter->lista->ultimo = a_insertar;
    }else if (iter->anterior == NULL){
        a_insertar->proximo = iter->actual;
        iter->lista->primero = a_insertar;
    }else if (iter->actual == NULL){
        a_insertar->proximo = NULL;
        iter->anterior->proximo = a_insertar;
        iter->lista->ultimo = a_insertar;
    }else{
        iter->anterior->proximo = a_insertar;
        a_insertar->proximo = iter->actual;
    }
    iter->actual = a_insertar;
    iter->lista->largo += 1;
    return true;
}


void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    nodo_t* nodo_actual = lista->primero;
    while ((nodo_actual != NULL) && (visitar(nodo_actual->dato,extra))){
        nodo_actual = nodo_actual->proximo;
    }
}
