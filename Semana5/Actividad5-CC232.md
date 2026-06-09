## Actividad 5 - CC232

### Estudiante

- Rydell Jonel Mosquera Huayhua

#### Bloque 1 - Núcleo conceptual
##### 1. Explica con tus palabras qué diferencia hay entre un árbol binario enlazado y un árbol binario almacenado implícitamente en un arreglo.
La diferencia principal está en cómo conectan sus elementos. El árbol enlazado usa nodos dispersos en la memoria que se unen mediante punteros reales (hijo izquierdo, derecho y padre). En cambio, el árbol implícito no usa punteros; guarda todo en un arreglo tradicional y usa fórmulas matemáticas sobre las posiciones (como 2*i + 1 o 2*i + 2) para simular la jerarquía y saber quién es hijo de quién.

##### 2. Explica qué información guarda un `BinNode`: dato, padre, hijo izquierdo, hijo derecho y altura.
- Dato (data): Es la "carga útil", el valor real que queremos almacenar (un número, etc).
- Hijo izquierdo (left) e hijo derecho (right): Son los punteros que conectan al nodo con los que están justo debajo. Arman la jerarquía descendente.
- Padre (parent): Puntero hacia el nodo que está inmediatamente arriba. Permite "subir" por el árbol de forma directa, útil para iteradores sin usar pila.
- Altura (height): Guarda precalculada la altura del subárbol que nace desde este nodo. Evita recalcularla bajando hasta las hojas cada vez.

##### 3. Explica por qué el puntero `parent` permite implementar operaciones como `succ()`, `pred()` y actualización ascendente de alturas.
Porque al tener el puntero `parent` puedes recorrer el árbol hacia arriba. Si quieres el sucesor de un nodo que no tiene hijo derecho, solo necesitas subir por los ancestros hasta encontrar el primer giro a la izquierda. Igual para actualizar alturas: modificas una hoja y vas subiendo por los `parent` ajustando las alturas de los ancestros sin tener que recalcular desde la raíz.

##### 4. Explica qué responsabilidad tiene `BinTree` frente a `BinNode`.
`BinNode` es solo la "caja" que guarda los datos y los punteros locales. `BinTree` es el "administrador" de todo el árbol: guarda el puntero a la raíz (`root_`), mantiene el contador del tamaño (`size_`) y provee los métodos de alto nivel para insertar, eliminar subárboles o actualizar las alturas globales.

##### 5. Explica qué agrega `BinaryTree` sobre la infraestructura base de `BinTree`.
Agrega la lógica de navegación como un contenedor estándar. Mientras `BinTree` maneja la estructura bruta, `BinaryTree` implementa iteradores, funciones para encontrar el primer nodo (`firstNode()`), el último (`lastNode()`) y avanzar secuencialmente usando el recorrido inorden.

##### 6. Explica qué propiedad adicional convierte un árbol binario en un `BinarySearchTree`.
La propiedad de ordenamiento: para cada nodo, todos los valores en su subárbol izquierdo son menores que su valor, y todos los valores en su subárbol derecho son mayores (o iguales, dependiendo de si permite duplicados).

##### 7. Explica qué propiedad adicional convierte un arreglo en un `BinaryHeap` mínimo.
La propiedad de heap (o de prioridad): el valor de cualquier nodo (padre) siempre es menor o igual al valor de sus hijos. Esto garantiza que el mínimo global siempre esté en la raíz (posición 0 del arreglo).

##### 8. Compara la propiedad de orden de un BST con la propiedad de prioridad de un heap.
En el BST el orden es horizontal (izquierda < nodo < derecha), lo que permite búsquedas exactas o rangos rápidamente. En el heap el orden es vertical (padre <= hijos), no hay relación estricta entre hermanos, solo asegura tener el extremo (mínimo o máximo) siempre a mano arriba de todo.

##### 9. Explica por qué un recorrido inorden de un BST produce una secuencia ordenada.
Porque el inorden visita primero el subárbol izquierdo (todos los menores), luego el nodo actual, y finalmente el subárbol derecho (todos los mayores). Al aplicar esto recursivamente en un BST, estás básicamente "imprimiendo" los números de menor a mayor.

##### 10. Explica por qué un heap no permite, por sí solo, recorrer los elementos en orden sin destruir o copiar la estructura.
Porque el heap solo garantiza que el padre es menor que los hijos, pero no ordena a los hermanos entre sí. Para sacarlos en orden tendrías que hacer `delMin()` repetidas veces, lo que destruye el heap. Si quisieras hacerlo sin destruirlo, tendrías que clonarlo primero.

#### Bloque 2 - Navegación, altura, profundidad y tamaño

##### 1. En `BinNode`, explica qué significan `hasLeft()`, `hasRight()`, `isRoot()`, `isLeaf()`, `isLeftChild()` e `isRightChild()`.
Son macros o funciones helper para saber el estado local del nodo. `hasLeft` y `hasRight` ven si el puntero respectivo no es nulo. `isRoot` chequea si no tiene padre. `isLeaf` si no tiene ni hijo izquierdo ni derecho. `isLeftChild` verifica si el hijo izquierdo de su padre apunta a él mismo.

##### 2. Explica el caso en que `succ()` baja al subárbol derecho y luego busca el nodo más a la izquierda.
Si el nodo actual tiene un hijo derecho, el sucesor (el siguiente mayor) está garantizado de estar en ese subárbol. Específicamente, es el valor más pequeño de los mayores, así que bajas un paso a la derecha y luego vas todo lo posible a la izquierda.

