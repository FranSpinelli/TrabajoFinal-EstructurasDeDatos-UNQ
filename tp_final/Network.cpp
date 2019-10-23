#include "Common.h"
#include "Network.h"
#include "Map.h"
#include "Stack.h"


struct NetworkRepr {
    ///INVARIANTE: la cantidad de elementos del stack es como minimo la cantidad de elementos del
    ///             map, y como maximo el doble de la cantidad de elementos del map -1.

    Map flechas;
    Stack acciones;
};
//RELACIONADO A emptyN-----------------------------------------------------------------------------------------------
Network emptyN() {
    ///PROPOSITO: crea una net vacia

    NetworkRepr* net = new NetworkRepr;

    net -> flechas  = emptyM();
    net -> acciones = emptyS();

    return net;
}
//RELACIONADO A emptyS-----------------------------------------------------------------------------------------------
void addN(Network net, Id id) {
    ///PROPOSITO: agrega un elemento con esa id a la net
    ///PRECONDICION: no hay ningun elemento con esa id en la net
    insertM(net -> flechas, id, id);
    pushS(net -> acciones, id);
}
//RELACIONADO A elemN----------------------------------------------------------------------------
bool elemN(Network net, Id id) {
    ///PROPOSITO: dice si un elemento esta en la network o no

    Value v;
    return lookupM(net -> flechas, id, v);
}
//RELACIONADOS A connectedN----------------------------------------------------------------------
int representante(Network net, Id id){
    ///PRECONDICION: la id dada se debe corresponder a un elemento de la net
    ///PROPOSITO: busca el ultimo elemento de la conexion
    int representante;

    lookupM(net -> flechas, id, representante);
    while(id != representante){

        id = representante;
        lookupM(net -> flechas, id, representante);
    }
    return representante;
}

bool connectedN(Network net, Id id1, Id id2) {
    ///PROPOSITO: dice si dos elemetos de la red estan conectados entre si.
    ///PRECONDICION: las 2 id provistas se corresponden a 2 elementos existentes en la net

    return representante(net, id1) == representante(net, id2);
}
//RELACIONADOS A connectN-----------------------------------------------------------------------
void connectN(Network net, Id id1, Id id2) {
    ///PRECONDICION: las 2 id provistas se corresponden a 2 elementos existentes en la net
    ///PROPOSITO: dados dos nodos, los conecta ya sea directa o indirectamente segun corresponda

    int representanteDeid1 = representante(net,id1);
    int representanteDeid2 = representante(net,id2);

    if(!connectedN(net,id1,id2)){

        insertM(net -> flechas, representanteDeid1, representanteDeid2);
        pushS(net -> acciones, representanteDeid1);
    }
}
//RELACIONADOS A undoN---------------------------------------------------------------------------
bool estaConectadoAAlgo(Network net, Id id){



    return representante(net, id) == id;
}

void undoN(Network net) {
    ///PRECONDICION: se debe haber realizado alguna accion sobre la net
    ///PROPOSITO: deshace la ultima accion realizada

    int elementoDeTopeDeLaPila = topS(net -> acciones);

    if(estaConectadoAAlgo(net, elementoDeTopeDeLaPila)){

        removeM(net -> flechas, elementoDeTopeDeLaPila);
        popS(net -> acciones);
    }else{

        insertM(net -> flechas, elementoDeTopeDeLaPila, elementoDeTopeDeLaPila);
        popS(net -> acciones);
    }
}
//RELACIONADO A destroyN------------------------------------------------------------------------
void destroyN(Network net) {
    ///PROPOSITO: destruye la network

    destroyM(net -> flechas);
    destroyS(net -> acciones);

    delete net;
}
