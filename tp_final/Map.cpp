#include "Common.h"
#include "Map.h"

typedef int Priority;
//DEFINICION DE ESTRUCTURAS--------------------------------------------------------------------------------
struct Node {
    Key clave;
    Value valor;
    Priority prioridad;
    Node* hijoIzq;
    Node* hijoDer;
};

struct MapRepr {
    ///INVARIANTE: la cantidad de nodos del arbol = el tam del arbol.
    ///INVARIANTE2: la rama izquierda del nodo raiz tiene claves mas pequeñas, la rama derecha tiene claves mas grandes
    ///INVARIANTE3: el nodo raiz siempre va a tener mayor prioridad que sus ramas.

    Node* raiz;
    int tam;
};

Priority randomPriority() {
    return rand();
}
//METODOS BASICOS--------------------------------------------------------------------------------------------
Map emptyM() {
    ///PROPOSITO: retorna un mapa vacio con tam 0

    MapRepr* map1 = new MapRepr;

    map1 -> raiz= NULL;
    map1 -> tam = 0;

    return map1;
}

int sizeM(Map m) {
    /// PROPOSITO: retorna el tamaño del mapa M

    return m -> tam;
}
//RELACIONADOS A lookUpM----------------------------------------------------------------------------------------
Node* nodoCorrespondiente(Node* n, Key k){

    if(k < n -> clave){
        return n -> hijoIzq;
    }else{
        return n -> hijoDer;
    }
}

bool lookupN(Node* n, Key k, Value& v) {
    /// PROPOSITO: busca un nodo con clave K en el arbol actual, en caso de haberlo completa la referencia V con el
    ///              valor del nodo.

    if(n == NULL) {

        return false;
    }
    if(n -> clave == k){

        v = n -> valor;
        return true;
    }else{

        return lookupN(nodoCorrespondiente(n,k), k, v);
    }

    /*if(k > n -> clave) {

        return lookupN(n -> hijoDer, k, v);
    }
    if(k < n -> clave) {

        return lookupN(n -> hijoIzq, k, v);
    }*/
}

bool lookupM(Map m, Key k, Value& v) {
    ///PROPOSITO: busca un nodo en el mapa M y retorna un booleano, en caso de haberlo completa la referencia v con el
    ///              valor del nodo

    return lookupN(m -> raiz,k,v);
}
//RELACIONADOS A insertM---------------------------------------------------------------------------------------------------
void intercambiarContenido(Node* n1, Node* n2){
    ///PRECONDICION: ninguno de los 2 puede ser null
    ///PROPOSITO: intercambia los contenidos de n1 y n2

     int tmpClave = n1 -> clave;
     int tmpValor = n1 -> valor;
     int tmpPrioridad = n1 -> prioridad;

     n1 -> clave = n2 -> clave;
     n1 -> valor = n2 -> valor;
     n1 -> prioridad = n2 -> prioridad;

     n2 -> clave = tmpClave;
     n2 -> valor = tmpValor;
     n2 -> prioridad = tmpPrioridad;
}

void balancearDerecha(Node* padre){
    ///PRECONDICION: ni el nodo padre nu rama derecha pueden estar en null
    ///PROPOSITO: si corresponde, balancea la rama derecha del nodo actual

    if(padre -> hijoDer -> prioridad > padre -> prioridad){

        Node* hijo = padre -> hijoDer;
        Node* x = padre -> hijoIzq;
        Node* y = hijo -> hijoIzq;
        Node* z = hijo -> hijoDer;

        intercambiarContenido(padre, hijo);

        padre -> hijoIzq = hijo;
        padre -> hijoDer = z;
        hijo -> hijoIzq = x;
        hijo -> hijoDer = y;
    }
}

void balancearIzquierda(Node* padre){
    ///PRECONDICION: ni el nodo padre ni su rama izquierda pueden estar en null
    ///PROPOSITO: si corresponde, balancea la rama izquierda del nodo actual

    if(padre -> hijoIzq -> prioridad > padre -> prioridad){

        Node* hijo = padre -> hijoIzq;
        Node* x = hijo -> hijoIzq;
        Node* y = hijo -> hijoDer;
        Node* z = padre -> hijoDer;

        intercambiarContenido(padre, hijo);

        padre -> hijoIzq = x;
        padre -> hijoDer = hijo;
        hijo -> hijoIzq = y;
        hijo -> hijoDer = z;
    }
}