##### 3. Explica el caso en que `succ()` sube por los ancestros hasta encontrar el primer giro hacia la izquierda.
Si el nodo no tiene hijo derecho, significa que ya es el máximo de su subárbol. Para encontrar al sucesor hay que subir por los padres: sigues subiendo mientras seas el hijo derecho de tu padre. En el momento que eres el hijo izquierdo de tu padre, ese padre es el sucesor.

##### 4. Explica simétricamente cómo debe funcionar `pred()`.
Si tiene hijo izquierdo, el predecesor es el nodo más a la derecha de ese subárbol izquierdo. Si no tiene hijo izquierdo, subes por los ancestros mientras seas hijo izquierdo, y el primer padre del que seas hijo derecho será tu predecesor.

##### 5. Dibuja un árbol de al menos 7 nodos y marca el sucesor y predecesor inorden de tres nodos distintos.
(Mentalmente: Raíz 10, izq 5, der 15. De 5: izq 3, der 7. De 15: izq 12, der 18).
Predecesor de 10 es 7. Sucesor de 10 es 12.
Predecesor de 5 es 3. Sucesor de 5 es 7.

##### 6. Explica qué calcula `depth(u)` y por qué puede implementarse subiendo por `parent`.
La profundidad es la distancia (aristas) desde la raíz hasta el nodo `u`. Puedes subir iterativamente usando el `parent` y contando cuántos pasos das hasta llegar a la raíz.

##### 7. Explica qué calcula `height(u)` y por qué suele implementarse bajando recursivamente por los hijos.
La altura es la máxima distancia desde `u` hasta alguna de sus hojas descendientes. Se baja recursivamente porque necesitas calcular `max(height(left), height(right)) + 1`, así que tienes que explorar las ramas hacia abajo.

##### 8. Explica qué calcula `subtreeSize(u)`.
Cuenta la cantidad total de nodos que hay en el subárbol donde `u` es la raíz (incluyendo a `u`). 

##### 9. Demuestra que para todo nodo `u` se cumple `depth(u) + height(u) <= height(T)`.
La suma de la distancia de la raíz a `u` (depth) y la máxima distancia de `u` a una hoja (height) representa la longitud de un camino particular desde la raíz hasta una hoja pasando por `u`. Como `height(T)` es el camino MÁXIMO de todo el árbol, cualquier camino particular será menor o a lo sumo igual.

##### 10. Indica la condición necesaria y suficiente para que se alcance la igualdad anterior.
La igualdad se cumple solo si el nodo `u` pertenece al camino más largo de todo el árbol (la rama crítica que define la altura total de `T`).

#### Bloque 3 - Recorridos y trazado guiado

| Recorrido | Versión revisada | Estructura auxiliar | Secuencia (ejemplo) | Argumento de correctitud y costo |
|---|---|---|---|---|
| Preorden recursivo | `travPre_R` | Pila de llamadas | Raíz, Izq, Der | O(n) tiempo. Correcto por inducción recursiva. |
| Preorden iterativo | `travPre_I2` | `std::stack` explícita | Raíz, Izq, Der | O(n) tiempo. Evita desbordamiento de pila del sistema. |
| Inorden recursivo | `travIn_R` | Pila de llamadas | Izq, Raíz, Der | O(n) tiempo. Produce salida ordenada en un BST. |
| Inorden iterativo #1 | `travIn_I1` | Pila explícita | Izq, Raíz, Der | O(n) tiempo. Simula la bajada izquierda y el retroceso. |
| Inorden iterativo #2 | `travIn_I2` | Pila explícita | Izq, Raíz, Der | Otra variante iterativa, mismo costo O(n). |
| Inorden iterativo #3 | `travIn_I3` / `succ` | `parent` (sin pila) | Izq, Raíz, Der | O(n) tiempo, O(1) memoria. El mejor diseño por no usar RAM extra. |
| Postorden recursivo | `travPost_R` | Pila de llamadas | Izq, Der, Raíz | O(n) tiempo. Ideal para liberar memoria desde las hojas. |
| Postorden iterativo | `travPost_I` | Pila explícita | Izq, Der, Raíz | Más complejo iterativamente pero mantiene O(n) de tiempo. |
| Niveles | `travLevel` | `std::queue` (Cola) | Arriba abajo, izq der | O(n) tiempo, memoria O(w) donde w es el ancho máximo. |

##### 1. ¿Qué significa visitar un nodo en preorden?
Visitar primero el nodo actual, luego todo su subárbol izquierdo, y finalmente todo su derecho.

##### 2. ¿Qué significa visitar un nodo en inorden?
Visitar el subárbol izquierdo, luego el nodo actual, y después el derecho. (Produce secuencia ordenada en BST).

##### 3. ¿Qué significa visitar un nodo en postorden?
Visitar el subárbol izquierdo, luego el derecho, y al final el nodo actual. (Útil para liberar memoria, borras a los hijos y luego al padre).

##### 4. ¿Qué significa visitar un árbol por niveles?
Recorrerlo de arriba hacia abajo, nivel por nivel (raíz primero, luego sus hijos de izq a der, luego los nietos, etc). Se implementa con una cola (BFS).

