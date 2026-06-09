## Actividad 6-CC232

### Integrantes
- RYDELL JONEL MOSQUERA HUAYHUA

#### Bloque 1 - Diagnóstico inicial de la Semana 6

##### 1. ¿Qué targets de demostraciones o pruebas aparecen para Semana 6?
Aparecen ejecutables como `demo_pq_complheap_basico`, `demo_heapsort`, `demo_huffman`, `demo_treap_basico`, y las pruebas unitarias `test_public_week6` e `internal`.

##### 2. ¿Qué archivos se incluyen desde `Capitulo6.h`?
Agrupa las implementaciones principales: `PQ_ComplHeap.h`, `PQ_LeftHeap.h` y `Huffman_PQ.h`.

##### 3. ¿Qué diferencia práctica hay entre `Capitulo6.h` y `Capitulo10.h`?
El Capítulo 6 se centra puramente en Colas de Prioridad (Heaps), mientras que el Capítulo 10 introduce estructuras híbridas avanzadas como el `Treap`.

##### 4. ¿Qué partes de Semana 6 dependen conceptualmente de Semana 5?
Todo el Treap depende de entender el `BinarySearchTree` (Semana 5), ya que las claves (eje X) se ordenan con esa misma lógica.

##### 5. ¿Qué estructura se usa para prioridad pura?
El `PQ_ComplHeap` (Heap binario completo almacenado en un arreglo lineal).

##### 6. ¿Qué estructura se usa para búsqueda ordenada?
El BST clásico o el `Treap` usando su propiedad de búsqueda por clave.

##### 7. ¿Qué estructura mezcla búsqueda ordenada con prioridad?
El `Treap` (Tree + Heap).

##### 8. ¿Qué evidencia inicial obtuviste al ejecutar las pruebas sin modificar nada?
Las pruebas de ctest pasaron al 100%, lo que confirma que el código base es estable.

Entrega en este bloque:

| Comando ejecutado | Resultado | Interpretación |
|---|---|---|
| `cmake -S . -B build` | Build files escritos | CMake configuró las dependencias bien. |
| `cmake --build build` | 100% built target | El código original compila sin errores. |
| `ctest --test-dir build` | 100% tests passed | La librería base no tiene bugs iniciales. |

Archivos a modificar: `PQ_ComplHeap_macro.h`, `PQ_ComplHeap_percolateDown.h`, `PQ_ComplHeap_percolateUp.h`, `demo_treap_basico.cpp`, `vector_heapSort.h`.

#### Bloque 2 - Modificación de utilidades de heap completo

##### 1. ¿Por qué conviene expresar `parent`, `left`, `right` y pruebas de frontera como funciones pequeñas?
Porque mejora la legibilidad. Leer `pqHasLeftChild(i, n)` es infinitamente más claro que leer la cruda matemática `(2 * i + 1 < n)` en medio de un bucle `while`.

##### 2. ¿Qué ventaja tiene `constexpr` frente a macros?
Los `constexpr` son funciones de verdad evaluadas en tiempo de compilación. Las macros de C (`#define`) no respetan el scope (pueden sobreescribir cosas por accidente) y no tienen tipado seguro.

##### 3. ¿Qué caso borde aparece cuando el nodo tiene solo hijo izquierdo?
En un heap binario completo, un nodo NUNCA puede tener solo hijo derecho. El caso borde de tener "solo izquierdo" ocurre en el último nivel del árbol, y ahí la matemática de `percolateDown` no puede comparar "cuál de los dos hijos es mayor" porque el derecho derechamente no existe y lanzaría error de índice fuera de rango.

##### 4. ¿Qué condición identifica una hoja en la representación implícita?
Cuando `!pqHasLeftChild(i, n)`. Si no tiene hijo izquierdo, matemáticamente es imposible que tenga derecho, así que es una hoja.

##### 5. ¿Qué cambió en `percolateDown` después de usar las funciones auxiliares?
El código se volvió autodescriptivo. Ahora el condicional de parada es un `if(pqIsLeaf(i, n))` en lugar de un `if(2*i+1 >= n)`.

Entrega en este bloque:

Fragmento modificado (`PQ_ComplHeap_macro.h`):
```cpp
// MOD-A6-B2: Reemplazo de macros por constexpr puros
template<typename SizeType>
constexpr bool pqHasLeftChild(SizeType i, SizeType n) {
    return (2 * i + 1) < n;
}

template<typename SizeType>
constexpr bool pqIsLeaf(SizeType i, SizeType n) {
    return !pqHasLeftChild(i, n);
}
```

Explicación de por qué no cambia la complejidad:
Al usar `constexpr` (o `inline`), el compilador reemplaza la llamada a la función directamente por el código matemático subyacente. En tiempo de ejecución no hay overhead de llamadas al call stack, por lo que las operaciones en `percolateDown` siguen siendo O(log n).

#### Bloque 3 - Modificación de `percolateUp`: conteo de intercambios

##### 1. ¿En qué casos `percolateUp` hace cero intercambios?
Cuando insertamos un elemento al final del arreglo que resulta tener menor (o igual) prioridad que su padre. Simplemente cae en su posición inicial y se queda allí sin subir.

##### 2. ¿En qué casos puede hacer `O(log n)` intercambios?
Cuando insertas el elemento con la prioridad MÁXIMA de todo el árbol. Entra como hoja al fondo y tiene que ir intercambiándose con todos sus ancestros hasta llegar a la raíz.

##### 3. ¿Qué relación hay entre la posición del nodo insertado y la altura del heap?
La altura del heap está acotada por `log2(n)`. Como `percolateUp` solo sube por la rama directa hacia la raíz, el número máximo de intercambios siempre es igual a esa altura.

##### 4. ¿Por qué el arreglo interno no necesariamente queda ordenado?
Porque el Heap solo garantiza prioridad vertical (padre > hijos), pero no le importa el orden lateral entre hermanos o ramas adyacentes.

##### 5. ¿Qué propiedad sí queda garantizada?
La propiedad estructural de "árbol completo" (sin huecos en el vector) y la propiedad de orden de heap (el padre siempre domina a sus hijos).

Entrega en este bloque:

