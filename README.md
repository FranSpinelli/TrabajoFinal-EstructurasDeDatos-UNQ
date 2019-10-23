# TrabajoFinal-EstructurasDeDatos-UNQ

Nombre del proyecto: **Network**.    
Calificacion final: **8**.

***
## Introduccion:

Este trabajo consiste en implementar en C++ un tipo abstracto de dato(TAD) para describir y operar con redes de elementos. Una red de elementos es una estructura en la que los elementos pueden estar conectados entre sí. Por ejemplo, una red ferroviaria consta de estaciones conectadas por vías, mientras que una red de computadoras consta de servidores conectados por cables.  
En C++ una red se representará con un valor del tipo abstracto Network. Para poder implementar el tipo Network nos concentraremos primero en la implementación de dos tipos auxiliares: el tipo Stack, que sirve para manipular pilas de elementos, y el tipo Map, que sirve para manipular diccionarios, es decir, asociaciones entre claves y valores.

***

## Tipo Abstracto Stack:

El tipo Stack sirve para representar pilas de números enteros.

### Interfaz de Stack:

1. Stack emptyS() — Crea una pila vacía. Eﬁciencia: debe ser O(1).
2. void pushS(Stack s, int x) — Apila x en la pila. Eﬁciencia: si la pila se encuentra vacía, el costo de insertar n elementos debe ser O(n) en peor caso1. 
3. int sizeS(Stack s) — Devuelve el tamaño de la pila. Eﬁciencia: debe ser O(1). 
4. int topS(Stack s) — Devuelve el tope de la pila. Precondición: la pila no está vacía. Eﬁciencia: debe ser O(1).
5. void popS(Stack s) — Desapila el tope de la pila. Precondición: la pila no está vacía. Eﬁciencia: debe ser O(1).
6. void destroyS(Stack s) — Libera toda la memoria usada por la pila.

***

## Tipo Abstracto Map:

El tipo Map sirve para representar diccionarios, es decir asociaciones de claves a valores. En este TP, tanto las claves como los valores son números enteros. Por claridad deﬁnimos en el archivo Map.h los siguientes renombres de tipo, Key para el tipo de las claves y Value para el tipo de los valores:

typedef int Key;   
typedef int Value;

### Interfaz de Map:

La interfaz del diccionario se detalla a continuación. Al momento de expresar la complejidad de las operaciones, n representa la cantidad de elementos del diccionario. Las complejidades de inserción, búsqueda y borrado corresponden al caso promedio, de acuerdo con lo que se detalla en la implementación de Map: 

1. Map emptyM() — Crea un diccionario vacío. Eﬁciencia: debe ser O(1). 
2. int sizeM(Map m) — Devuelve el tamaño del diccionario, es decir, el número de claves distintas. Eﬁciencia: debe ser O(1). 
3. void insertM(Map m, Key k, Value v) — Inserta una clave k en el diccionario, y la asocia al valor v. Si la clave ya se encuentra deﬁnida, sobreescribe su valor. Eﬁciencia: debe ser O(logn) en caso promedio. 
4. bool lookupM(Map m, Key k, Value& v) — Si la clave k está deﬁnida en el diccionario, devuelve true y modiﬁca el valor del parámetro v para que sea el valor asociado a k. Si la clave no se encuentra deﬁnida en el diccionario, devuelve false. Eﬁciencia: debe ser O(logn) en caso promedio. 
5. void removeM(Map m, Key k) — Elimina la clave k del diccionario. Si la clave no se encuentra deﬁnida en el diccionario, esta operación no tiene ningún efecto. Eﬁciencia: debe ser O(logn) en caso promedio. 
6. void destroyM(Map m) — Libera toda la memoria usada por el diccionario.

### Implementacion de Map:

En este TP pedimos que el Map se represente sobre una estructura de datos conocida como treap. Un treap es un árbol binario, en el que cada nodo tiene una clave, un valor, una prioridad, y punteros a sus dos hijos. El invariante de un treap combina el invariante de orden en un árbol binario de búsqueda (BST) para las claves junto con el invariante de orden en un heap para las prioridades.
**La prioridad** de un nodo es un número que se elige “al azar” cada vez que se inserta un elemento en el treap. El objetivo de incorporar prioridades elegidas al azar es conseguir que el árbol quede balanceado. En la materia ya estudiamos el caso de los árboles AVL, que garantizan que el árbol queda siempre balanceado, pero con la desventaja de que los algoritmos de inserción y borrado son bastante complejos. En el caso de los treaps, los algoritmos de inserción y borrado son bastante más sencillos que en el caso de los AVLs. La desventaja de los treaps es que el balanceo puede depender de la suerte que uno haya tenido al elegir aleatoriamente las prioridades. Si uno tiene mala suerte, el árbol puede quedar muy desbalanceado. Se puede justiﬁcar, usando argumentos probabilísticos, que en promedio un treap de n nodos tendrá altura O(logn). En general uno debería tener muy mala suerte para que la altura treap sea peor que logarítmica. En este trabajo nos limitaremos a implementar un map sobre treap, sin estudiar con mayor profundidad su eﬁciencia

***

## Tipo Abstracto Network:

El tipo Network sirve para representar redes de elementos que pueden estar conectados. Los elementos de la red se identiﬁcan con un número que por claridad representamos con el siguiente tipo, ya deﬁnido en el archivo Network.h: 

typedef int Id;

### Interfaz de Network
La interfaz de la red de elementos se detalla a continuación.Una red de elementos permite hacer las siguientes operaciones: agregar un elemento, conectar directamente dos elementos, preguntar si dos elementos están conectados y deshacer una acción. Dos elementos están conectados si se puede llegar del uno al otro pasando por conexiones directas. 
Una característica importante de la red es que permite aplicar una acción undoN para deshacer la última acción.

1. Network emptyN() — Crea una red vacía. 
2. void addN(Network net, Id id) — Agrega un elemento a la red, con el identiﬁcador id. Precondición: el elemento no está en la red aún. 3. bool elemN(Network net, Id id) — Devuelve verdadero si el elemento está en la red. 
4. void connectN(Network net, Id id1, Id id2)—Establece una conexión directa entre dos elementos de la red.Si los elementos ya están conectados(ya sea directa o indirectamente),esta acción no tiene efecto. Precondición: id1 e id2 identiﬁcan a dos elementos de la red. 5. bool connectedN(Network net, Id id1, Id id2) — Devuelve verdadero si id1 e id2 identiﬁcan a dos elementos de la red que están conectados, ya sea directa o indirectamente. Precondición: id1 e id2 identiﬁcan a dos elementos de la red. 
6. void undoN(Network net) — Deshace la última acción, que puede consistir en agregar un elemento o en conectar dos elementos. Precondición: debe haber habido una última acción. 
7. void destroyN(Network net) — Libera toda la memoria usada por la red de elementos.

### Implementacion de Network:

Usaremos una variante simpliﬁcada de la estructura conocida como union–find. La estructura cuenta con dos campos: por un lado un map que representa la estructura de la red, y por otro lado una pila de números que guarda información para deshacer las acciones.
Los elementos de la red están dados por las claves del diccionario flechas. El diccionario flechas representa “ﬂechas” entre elementos. De cada elemento sale exactamente una ﬂecha, pero a un elemento pueden llegar ninguna, una, o más ﬂechas. 