##### 5. ¿Por qué los recorridos recursivos tienen tiempo `O(n)`?
Porque la recursión visita cada nodo exactamente un número constante de veces (básicamente entras y sales del nodo). Si hay n nodos, hace ~O(n) trabajo.

##### 6. ¿Por qué las versiones iterativas también tienen tiempo `O(n)`?
Igual, empujar y sacar de la pila explícita se hace una vez por cada nodo. El trabajo total es proporcional a n.

##### 7. ¿Cuál es la memoria auxiliar de un recorrido recursivo en un árbol balanceado?
`O(log n)`. La profundidad máxima de la recursión (el call stack) es la altura del árbol, que en uno balanceado es logarítmica.

##### 8. ¿Cuál es la memoria auxiliar de un recorrido recursivo en un árbol degenerado?
`O(n)`. Si el árbol parece una lista enlazada, la recursión baja `n` niveles antes de empezar a regresar, llenando el call stack con `n` frames.

##### 9. ¿Qué diferencia hay entre usar una pila explícita y usar la pila de llamadas?
La pila de llamadas la maneja el sistema operativo/compilador automáticamente con la recursión, pero tiene un tamaño limitado (puede dar stack overflow). Una pila explícita (`std::stack`) usa el heap memory, lo que te permite manejar árboles muchísimo más profundos sin crashear.

##### 10. ¿Por qué la cola del recorrido por niveles puede crecer mucho más en un árbol completo que en un árbol degenerado?
En un árbol completo, el último nivel tiene aproximadamente `n/2` nodos. La cola almacena todo un nivel antes de pasar al siguiente, así que crece hasta O(n). En un degenerado, cada nivel tiene solo 1 nodo, así que la cola nunca pasa de tamaño 1 o 2.

### Bloque 4 - Demos

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo, espacio o diseño |
|---|---|---|---|
| `demo_binary_tree.cpp` | Impresiones en consola de inorden, preorden y postorden usando functores `visit`. Gráfico ASCII que visualiza la jerarquía real. Iteración manual con `succ()` que reproduce el inorden. | Árbol binario enlazado con punteros left, right y parent. Recorridos recursivos e iterativos que visitan nodos en orden. Funciones `succ()` y `pred()` navegando sin pila explícita. | O(n) tiempo para cada recorrido. O(log n) memoria en árbol balanceado (altura del call stack). Diseño sin pila explícita usando `parent` ahorra O(1) memoria auxiliar vs pila. |
| `demo_bst.cpp` | Secuencia de números impresos en consola mostrando el recorrido inorden perfectamente ordenado, incluso si fueron insertados en orden aleatorio. Operaciones `lowerBound` y `upperBound` distinguen búsqueda por rango vs búsqueda exacta. | Árbol binario de búsqueda: propiedad izq < raíz < der en cada nodo. El recorrido inorden respeta esta propiedad produciendo salida ordenada. Búsqueda binaria durante insert/find. | Búsqueda O(log n) en árbol balanceado, O(n) en degenerado. Insert/remove O(log n) promedio. Inorden O(n) siempre. Superior a un vector lineal que necesita O(n) para buscar y O(n) para insertar en orden. |
| `demo_heap.cpp` | Impresión del arreglo interno mostrando que el mínimo siempre está en posición 0 después de `add()`. Comparación visual del arreglo resultante de `add()` repetidas veces vs `heapify()`. Extracción repetida con `delMin()` que produce salida ordenada (HeapSort). | Heap binario representado implícitamente en `std::vector`. Fórmulas de índices: left(i)=2i+1, right(i)=2i+2, parent(i)=(i-1)/2. Invariante: padre <= hijos. Operaciones `bubbleUp` y `trickleDown` restauran la propiedad. | Insertar n elementos: `add()` repetido O(n log n). `heapify()` construye en O(n). `delMin()` es O(log n). Heap compite con BST: Heap gana para mínimo repetido, BST gana para búsquedas arbitrarias. Sin punteros, memoria caché amigable. |
| `demo_capitulo5_panorama.cpp` | Presentación lado a lado de árbol enlazado puro, BST con búsqueda, y heap con prioridad. Demostración de cómo cada estructura especializa la idea base de jerarquía. | Transición desde estructura neutral (árbol enlazado) a estructura con propiedad de orden (BST: horizontal) a estructura con propiedad de prioridad (heap: vertical). Muestra la progresión de generalidad → especialidad. | Árbol enlazado genérico O(n) búsqueda. BST promedio O(log n) búsqueda. Heap O(1) mínimo. Cada estructura añade restricciones que sacrifican flexibilidad pero ganan velocidad en caso de uso específico. |

#### Bloque 5 - Pruebas e invariantes

##### 1. ¿Qué operaciones del BST valida la prueba pública?
Valida `insert`, `remove`, `find`, las cotas `lowerBound`/`upperBound`, y chequea que el inorden siempre dé una lista ordenada.

##### 2. ¿Qué casos validan que el BST no acepta duplicados?
Insertar el mismo número varias veces y chequear que `size()` no aumente después del primer insert.

##### 3. ¿Qué se verifica al comparar el inorden recursivo con las versiones iterativas?
Se verifica que la implementación con pilas explícitas (o la que usa el puntero `parent`) sea algorítmicamente equivalente a la recursiva, produciendo la misma secuencia exacta.

##### 4. ¿Qué se espera de `findEQ(8)` en la prueba pública?
Que retorne el nodo con valor 8 si fue insertado, o nullptr si no existe o fue eliminado.