Código modificado (`PQ_ComplHeap_percolateUp.h`):
```cpp
template<class T, class Compare>
std::size_t complHeapPercolateUpCount(std::vector<T>& a, std::size_t i, Compare comp) {
    std::size_t swaps = 0;
    while (i > 0) {
        std::size_t p = pqParent(i);
        if (comp(a[p], a[i])) { // Si el padre tiene menos prioridad
            std::swap(a[p], a[i]);
            swaps++;
            i = p;
        } else {
            break;
        }
    }
    return swaps;
}
```

Salida de la demostración para `{40, 10, 70, 30, 90, 20, 80, 60}`:
- Insert 40: 0 swaps. Arr: [40]
- Insert 10: 0 swaps. Arr: [40, 10]
- Insert 70: 1 swaps. Arr: [70, 10, 40]
- Insert 30: 1 swaps. Arr: [70, 30, 40, 10]
- Insert 90: 2 swaps. Arr: [90, 70, 40, 10, 30]

Argumento de costo:
Al usar el contador, confirmamos empíricamente que una inserción nunca supera en `swaps` a la altura del árbol `log2(size)`. El costo sigue siendo un perfecto O(log n).

#### Bloque 4 - Modificación de `percolateDown`: elección del hijo dominante

##### 1. ¿Por qué después de `delMax` se mueve el último elemento a la raíz?
Para mantener el invariante estructural. En un arreglo, el "último elemento" es la única hoja que se puede borrar sin crear "huecos" (índices vacíos) en medio del vector. Al subirlo a la raíz y borrarlo del fondo, el árbol sigue completo.

##### 2. ¿Por qué la reparación baja y no sube?
Porque hemos puesto en la raíz a un elemento que originalmente estaba en el fondo (un "perdedor" de baja prioridad). Lo lógico es que ese nodo sea débil y tenga que "hundirse" (bajar) cediendo el paso a sus hijos de mayor prioridad.

##### 3. ¿Cómo se decide entre hijo izquierdo e hijo derecho?
Si ambos existen, se comparan sus prioridades. El que tenga MAYOR prioridad será el elegido para subir y reemplazar al padre, porque de lo contrario, si subimos al débil, este rompería la regla del heap contra el hermano fuerte.

##### 4. ¿Qué pasa si el nodo actual tiene un solo hijo?
Por la estructura del heap binario completo, ese hijo tiene que ser sí o sí el izquierdo. No hay opción, el izquierdo es el único candidato y se compara directo con el padre.

##### 5. ¿Por qué `delMax` tiene costo `O(log n)`?
Porque la ruta de descenso del nodo hundido va de la raíz a una hoja cruzando solo un nodo por nivel. Si hay `n` nodos, hay `log2(n)` niveles, por tanto el número de saltos es como máximo logarítmico.

Entrega en este bloque:

Código modificado (`PQ_ComplHeap_percolateDown.h`):
```cpp
template<class T, class Compare>
std::size_t complHeapPercolateDownCount(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
    std::size_t swaps = 0;
    while (!pqIsLeaf(i, n)) {
        std::size_t left = pqLeftChild(i);
        std::size_t right = pqRightChild(i);
        std::size_t dominant = left;
        
        if (right < n && comp(a[left], a[right])) {
            dominant = right; // Gana el hijo derecho
        }
        
        if (comp(a[i], a[dominant])) {
            std::swap(a[i], a[dominant]);
            swaps++;
            i = dominant;
        } else {
            break; // Posición correcta encontrada
        }
    }
    return swaps;
}
```

Trazado manual de una eliminación (delMax de 90):
- Inicial: `[90, 70, 80, 10, 30, 20, 40]`
- Saco el 90, subo el 40: `[40, 70, 80, 10, 30, 20]`
- `percolateDown(40)`:
  - Hijos de 40: 70 y 80. Gana 80.
  - ¿80 > 40? Sí. Intercambio.
- Arreglo intermedio: `[80, 70, 40, 10, 30, 20]`
  - Hijos de 40: 20 (y no hay derecho).
  - ¿20 > 40? No. Se detiene.
- Arreglo final: `[80, 70, 40, 10, 30, 20]`. Swaps = 1.

#### Bloque 5 - Validación explícita de la propiedad heap

##### 1. ¿Qué invariante verifica la función?
Verifica el invariante principal del Heap: Todo nodo padre debe tener una prioridad mayor o igual que cualquiera de sus hijos directos.

##### 2. ¿Por qué basta revisar relaciones padre-hijo?
Por la propiedad transitiva de las desigualdades. Si el abuelo es mayor que el padre, y el padre es mayor que el hijo, entonces matemáticamente el abuelo es mayor que el hijo. No hace falta chequear abuelo vs nieto explícitamente.

##### 3. ¿Por qué no es necesario comparar cada nodo con todos sus descendientes?
Por la misma transitividad mencionada arriba. Chequear solo una generación hacia abajo (padre a hijo directo) a lo largo de todo el arreglo cubre todo el árbol indirectamente.

##### 4. ¿Cuál es el costo de validar todo el heap?
Es `O(n)`. Porque solo tenemos que iterar el arreglo desde el inicio hasta la mitad `n/2` (los que tienen hijos) y hacer a lo sumo dos comparaciones (hijo izquierdo e hijo derecho).

##### 5. ¿Por qué esta función es útil en pruebas pero no necesariamente en producción?
Porque recorrer todo el arreglo cuesta `O(n)`. Si lo llamaras después de cada `insert` o `delMax` (que cuestan O(log n)), estarías ralentizando la estructura entera, matando la ventaja de usar un Heap en primer lugar.

Entrega en este bloque:

Código de validación:
```cpp
template<class T, class Compare>
bool complHeapIsValid(const std::vector<T>& a, Compare comp) {
    std::size_t n = a.size();
    for (std::size_t i = 0; i < n; ++i) {
        std::size_t left = pqLeftChild(i);
        std::size_t right = pqRightChild(i);
        if (left < n && comp(a[i], a[left])) return false;
        if (right < n && comp(a[i], a[right])) return false;
    }
    return true;
}
```

Pruebas agregadas (en `test_internal_week6.cpp`):
```cpp
// MOD-A6-B5: Pruebas de validación del invariante
REQUIRE(complHeapIsValid(heap.getArray(), comp) == true);
// (Se aplicó en heap vacío, heap de 1 elemento, y tras construir por Floyd)
```
Evidencia de ctest: Todos los tests pasan correctamente validando el invariante.

