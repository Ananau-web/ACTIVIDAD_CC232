# Bitácora PC3 - Minimum Xor Pair

## Día 1 — leer y entender el problema

Leí el problema varias veces. Al principio no entendía bien qué era "mínimo XOR entre todos los pares", pensé que era entre un elemento y el conjunto pero no, es entre cualquier par (a,b) con a≠b.

La solución obvia es guardar todo en un array y en cada consulta hacer doble loop. Eso sería O(n²) por consulta. Con 200k operaciones eso no pasa.

Fui a repasar la semana 5 porque recordé algo de propiedades de bits en árboles binarios. Ahí me acordé: si los números están ordenados, el XOR mínimo siempre está entre elementos que son vecinos en ese orden. Si tengo a < b < c, b y c comparten más bits altos que a y c, así que b XOR c ≤ a XOR c. Eso significa que nunca necesito revisar pares no adyacentes.

Plan inicial: usar un Treap para tener los elementos ordenados y poder encontrar el vecino anterior/siguiente, y un heap para guardar solo los XOR de pares vecinos. Cada insert/erase sería O(log n).

## Día 2 — intentar implementarlo y encontrar problemas

Empecé con el Treap. La librería de Semana 6 tiene `Treap.h` que usa `add()`, `remove()` y `upperBound()`. El `upperBound(x)` me da el sucesor directo, eso fue fácil.

El problema fue el predecesor. La librería no tiene un `lowerBound` equivalente para el lado izquierdo, o al menos no lo encontré fácil de usar. Terminé haciendo el recorrido manual desde el root: si `current->key < x` guardo ese nodo como candidato y sigo a la derecha buscando uno mayor. Si no, voy a la izquierda. Al final el último candidato es el predecesor. Esto funciona en O(log n) porque el Treap está balanceado.

Otro problema: el `PQ_ComplHeap` es un max-heap. Para el XOR mínimo necesito min-heap. Le pasé `std::greater<long long>` como comparador y eso lo da vuelta. Al llamar `getMax()` en realidad me devuelve el mínimo. Nombre confuso pero funciona.

El tema de los duplicados lo encontré casi por accidente: puse `add(14)` dos veces y el segundo add devolvió false. El Treap no acepta repetidos. Si no manejo eso, un caso como insertar el mismo número dos veces nunca generaría el XOR = 0 que debería dar. Resolví esto con un `unordered_map<long long,int>` de frecuencias afuera del Treap. Si `freq[val] > 0` solo incremento y meto 0 al heap directamente.

## Día 3 — pruebas y bugs

Me senté a escribir las pruebas con assert. La prueba 4 (duplicados) me descubrió un bug inmediatamente: al hacer `erase(14)` cuando `freq[14]` era 2, decrementé a 1 pero también llamé `treap.remove(14)` por error. Eso borraba el elemento del árbol aun cuando todavía había una instancia. Las pruebas siguientes empezaban a dar -1 donde no debían.

La corrección fue simple: solo llamo `treap.remove()` cuando `freq[val]` baja a 0. Antes de eso solo decremento el mapa y marco obsoleto el 0 en el heap.

La prueba de fuerza bruta la escribí con un vector de 10 valores y doble loop O(n²). Comparo ese resultado contra `getMinXor()`. Si coinciden, el algoritmo de vecinos es correcto. Pasó desde el principio una vez que corregí el bug de erase.

También agregué la prueba 7 que verifica el invariante directamente: calculo el mínimo XOR solo entre vecinos consecutivos del conjunto ordenado, y lo comparo con `getMinXor()`. Si el invariante se mantiene tienen que ser iguales.

## Día 4 — documentación y demo del reto

Escribí el README y las respuestas obligatorias. La parte más difícil fue la pregunta de por qué el XOR mínimo siempre está entre vecinos: tuve que pensar bien la justificación en términos de bits compartidos, no solo decirla de memoria.

Hice `traza_reto.cpp` para el bloque de modificación grabada. El programa muestra paso a paso qué pares se crean y cuáles quedan obsoletos al insertar o borrar. Activé el `debug_mode` de XorManager para que también imprima los vecinos que encuentra internamente.

Además, modifiqué `XorManager` (tanto el `.h` como el `.cpp`) para agregar el método `printNeighborXors()`. Este método recorre el treap en inorden e imprime cada par vecino con su valor XOR, validando también con un `assert` que el mínimo entre esos pares sea igual a `getMinXor()`. Esto sirve para verificar de manera explícita que el invariante se cumple.

## Día 5 — 