##### 5. ¿Qué se espera de `lowerBound(9)` y `upperBound(8)`?
`lowerBound(9)` debe dar el nodo con el menor valor >= 9. `upperBound(8)` debe dar el nodo con el menor valor estrictamente > 8. 

##### 6. ¿Qué propiedad se valida con `isBST()`?
Verifica recursivamente que para todo nodo, todos los de su izquierda sean menores y los de su derecha mayores, confirmando que la inserción/eliminación no corrompió la estructura de búsqueda.

##### 7. ¿Qué se valida después de eliminar un nodo con `remove()`?
Que el `size` bajó en 1, que `find` ya no lo encuentra, y que el árbol sigue cumpliendo `isBST()`. Especialmente crítico si el nodo borrado tenía dos hijos y se usó su sucesor para reemplazarlo.

##### 8. ¿Qué valida `checkParentLinks()` después de borrar, separar o adjuntar subárboles?
Se asegura de que ningún puntero haya quedado huérfano o apuntando a basura. Si el hijo apunta al padre, el padre debe tener a ese nodo como uno de sus hijos. 

##### 9. ¿Qué operaciones del heap valida la prueba pública?
La inserción (`add`), la extracción del mínimo (`delMin` o `getMin`), y la conservación del invariante de prioridad.

##### 10. ¿Qué demuestra extraer repetidamente de un min-heap hasta vaciarlo?
Demuestra el `HeapSort`. Si haces `delMin()` repetidas veces y vas guardando el resultado, la secuencia obtenida debe estar perfectamente ordenada de menor a mayor.

##### 11. ¿Qué operaciones de `BinTree` se validan con `attachAsRC`, `secede` y `removeSubtree`?
Las manipulaciones estructurales en masa: poder cortar una rama entera de un árbol y pegarla en otro, asegurando que los punteros parent/child y las alturas se actualicen bien en ambos árboles.

##### 12. ¿Qué agregan las pruebas internas respecto a rotaciones, `bubbleUp`, `trickleDown`, profundidad, altura, sucesor y predecesor?
Miden la robustez de las herramientas internas que el usuario normalmente no ve. Validan que `trickleDown` no hunda un nodo más de lo debido, o que las alturas se actualicen exactamente a los valores precalculados manualmente.

##### 13. ¿Qué sí demuestra pasar las pruebas públicas?
Demuestra que la lógica central y las firmas de los métodos hacen lo que se pide para los casos comunes y algunos bordes conocidos. Básicamente que el código "funciona".

##### 14. ¿Qué no demuestra pasar las pruebas públicas?
No garantiza que la complejidad asintótica sea la pedida (podrías tener un insert en O(n) y pasaría la prueba igual). Tampoco prueba resistencia a memory leaks o casos borde absurdamente grandes (como un árbol degenerado de 1 millón de nodos).

##### 15. ¿Por qué una defensa correcta debe mencionar invariantes y complejidad además de resultados observables?.
Porque el resultado observable es solo la mitad de la nota. Si el BST imprime ordenado, pero el insert lo hiciste en O(n), mataste el propósito de la estructura. El invariante garantiza por qué el algoritmo es correcto siempre, y la complejidad justifica por qué usar esta estructura sobre un simple vector.
#### Bloque 6 - Lectura cercana: `BinNode`, `BinTree` y `BinaryTree`

##### 1. En `BinNode`, ¿qué invariantes deben mantenerse entre `parent`, `left` y `right`?
Si un nodo `u` tiene `left != nullptr`, entonces `left->parent == u`. Si un nodo `u` tiene `right != nullptr`, entonces `right->parent == u`. Si `u` es la raíz, entonces `u->parent == nullptr`. Si `u` no es raíz, entonces `u->parent != nullptr`. Estas invariantes garantizan que los punteros forma una jerarquía bidireccional consistente.

##### 2. ¿Por qué `insertAsLC` e `insertAsRC` deben rechazar una inserción cuando el hijo correspondiente ya existe?
Porque permitir sobrescribir un hijo existente haría perder el acceso a todo su subárbol (memory leak). El código lanza `std::logic_error` si `left != nullptr` o `right != nullptr` antes de insertar, forzando al usuario a eliminar primero el hijo viejo o estar consciente del error.

##### 3. Explica cómo `size()` de `BinNode` recorre el subárbol.
`size()` es recursivo. Calcula el tamaño del subárbol izquierdo llamando `left->size()` (o 0 si no existe), el tamaño del subárbol derecho llamando `right->size()` (o 0 si no existe), y retorna `1 + ls + rs`. Visita cada nodo exactamente una vez, por lo que es O(n).

##### 4. Explica cómo funcionan `leftmost()` y `rightmost()`.
`leftmost()` parte de `this` y sigue el puntero `left` hacia abajo hasta que `u->left == nullptr`, retornando ese nodo (el más a la izquierda). `rightmost()` hace lo simétrico: sigue `right` hasta que `u->right == nullptr`. Ambas son iterativas con costo O(h) donde h es la altura.

##### 5. Explica paso a paso cómo funciona `succ()`.
Caso 1: Si el nodo tiene hijo derecho, el sucesor está en ese subárbol. Desciende una vez a la derecha (`s = right`), luego busca el nodo más a la izquierda de ahí (`while (s->left != nullptr) s = s->left`), y retorna ese nodo.
Caso 2: Si no tiene hijo derecho, sube por los ancestros (`while (s->isRightChild()) s = s->parent`) hasta que sea hijo izquierdo de su padre. Entonces retorna el padre (`s->parent`). Si llega a la raíz siendo hijo derecho, retorna nullptr (no hay sucesor).