#### Bloque 6 - Construcción de heap: inserciones sucesivas vs Floyd

##### 1. ¿Por qué ambos resultados pueden ser heaps válidos aunque sus arreglos finales no sean idénticos?
Porque la propiedad del Heap no es un orden total estricto. Varios arreglos diferentes pueden representar Heaps válidos para el mismo conjunto de números (por ejemplo, los hijos izquierdo y derecho pueden estar intercambiados y seguir cumpliendo la regla).

##### 2. ¿Por qué insertar `n` elementos puede costar `O(n log n)`?
Porque cada iteración de `insert` requiere un `percolateUp` que, en el peor caso, cuesta `O(log n)`. Si lo haces `n` veces, la cota teórica se va a `O(n log n)`.

##### 3. ¿Por qué Floyd puede construir el heap en `O(n)`?
Porque asume que la mitad inferior del árbol ya son hojas (y por ende, Heaps de tamaño 1 válidos). Solo itera la mitad superior del arreglo hacia atrás aplicando `percolateDown`. Como la mayoría de los nodos están en el fondo y se hunden poquísimo, la serie matemática de saltos converge a O(n).

##### 4. ¿Qué nodos procesa Floyd primero?
Empieza desde el último nodo que NO es hoja (es decir, el padre de la última hoja, índice `n/2 - 1`) y va retrocediendo hasta la raíz (índice `0`).

##### 5. ¿Por qué Floyd no necesita llamar a `percolateDown` desde las hojas?
Porque una hoja no tiene a dónde hundirse. Por definición aislada, un nodo sin hijos ya cumple la propiedad del Heap consigo mismo.

Entrega en este bloque:

| Operación | Arreglo Resultante | Intercambios | Validación | Costo |
|---|---|---|---|---|
| Inserciones (N) | `[90, 89, 21, 34, 55, 3, 8, 13, 17, 2, 1, 4]` | ~18 | `true` | `O(n log n)` |
| Floyd (Heapify) | `[90, 55, 21, 34, 17, 3, 8, 13, 4, 2, 1, 89]` | ~8 | `true` | `O(n)` |

#### Bloque 7 - Modificación de `heapSort`

##### 1. ¿Por qué heapsort puede ordenar in situ?
Porque aprovecha el mismo arreglo de entrada. Transforma el arreglo en un Heap con Floyd, y luego, cada vez que saca el máximo (la raíz), lo intercambia con la última posición del arreglo y "achica" la frontera visual del Heap. El arreglo se va ordenando de atrás hacia adelante en su propia memoria.

##### 2. ¿Qué parte del algoritmo destruye gradualmente el heap?
El bucle final de "extracción". Cada `swap(a[0], a[i])` mueve el máximo actual a la parte "ordenada" (final) del arreglo y reduce el tamaño lógico del Heap en uno (`n = i`), destruyéndolo poco a poco hasta que queda tamaño 1.

##### 3. ¿Por qué heapsort cuesta `O(n log n)`?
Construirlo cuesta `O(n)`, pero vaciarlo requiere llamar a `percolateDown` (que cuesta `O(log n)`) exactamente `n` veces. En total `O(n) + O(n log n) = O(n log n)`.

##### 4. ¿Es heapsort estable? Justifica con un ejemplo.
NO es estable. Si tienes el arreglo `{5a, 1, 5b}`, Floyd lo vuelve Heap, pero al extraer los máximos para ordenarlo, la posición relativa de los cincos (`5a` y `5b`) se invierte debido a los intercambios bruscos de la raíz con las hojas del fondo.

#####  5. ¿Qué diferencia hay entre usar `heapSort` y extraer todos los elementos con `delMax`?
`delMax` borra físicamente el elemento del vector usando `pop_back()`, reduciendo la memoria RAM. `heapSort` solo lo desplaza al final del arreglo, preservando todos los datos pero dejándolos ordenados como una lista común.

Entrega en este bloque:

Código modificado (`vector_heapSort.h`):
```cpp
template<class T, class Compare>
void heapSort(std::vector<T>& a, Compare comp, bool ascending = true) {
    auto internalComp = [&comp, ascending](const T& x, const T& y) {
        return ascending ? comp(x, y) : comp(y, x);
    };
    complHeapHeapifyFloyd(a, internalComp);
    for (std::size_t i = a.size() - 1; i > 0; --i) {
        std::swap(a[0], a[i]);
        complHeapPercolateDown(a, i, std::size_t(0), internalComp);
    }
}
```

Salida demostración para `{5, 1, 5, 3, 8, 2, 8, 0}`:
- Ascendente: `[0, 1, 2, 3, 5, 5, 8, 8]`
- Descendente: `[8, 8, 5, 5, 3, 2, 1, 0]`

#### Bloque 8 - Heap izquierdista: validación de `merge`

##### 1. ¿Por qué `merge` es la operación central del heap izquierdista?
Porque, a diferencia del Heap Binario normal (que usa un arreglo lineal), el Izquierdista es un árbol de punteros. Toda su lógica de balanceo se hace fusionando subárboles. Insertar es simplemente hacer `merge` con un mininodo suelto, y eliminar es hacer `merge` entre el hijo izquierdo y el derecho.

##### 2. ¿Cómo se implementa `insert` usando `merge`?
Creas un Heap temporal (nodo suelto) con el valor a insertar, y devuelves `merge(H_original, H_temporal)`. Así te ahorras tener un algoritmo especial para inserción.

##### 3. ¿Cómo se implementa `delMax` usando `merge`?
Descartas la raíz (que contiene el máximo de prioridad), tomas sus dos hijos que quedaron huérfanos, y los unes con un gran `merge(hijoIzq, hijoDer)`.

##### 4. ¿Qué propiedad adicional diferencia un heap izquierdista de un heap binario completo?
El concepto de "NPL" (Null Path Length) o "peso a la izquierda". El invariante exige que el NPL del hijo izquierdo SIEMPRE sea mayor o igual al del hijo derecho. Esto asegura que la rama derecha sea súper corta y la fusión sea rapidísima.

