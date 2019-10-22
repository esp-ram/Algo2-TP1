#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>


struct lista;
typedef struct lista lista_t;

typedef struct lista_iter lista_iter_t;


//// PRIMITIVAS DE LISTA ENLAZADA ////


// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* lista_crear(void);


// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void*));


// Devuelve verdadero si la lista no tiene elementos enlistados, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);


// Agrega un nuevo elemento al principio de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento al comienzo de la lista, se incrementa en
// uno la longitud de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);


// Agrega un nuevo elemento al final de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento al final de la lista, se incrementa en uno
// la longitud de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);


// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t *lista);


// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void* lista_ver_ultimo(const lista_t *lista);


// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void* lista_borrar_primero(lista_t *lista);


// Devuelve el largo de la lista. Se devuelve la cantidad de elementos que contiene la lista.
// Pre: la lista fue creada.
// Post: se devolvio el largo de la lista.
size_t lista_largo(const lista_t *lista);


//// PRIMITIVAS DE ITERADOR EXTERNO ////


// Crea un iterador de la lista que se pasa por parametro.
// Pre: la lista fue creada.
// Post: el iterador de la lista fue creado.
lista_iter_t *lista_iter_crear(lista_t *lista);


// El iterador avanza a la posicion siguiente, devuelve false si se encuentra en al final.
// Pre: tanto la lista como el iterador fueron creados.
// Post: el iterador avanzo al siguiente elemento de la lista (devolvio true) o devolvio false si ya se encuentra al final.
bool lista_iter_avanzar(lista_iter_t *iter);


// El iterador devuelve el  elemento actual.
// Pre: tanto la lista como el iterador fueron creados.
// Post: el iterador devolvio el elemento actual o NULL si se encuentra al final.
void *lista_iter_ver_actual(const lista_iter_t *iter);


// Indica con true o false si el iterador se encuentra al final.
// Pre: tanto la lista como el iterador fueron creados.
// Post: devuelve true si el iterador llego al final de la lista o false si todavia
// no esta en el final.
bool lista_iter_al_final(const lista_iter_t *iter);


// El iterador borra el elemento "actual" y se devuelve.
// Pre: tanto la lista como el iterador fueron creados.
// Post: se borra el elemento de la lista, se devuelve y la longitud de la lista
// disminuye en uno.
void *lista_iter_borrar(lista_iter_t *iter);


// Se inserta un elemento en la posicion actual del iterador.
// Pre: tanto la lista como el iterador fueron creados.
// Post: el elemento se inserto en la posicion del actual, la longitud de la lista
// se incrementa en uno.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);


// Se elimina el iterador.
// Pre: el iterador fue creado.
// Post: el iterador fue destruido
void lista_iter_destruir(lista_iter_t *iter);




//// PRIMITIVA DE ITERADOR INTERNO ////
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);





void pruebas_lista_alumno(void);



#endif // LISTA_H