Node* nodoNuevo(Key k, Value v){
    /// PROPOSITO: crea un nuevo nodo con la clave y el valor recibidos por parametros

    Node* n = new Node;
    n -> clave = k;
    n -> valor = v;
    n -> prioridad = randomPriority();
    n -> hijoDer = NULL;
    n -> hijoIzq = NULL;

    return n;
}

Node* insertN(Node* n, Key k, Value v, int& tam){
    ///PROPOSITO: inserta un nodo con clave K y valor V en el arbol actual y le suma 1 a la referenca TAM
    ///              , en caso de que la clave ya exista, solo modifica el valor.

    Node* res = n;

    if(n != NULL && k < n -> clave){

        res -> hijoIzq = insertN(res -> hijoIzq, k, v, tam);
        balancearIzquierda(res);

    }else if(n != NULL && k > n -> clave){

        res -> hijoDer = insertN(res -> hijoDer, k, v, tam);
        balancearDerecha(res);

    }else if(n != NULL){

        res -> valor = v;
    }else{

        tam++;
        res = nodoNuevo(k,v);
    }

    return res;
}

void insertM(Map m, Key k, Value v) {
    ///PROPOSITO: añade un nuevo nodo, con clave K y valor V, al mapa M

    m -> raiz = insertN(m -> raiz, k, v, m -> tam);
}

//RELACIONADOS A removeM-----------------------------------------------------------------------------------------------------
Node* borrarMinimo(Node* n, int& claveMin, int& valorMin){
    ///PROPOSITO: busca el nodo minimo del arbol actual, guarda sus valores en claveMin, valorMin y lo elimina

   if(n->hijoIzq==NULL){

        Node* temp= n->hijoDer;
        claveMin = n->clave;
        valorMin=n->valor;

        delete n;
        return temp;
    }else{

        n->hijoIzq=borrarMinimo(n->hijoIzq,claveMin,valorMin);
        return n;
    }
}

Node* removeRaizN(Node* n, int& tam){
    ///PRECONDICION: n != NULL
    ///PROPOSITO: elimina el nodo raiz N, del arbol

    tam--;
    Node* valorARetornar = n;
    if(n -> hijoDer == NULL){

        valorARetornar = n -> hijoIzq;
        delete n;
    }else{

        int claveMin;
        int valorMin;

        valorARetornar -> hijoDer = borrarMinimo(n -> hijoDer, claveMin, valorMin);

        valorARetornar -> clave = claveMin;
        valorARetornar -> valor = valorMin;
    }
    return valorARetornar;
}

Node* removeN(Node* n, Key k, int& tam){
    ///PROPOSITO: busca y elimina el nodo con clave K, del arbol que tiene como raiz el nodo N

    Node* nodoARetornar = n;
    if(n != NULL && k > n -> clave){

        nodoARetornar -> hijoDer = removeN(n -> hijoDer, k, tam);
    }else if(n != NULL && k < n -> clave){

        nodoARetornar -> hijoIzq = removeN(n -> hijoIzq, k, tam);
    }else if(n != NULL){

        nodoARetornar = removeRaizN(n, tam);
    }
    return nodoARetornar;
}

void removeM(Map m, Key k) {
    ///PROPOSITO eliminar un elemento con clave K del mapa

    m -> raiz = removeN(m -> raiz, k, m -> tam);
}

//RELACIONADOS A destroyM-------------------------------------------------------------------------------------------
void destroyM(Map m) {
    ///PROPOSITO: eliminar el mapa completamente

    /*if(m-> raiz != NULL){

        eliminarArbol(m -> raiz);
        delete m;
    }else{
        delete m;
    }*/

    while(m -> tam > 0){
        removeM(m, m -> raiz -> clave);
    }
    delete m;
}

//RELACIONADOS A mapSuccK---------------------------------------------------------------------------------
void sumarValorANodo(Node* n, int valorASumar){
    ///PRECONDICION: n != null
    ///PROPOSITO: le suma el valor dado al nodo dado

    n -> valor = n -> valor + valorASumar;
}

void mapSuccK(Key k, Node* n){
    ///PROPOSITO: le suma 1 al todos los nodos cuya clave sea menor o igual a la clave dada

    if(n != NULL){

        if(n -> clave > k){
            mapSuccK(k, n -> hijoIzq);
        }
        if(n -> clave == k){
            sumarValorANodo(n,1);
            mapSuccK(k, n -> hijoIzq);
        }
        if(n -> clave < k){
            sumarValorANodo(n,1);
            mapSuccK(k, n -> hijoIzq);
            mapSuccK(k, n -> hijoDer);
        }
    }

}