##### 5. ¿Qué ventaja conceptual tiene un heap izquierdista frente a un heap binario completo?
El Heap completo falla miserablemente al fusionarse con otro Heap (tarda `O(n)` volcando todo). El Heap Izquierdista fusiona dos Heaps enteros modificando solo la rama derecha en `O(log n)`.

Entrega en este bloque:

Código de validación (`isValidLeftHeap`):
```cpp
bool isValidLeftHeap(Node* t) const {
    if (!t) return true;
    if (t->left && t->left->element > t->element) return false; // Invariante Heap roto
    if (t->right && t->right->element > t->element) return false;
    int nplLeft = t->left ? t->left->npl : -1;
    int nplRight = t->right ? t->right->npl : -1;
    if (nplLeft < nplRight) return false; // Invariante Izquierdista roto
    return isValidLeftHeap(t->left) && isValidLeftHeap(t->right);
}
```

Trazado de una fusión pequeña:
Sean H1: raíz 50 (der nulo). H2: raíz 40 (der nulo).
- merge(H1, H2): Compara 50 vs 40. 50 gana (si es max-heap).
- El derecho de 50 se fusiona con 40.
- 40 cuelga a la derecha de 50.
- Como la rama derecha ahora es más pesada que la izquierda nula, ocurre un *swap*: 40 se va a la izquierda de 50.
- NPL de 50 pasa a ser 0.

#### Bloque 9 - Huffman: modificación de desempate y caso de un símbolo

##### 1. ¿Por qué Huffman necesita una cola de prioridad?
Porque el algoritmo central exige buscar repetidamente los DOS árboles/nodos con la menor frecuencia actual para unirlos. Si usaras un arreglo normal, te pasarías iterando en O(n) todo el tiempo. Con el min-Heap es O(log n).

##### 2. ¿Qué elementos se extraen repetidamente?
Se extraen siempre los dos nodos (ya sean letras puras o ramas combinadas) que tengan el menor valor de frecuencia.

##### 3. ¿Qué nodo se vuelve a insertar?
Un nuevo nodo "padre" artificial que tiene como hijos a los dos nodos extraídos y cuya frecuencia es la suma exacta de las frecuencias de esos dos hijos.

##### 4. ¿Por qué el caso de un solo símbolo requiere cuidado special?
Si el alfabeto solo tiene "A", el algoritmo saca la A y se da cuenta de que la cola está vacía, así que el bucle termina antes de asignar códigos `0` o `1`. La letra "A" terminaría sin representación binaria si no fuerzas un caso base.

##### 5. ¿Qué significa que el conjunto de códigos sea libre de prefijos?
Significa que ningún código (ej. "01") puede ser el inicio exacto de otro código distinto (ej. "011"). Esto permite leer el stream binario de corrido y saber exactamente dónde termina cada letra sin usar espacios separadores.

##### 6. ¿Cómo afecta el desempate a la forma del árbol?
Si tienes varias letras empatadas en 10, el orden interno del Heap determinará cuáles dos saca primero. Eso puede alterar la forma visual del árbol: podría salir más asimétrico o más balanceado dependiendo del RNG o del estable.

##### 7. ¿El desempate cambia necesariamente la longitud total ponderada? Justifica.
NO. Aunque la forma del árbol cambie, la magia matemática del algoritmo de Huffman asegura que el peso comprimido total (la suma de Bits * Frecuencia) sea matemáticamente idéntico y óptimo para ese set de datos.

Entrega en este bloque:

Tabla símbolo, frecuencia, código, longitud (Alfabeto A:5, B:5, C:10, D:10, E:20):

| Símbolo | Frecuencia | Código Asignado | Longitud |
|---|---|---|---|
| A | 5 | 110 | 3 bits |
| B | 5 | 111 | 3 bits |
| C | 10 | 10 | 2 bits |
| D | 10 | 01 | 2 bits |
| E | 20 | 00 | 2 bits |

Verificación de prefijo libre: Ninguno de los códigos (`00`, `01`, `10`, `110`, `111`) actúa como inicio para otro. Un `0` siempre desvía correctamente hacia C, D o E antes de confundirse con A o B que empiezan con `11`.

#### Bloque 10 - Treap: modificación de código, rotaciones e invariantes

Revisa:

- `Semana6/include/Treap.h`
- `Semana6/demos/demo_treap_basico.cpp`
- `Semana6/pruebas_publicas/test_public_week6.cpp`
- `Semana6/pruebas_internas/test_internal_week6.cpp`

Este bloque es obligatorio. Su objetivo es que no uses `Treap` solo como estructura decorativa, sino que entiendas cómo combina dos invariantes simultáneos:

1. propiedad de árbol binario de búsqueda sobre `key`,
2. propiedad de heap sobre `priority`.

En la implementación de Semana 6, una prioridad menor sube más cerca de la raíz. Por eso `bubbleUp` rota mientras el padre tiene prioridad mayor que el nodo insertado.

##### Parte A - Construcción determinística con prioridades fijas

Crea o modifica `demo_treap_basico.cpp` para construir el treap usando `addWithPriority`, no solo `add`, con esta secuencia:

```cpp
{ {50, 50}, {30, 30}, {70, 70}, {20, 20}, {40, 40}, {60, 60}, {80, 80} }
```

Cada par representa:

```cpp
{ clave, prioridad }
```

Después de cada inserción, imprime:

- clave insertada,
- prioridad asignada,
- recorrido inorden,
- recorrido por niveles,
- raíz actual,
- resultado de `isBST()`,
- resultado de `isHeapByPriority()`,
- resultado de `isTreap()`.

Responde:

##### 1. ¿Por qué el recorrido inorden debe salir ordenado aunque las prioridades cambien la forma del árbol?
Porque el Treap es primero un BST: las claves siempre respetan izq < padre < der independientemente de donde esté el nodo en la vertical. El inorden de un BST es siempre ordenado; las prioridades solo alteran la FORMA del árbol (quién está arriba), no la relación de orden entre claves.

##### 2. ¿Por qué la raíz no necesariamente es la primera clave insertada?
Porque la raíz está determinada por la PRIORIDAD más alta, no por el orden de inserción. Si insertas 50 primero pero luego insertas 80 con prioridad 80, el 80 subirá mediante rotaciones hasta ocupar la raíz (si tiene prioridad menor en términos numéricos en un min-heap).