##### 6. Explica paso a paso cómo funciona `pred()`.
Es simétrico a `succ()`. Caso 1: Si el nodo tiene hijo izquierdo, el predecesor está en ese subárbol. Desciende una vez a la izquierda (`s = left`), luego busca el nodo más a la derecha (`while (s->right != nullptr) s = s->right`), y retorna ese nodo.
Caso 2: Si no tiene hijo izquierdo, sube por los ancestros (`while (s->isLeftChild()) s = s->parent`) hasta que sea hijo derecho de su padre. Retorna el padre. Si llega a la raíz siendo hijo izquierdo, retorna nullptr (no hay predecesor).

##### 7. En `BinTree`, ¿qué papel cumplen `root_` y `size_`?
`root_` es el puntero a la raíz del árbol (nullptr si está vacío). `size_` mantiene el contador de nodos totales. Juntos, representan el estado global del árbol. `size_` se incrementa con cada inserción y se decrementa con cada eliminación, evitando recalcular n nodos.

##### 8. Explica qué hace `updateHeight(Node*)`.
Calcula la altura de un nodo basándose en las alturas de sus hijos: `node->height = 1 + max(stature(left), stature(right))`. Si el nodo es nullptr, retorna -1. El resultado se guarda en `node->height` para consultas O(1) futuras.

##### 9. Explica qué hace `updateHeightAbove(Node*)` y por qué sube hacia la raíz.
Parte de un nodo y sube recursivamente por los padres (`while (node != nullptr)`) llamando `updateHeight(node)` en cada paso. Sube porque cambiar la altura de un nodo puede cambiar la altura de sus ancestros. Es el único modo de mantener las alturas precisas después de insertar/eliminar.

##### 10. Explica cómo `attachAsLC` o `attachAsRC` transfieren un subárbol desde un árbol hacia otro.
Toma un árbol `subtree` y lo cuelga como hijo izquierdo (o derecho) del nodo `parent`. Actualiza `parent->left = subtree.root_`, establece `subtree.root_->parent = parent`, suma `subtree.size_` a `size_` del árbol receptor, y limpia `subtree` (deja `subtree.root_ = nullptr` y `subtree.size_ = 0`). Luego llama `updateHeightAbove(parent)` para actualizar alturas.

##### 11. Explica qué diferencia hay entre `removeSubtree` y `secede`.
`removeSubtree` corta un subárbol y lo destruye (libera memoria con `destroy(node)`). Decrementa `size_` en el árbol padre.
`secede` corta el subárbol pero lo devuelve como un nuevo árbol intacto (sin destruir). El árbol cortado se retorna como `BinTree<T>`. El nodo padre pierde su referencia, pero los nodos desprendidos siguen vivos.

##### 12. Explica por qué `secede` no debe destruir los nodos desprendidos.
Porque el objetivo de `secede` es desacoplar un subárbol para usarlo de forma independiente. Destruir los nodos haría perder el subárbol. En cambio, se retorna un nuevo `BinTree` que toma posesión de esos nodos y los destruirá solo cuando ese nuevo árbol sea destruido.

##### 13. Explica por qué `removeSubtree` sí debe liberar nodos.
Porque `removeSubtree` expresa intención de descartar un subárbol completamente. Si no los libera, habrá memory leak. El código llama `destroy(node)` que recursivamente borra primero los hijos y luego el nodo.

##### 14. Explica qué verifica `checkParentLinks()`.
Verifica la invariante bidireccional: recorre recursivamente todo el árbol y chequea que para cada nodo, `node->parent` apunte correctamente al padre, y que el padre tenga a ese nodo como `left` o `right`. Retorna `false` si encuentra inconsistencia. Útil para detectar corrupción de memoria o bugs en `attach`/`secede`.

##### 15. En `BinaryTree`, explica cómo se implementan `firstNode`, `lastNode`, `nextNode` y `prevNode`.
`firstNode()` retorna `root_->leftmost()` (el nodo más izquierdo del árbol). `lastNode()` retorna `root_->rightmost()` (el más derecho). `nextNode(node)` retorna `node->succ()` (el sucesor inorden). `prevNode(node)` retorna `node->pred()` (el predecesor inorden). Estas cuatro funciones permiten navegación secuencial sin usar pila explícita.

##### 16. Explica por qué un iterador basado en `succ()` produce recorrido inorden.
Por definición, `succ()` retorna el siguiente nodo en orden inorden. El iterador `operator++()` llama `current_ = current_->succ()`, avanzando secuencialmente. Empezar en `firstNode()` (el más izquierdo) y seguir sucesores garantiza visitar todos los nodos en orden inorden: izq, raíz, der, recursivamente.

##### 17. Explica qué aporta `asciiArt()` para depuración y sustentación.
`asciiArt()` genera una representación visual en texto del árbol usando caracteres especiales (┌, └, │). Permite ver la jerarquía real: padres, hijos izq/der, profundidades. En depuración, visualizar el árbol es más útil que confiar ciegamente en recorridos. En sustentación, mostrar el ASCII permite defender visualmente que el árbol se armó correctamente y que los recorridos respetan la estructura esperada.


