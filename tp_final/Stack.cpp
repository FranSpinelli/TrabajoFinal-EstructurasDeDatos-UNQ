#include "Common.h"
#include "Stack.h"
#include <cstddef>

struct Nodo {

    int valor;
    Nodo* siguiente;
};

struct StackRepr {

    int tam ;
    Nodo * tope;
};
//RELACIONADO A emptyS----------------------------------------------------------------------------------------------------------------
Stack emptyS() {
    /// PROPOSITO: retornta un stack vacio con tam 0

    StackRepr*stack1 = new StackRepr;

    stack1 -> tam = 0;
    stack1 -> tope = NULL;

    return stack1;
}
//RELACIONADO A sizeS-------------------------------------------------------------------------------------------------------------------
int sizeS(Stack s) {
    /// PROPOSITO: retorna el tamaño del stack

    return s -> tam;
}
//RELACIONADO A pushS-------------------------------------------------------------------------------------------------------------------
void pushS(Stack s, int x) {
    ///PROPOSITO: agrega un nodo a la pila

    Nodo * nuevoNodo = new Nodo;

    nuevoNodo -> valor = x;
    nuevoNodo -> siguiente = s -> tope;

    s -> tam = s -> tam + 1;
    s -> tope = nuevoNodo;
}
//RELACIONADO A topS----------------------------------------------------------------------------------------------------------------------
int topS(Stack s) {
    /// PROPOSITO: retorna el valor del primer nodo de la pila
    ///PRECONDICION: la pila debe tener al menos 1 nodo.

    Nodo* primerNodo = s -> tope;
    return primerNodo -> valor;
}
//RELACIONADO A popS----------------------------------------------------------------------------------------------------------------------
void popS(Stack s) {
    /// PROPOSITO: saca el elemento tope de la pila
    /// PRECONDICION: la pila no esta vacia.

    Nodo* primerNodo = s -> tope;
    s -> tope = primerNodo -> siguiente;
    s -> tam = s -> tam - 1;
    delete primerNodo;
}

void destroyS(Stack s) {
    ///PROPOSITO: destruye el stack

    while(s -> tope != NULL){
        popS(s);
    }
    delete s;
}