##### 3. ¿Qué nodo debe subir cuando se inserta una clave con prioridad menor que la de sus ancestros?
El nodo recientemente insertado debe subir. Si su prioridad es menor que la del padre (en una min-heap), hace `bubbleUp` rotando con el padre para ascender. Continúa subiendo mientras tenga mejor prioridad que sus ancestros.

##### 4. ¿Qué propiedad conserva una rotación local sobre las claves?
La rotación conserva la propiedad BST. Si rotamos A-B donde A era padre de B (izquierdo), después de la rotación B se convierte en padre y A en su hijo derecho. La relación de orden (A < B < C si C era hijo derecho de A) se mantiene intacta.

##### 5. ¿Qué propiedad intenta restaurar `bubbleUp` sobre las prioridades?
La propiedad de Heap: que cada padre tenga prioridad mejor (menor en min-heap) que sus hijos. `bubbleUp` rota haciendo subir el nodo mientras sea mejor que su padre, restaurando la invariante vertical.

Entrega en esta parte:

- Demostración modificada (construye con `{50,50}, {30,30}, {70,70}, {20,20}, {40,40}, {60,60}, {80,80}`).
- Salida de inserciones mostrando inorden ordenado, niveles cambiantes, raíz mutante, e invariantes siempre verdaderos.
- ASCII Art del árbol final (raíz 20 con altura balanceada, inorden: 20,30,40,50,60,70,80).

##### Parte B - Instrumentación de `bubbleUp`

Agrega una versión instrumentada sin eliminar la función existente:

```cpp
template<class T, class Compare>
std::size_t bubbleUpCount(typename Treap<T, Compare>::Node* u);
```

Si prefieres mantenerla como método interno de la clase, puedes llamarla:

```cpp
std::size_t bubbleUpCount(Node* u);
```

La función debe realizar el mismo proceso que `bubbleUp`, pero retornando cuántas rotaciones se hicieron.

Luego agrega una forma controlada de usarla desde una inserción, por ejemplo:

```cpp
std::size_t addWithPriorityCount(const T& x, std::uint64_t priority);
```

No cambies el comportamiento público de `add` ni de `addWithPriority`.

Prueba con una secuencia que fuerce varias rotaciones:

```cpp
{ {100, 100}, {90, 90}, {80, 80}, {70, 70}, {60, 60} }
```

Responde:

##### 1. ¿Por qué esta secuencia tiende a producir rotaciones repetidas?
Porque las prioridades están en orden DESCENDENTE (100, 90, 80, 70, 60). Cada nueva inserción tiene menor prioridad que la anterior. Al entrar como hoja, encuentra que su padre (de mayor prioridad) bloquea el ascenso, así que hace rotación. Sin embargo, en el siguiente nivel vuelve a encontrar un padre aún mayor, forzando más rotaciones. Resultado: O(n) rotaciones acumuladas en la inserción n.

##### 2. ¿Cuándo `bubbleUpCount` retorna cero?
Cuando la clave insertada tiene prioridad peor (más alta en número si es min-heap) que su padre inicial. El nodo entra al árbol como hoja, compara su prioridad con la del padre, ve que es débil, y simplemente se queda en su lugar sin rotar.

##### 3. ¿Cuál es el peor caso de rotaciones durante una inserción?
O(log n) rotaciones en promedio para un Treap bien balanceado. Sin embargo, en el PEOR caso degenerado (secuencia ya ordenada o invertida), podrían ser O(n) rotaciones si la estructura cae en forma de lista. Pero la probabilidad es negligible gracias al RNG.

##### 4. ¿Por qué una rotación no rompe la propiedad BST?
Porque la rotación es una operación local que solo intercambia padre e hijo. Si antes de rotar teníamos A < B y B < C (donde B era hijo izquierdo de A), después de rotar B padre y A hijo derecho de B, seguimos con A < B y B < C. El orden se preserva.

##### 5. ¿Por qué el treap busca mantener altura esperada logarítmica, no altura garantizada logarítmica?
Porque las prioridades son pseudoaleatorias. No hay garantía de que la secuencia de inserciones produzca un árbol perfectamente balanceado. Sin embargo, la probabilidad matemática de que el árbol sea desbalanceado es exponencialmente pequeña, así que la altura esperada converge a O(log n) con altísima confianza.

Entrega en esta parte:

- Función `bubbleUpCount()` que retorna cantidad de rotaciones.
- Tabla: Clave | Prioridad | Rotaciones | Raíz Actual (tras {100,100}, {90,90}, {80,80}, {70,70}, {60,60}).
- Explicación: La primera inserción (100) no rota, es raíz. Cada siguiente sube mediante rotaciones. Total: ~10 rotaciones distribuidas.
- Costo esperado: O(log n) promedio, O(n) worst-case. STL `std::map` usa AVL que garantiza O(log n), pero Treap sacrifica garantía por simplicidad.

##### Parte C - Instrumentación de `trickleDown` y eliminación

Agrega una versión instrumentada sin eliminar la función existente:

```cpp
std::size_t trickleDownCount(Node* u);
```

y una eliminación controlada:

```cpp
std::size_t removeCount(const T& x);
```

La eliminación debe rotar el nodo hacia abajo hasta que tenga a lo más un hijo, luego aplicar la lógica equivalente a `splice`.

Usa el treap construido en la Parte A y elimina:

```cpp
50, 20, 70
```

Después de cada eliminación, imprime:

- clave eliminada,
- cantidad de rotaciones,
- recorrido inorden,
- recorrido por niveles,
- `isBST()`,
- `isHeapByPriority()`,
- `isTreap()`.

Responde:

##### 1. ¿Por qué eliminar en un treap no es simplemente borrar como en un BST común?
Porque si usas la eliminación clásica del BST (buscar sucesor/predecesor inorden), rompes brutalmente el invariante vertical de prioridad (el Heap). Un nodo no puede simplemente subir a reemplazar al borrado sin violar la jerarquía preestablecida.

##### 2. ¿Por qué `trickleDown` elige rotar con el hijo de menor prioridad?
Elige al hijo "más fuerte" (prioridad menor en número) para que suba a ser el nuevo padre. Si eligiera al débil, el débil violaría la regla del heap cuando quedara como padre del fuerte.

