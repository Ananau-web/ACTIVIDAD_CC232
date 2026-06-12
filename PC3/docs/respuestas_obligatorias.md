# Respuestas Obligatorias - PC3

## Preguntas comunes

**1. ¿Cuál es el problema exacto asignado?**

AtCoder ABC308 G - Minimum Xor Pair. Dado un conjunto dinámico de enteros, hay que soportar tres operaciones: insertar un número, eliminar un número, y consultar cuál es el par de elementos cuyo XOR da el valor más pequeño posible.

**2. ¿Qué recibe la entrada y qué produce la salida?**

Llegan operaciones una por línea:
- tipo 1 x: agrega x al conjunto
- tipo 2 x: quita una instancia de x del conjunto
- tipo 3: imprime el XOR mínimo entre todos los pares posibles del conjunto actual

Por cada tipo 3 hay que imprimir un número en la salida estándar.

**3. ¿Cuál es la restricción que vuelve insuficiente una solución ingenua?**

Hasta 200,000 operaciones. Una solución que recorra todos los pares en cada consulta sería O(n²) por consulta. Para n del orden de 200k eso es demasiado lento.

**4. ¿Cuál sería la solución ingenua y cuál es su complejidad?**

Guardar los números en un vector. En cada consulta tipo 3, iterar todos los pares (i,j) y calcular `v[i] XOR v[j]`, guardando el mínimo. Complejidad: O(n²) por consulta, O(m·n²) total. No sirve.

**5. ¿Qué estructura de datos elegí?**

Dos estructuras combinadas:
- Un **Treap** (`ods::Treap<long long>`) para mantener los números en orden y encontrar predecesor y sucesor en O(log n)
- Un **LazyHeap** propio, que envuelve `ods::PQ_ComplHeap` con un mapa adicional para lazy deletion, y guarda solo los XOR entre vecinos directos

Además un `unordered_map<long long,int>` para manejar frecuencias, porque el Treap no acepta duplicados.

**6. ¿Qué estructura de la librería cc232 se parece más?**

El Treap está en `include/Semana6/Treap.h`, lo uso directamente para la capa de ordenamiento.

El `PQ_ComplHeap` está en `include/Semana6/PQ_ComplHeap.h`. Es max-heap por defecto pero le paso `std::greater<long long>` como comparador para invertirlo y que funcione como min-heap. Lo envuelvo en `LazyHeap.h` para agregar la lógica de lazy deletion encima.

**7. ¿Qué operación domina el tiempo?**

La búsqueda del predecesor y sucesor en el Treap, que se hace en cada `insert` y `erase`. Es O(log n) porque el Treap mantiene altura esperada O(log n) gracias a las prioridades aleatorias. Las inserciones al heap también son O(log n) pero no cambia el orden total.

Las funciones en cuestión son `getPredecessor()` y `getSuccessor()` en `src/XorManager.cpp`.

**8. ¿Qué invariante mantiene la estructura?**

El único par que puede tener el XOR mínimo es algún par de vecinos consecutivos en el orden del Treap. Nunca necesito calcular XOR entre elementos no adyacentes. Esto es porque si tengo a < b < c, b y c comparten más bits altos que a y c, así que `b XOR c ≤ a XOR c`.

Por eso el heap solo guarda XOR entre vecinos directos, y ese conjunto de candidatos siempre contiene al mínimo real.

**9. ¿Dónde se actualiza ese invariante en el código?**

En `insert()` (`XorManager.cpp` líneas 44-73): cuando inserto `val`, marco obsoleto el par anterior entre su predecesor y sucesor, y agrego los dos pares nuevos: `(pred, val)` y `(val, succ)`.

En `erase()` (líneas 75-105): cuando elimino `val`, marco obsoletos sus dos pares y agrego el par directo entre los que quedaron como vecinos.

En `LazyHeap::clean()` (`LazyHeap.h` líneas 14-26): al consultar el mínimo, saco los obsoletos de la raíz hasta encontrar uno válido.

**10. ¿Qué caso borde puede romper una solución superficial?**

Los duplicados. Si inserto 14 dos veces, el XOR mínimo es `14 XOR 14 = 0`. Pero `Treap::add()` devuelve false si el valor ya existe, así que si no manejo eso por separado nunca se agrega el 0 al heap. Lo resolví con el mapa `freq`: si `freq[val] > 0`, solo incremento y hago `push(0)` en el heap sin tocar el Treap.

**11. ¿Cómo manejo duplicados, empates o elementos obsoletos?**

Duplicados: el mapa `freq[]` lleva la cuenta. Al insertar un valor que ya existe, solo hago `push(0)` al heap. Al eliminar un duplicado (`freq > 1`), solo decremento `freq` y marco 0 como obsoleto.

Obsoletos: lazy deletion. Cuando un par XOR deja de ser entre vecinos directos no lo busco dentro del heap, sino que llamo `markAsObsolete(valor)` que incrementa un contador en el mapa de obsoletos. Al pedir el mínimo, `clean()` extrae de la raíz mientras esté marcado como obsoleto.

**12. ¿Cuál es la complejidad temporal por operación?**

- `insert`: O(log n) — buscar vecinos en Treap + push al heap + `treap.add`
- `erase`: O(log n) — buscar vecinos + `markAsObsolete` + `treap.remove`
- `getMinXor`: O(log n) amortizado — el `clean()` puede sacar varios obsoletos pero cada uno fue insertado antes, así que amortizado es O(log n) por la extracción del heap

**13. ¿Cuál es la complejidad total?**

