# CC232 - Evaluación Parcial 1 -  Versión B
#### Nombre: Rydell Jonel Mosquera Huayhua | Código: 20232690K

#### Pregunta 1
Un editor de texto simplificado expone el ADT CursorBuffer:
```cpp
class CursorBuffer {
public:
    void insert(char c);     // insertar en la posición del cursor
    char erase();            // elimina el caracter bajo el cursor
    void moveLeft();        // mover el cursor a la izquierda
    void moveRight();       // mover el cursor a la derecha
    char curent() const;    // retorna el caracter bajo el cursor 
    int size() const;       // retorna el número de caracteres en el buffer
};
```
Se propone dos representaciones: A: un arreglo dinámico con índice del cursos; B: una lista doblemente enlazada con nodo centinela y un puntero al nodo del cursor
##### a) Identifique con precisión qué especifica el ADT y qué queda abierto a la implementación.
El ADT (CursorBuffer) solo te dice "qué" hace la estructura: su interfaz pública como insert, erase, o current. Queda abierto el "cómo" se implementa por debajo, es decir, si se usa memoria contigua (arreglos) o nodos enlazados, y cómo maneja sus punteros o índices
##### b) Compare el costo de insert, erase, moveLeft, moveRight y current para A y B. Justifique cada entrada de la tabla.
- insert/erase: En A (arreglo) es `O(n)` porque hay que desplazar todos los elementos que están a la derecha del cursor. En B (lista doble) es `O(1)` porque solo actualizas los punteros prev/next del nodo local
- move/current: Es `O(1)` en ambas. En A solo sumas/restas al índice cursor_index. En B solo avanzas con cursor = cursor->next o prev
##### c) Indique dos invariantes de representación para cada alternativa. 
- A: El índice válido debe ser 0 <= cursor_index <= _size y _size <= _capacity
- B: El puntero dummy nunca puede ser null y cursor siempre debe apuntar a un nodo válido del anillo
##### d) Si el patrón de uso tiene muchas ediciones locales alrededor del cursos y pocas consultas por índice, elije una representación y defienda la elección. 
Elegiría la B. Si el patrón es de muchas ediciones locales, me conviene aprovechar el `O(1)` de inserción/borrado. Usar el arreglo me penalizaría con un costo `O(n)` por cada tecla que aprete el usuario, por culpa de los desplazamiento
##### e) Explique un caso borde que puede romper cada implementación si no maneja explicacionadamente. 
En A, un caso borde es intentar hacer insert cuando _size == _capacity y que el código no llame a expand(), causando desbordamiento. En B, hacer erase cuando la lista está vacía (o sea, cuando cursor apunta al nodo dummy); borraríamos el centinela por error rompiendo toda la estructura
#### Pregunta 2
Considere el algoritmo de Euclides:
```cpp
int gcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}
```
##### a) Trace gcd(252, 105) mostando a, b y r.
Iteración 1: a=252, b=105, r=42
Iteración 2: a=105, b=42, r=21
Iteración 3: a=42, b=21, r=0
Iteración 4: a=21, b=0 (termina el while). Retorna 21
##### b) Justifique la correctitud usando la propiedad gcd(a, b) = gcd(b, a mód b). Debe explicar cómo se conserva el valor buscado. 
La correctitud se da porque cualquier divisor común que tengan a y b, también dividirá exactamente a su residuo r. Entonces, reemplazar (a, b) por (b, r) reduce el tamaño del problema pero conserva el mismo máximo común divisor intacto hasta llegar al caso base
##### c) Justifique terminación 
Como en cada vuelta sacas el módulo, el residuo r siempre es estrictamente menor que b. Dado que b disminuye de forma estricta en cada iteración y son números enteros positivos, obligatoriamente b va a llegar a 0, haciendo que el bucle while(b != 0) termine sí o sí
##### d) Indique precondiciones rezonables para evitar ambigüedades con errores negativos o ambos argumentos cero. 
a >= 0, b >= 0, y que a + b > 0. Esto último evita el caso gcd(0, 0) que matemáticamente no está definido
##### e) Compare con un algoritmo que prueba todos los divisores desde mín(a, b) hacia abajo. Analice costo y explique por qué pasar pruebas pequeñas no demuesrta eficiencia.
El algoritmo ingenuo de probar hacia abajo cuesta `O(min(a, b))`. Euclides cuesta `O(log(min(a, b)))`. Pasar pruebas con números pequeños (ej. 10 y 15) no demuestra eficiencia porque hasta el código más ineficiente corre rápido con 10 iteraciones. La diferencia real se nota cuando metes números de miles de millones
#### Pregunta 3
Un `DengVector` mantiene `_elem`, `_size` y `_capacity`. En `insert(i, x)`, si hay capacidad, desplaza a la derecha los elementos en posiciones `i, i+1, ..., size-1`. Si no hay capacidad, primero duplica la capacidad y copia los elementos.
##### a) Para `_size = 5, capacity = 6`, calcule el costo de insert (0,x), insert (3,x) y insert (7,x) sin redimensionamiento. Justifique en términos de desplazamientos.
- insert(0, x): Cuesta `O(n)` porque debo desplazar los 5 elementos actuales a la derecha.
- insert(3, x): Cuesta `O(n)` porque debo desplazar 2 elementos (los de la pos 3 y 4)
- insert(7, x): Esto lanza un error de "out of bounds". Si tengo _size=5, el máximo índice válido para insertar es el 5
##### b) Repita para `_size = 6, capacity = 7`, considerando el costo de copiar al nuevo arreglo y luego desplazar. No olvide la escritura de x.
Al estar lleno, primero hace falta copiar todos los elementos al nuevo arreglo (costo `O(n)`).
- insert(0, x): `O(n)` de la copia inicial + `O(n)` del desplazamiento + `O(1)` por escribir x. Total: `O(n)`
- insert(3, x): Igual, `O(n)` de la copia inicial + `O(n)` desplazar + `O(1)`. Total: `O(n)`
- insert(7, x): Inválido. Si fuera al final (índice 6), costaría `O(n)` solo por la copia al nuevo arreglo, sin desplazamientos
##### c) Explique por qué pushBack puede ser amortizado $\mathcal{O}(1)$, pero insert $(\theta,x)$ no lo es bajo la misma representación.
pushBack se puede amortizar a ``O(1)`` porque casi siempre es ``O(1)`` y el costo pesado ``O(n)`` solo ocurre rara vez al duplicar capacidad. `insert(0,x)` no, porque no importa si tienes capacidad de sobra, de todas formas te obliga a mover todos los elementos en cada llamada, siempre es `O(n)`
##### d) Indique un invariante que involucre _size, _capacity y posiciones válidas de _elem.
`0 <= _size <= _capacity`, y los elementos válidos están almacenados secuencialmente exactamente en los índices desde 0 hasta `_size - 1` del arreglo `_elem`
##### e) Proponga una política de expand/shrink y explique cómo afecta memoria desperdiciada y número de copias.
Política: duplicar la capacidad al llegar al límite (expand), y reducir la capacidad a la mitad pero recién cuando el `_size` cae por debajo de `_capacity / 4`. Reducir en 1/4 (en lugar de la mitad) evita redimensionar a cada rato si el usuario inserta y borra repetidamente, ahorrando memoria y copias inútiles
#### Pregunta 4
Una ArrayQueue circular usa un arreglo de longitud 10, índice j del primer elemento y tamaño n. El elemento lógico k está en a[(j+k) mód 10]. Inicialmente j=7, n=5 y el contenido lógico es `[4, 8, 15, 16, 23]`
##### a) Dibuje el estado físico inicial.
Se usa la fórmula física a[(j+k)%10]. Con j=7 y n=5, ocupamos:
(7+0)%10 = pos 7
(7+1)%10 = pos 8
(7+2)%10 = pos 9
(7+3)%10 = pos 0
(7+4)%10 = pos 1
Físico inicial: `[16, 23, _, _, _, _, _, 4, 8, 15]`
##### b) Aplique add (42), remove(), add (7), add (9), remove() y muestre `j, n,` contenido lógico y posiciones físicas ocupadas.
- add(42): va a pos (7+5)%10 = 2. Físico: `[16, 23, 42, _, _, _, _, 4, 8, 15]`
- remove(): sale pos 7. j pasa a 8, n a 5. Físico: `[16, 23, 42, _, _, _, _, _, 8, 15]`
- add(7): va a (8+5)%10 = pos 3. Físico: `[16, 23, 42, 7, _, _, _, _, 8, 15]`
- add(9): va a (8+6)%10 = pos 4. Físico: `[16, 23, 42, 7, 9, _, _, _, 8, 15]`
- remove(): sale pos 8. j pasa a 9, n a 6. Físico: `[16, 23, 42, 7, 9, _, _, _, _, 15]`
##### c) Explique por qué el módulo es necesario y qué error aparece si se usa simplemente `j + k`.
Sin el módulo, sumar j + k daría un índice fuera de los límites reales del arreglo (ej. 7+4 = 11, pero el array es de tamaño 10). El módulo hace que el comportamiento sea verdaderamente circular
##### d) Compare ArrayQueue con una cola implementada mediante ArrayStack que elimina siempre en posición 0. Analice costos.
ArrayQueue quita en `O(1)` simplemente moviendo el índice j. Si usaramos un ArrayStack normal que quite del inicio (índice 0), nos obligaría a desplazar todo a la izquierda tomando `O(n)`
##### e) Explique cómo DualArrayDeque combina dos arreglos y por qué necesita rebalanceo. Indique qué propiedad debe mantener el rebalanceo.
DualArrayDeque usa un stack apuntando al frente y otro hacia atrás. Necesita rebalanceo para evitar que uno de los arreglos se vacíe totalmente mientras el otro concentra toda la carga. El rebalanceo asegura que `3 * front.size() >= back.size()` y viceversa
#### Pregunta 5
Una `DLList<T>` usa nodo centinela dummy, donde `dummy.next` apunta al primer nodo real y `dummy.prev` al último. Si la lista está vacía, ambos apuntan a dummy
##### a) Escriba pseudocódigo de addBefore (Node* w, T x) actualizando todos los enlaces necesarios.
```cpp
Node* u = new Node(x);
u->prev = w->prev;
u->next = w;
w->prev->next = u;
w->prev = u;
```
##### b) Explique por qué el nodo centinela elimina casos especiales al insertar al inicio o al final.
Porque con el dummy, matemáticamente "todo nodo tiene un previo y un siguiente", incluso el head y el tail. Te ahorra llenar el código de comprobaciones tipo `if (head == nullptr)` o tratar los extremos por separado
##### c) Justifique por qué getNode(i) puede implementarse en $\mathcal{O}(1+min\{i,v-i\})$.
Porque si el índice i está en la primera mitad (`i < v/2`), conviene iterar desde `dummy->next` hacia adelante tomando O(i). Si está en la segunda mitad, conviene empezar de `dummy->prev` hacia atrás tomando O(v-i)
##### d) Diseñe rotate(r) que rota la lista r posiciones a la derecha sin mover los datos elemento por elemento. Puede describir los cambios de enlaces.
Para rotar sin mover los datos reales: Tomas el tamaño total n. El nuevo primer nodo será el de la posición n-r. Solo buscas ese nodo con `getNode(n-r)`, el que era su previo se vuelve el nuevo último, unes el viejo inicio con el viejo final para cerrar el círculo, y reconectas los punteros de dummy al nuevo inicio y al nuevo final. Son puros cambios de punteros
##### e) Proponga dos invariantes estructurales que permitan detectar errores de punteros en una prueba tipo checkSize() o recorrido doble.
1. Recorrer la lista desde `dummy->next` hasta volver al dummy debe dar exactamente los mismos saltos que dice la variable `_size`
2. Para todo nodo u, se debe cumplir sí o sí que `u->next->prev == u`
#### Pregunta 6
Se desea probar una implementación de isBalanced (string s) que acepta paréntesis, corchetes y llaves: (), [] y {}. Debe retornar true si toda apertura se cierra en orden correcto
##### a) Proponga 8 casos de prueba con salida esperada. Deben incluir cadena vacía, anidamiento correcto, cruce incorrecto, cierre sin apertura y apertura sin cierre.
1. "" -> true
2. "()" -> true
3. "[{}]" -> true
4. "([{}])" -> true
5. "([)]" -> false (cruce)
6. "(()" -> false (sobra apertura)
7. "())" -> false (sobra cierre)
8. "]" -> false (inicia con cierre)
##### b) Explique qué error específico detecta cada grupo de pruebas.
Las primeras pruebas revisan funcionamientos normales y anidados. La 5 detecta que la pila valida los tipos correspondientes. La 6 detecta si olvidamos chequear que la pila esté vacía al final del código. La 7 y 8 detectan errores al intentar hacer pop sobre una pila ya vacía
##### c) Indique el ADT adecuado para resolver el problema y justifique por qué.
Una Pila (Stack). La política LIFO sirve porque en cadenas balanceadas el último corchete que abriste es el que tiene la obligación de cerrarse primero
##### d) Analice complejidad temporal y espacial.
Complejidad Temporal: `O(n)` porque iteramos carácter por carácter una sola vez. Espacial: `O(n)` en el peor de los casos (ej: `"(((((("`), ya que todos los caracteres de apertura se terminarán apilando
#### Pregunta 7
Se recibe un flujo de enteros y se desea responder, para cada posición, el mínimo de los últimos k elementos procesados. Por ejemplo, para una ventana deslizante de tamaño k. Diseñe un algoritmo usando estructuras estudiadas
##### a) Defina claramente la entrada, la salida y las precondiciones sobre k.
In: Flujo de enteros y tamaño de ventana k > 0. Out: Mínimo actual de los últimos k vistos. Precondición: que los elementos soporten operadores relacionales (que se puedan comparar con <)
##### b) Proponga una representación basada en una cola/deque auxiliar que mantenga candidatos a mínimo.
Usaría una Deque (MinQueue). No guardo los valores brutos, guardo sus "índices". La idea central es mantener esta deque siempre ordenada de menor a mayor valor de manera estricta
##### c) Dé los invariantes de la estructura auxiliar.
1. El frente de la Deque siempre tiene el índice del elemento más chico de la ventana actual
2. Los valores correspondientes a los índices dentro de la Deque siempre están en orden estrictamente creciente
3. Ningún índice en la Deque está "caducado" (todos están dentro del rango lógico actual de la ventana k)
##### d) Trace su algoritmo para la secuencia `[5, 2, 4, 1, 3, 0, 6]` con k=3.
- Entra 5: D=[0] (min: 5)
- Entra 2: Saca a 5. D=[1] (min: 2)
- Entra 4: D=[1, 2] (min: 2)
- Entra 1: Saca a 4 y 2. D=[3] (min: 1)
- Entra 3: D=[3, 4] (min: 1)
- Entra 0: Saca a 3 y 1. D=[5] (min: 0)
- Entra 6: D=[5, 6] (min: 0)
##### e) Justifique complejidad total y costo amortizado por elemento.
Complejidad total `O(n)`. Aunque a simple vista el while que expulsa mayores parece O(k), cada índice entra a la deque una única vez y sale a lo sumo una única vez en toda su existencia. Por análisis amortizado, es `O(1)` por elemento evaluado
##### f) Compare con recalcular el mínimo recorriendo la ventana en cada posición.
Si iteramos la ventana con fuerza bruta en cada paso nos costaría O(k). Para todo el arreglo sería O(n*k). La estructura auxiliar de Deque baja el tiempo a `O(n)`, lo cual es una diferencia abismal en tiempo de ejecución si el k fuera enorme