#### Bloque 7 - Árbol binario de búsqueda: búsqueda, eliminación y rotaciones

##### 1. Define formalmente la propiedad BST.
Para todo nodo `u` en el árbol, todos los valores en su subárbol izquierdo son estrictamente menores que el valor de `u`, y todos los valores en su subárbol derecho son estrictamente mayores (o iguales, si se permiten duplicados).

##### 2. Explica por qué el recorrido inorden de un BST debe producir una secuencia no decreciente.
Porque la definición del inorden (visitar subárbol izquierdo, luego raíz, luego subárbol derecho) coincide exactamente con la propiedad BST (menores, luego actual, luego mayores).

##### 3. Explica la diferencia entre `find`, `findEQ`, `lowerBound` y `upperBound`.
- `find`: Retorna un booleano (si existe o no).
- `findEQ`: Retorna un puntero al nodo exacto que contiene el valor (o nullptr).
- `lowerBound`: Retorna el primer nodo cuyo valor es `>=` al buscado.
- `upperBound`: Retorna el primer nodo cuyo valor es estrictamente `>` al buscado.

##### 4. Explica por qué `findEQ(x)` puede fallar aunque `lowerBound(x)` no falle.
Si buscas `5` pero en el árbol solo están `4` y `6`, `findEQ(5)` retornará `nullptr` porque el 5 exacto no existe. Sin embargo, `lowerBound(5)` no fallará: retornará el nodo `6`, porque es el primer elemento `>= 5`.

##### 5. Construye manualmente el BST que se obtiene al insertar: `7, 3, 10, 1, 5, 8, 12, 4, 6`.
Raíz: 7. Izq de 7: 3. Der de 7: 10.
Hijos de 3: 1 (izq) y 5 (der).
Hijos de 10: 8 (izq) y 12 (der).
Hijos de 5: 4 (izq) y 6 (der).

##### 6. Escribe el inorden, preorden, postorden y recorrido por niveles de ese árbol.
- **Inorden**: 1, 3, 4, 5, 6, 7, 8, 10, 12
- **Preorden**: 7, 3, 1, 5, 4, 6, 10, 8, 12
- **Postorden**: 1, 4, 6, 5, 3, 8, 12, 10, 7
- **Por niveles**: 7, 3, 10, 1, 5, 8, 12, 4, 6

##### 7. Simula `lowerBound(9)` y `upperBound(8)` paso a paso.
- **`lowerBound(9)`**: Empieza en 7. 9 > 7, va a la derecha (10). 9 <= 10, guarda 10 como candidato, va a la izquierda (8). 9 > 8, va a la derecha (nulo). Retorna el mejor candidato: 10.
- **`upperBound(8)`**: Empieza en 7. 8 > 7, va a la derecha (10). 8 < 10, guarda 10 como candidato, va a la izquierda (8). 8 no es menor estricto que 8, va a la derecha (nulo). Retorna: 10.

##### 8. Explica qué casos de eliminación existen en un BST: hoja, un hijo, dos hijos.
- **Hoja**: Se desconecta del padre y se borra directamente.
- **Un hijo**: El nodo se elimina y su único hijo pasa a ocupar su lugar, conectándose directamente con el "abuelo".
- **Dos hijos**: No se puede borrar directamente. Se busca su sucesor (el menor de los mayores), se copia el valor del sucesor al nodo actual, y luego se elimina el nodo original del sucesor (que a lo mucho tendrá un hijo derecho).

##### 9. Explica qué papel cumple `splice` durante una eliminación.
`splice` (empalmar) es la función que maneja el "bypass" físico en la memoria. Cuando eliminas un nodo que tiene un solo hijo (o ninguno), `splice` desconecta el nodo a eliminar y conecta directamente a su padre con su hijo.

##### 10. Después de eliminar una clave, ¿qué invariantes deben seguir siendo ciertos?
La propiedad BST debe mantenerse para todos los nodos restantes. `size_` debe haberse reducido en 1. Las alturas `height` a lo largo del camino hacia la raíz deben haberse actualizado correctamente.

##### 11. Explica por qué `remove(3)` en las pruebas debe conservar el inorden ordenado.
Porque el algoritmo de eliminación garantiza reestructurar el árbol sin violar la regla de que todo lo de la izquierda es menor y lo de la derecha es mayor. Por tanto, el recorrido inorden seguirá arrojando una secuencia puramente ascendente.

##### 12. Explica qué hace `rotateLeft`.
Toma un nodo `P` y su hijo derecho `R`. Hace que `R` suba a la posición de `P`, `P` baja a ser el hijo izquierdo de `R`, y el antiguo hijo izquierdo de `R` pasa a ser el nuevo hijo derecho de `P`. Sirve para balancear ramas derechas pesadas.

##### 13. Explica qué hace `rotateRight`.
La inversa exacta: toma a `P` y a su hijo izquierdo `L`. `L` sube a ocupar el lugar de `P`, `P` baja a ser el hijo derecho de `L`, y el antiguo hijo derecho de `L` pasa a ser el hijo izquierdo de `P`.

##### 14. Demuestra que una rotación local preserva la propiedad BST.
En un `rotateRight(P)`, originalmente tenemos `L < P` y `L.right < P`. Tras la rotación, `P` es el hijo derecho de `L`, lo cual es correcto (`L < P`). El subárbol `L.right` se convierte en el hijo izquierdo de `P`, lo cual también es válido porque sabemos que `L.right > L` y `L.right < P`. El inorden relativo de los subárboles no cambia.