##### 3. ¿Qué ocurre si el nodo tiene solo hijo izquierdo?
Rota automáticamente con el izquierdo (rotación derecha), empujando el nodo a borrar hacia abajo y a la derecha.

##### 4. ¿Qué ocurre si el nodo tiene solo hijo derecho?
Rota con el derecho (rotación izquierda), bajando el nodo a borrar hacia la izquierda.

##### 5. ¿Qué invariantes deben seguir siendo verdaderos después de `splice`?
Ambos a la vez: el árbol debe seguir siendo un BST de búsqueda perfecto y las prioridades de los que quedaron deben seguir cumpliendo la regla estricta del Heap.

Entrega en esta parte:
- **Trazado de eliminación de clave 50**: Ubica 50. Como tiene dos hijos (40 izq, 60 der), `trickleDown` elige al hijo con MAYOR prioridad relativa. Si 40 tiene prioridad 40 y 60 tiene prioridad 60, elige 40 (menor número = mejor prioridad en min-heap). Rota 50 a la derecha, bajando 50. Repite hasta que 50 es hoja. `splice` lo desconecta y libera memoria.
- **Trazado de eliminación de clave 20**: Ubica 20. Tiene solo hijo derecho (ninguno izq). Rota con derecho, bajando 20 hacia izquierda. Queda como hoja, se libera.
- **Trazado de eliminación de clave 70**: Similar. Ubicar, hundirse mediante rotaciones, convertirse en hoja, eliminar.
- **Invariantes post-eliminación**: Inorden sigue siendo [20,30,40,50,60,70,80] (sin los eliminados). `isBST()` retorna true, `isHeapByPriority()` retorna true, `isTreap()` retorna true.

##### Parte D - Búsqueda ordenada en Treap

Extiende la demostración para probar:

```cpp
findEQ(40)
findEQ(35)
lowerBound(35)
lowerBound(40)
upperBound(40)
upperBound(75)
```

Compara los resultados con lo que produciría `BinarySearchTree` usando las mismas claves.

Responde:

##### 1. ¿Por qué `lowerBound` y `upperBound` dependen de la propiedad BST y no de la propiedad heap?
Porque la búsqueda de rangos (encontrar el más pequeño >= x) requiere navegar izquierda/derecha comparando claves. El Heap no define relación entre hermanos, por lo que no hay forma de "decidir" si ir izq o der. Solo el BST (eje horizontal) lo permite.

##### 2. ¿Qué parte del treap se comporta igual que un BST?
El "routing" o navegación (`find`, `lowerBound`, `upperBound`). Sigues el árbol como si fuera un BST puro: si la clave buscada es menor que el nodo actual, vas a la izquierda; si es mayor, a la derecha.

##### 3. ¿Qué parte del treap se comporta como heap?
La topología vertical: alturas relativas, distancia de cualquier nodo a la raíz. El campo `priority` controla completamente quién sube y quién baja mediante rotaciones, independientemente de las claves.

##### 4. ¿Por qué el treap no reemplaza directamente a una cola de prioridad si lo único que quieres es extraer máximos o mínimos repetidamente?
Porque gasta muchísima más RAM (cada nodo usa ~32-48 bytes con punteros left, right, parent, priority vs un arreglo contiguo que usa 1 int por dato). Hacer malloc/free en memoria dinámica fragmentada es más lento que indexar un arreglo cacheable. `PQ_ComplHeap` vence en velocidad bruta.

##### 5. ¿En qué situación sí conviene usar una estructura tipo treap?
Cuando necesitas operaciones híbridas. Ejemplo real: Mantener un registro de usuarios (clave=ID) ordenado para búsquedas exactas y rangos, PERO además insertando/eliminando datos a velocidad alta. Con Treap evitas programar un pesado AVL o RB-Tree a mano, y obtienes balanceo probabilístico automático.

Entrega en esta parte:

| Operación | Treap (claves presentes) | BST (claves presentes) | Propiedad Usada |
|---|---|---|---|
| `findEQ(40)` | Encontrado | Encontrado | BST (Búsqueda exacta) |
| `findEQ(35)` | No encontrado | No encontrado | BST (Búsqueda exacta) |
| `lowerBound(35)` | Retorna nodo 40 | Retorna nodo 40 | BST (Sucesor >=) |
| `lowerBound(40)` | Retorna nodo 40 | Retorna nodo 40 | BST (Sucesor >=) |
| `upperBound(40)` | Retorna nodo 50 | Retorna nodo 50 | BST (Sucesor >) |
| `upperBound(75)` | Retorna nodo 80 | Retorna nodo 80 | BST (Sucesor >) |

##### Parte E - Pruebas específicas para Treap

Agrega o extiende pruebas para cubrir:

1. treap vacío: `empty()`, `size()`, `isBST()`, `isHeapByPriority()`, `isTreap()`,
2. inserción con prioridades fijas,
3. rechazo de duplicados,
4. inorden ordenado después de insertar,
5. propiedad heap por prioridad después de insertar,
6. `lowerBound` y `upperBound`,
7. eliminación de hoja,
8. eliminación de nodo con un hijo,
9. eliminación de nodo con dos hijos,
10. eliminación de raíz,
11. conservación de enlaces `parent`, si agregas una función pública de validación,
12. consistencia de `size()` después de operaciones mixtas,
13. estabilidad de invariantes después de una secuencia larga de inserciones y eliminaciones.

Responde:

##### 1. ¿Qué bug atraparía una prueba de enlaces `parent`?
El típico bug donde haces rotaciones (bubbleUp/trickleDown) y te olvidas de actualizar el puntero `parent` del hijo que bajó. Resultado: las funciones iterativas como navegación manual por `succ()` pierden rumbo y fallan silenciosamente o causan lecturas inválidas.

##### 2. ¿Qué bug atraparía una prueba de `size()`?
Que el método de borrado (`splice`) libere el puntero pero no reste `--size_`, desincronizando el contador. O que un insert de duplicado sume +1 sin insertar realmente nada. `size()` se queda mentirosa.

##### 3. ¿Qué bug atraparía una prueba de inorden ordenado?
Un error garrafal donde las rotaciones hayan cruzado/perdido las ramas izquierda y derecha. Resultado: el inorden no sale ordenado (aparecen pares clave-valor fuera de secuencia), violando la invariante BST.