O(m log n) para m operaciones con conjunto de tamaño máximo n.

**14. ¿Cuál es la complejidad espacial?**

O(n) para el Treap, O(n) para el heap (a lo sumo guarda un par por cada inserción), O(n) para el mapa de frecuencias. Total O(n) con constante algo mayor por tener tres contenedores.

**15. ¿Qué parte del código sería más fácil de romper?**

El `erase()`. Si me olvido de hacer `push(pred ^ succ)` al final (línea 100 en `XorManager.cpp`) después de eliminar un elemento intermedio, el heap pierde el par entre los ex-vecinos y el siguiente `getMinXor()` puede devolver un valor incorrecto o -1 cuando no debería.

También el manejo de duplicados en `erase`: si `freq[val]` era 2 y lo reduzco a 1, tengo que marcar obsoleto el 0 pero no llamar `treap.remove()`. Si lo llamo igual, el Treap pierde el elemento y todo el estado posterior queda corrupto.

**16. ¿Qué alternativa de estructura existe y qué perdería con ella?**

Podría usar `std::set` que ya tiene `lower_bound` y `upper_bound` para encontrar vecinos. La diferencia es que `std::set` sería caja negra para la materia: no puedo mostrar la implementación interna con los conceptos de Semana 5. Con el Treap de la librería puedo señalar el `root()`, los nodos, las rotaciones y cómo la prioridad aleatoria balancea el árbol en altura esperada O(log n).

**17. ¿Qué prueba propia escribí?**

7 pruebas en `tests/main.cpp`:
1. caso básico de 2 elementos
2. inserción intermedia que invalida un par y crea dos nuevos
3. eliminación que reconecta los vecinos originales
4. duplicados que generan XOR 0 y su eliminación posterior
5. frontera: 1 solo elemento devuelve -1
6. comparación contra fuerza bruta O(n²) con 10 valores antes y después de eliminar 2 de ellos
7. verificación explícita del invariante: mínimo entre vecinos del Treap ordenado == `getMinXor()`

**18. ¿Qué cambié durante el bloque sin cortes?**

Agregué dentro de `LazyHeap::clean()` una línea de debug que imprime cada vez que se descarta un elemento obsoleto de la raíz. También agregué un `assert` al final de `getMin()` que verifica que el valor devuelto sea no negativo. Además, implementé el método `printNeighborXors()` en `XorManager` que recorre los vecinos en inorden, imprime sus valores XOR y verifica con un `assert` que el mínimo coincida con `getMinXor()` para validar el invariante. Luego recompilé y ejecuté las pruebas.

**19. ¿Cómo sé que el cambio no rompió la solución?**

Recompilé y ejecuté `./build/test_pc3`. Si algún assert falla (incluyendo el nuevo en `printNeighborXors()`), el programa aborta indicando exactamente la línea. Todas las 7 pruebas siguieron pasando después del cambio. También ejecuté `./build/demo_traza` para ver la salida actualizada.

**20. ¿Qué demuestra que no es una solución de caja negra?**

Implementé `getPredecessor()` manualmente recorriendo los nodos del Treap (`XorManager.cpp` líneas 13-31), sin usar ningún método de búsqueda de la librería. Puedo explicar por qué cuando `current->key < x` guardo ese nodo como candidato y sigo hacia la derecha buscando uno mayor que todavía sea menor que x.

`LazyHeap` tampoco es caja negra: es una clase que construí sobre `PQ_ComplHeap` con un mapa de obsoletos adicional. El `clean()` revisa si la raíz está marcada y la extrae mientras lo esté, hasta encontrar un par válido. La idea de lazy deletion la vimos en Semana 6 con `heapSort` y `delMax`.

---

## Preguntas específicas del problema 16 (AtCoder ABC308 G - Minimum Xor Pair)

**1. ¿Por qué el par de XOR mínimo aparece entre vecinos ordenados?**

Porque dos números que están cerca en magnitud comparten más bits altos. El XOR se vuelve 0 en las posiciones donde los bits coinciden, así que cuanto más bits comparten dos números, menor es su XOR. Si tengo a < b < c, b y c comparten más bits en las posiciones altas que a y c, entonces `b XOR c ≤ a XOR c`. Esto se puede ver directamente comparando en binario: el bit más alto en que difieren dos números determina el orden de magnitud del XOR, y ese bit siempre será menor entre vecinos.

**2. ¿Qué cambia al insertar o eliminar un valor?**

Al insertar `val` entre `pred` y `succ`:
- el par `(pred, succ)` ya no son vecinos directos → marco `pred XOR succ` como obsoleto
- agrego los pares nuevos: `pred XOR val` y `val XOR succ` al heap

Al eliminar `val` que tiene vecinos `pred` y `succ`:
- marco obsoletos: `pred XOR val` y `val XOR succ`
- agrego `pred XOR succ` al heap para reconectar

El código está en `XorManager.cpp` en las funciones `insert()` y `erase()`.

**3. ¿Cómo mantengo candidatos sin recalcular todos los pares?**

Con el heap de lazy deletion. Solo guardo en el heap los XOR entre vecinos directos, que son los únicos candidatos al mínimo. Cuando un par deja de ser de vecinos directos, en vez de buscarlo en el heap (que costaría O(n)) lo marco como obsoleto con un contador en `LazyHeap::obsoletos`. Al consultar `getMin()`, el `clean()` extrae los obsoletos de la raíz hasta encontrar uno válido. Así nunca recalculo todos los pares en cada consulta.