##### 15. Explica para qué sirve construir un BST balanceado desde un arreglo ordenado.
Para garantizar que la altura sea mínima `O(log n)`. Si insertas números ordenados secuencialmente con `insert()`, el árbol se degenera en una lista enlazada `O(n)`. Construirlo tomando el elemento central como raíz asegura el mejor rendimiento posible.

##### 16. Compara el costo de búsqueda en un BST balanceado y en un BST degenerado.
- Balanceado: `O(log n)`. El espacio de búsqueda se reduce a la mitad en cada paso.
- Degenerado: `O(n)`. Se tiene que recorrer nodo por nodo linealmente, perdiendo el beneficio principal de la estructura de árbol.

#### Bloque 8 - Heap binario y representación implícita

##### 1. Explica por qué un heap binario puede almacenarse en un `std::vector` sin punteros.
Porque es un "árbol binario completo". Al no tener huecos en sus niveles superiores y llenarse de izquierda a derecha, se puede mapear perfectamente a un arreglo secuencial utilizando simple aritmética para encontrar los hijos y el padre.

##### 2. Demuestra las fórmulas:
Si dibujamos los índices por niveles: el nivel 0 tiene 1 elemento (índice 0). El nivel 1 tiene 2 (índices 1, 2). El nivel 2 tiene 4 (índices 3, 4, 5, 6).
Por inducción geométrica, el hijo izquierdo de un nodo en el índice `i` siempre cae en `2*i + 1`, y su hijo derecho en `2*i + 2`. Si inviertes la fórmula para hallar el padre, `(2i+1 - 1)/2` y `(2i+2 - 1)/2` te devuelven siempre `(i-1)/2` gracias al truncamiento de los enteros.

##### 3. Define la propiedad de min-heap.
Para cada nodo en un índice `i`, su valor siempre es menor o igual al valor de sus hijos en `2*i + 1` y `2*i + 2`. Por transitividad, el nodo raíz es siempre el mínimo global.

##### 4. Explica por qué `top()` devuelve el mínimo.
Porque, según la definición del min-heap, el nodo más pequeño forzosamente termina flotando hasta la posición superior (el índice 0 del vector), que es exactamente lo que consulta `top()`.

##### 5. Explica paso a paso cómo `bubbleUp(i)` restaura la propiedad de heap después de insertar.
Al insertar, el elemento se coloca al final del arreglo. `bubbleUp` compara el elemento con su padre en `(i-1)/2`. Si el elemento es menor que el padre, están invertidos; entonces los intercambia de lugar (swap) y repite el proceso subiendo por el árbol hasta que el elemento sea mayor que su nuevo padre o alcance la raíz.

##### 6. Explica paso a paso cómo `trickleDown(i)` restaura la propiedad de heap después de eliminar la raíz.
Tras sacar el mínimo y reemplazar la raíz con el último elemento, `trickleDown` agarra ese nuevo elemento en la raíz y lo compara con sus dos hijos. Si es mayor que alguno de ellos, lo intercambia con el **hijo más pequeño** de los dos (para no violar la propiedad de heap entre los hermanos). Esto se repite hundiendo al nodo nivel por nivel hasta que sea menor que sus dos hijos actuales o se convierta en una hoja.

##### 7. Explica por qué `remove()` debe mover el último elemento a la raíz antes de aplicar `trickleDown(0)`.
Para mantener el invariante de que la estructura es un "árbol binario completo" sin huecos. Si borramos la raíz y subimos directamente a los hijos, dejaríamos "huecos" en medio de la estructura que romperían la matemática de los índices `2*i+1`. Mover el último nodo repara la forma, y luego `trickleDown` repara la prioridad.

##### 8. Explica qué verifica `isHeap()`.
Verifica iterativamente (o recursivamente) que a lo largo de todo el arreglo, todos los elementos en la posición `i` sean efectivamente menores o iguales que sus hijos `2*i+1` y `2*i+2`. Es la comprobación algorítmica de la propiedad de min-heap.

##### 9. Compara construir un heap insertando `n` elementos con construirlo usando `heapify()`.
Insertar elemento por elemento empuja el costo del hundimiento/burbujeo hacia las capas más profundas, sumando `O(n log n)`. `heapify()` (de Floyd) trata al arreglo bruto como si ya fuera un heap completo pero roto, y va arreglándolo desde el último nodo padre hacia la raíz aplicando `trickleDown`, lo que resulta más rápido y económico en tiempo.

##### 10. Justifica por qué insertar `n` elementos uno por uno cuesta `O(n log n)` en el peor caso.
Cada inserción puede requerir que el elemento flote (`bubbleUp`) desde el fondo hasta la raíz, lo cual toma `O(log k)` pasos (donde k es el tamaño del heap en ese instante). La suma de los logaritmos de 1 a n es asintóticamente equivalente a `O(n log n)`.

##### 11. Justifica por qué `heapify()` puede ejecutarse en `O(n)`.
Porque la mayoría de los nodos de un heap están en el fondo (en las hojas). `heapify` no hace `trickleDown` a las hojas. A los nodos del penúltimo nivel solo los baja 1 vez, a los del antepenúltimo 2 veces, etc. Matemáticamente, esta suma es una progresión que converge a O(n), no a O(n log n).