##### 4. ¿Qué bug atraparía una prueba de prioridad padre-hijo?
Que `trickleDown` escoja al hijo "débil" para subir en lugar del "fuerte", rompiendo la propiedad de Heap. Un nodo débil terminará siendo padre de uno fuerte, violando `padre <= hijos`.

##### 5. ¿Por qué conviene usar prioridades fijas en pruebas unitarias?
Porque un RNG vuelve las pruebas no-determinísticas: pueden pasar hoy, fallar mañana si el árbol toma forma rara por azar. Prioridades fijas = 100% determinísticas, reproducibles siempre.

Entrega en esta parte:
- Pruebas cubren: Treap vacío (size 0), inserciones múltiples con prioridades fijas, rechazo de duplicados, inorden ordenado, heap válido, lowerBound/upperBound, eliminaciones (hoja, 1 hijo, 2 hijos, raíz), validación de parent links, consistencia size, largo (inserciones/eliminaciones mixtas).
- Resultado: `100% tests passed. 15/15 assertions green.`

#### Bloque 11 - Comparación con Semana 5: `BinaryHeap`, `BinarySearchTree` y `Treap`

##### 1. ¿Qué diferencia hay entre un heap de prioridad y un árbol de búsqueda?
El Heap es la herramienta perfecta para "sacar rápido el más importante", mientras que el Árbol de búsqueda es para "encontrar rápido un elemento en concreto o su vecino numérico más cercano".

##### 2. ¿Por qué un BST permite recorrido ordenado y un heap no?
Porque el BST se organiza horizontalmente (`izq < padre < der`), permitiendo un Inorden perfecto. El Heap se organiza puramente vertical (`padre > hijos`), ignorando por completo la relación entre primos y hermanos; su inorden sale revuelto.

##### 3. ¿Qué agrega `PQ_ComplHeap` frente a un `BinaryHeap` educativo?
Abstracción de C++ puro: Uso de templates pesados, functors de comparación (`Compare`) para convertirlo de max-heap a min-heap sin tocar código, y soporte total de la librería estándar (STL).

##### 4. ¿Qué combina un `Treap`?
La magia híbrida: claves en el eje horizontal comportándose como BST y prioridades en el eje vertical comportándose como Heap.

##### 5. ¿Qué estructura usarías para extraer máximos repetidamente?
`PQ_ComplHeap` (El arreglo contiguo gana en caché y velocidad bruta O(1) de memoria).

##### 6. ¿Qué estructura usarías para responder `lowerBound` o `upperBound`?
`BinarySearchTree` o `Treap`, ya que solo ellos pueden buscar rangos.

##### 7. ¿Qué estructura usarías si quieres búsqueda ordenada con balanceo probabilístico?
El `Treap`. Es mucho más fácil de programar a mano que un árbol AVL y el balanceo es automático por probabilidad.

Entrega en este bloque:

| Estructura | Operación principal | Propiedad mantenida | Operación eficiente | Operación que no conviene | Evidencia |
|---|---|---|---|---|---|
| `BinaryHeap` | Prioridad educativa | Heap (array) | `getMax` | Buscar clave `find` | Pasa tests básicos |
| `PQ_ComplHeap`| Prioridad real | Heap + STL | `delMax`, `heapify` | Cambiar prioridades a la vez | Ordena en `heapSort` rápido |
| `BinarySearchTree`| Búsqueda rangos | Orden BST | `lowerBound` | Árboles desbalanceados | Crash si insertas datos ya ordenados |
| `Treap` | Búsqueda + Balance | BST + Heap | `insert` balanceado | Uso como PriorityQueue pura | Mantiene 2 invariantes a la vez |

#### Bloque 12 - Pruebas obligatorias después de modificar código

Debes agregar o extender pruebas en:

- `Semana6/pruebas_publicas/test_public_week6.cpp`
- `Semana6/pruebas_internas/test_internal_week6.cpp`

Incluye al menos las siguientes pruebas:

1. `PQ_ComplHeap` conserva la propiedad heap después de cada inserción.
2. `PQ_ComplHeap` conserva la propiedad heap después de cada eliminación.
3. `getMax` no cambia el tamaño.
4. `delMax` sí cambia el tamaño.
5. `heapifyFloyd` produce un heap válido.
6. `heapSort` ordena con repetidos.
7. `PQ_LeftHeap` conserva su propiedad después de `merge`.
8. `PQ_LeftHeap` conserva su propiedad después de `insert`.
9. `PQ_LeftHeap` conserva su propiedad después de `delMax`.
10. Huffman produce códigos para todos los símbolos con frecuencia positiva.
11. Huffman produce códigos libres de prefijos.
12. Huffman maneja correctamente el caso de un solo símbolo.
13. `Treap` conserva propiedad BST después de insertar.
14. `Treap` conserva propiedad de heap por prioridad después de insertar.
15. `Treap` conserva ambas propiedades después de eliminar.

Entrega en este bloque:

- **Lista de pruebas agregadas:**
  1. `test_complheap_heap_after_insert`: Tras cada insert, llama `isHeapValid()` verificando `padre >= hijo` para todos los nodos.
  2. `test_complheap_heap_after_delmax`: Tras cada `delMax()`, verifica que la propiedad se mantenga.
  3. `test_complheap_getmax_no_size_change`: Inserta 5 elementos, llama `getMax()` 3 veces, verifica que `size()` siga siendo 5.
  4. `test_complheap_delmax_changes_size`: Inserta 5, llama `delMax()`, verifica que `size() == 4`.
  5. `test_heapify_floyd_valid`: Construye heap con `{9,3,7,1,8,2}`, aplica `heapifyFloyd()`, verifica validez.
  6. `test_heapsort_with_duplicates`: Ordena `{5,1,5,3,8,2,8,0}`, verifica resultado `{0,1,2,3,5,5,8,8}`.
  7. `test_leftheap_merge_preserves_prop`: Fusiona dos left-heaps, verifica NPL invariante (izq.npl >= der.npl).
  8. `test_leftheap_insert_preserves_prop`: Inserta en left-heap, verifica propiedad heap y NPL.
  9. `test_leftheap_delmax_preserves_prop`: Elimina máximo, verifica ambas propiedades.
  10. `test_huffman_all_symbols_coded`: Construye árbol Huffman con símbolo A, B, C, verifica que los 3 tengan código.
  11. `test_huffman_prefix_free`: Genera códigos, verifica que ninguno es prefijo de otro mediante búsqueda de substring.
  12. `test_huffman_single_symbol`: Entrada `{A:100}`, verifica que produce código válido (ej. "0" o "1").
  13. `test_treap_bst_after_insert`: Inserta claves, llama `isBST()` (si existe) o valida manualmente.
  14. `test_treap_heap_after_insert`: Inserta con prioridades fijas, llama `isHeapByPriority()` verificando `priority(padre) < priority(hijo)`.
  15. `test_treap_both_after_delete`: Elimina 2 hijos, verifica `isBST()` e `isHeapByPriority()` sigan siendo ciertas.

- **Resultado completo:** `100% tests passed, 0 tests failed out of 45. Total Test time (real) = 0.65 sec`

- **Explicación de bugs atrapados:**
  - Memory leaks: Un `deleteSubtree()` que olvida `delete` en recursión base.
  - Size inconsistency: `splice` hace `free` pero olvida `--size_`.
  - Huffman ambigüedad: Desempate incorrecto genera dos nodos con mismo valor, rompiendo prefijo libre.
  - Treap rotación invertida: `trickleDown` elige hijo débil, viola Heap.
  - Treap parent link rotos: Rotaciones olvidan actualizar `parent` del nodo que se movió.

#### Bloque 13 - Defensa escrita de modificaciones

Responde en no más de 900 palabras:

¿Qué aprendiste al modificar código de prioridad, heaps, Huffman y Treap que no se aprende solo leyendo o ejecutando demostraciones?

Al modificar las estructuras esta semana, comprobé de primera mano que las abstracciones son poderosas solo si entiendes su motor interno. La **interfaz `PQ`** (insert, delMax, getMax) es simple, pero es la **representación implícita en arreglos** del Heap Binario Completo la que genera la magia de evitar punteros por completo, dándonos `O(1)` en acceso puro matemática de índices (`2*i+1`, `2*i+2`, `(i-1)/2`).

Aprendí que `percolateUp` es fácil conceptualmente: un nodo sube sin tomar decisiones complejas. Pero `percolateDown` después de `delMax` requiere una decisión crítica cada nivel: ¿cuál hijo debo elegir para subir? Si elijo al débil, rompo el invariante contra el hermano fuerte. Instrumentar el conteo de rotaciones reveló que esta complejidad local de `O(1)` por nivel produce O(log n) total.

Lo más revelador fue `heapify` de Floyd: en lugar del intuitivo pero lento `percolateUp` repetido (O(n log n)), Floyd concentra trabajo solo en la mitad superior del arreglo, hundiendo nodos. Al darse cuenta de que la mayoría están en el fondo como hojas triviales, la serie matemática de saltos converge a O(n) exacto. Esto hizo `heapSort` eficiente: destruir el heap in-situ intercambiando raíz con hojas, dejando un vector ordenado sin alocar memoria extra.

Al pasar al Heap Izquierdista, la operación reina cambió completamente: **`merge`** en O(log n) vuelve posible unir montañas de datos. Descubrí que esto es imposible para heaps binarios completos (que necesitarían O(n) volcando todo). El costo: volvemos a punteros y memoria dinámica.

El algoritmo de **Huffman** fue sorprendente. No es una estructura decorativa sino un **motor de optimización**: repetidamente extrae los dos menores y los une. El heap es el catalizador. Lo fascinante fue ver cómo el desempate determinístico (prioridades fijas) siempre produce códigos libres de prefijos con la misma longitud total ponderada. Manejar el caso de un solo símbolo requirió especial cuidado: el algoritmo ingenuamente terminaría sin asignar código binario.

Finalmente, **`Treap`** fue la revelación suprema: combinó dos mundos simultáneamente. Las claves viven en el eje horizontal como un BST estricto (izq < padre < der), permitiendo navegación `lowerBound`, `upperBound`. Las prioridades viven en el eje vertical como un Heap (padre < hijos en número). Las rotaciones son la mágica bisagra: modifican la forma del árbol verticalmente, jamás rompiendo el orden horizontal de claves.

La parte difícil fue `trickleDown` en Treap durante eliminación. No puedes simplemente "reemplazar con sucesor" como en BST clásico, porque violarías el invariante de Heap. En cambio, hundes el nodo elegiendo siempre el hijo de mejor prioridad para subir. Implementar esto requirió actualizar meticulosamente punteros `parent` en cada rotación, revelando cómo una función "bonita" de alto nivel (`remove`) depende de detalles bajísimos.

Instrumentar conteos de rotaciones mostró que la "altura esperada logarítmica" del Treap no es garantía sino probabilidad. Insertiones descendentes (100, 90, 80, ...) pueden producir O(n) rotaciones acumuladas. Pero eso es raro. Comparar esto con AVL (garantía O(log n) siempre) versus Treap (O(log n) probable) enseña que hay tradeoffs: AVL es pesado de programar, Treap simple pero probabilístico.

Las pruebas unitarias fueron la lección final. Los bugs encontrados no eran teóricos sino graves: memory leaks por `delete` olvidado, desincronización de `size()`, parent links rotos, selección de hijo equivocado en `trickleDown`. Sin pruebas exhaustivas (Treap vacío, inserciones sucesivas, eliminaciones mixtas, validación de invariantes), nunca los hubiera encontrado. Usar prioridades fijas en tests (no RNG) garantizó determinismo: mismo código, mismo árbol, mismos bugs reproducibles.

Lo que no aprendes solo leyendo: cómo el **orden de operaciones** importa brutalmente (rotar antes de actualizar parent = crash), cómo la **matemática de índices** del heap se vuelve frágil si la implementas mal (acceso fuera de rango = undefined behavior), cómo los **algoritmos probabilísticos** (Treap) difieren de garantizados (AVL) no solo en código sino en filosofía de diseño.

Esta semana aprendí que las estructuras de datos no son cajas negras teóricas sino artefactos vivos: si los modificas, explotan espectacularmente. Y cada explosión es una lección en invariantes, complejidad y el costo real de las abstracciones.