##### 12. Ejecuta una extracción completa del heap construido con `{7, 3, 10, 1, 5, 8, 2}` y explica por qué la secuencia extraída sale ordenada.
Primero extraigo el 1 y reordeno el heap. Luego el 2, luego 3, 4, 5, 7, 8, 10. La secuencia sale estrictamente ordenada `[1, 2, 3, 5, 7, 8, 10]` porque, tras cada extracción del mínimo global, `trickleDown` garantiza que el siguiente elemento más pequeño de todo el conjunto suba a la raíz listo para ser la próxima víctima del `delMin()`. A este proceso se le conoce como **HeapSort**.

##### 13. Compara el heap con el BST: ¿cuál estructura conviene para consultar mínimo repetidamente y cuál conviene para búsquedas ordenadas?.
- **Para extraer el mínimo repetidamente:** Conviene usar el Heap. Cuesta O(log n) garantizar el siguiente mínimo, es más amigable con la caché de la CPU porque es un arreglo continuo de bytes en vez de punteros dispersos, y no sufre degeneración.
- **Para búsquedas ordenadas o encontrar un valor "k":** Conviene el BST (preferiblemente balanceado). El heap no está ordenado horizontalmente; buscar el número 7 en un heap te obliga a revisar todos los elementos (O(n)), mientras que en el BST es instantáneo (O(log n)).

#### Bloque 9 - Cierre comparativo y preparación de sustentación

##### Responde esta pregunta final:

¿Qué cambia cuando pasamos de estudiar listas, pilas y colas a diseñar árboles binarios, heaps y árboles binarios de búsqueda?

Al dar el salto desde estructuras lineales (listas, pilas y colas) hacia estructuras de árbol y heaps, el paradigma cambia de simplemente "almacenar y leer en orden cronológico" a **almacenar organizando de manera jerárquica para optimizar la velocidad de operaciones masivas**. A continuación explico los cambios más drásticos:

- **Sobre la representación enlazada con nodos y punteros:** A diferencia de una lista enlazada simple, en los árboles multiplicamos las dimensiones. Un solo nodo ahora dispara ramificaciones con punteros `left` y `right`, lo cual nos permite esquivar recorrer todo secuencialmente y saltar secciones enormes de datos.
- **Sobre la representación implícita en arreglo:** Descubrimos que la memoria jerárquica no necesita forzosamente punteros físicos. Usando matemática de índices básica, podemos simular la jerarquía de un árbol binario completo dentro de un arreglo tradicional (vector), eliminando el overhead de los punteros y disparando el rendimiento en caché de CPU.
- **Sobre la diferencia entre propiedad estructural y propiedad de orden:** La base (BinTree) nos dio la propiedad estructural (cómo se unen los nodos), pero son las reglas aplicadas encima de ella las que definen la utilidad. En el BST es el "orden horizontal", y en el Heap es la "prioridad vertical".
- **Sobre los recorridos como conversores:** Los recorridos (Inorden, Preorden) sirven como traductores. Nos permiten "aplanar" o serializar la estructura jerárquica bidimensional y convertirla en una secuencia unidimensional que podemos imprimir en consola, procesar o enviar.
- **Sobre el mantenimiento de alturas y enlaces `parent`:** Al tener operaciones de `O(log n)`, no podemos permitirnos "bajar hasta las hojas" cada vez para recalcular métricas. Mantener variables locales como `height` y un enlace rápido hacia el `parent` nos permite mantener el árbol actualizado de forma ascendente e iterativa en tiempo casi cero.
- **Sobre el BST y la búsqueda ordenada:** El BST revoluciona el almacenamiento sacrificando la inserción sencilla por una búsqueda asombrosa. Al mantener el árbol rígidamente estructurado, su recorrido inorden es capaz de ordenarse solo, reduciendo las búsquedas exactas al mágico costo logarítmico O(log n).
- **Sobre el Heap y la prioridad:** El Heap descarta cualquier intento de ordenar de izquierda a derecha en favor del pragmatismo. Nos provee `add` en O(log n), `remove` (del mínimo) en O(log n), y gracias a la magia matemática del algoritmo de Floyd, una construcción total `heapify` en apenas O(n).
- **Sobre la evidencia de correctitud:** En la sustentación final, las simples palabras no bastan. Para defender la correctitud de los árboles utilizaría **trazados inorden iterativos** que demuestren que los punteros apuntan bien; utilizaría **los invariantes de `isBST()` o `isHeap()`** que auditan recursivamente la integridad estructural completa, y presentaría los **tiempos de ejecución empíricos** junto con los costos teóricos asintóticos (O(log n)) para demostrar la evidente mejora algorítmica.

### Autoevaluación breve

- Qué puedo defender con seguridad: Cómo los recorridos (inorden, preorden) y las funciones como `succ()` navegan el árbol basándose solo en los punteros left, right y parent.
- Qué todavía confundo: En la eliminación del BST con dos hijos, todavía me cuesta visualizar exactamente cómo se desconecta el sucesor sin romper los punteros del padre del sucesor.
- Qué evidencia usaría en una sustentación: Los `assert` de `checkParentLinks()` y la demostración de que `inorder` iterativo y recursivo dan lo mismo.
- Qué parte del código me parece más importante para revisar otra vez: Las funciones de manipulación estructural masiva (`secede` y `attach`), porque manejar tantos punteros a la vez es el lugar más fácil para dejar un memory leak o un segment fault.