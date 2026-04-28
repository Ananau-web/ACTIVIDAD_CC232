## Actividad 3-CC232

### Integrantes
- RYDELL JONEL MOSQUERA HUAYHUA

#### Bloque 1 - Núcleo conceptual de la semana

Respondan:

##### 1. Expliquen con sus palabras qué cambia cuando una estructura pasa de almacenamiento contiguo a almacenamiento dinámico.
- Al pasar de alamacenamiento continuo a dinámico, desaparece la correspondencia directa entre el orden lógica de los datos y su posición física en la memoria.
- En lugar de disponerse en bloques físicos consecutivos, la secuencia se mantiene de forma dinámica mediante referencias(punteros) que conectan nodos dispersos.
##### 2. Expliquen la diferencia entre acceso por rango y acceso por posición o enlace.
- El acceso por rango (típico en arreglos) asume que la posición física de cualquier elemento puede calcularse matemáticamente de forma directa y en tiempo constante.
- El acceso por enlace implica que no se puede saltar directamente a una posición; obliga a recorrer la estructura de forma secuencial, siguiendo las referencias nodo por nodo hasta descubrir la ubicación del dato.
##### 3. Expliquen por qué una lista enlazada mejora inserciones y eliminaciones locales, pero empeora el acceso por índice.
- El acceso por índice empeora porque, al no estar en bloques contiguos, es forzoso navegar secuencialmente la cadena de punteros desde un extremo para localizar un elemento profundo.
- Por otro lado, las inserciones y eliminaciones mejoran significativamente porque, una vez encontrada la posición de trabajo, solo hace falta reasignar una cantidad constante de referencias locales, evitando los costosos desplazamientos en masa de los arreglos contiguos.
##### 4. Expliquen por qué `SLList` implementa bien operaciones de `Stack` y `Queue`.
- Una lista simplemente enlazada (SLList) resulta muy eficaz para implementar una pila (Stack) dado que las operaciones de inserción y retiro en el inicio (la cabeza) se completan en tiempo constante reasignando la primera referencia.
- También implementa bien una cola (Queue) si mantiene un puntero adicional hacia el nodo final, permitiendo agregar elementos al final y retirarlos del frente de manera inmediata sin tener que recorrer toda la estructura.
##### 5. Expliquen por qué `SLList` no implementa naturalmente todas las operaciones de un `Deque` con el mismo costo.
- La estructura Deque requiere poder insertar y eliminar con alta eficiencia en ambos extremos (frente y final).
- La SLList carece de esta capacidad bidireccional uniforme, ya que, para eliminar un elemento en el extremo final, debe actualizar la referencia proveniente del nodo penúltimo; como sus enlaces solo van hacia adelante, la única manera de encontrar al penúltimo es recorriendo la lista completa desde el inicio.
##### 6. Expliquen qué aporta el nodo centinela `dummy` en `DLList`.
- El nodo centinela actúa como un eslabón ficticio que une el final con el inicio, sirviendo como predecesor del primer nodo y sucesor del último para formar un ciclo.
- Su principal beneficio es simplificar drásticamente el código, logrando que casos que normalmente requerirían validaciones especiales (insertar en una lista vacía, agregar al final o eliminar el único nodo) se manejen con la misma lógica unificada sin preocuparse por manejar punteros nulos.
##### 7. Expliquen por qué `DLList` permite justificar `get(i)`, `set(i,x)`, `add(i,x)` y `remove(i)` con costo `O(1 + min(i, n-i))`.
- Este costo refleja la ventaja estratégica de una lista con enlaces en ambos sentidos: la capacidad de elegir el camino más corto.
- Si el índice buscado i está en la primera mitad, se localiza avanzando desde la cabeza (costando proporcional a `i`); si está en la segunda mitad, se localiza retrocediendo desde la cola (costando proporcional a `n-i`), y una vez situado, las modificaciones propias de add, remove o set se realizan en tiempo constante.
##### 8. Expliquen cuál es la idea espacial central de `SEList`.
- Las listas enlazadas tradicionales sufren de una fuerte sobrecarga de memoria debido a que se asignan múltiples punteros para almacenar un único elemento.
- La SEList resuelve este desperdicio agrupando los elementos en bloques acotados por cada nodo, de forma que el gran costo de almacenamiento de las referencias estructurales se diluye y reparte entre múltiples datos.
##### 9. Expliquen por qué `SEList` reutiliza una `BDeque` basada en `ArrayDeque`.
- La SEList delega el almacenamiento interno de cada uno de sus nodos a un arreglo dinámico pequeño (ArrayDeque), lo que permite realizar inserciones y desplazamientos en un nivel microscópico sin consumir referencias adicionales.
- En conjunto, la estructura logra comportarse como una lista enlazada eficiente a nivel macro (viajando de bloque en bloque) y aprovechando la velocidad y compacidad de un arreglo secuencial a nivel micro.
##### 10. Expliquen qué papel cumple `DengList` dentro de esta semana y por qué no reemplaza a las estructuras de Morin.
- Basado en el concepto de puentes propuesto en los archivos de la semana (`MorinDengBridge`), la DengList proporciona un terreno robusto y bien acoplado para ejecutar fácilmente algoritmos de ordenamiento, manipulaciones profundas y deduplicación a nivel de nodos.
- No reemplaza a las estructuras de Morin (`SLList`, `DLList`, `SEList`) porque las listas de Morin están especializadas milimétricamente para responder a interfaces de colas, pilas y balances de memoria muy concretos con complejidades óptimas, mientras que la lista de Deng sirve más como un formato puente para facilitar el despliegue de procesos algorítmicos transversales sin tener que reinventarlos para cada adaptación.

#### Bloque 2 - Demostración y trazado guiado


##### 1. En `demo_sllist.cpp`, ¿qué secuencia deja más clara la coexistencia de comportamiento tipo pila y tipo cola dentro de `SLList`?
La coexistencia queda clara al intercalar operaciones: se utiliza `q.add(10)` y `q.add(20)` para agregar elementos al final y `q.remove()` para extraer del frente (comportamiento tipo *Queue*), y en la misma estructura se invoca `q.push(5)` y `q.pop()` para insertar y extraer en el tope o frente (comportamiento tipo *Stack*).
##### 2. En `demo_dllist.cpp`, ¿qué operación muestra mejor la inserción en una posición intermedia?
La inserción de los elementos 30 y 20 en la misma posición relativa: `d.add(1, 30); d.add(1, 20);`. El resultado `10 20 30` evidencia cómo los punteros previos y siguientes se reasignan localmente empujando al 30 hacia adelante para hacer lugar al 20 sin reubicar toda la lista.
##### 3. En `demo_selist.cpp`, ¿qué observable permite defender que la lista mantiene orden lógico aunque internamente trabaje por bloques?
El hecho de poder iterar usando un ciclo secuencial normal `for (int i = 0; i < s.size(); ++i)` e invocar `s.get(i)` para imprimir exactamente `0 10 20 30... 90` en orden ascendente. Aunque la memoria esté particionada en bloques de tamaño 3, la interfaz matemática del índice permanece inalterada y transparente para el usuario.
##### 4. En `demo_deng_list.cpp`, ¿qué evidencia muestra que la lista reforzada por Deng ofrece operaciones más cercanas a un ADT de lista completo?
La capacidad de invocar el método interno `lista.sort()` directamente sobre la estructura y recibir la salida ordenada `5 10 20 30` mediante el utilitario integrado `to_vector()`. Las estructuras estándar de Morin carecen de estos algoritmos complejos embebidos.
##### 5. En `demo_morin_deng_bridge.cpp`, ¿qué parte de la salida permite justificar que se reutilizan algoritmos sin reescribir la estructura base?
El observable donde se pasa un objeto crudo `ods::DLList` a las funciones `cc232::stable_sort_with_deng(lista)` y `cc232::dedup_with_deng(lista)`, obteniendo como resultado un arreglo sin duplicados (`1 2 3 4`) y la confirmación de `Removido = 1`. Esto justifica que el algoritmo reside en un puente aislado y no contamina la base original de la `DLList`.
##### 6. En `demo_min_structures.cpp`, ¿qué diferencia conceptual observan entre almacenar valores y almacenar información adicional para responder `min()`?
Se observa que mientras la consulta estándar `ms.top()` requiere solo extraer la variable de datos normal, la consulta paralela `ms.min()` entrega de inmediato la respuesta sin recorrer la lista, demostrando conceptualmente que en la fase de inserción se gastó memoria extra (un caché) para preservar el estado histórico de los mínimos y garantizar que la respuesta cueste `O(1)`.
##### 7. En `demo_linked_adapters.cpp`, ¿qué adaptador representa mejor la idea de reutilizar una estructura existente para ofrecer una interfaz nueva?
Aunque los tres son grandes ejemplos, `LinkedStack<int> st` ilustra perfectamente la idea al restringir de forma tajante su API para proveer únicamente `push()`, `pop()` y `top()`. Todo el motor interno y la complejidad asintótica se heredan directamente de la base (`SLList`), pero bloqueando cualquier acceso aleatorio o por la cola que rompa el contrato LIFO.
##### 8. En `demo_contiguous_vs_linked.cpp`, ¿qué contraste se observa entre acceso por índice, inserción local y localidad de memoria?
Se evidencia que las estructuras contiguas (`ArrayDeque`) brillan al efectuar saltos instantáneos (`adq.get(4)`) aprovechando su almacenamiento físico alineado, lo que genera una alta localidad de memoria y mejor rendimiento en la caché del procesador. En contraparte, se observa que las listas enlazadas son superiores gestionando la manipulación local (inserciones en extremos o centro) porque no sufren el enorme costo computacional de desplazar toda la cadena de memoria.
## Tabla Resumen de Demostraciones

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo, espacio o diseño |
| :--- | :--- | :--- | :--- |
| `demo_sllist.cpp` | `size = 3`, `peek = 5`, `pop = 5`, `remove = 10` | Lista enlazada unidireccional básica. | Operaciones en extremos (frente/final) son `O(1)`, muy económica en uso de memoria. |
| `demo_dllist.cpp` | La secuencia impresa: `10 20 30` | Lista doblemente enlazada, navegación simétrica. | La inserción arbitraria `add(i, x)` cuesta `O(1 + min(i, n-i))`, balanceando recorridos. |
| `demo_selist.cpp` | `SEList: 0 10 20 30 40 50 60 70 80 90` | Lista desenrollada (nodos son bloques tipo `BDeque`). | Diluye el desperdicio de punteros (espacio) empaquetando varios elementos por bloque. |
| `demo_deng_list.cpp` | `ordenada: 5 10 20 30` | ADT de lista rica con algoritmos integrados (`sort`). | Encapsula el comportamiento algorítmico de manera nativa sin exponer los punteros. |
| `demo_morin_deng_bridge.cpp` | `DLList reforzada con Deng: 1 2 3 4`, `Removido = 1` | Uso del patrón adaptador/puente algorítmico. | Permite aplicar `sort` o `dedup` en listas de Morin sin tener que reescribir la lógica por estructura. |
| `demo_capitulo3_panorama.cpp` | Carga e inicialización de 7 estructuras distintas con sus consultas a extremos | Visión general y unificada de todas las secuencias lineales. | Demuestra que interfaces abstractas similares ocultan implementaciones asintóticamente distintas. |
| `demo_min_structures.cpp` | Reporte en tiempo real de `min()` junto a `top()` o `front()` para Stack, Queue y Deque | Estructuras lineales enriquecidas para guardar mínimo global. | Sacrifica una cantidad `O(n)` de espacio para tener un reporte del valor mínimo en tiempo `O(1)`. |
| `demo_xor_list.cpp` | `5 10 20`, `front=5`, `back=20` | Simulación de lista doble mediante aritmética de punteros (XOR). | Logra navegación bidireccional usando la misma cantidad de memoria (1 puntero) que una `SLList`. |
| `demo_linked_adapters.cpp` | Pruebas de `LinkedStack`, `LinkedQueue` y `LinkedDeque` | Restricción de interfaces mediante el patrón Adaptador. | Reutiliza código sólido existente para forzar restricciones estables (LIFO/FIFO). |
| `demo_contiguous_vs_linked.cpp` | Comparativa de accesos y el resumen impreso en "Observaciones" | Contigüidad física (Arrays) vs. Enlaces dinámicos. | Arreglos ganan en localidad de caché; Listas ganan en borrados/inserciones sin desplazamiento masivo. |

#### Bloque 3 - Pruebas públicas, stress y correctitud


##### 1. ¿Qué operaciones mínimas valida la prueba pública para `SLList`?
Valida la inserción mediante add(x) (al final) y push(x) (al inicio), la consulta de tamaño con size(), la observación del tope con peek(), la extracción del frente con pop(), y la extracción simulada general con remove().
##### 2. ¿Qué operaciones mínimas valida la prueba pública para `DLList`?
Valida la inserción por índice posicional explícito add(i, x), la recuperación por índice get(i), el borrado por índice remove(i) y la cantidad de elementos a través de size().
##### 3. ¿Qué operaciones mínimas valida la prueba pública para `SEList`?
Al igual que en DLList, valida inserción, lectura y borrado por índice (add(i, x), get(i), remove(i)), además del tamaño (size()), sumando explícitamente la operación de sobreescritura in-place set(i, x).
##### 4. ¿Qué operaciones nuevas quedan cubiertas por `test_public_extras.cpp`?
- En SLList: Inserción por índice interno add(i, x), obtención del penúltimo elemento secondLast(), inversión reverse(), y chequeos de consistencia con checkSize().
- En DLList: Rotación circular rotate(r) y evaluación de palíndromos simétricos isPalindrome().
- También introduce pruebas para las variantes con mínimo (MinStack, MinQueue, MinDeque) con su operación extra min(), y para la lista doblemente enlazada construida con lógica XOR (XorList) validando sus extremos y su reversión.
##### 5. ¿Qué valida específicamente `test_public_linked_adapters.cpp` sobre `LinkedStack`, `LinkedQueue` y `LinkedDeque`?
Valida que cada clase adaptadora expone y defiende de manera estricta únicamente la interfaz permitida por su modelo de datos abstracto: LinkedStack solo reacciona con lógica LIFO (push, pop, top), LinkedQueue aplica disciplina FIFO (add, remove, front), y LinkedDeque defiende operaciones eficientes exclusivas en ambos extremos (addFirst/addLast, removeFirst/removeLast, front/back). Además verifica que el control de vaciado empty() sea coherente.
##### 6. ¿Qué demuestra `test_public_deng_bridge.cpp` sobre integración y reutilización?
Demuestra cómo el patrón puente permite tomar listas que pertenecen a la familia de Morin (como DLList o SEList) y, sin necesidad de reescribir la estructura base internamente, aplicarles algoritmos avanzados originarios del paquete de Deng. Se evidencia pasando estas listas crudas por funciones adaptadoras externas como stable_sort_with_deng, dedup_with_deng y reverse_with_deng que mutan correctamente el estado original.
##### 7. En `stress_selist_week3.cpp`, ¿qué comportamiento intenta estresar sobre crecimiento, borrado y mantenimiento del tamaño lógico?
Intenta estresar los umbrales de reacomodo de bloques (mecanismos tipo spread y gather) configurando un límite de bloque estricto (b=8). Agrega 500 elementos de golpe para forzar al límite el fraccionamiento de la memoria, luego retira de manera masiva 250 elementos (forzando colapso o fusión de bloques vacíos) y finalmente inyecta otros 100 al inicio para provocar desplazamientos profundos. Evalúa si, tras esa tortura geométrica, los eslabones no se rompieron y el size() calculado lógicamente es exactamente 350.
##### 8. ¿Qué sí demuestra una prueba pública sobre una estructura enlazada?
Demuestra la correctitud funcional bajo escenarios del "camino feliz" (happy paths). Verifica que si a la estructura se le aplican secuencias controladas de ingresos y egresos de datos, esta devolverá respuestas lógicamente esperadas en concordancia con su contrato matemático de caja negra.
##### 9. ¿Qué no demuestra una prueba pública por sí sola?
Por sí sola, no puede garantizar que el código se ejecute dentro de las cotas de tiempo (complejidad O-grande) prometidas para las operaciones, no asegura la ausencia de pérdidas de memoria a nivel de sistema operativo (memory leaks o nodos huérfanos que nunca se destruyeron), ni evidencia cómo resistirá la estructura ante índices extremos o malintencionados.
##### 10. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes, punteros y complejidad?
Porque un desarrollador podría implementar fraudulentamente un DLList utilizando en el fondo un arreglo primitivo que recalcula todos los datos (costando $O(N)$ en lugar de $O(1)$ para las inserciones); esto pasaría las pruebas unitarias al dar el resultado exacto, pero sería una arquitectura inservible y contraria al paradigma del enlace . Explicar invariantes y manipulación manual de punteros garantiza que el alumno domina no solo el "qué" sale del código, sino el "cómo" y a "qué costo" se mantiene el estado dinámico en memoria.

#### Bloque 4 - SLList, DLList y SEList: lectura cercana del código

##### 1. `SLList`: `head`, `tail` y `n`
* **`head`**: Es el puntero que dirige al primer nodo de la secuencia. Permite realizar operaciones en el tope/frente (como `push` y `pop`) en tiempo $O(1)$.
* **`tail`**: Es el puntero que dirige al último nodo. Su presencia evita tener que recorrer toda la lista para insertar un elemento al final, permitiendo que la operación `add` (encolar) sea $O(1)$.
* **`n`**: Es un contador entero que almacena la cantidad actual de elementos lógicos en la lista. Permite que la función `size()` retorne el tamaño en $O(1)$ en lugar de iterar la estructura.
##### 2. Punteros en `SLList::push`, `pop`, `add` y `remove`
* **`push(x)`**: Se crea un nuevo nodo. El `next` de este nodo se enlaza al actual `head`. Luego, `head` se actualiza para apuntar al nuevo nodo. Si la lista estaba vacía, `tail` también se enlaza al nuevo nodo.
* **`pop()` (y `remove()` en el frente)**: El puntero `head` se reasigna para apuntar al siguiente nodo (`head = head->next`). El nodo antiguo se libera de la memoria. Si al hacer esto la lista queda vacía, `tail` se establece a `null`.
* **`add(x)`**: Se crea un nodo nuevo. El `next` del antiguo `tail` se actualiza para apuntar a este nuevo nodo. Luego, `tail` avanza hacia el nuevo nodo. Si la lista estaba vacía, tanto `head` como `tail` apuntan al nuevo nodo.
##### 3. Funcionamiento de `secondLast()`
La función `secondLast()` busca obtener el penúltimo nodo de la lista. En una `SLList` (simplemente enlazada), los nodos solo tienen un puntero `next` hacia adelante. Por lo tanto, no es posible usar `tail` y simplemente retroceder un paso. Para encontrar el penúltimo, el algoritmo debe iniciar en `head` y recorrer la lista de forma iterativa comprobando si el siguiente del siguiente nodo es nulo (`current->next->next == null`) o si el siguiente es la cola (`current->next == tail`).
##### 4. Funcionamiento de `reverse()`
Invierte los enlaces de la lista *in-place* sin usar estructuras adicionales de almacenamiento. Se usan tres punteros móviles: `prev` (inicializado en nulo), `curr` (inicializado en `head`) y `next`.
1.  En cada iteración, `next` guarda temporalmente el resto de la lista (`curr->next`).
2.  El puntero de avance se invierte: `curr->next = prev`.
3.  Los punteros base se desplazan una posición adelante: `prev` toma el lugar de `curr`, y `curr` toma el lugar de `next`.
4.  Cuando `curr` llega al final, el antiguo `head` pasa a ser el `tail`, y el último nodo procesado (`prev`) se convierte en el nuevo `head`.
No requiere memoria adicional ($O(1)$ espacial) porque recicla y reconecta los mismos nodos que ya existen.
##### 5. `checkSize()` como defensa de correctitud
La función `checkSize()` recorre la lista nodo por nodo desde `head` hasta llegar a nulo, sumando manualmente cuántos eslabones existen en memoria real. Al finalizar, compara esta cuenta física con la variable interna `n`. Esto defiende la correctitud de la estructura porque permite detectar corrupciones en el estado interno (como *memory leaks*, enlaces rotos o actualizaciones omitidas de `n` tras un borrado o inserción).
##### 6. `DLList::getNode(i)` bidireccional
Como `DLList` es doblemente enlazada, posee enlaces `prev` y `next`. `getNode(i)` optimiza la búsqueda preguntando primero en qué mitad de la lista está el índice `i`. Si $i < n/2$, recorre hacia adelante desde el inicio. Si $i \ge n/2$, recorre hacia atrás desde el final. Esto reduce a la mitad el tiempo máximo de búsqueda, garantizando una complejidad asintótica de $O(1 + \min(i, n-i))$.
##### 7. Punteros en `DLList::addBefore` y el nodo centinela
Para insertar un nuevo nodo `u` antes de un nodo existente `w`, se actualizan cuatro referencias:
1.  `u->prev = w->prev`
2.  `u->next = w`
3.  `u->prev->next = u`
4.  `w->prev = u`
El nodo centinela (`dummy`) elimina los casos borde porque garantiza que todo nodo (incluso el "primero" y el "último") siempre tenga un predecesor y un sucesor válidos. Así, nunca hay que hacer comprobaciones de punteros nulos (ej. `if (w->prev == null)`) ni manipular explícitamente casos especiales para listas vacías.
##### 8. `rotate(r)` sin desplazar datos
En una lista contigua, rotar implica reubicar cada dato. En una `DLList`, `rotate(r)` simplemente encuentra el nodo que ocupará la nueva primera posición, rompe los enlaces que lo conectan con su predecesor, e injerta esa porción desconectada al final de la lista. Todo se logra actualizando solo un puñado de referencias alrededor de `dummy` y el punto de corte temporal.
##### 9. `isPalindrome()` en listas dobles
Aprovecha directamente la cualidad bidireccional mediante el uso de dos punteros que se cruzan: uno avanza hacia la derecha desde el `dummy->next` (inicio lógico) y otro retrocede hacia la izquierda desde el `dummy->prev` (final lógico). En cada iteración se comprueba que el valor de ambos nodos sea idéntico. Es naturalmente eficiente porque ir hacia atrás no cuesta nada adicional.
##### 10. Representación de `Location` en `SEList`
En una lista desenrollada (`SEList`), los elementos no están solos, sino empaquetados en bloques (`BDeque`). `Location` es una abstracción que responde a la pregunta de dónde está un elemento lógico almacenando dos coordenadas concretas: la referencia al nodo (bloque) específico que lo contiene, y el índice local (`index`) de ese elemento dentro del arreglo interno del bloque.

##### 11. `spread()` y `gather()` en `SEList`
Son operaciones de rebalanceo de la estructura de bloques para asegurar que cada bloque mantenga la ocupación exigida (normalmente $b-1$, $b$ o $b+1$ elementos):
* **`spread(u)`**: Se invoca cuando, tras una inserción, el bloque `u` supera su capacidad límite. Esparce (desplaza) los elementos sobrantes hacia los bloques vecinos o, si estos también están llenos, crea un nuevo nodo en el centro.
* **`gather(u)`**: Se invoca tras un borrado cuando el bloque `u` queda subpoblado. Recolecta elementos de los bloques adyacentes o fusiona el bloque `u` con otro cercano si ambos tienen muy pocos elementos, eliminando el nodo vacío para evitar fugas de memoria.

##### 12. El tamaño de bloque `b` como punto de compromiso
El tamaño `b` regula qué tanto se parece `SEList` a un arreglo o a una lista:
* **Si `b` es muy alto:** Mejora el uso del espacio (menos punteros desperdiciados) y el acceso por índice se acelera debido a saltos masivos entre bloques y la localidad del caché de CPU. Sin embargo, inserciones/borrados aleatorios se vuelven más lentos porque los desplazamientos masivos internos simulan el comportamiento de un arreglo.
* **Si `b` es muy bajo:** Su comportamiento y costo se aproximan al de una `DLList` convencional. Los desplazamientos internos son ultrarrápidos, pero se pierde la ventaja espacial al gastar memoria excesiva en punteros.


#### Bloque 5 - Adaptadores y estructuras derivadas

##### 1. ¿Cómo reutiliza `LinkedStack` a `SLList`?
* `LinkedStack` actúa como un envoltorio (wrapper) que restringe la interfaz de `SLList` para asegurar un comportamiento LIFO.
* La operación `push(x)` llama a `list.push(x)` para insertar en la cabeza.
* La operación `pop()` invoca a `list.pop()` para extraer de la cabeza, garantizando un rendimiento de $O(1)$.

##### 2. ¿Cómo reutiliza `LinkedQueue` a `SLList`?
* De manera similar al caso anterior, `LinkedQueue` envuelve una `SLList` pero expone una interfaz FIFO.
* El método `add(x)` utiliza `list.add(x)` para insertar elementos al final de la lista de forma eficiente gracias al puntero `tail`.
* El método `remove()` utiliza `list.remove()` para extraer el elemento de la cabeza de la lista.

##### 3. ¿Por qué `LinkedDeque` se construye naturalmente sobre `DLList` y no sobre `SLList`?
* Una estructura `Deque` requiere que las inserciones y eliminaciones en ambos extremos tengan un costo constante de $O(1)$.
* Una `SLList` no puede eliminar elementos del extremo final eficientemente porque necesita conocer el nodo previo, lo que obliga a recorrer toda la lista.
* La `DLList`, al poseer enlaces en ambas direcciones y un nodo centinela, soporta las operaciones necesarias de `add(0, x)`, `add(size, x)`, `remove(0)` y `remove(size-1)` en tiempo $O(1)$, haciendo que la adaptación del `Deque` sea trivial.

##### 4. En `MinStack`, ¿por qué cada entrada guarda el valor y el mínimo acumulado?
* Almacenar el mínimo acumulado en la estructura interna `Entry` (junto al valor real) permite que la pila "recuerde" cuál era el elemento más pequeño en cada nivel histórico de profundidad.
* Cuando se inserta un nuevo valor, solo se compara con el `current_min` de la cima anterior; al hacer `pop()`, el mínimo histórico previo queda expuesto automáticamente.
* Esta técnica sacrifica memoria extra para asegurar que la consulta de la función `min()` responda de manera instantánea en $O(1)$.

##### 5. En `MinQueue`, ¿por qué usar dos pilas permite mantener semántica FIFO y consulta de mínimo?
* Una cola estándar sufre el problema de que, al retirar un elemento del frente, se pierde el conocimiento del mínimo si dicho elemento era el menor de la estructura.
* Al dividir la cola en dos pilas (`in_` y `out_`), se puede reutilizar la capacidad de retención de mínimos de `MinStack`.
* Los elementos ingresan a la pila `in_` y, cuando se requiere una extracción, se trasladan a la pila `out_` invirtiendo su orden para respetar la semántica FIFO.
* El mínimo global de toda la cola es simplemente el menor de los mínimos reportados por cada una de las dos pilas en tiempo $O(1)$.

##### 6. En `MinDeque`, ¿qué problema resuelve el rebalanceo entre `front_` y `back_`?
* En un deque se pueden extraer elementos de ambos extremos (frente o final).
* Si una de las pilas internas (`front_` o `back_`) queda vacía y el usuario pide extraer de ese extremo, la operación fallaría a pesar de que la otra pila podría tener todos los elementos acumulados.
* La función `rebalance()` previene este colapso extrayendo un volcado completo (`snapshotOrder()`) de los datos y reconstruyendo la estructura repartiendo los elementos equitativamente a la mitad entre ambas pilas.

##### 7. Comparen "implementar una estructura" y "adaptar una estructura existente" usando ejemplos de este bloque.
* Implementar una estructura, como se observa en `SLList` y `DLList`, requiere programar desde cero la lógica interna de la memoria, instanciar nodos, controlar variables como contadores y punteros, y mantener invariantes complejos.
* Adaptar una estructura, usando el patrón de diseño Adapter como en `LinkedStack` o `LinkedQueue`, consiste en encapsular una implementación funcional preexistente y restringir su API al exterior.
* La adaptación promueve el reciclaje de código robusto, evitando reinventar algoritmos de manipulación de punteros propensos a errores.

##### 8. ¿Qué operaciones pueden defender como constantes y cuáles deben defender como amortizadas?
* **Operaciones Constantes ($O(1)$):** Todas las consultas elementales y operaciones en `LinkedStack`, `LinkedQueue` y `LinkedDeque` (que solo invocan extremos), además del `push`, `pop`, `top` y `min` de `MinStack`.
* **Operaciones Amortizadas:** Las extracciones o lecturas en `MinQueue` (`remove()`, `front()`) y `MinDeque` (`front()`, `back()`, `removeFirst()`, `removeLast()`).
* Estas últimas se defienden como amortizadas porque funciones como `moveIfNeeded()` o `rebalance()` realizan ciclos de costo lineal ($O(n)$) para mover los datos entre pilas, pero estas reubicaciones masivas ocurren con una frecuencia tan baja que el costo promedio por cada operación individual se diluye a constante.


#### Bloque 6 - Deng como refuerzo algorítmico y puente de integración

##### 1. ¿Qué operaciones del ADT de lista aparecen reforzadas en `DengList`?
`DengList` actúa como un Tipo de Dato Abstracto (ADT) de lista enriquecido. Las operaciones que aparecen reforzadas (ausentes en las implementaciones minimalistas) incluyen algoritmos de mutación y búsqueda de alto nivel como:
* `sort()` / `stable_sort()` para ordenamiento interno.
* Consultas lógicas y posicionales como `contains(x)` y `find_index(x)`.
* Utilidades de conversión como `to_vector()`.

##### 2. ¿Qué ventaja tiene encapsular una lista más rica sin cambiar el resto de estructuras de Semana 3?
Mantener el código de `DengList` separado permite cumplir con el Principio de Responsabilidad Única. Las estructuras bases de Morin (`SLList`, `DLList`, `SEList`) se mantienen puras, minimalistas y enfocadas estrictamente en ilustrar la gestión interna de la memoria (enlaces, centinelas, bloques) y sus complejidades asintóticas para insertar/borrar. Al encapsular los algoritmos complejos en `DengList`, no se "contamina" ni se infla innecesariamente el código de las estructuras de Morin.

##### 3. Expliquen qué hacen `to_deng` y `assign_from_deng`.
Estas funciones forman el núcleo del patrón adaptador/puente:
* **`to_deng`**: Extrae secuencialmente los elementos de una estructura base (como una `DLList` o `SEList`) y los inserta temporalmente en una nueva instancia de `DengList`.
* **`assign_from_deng`**: Realiza el paso inverso; vacía completamente la estructura original e inserta en ella los elementos que ya fueron procesados y organizados dentro de la `DengList`.

##### 4. Expliquen por qué `stable_sort_with_deng` no obliga a reimplementar ordenamiento dentro de `DLList` o `SEList`.`stable_sort_with_deng`
En lugar de escribir lógica compleja de manipulación de punteros para ordenar una `DLList` o redistribuir bloques para ordenar una `SEList`, `stable_sort_with_deng` simplemente exporta los datos hacia la `DengList`. Una vez en la `DengList`, se aplica el algoritmo de ordenamiento nativo centralizado y, finalmente, se regresan los datos ordenados a su contenedor original. Esto garantiza que el algoritmo de ordenamiento se escriba y se mantenga en un solo lugar.

##### 5. Expliquen qué hace `dedup_with_deng` y qué relación guarda con `deduplicate()` o `uniquify()` de la teoría.
Esta función elimina las ocurrencias repetidas de elementos adyacentes o globales dentro de la estructura, retornando un número entero que representa la cantidad exacta de nodos removidos. En el marco teórico, esto responde a la necesidad de purificar secuencias para transformarlas en conjuntos lógicos únicos; corresponde a operaciones algorítmicas canónicas (a menudo referidas como `uniquify` para listas ordenadas o `deduplicate` para listas generales).

##### 6. Expliquen por qué `reverse_with_deng` es un ejemplo de reutilización de algoritmos sobre una interfaz común.
Invertir directamente los eslabones de una estructura matricial/desenrollada como `SEList` requeriría desensamblar bloques internos y reasignar índices, lo que sería propenso a errores graves de memoria. Gracias al puente, `reverse_with_deng` extrae el flujo de datos, lo invierte en el entorno seguro de `DengList` y lo inyecta de vuelta. Así, cualquier estructura que exponga una interfaz mínima de iteración e inserción puede ser invertida sin tocar su código interno.

##### 7. ¿Qué costo adicional introduce la conversión entre estructuras y cuándo vale la pena aceptarlo?
* **Costo:** El mecanismo puente introduce un costo temporal de $O(n)$ por extraer y reinyectar los datos, además de un costo espacial de $O(n)$ por instanciar la `DengList` auxiliar.
* **Justificación:** Vale la pena aceptarlo cuando la operación algorítmica principal (como un ordenamiento en $O(n \log n)$) domina el tiempo de ejecución de la simple copia lineal, o cuando desarrollar dicho algoritmo directamente sobre la estructura base (ej. invertir una `SEList`) es demasiado complejo. Prioriza la seguridad, mantenibilidad y modularidad de la arquitectura por encima de una optimización extrema del espacio.

#### Bloque 7 - Comparación enlazado vs contiguo, variantes y evidencia experimental

##### 1. Comparen `ArrayDeque` y `LinkedDeque`: ¿qué cambia en representación y qué cambia en costo observable?
* **Representación:** `ArrayDeque` utiliza un bloque de memoria física contigua (típicamente un arreglo circular) gobernado por índices para administrar la secuencia. `LinkedDeque`, en cambio, utiliza almacenamiento dinámico disperso; la secuencia se define lógicamente mediante nodos conectados por referencias dobles.
* **Costo observable:** El acceso aleatorio por índice en `ArrayDeque` es instantáneo en tiempo $O(1)$, mientras que en `LinkedDeque` cuesta $O(1 + \min(i, n-i))$ por la obligación de recorrer los eslabones. En compensación, las modificaciones en los extremos del `ArrayDeque` pueden disparar costosos redimensionamientos del arreglo subyacente (costo amortizado), mientras que el `LinkedDeque` mantiene un costo estricto de $O(1)$ constante puro para sus operaciones de frente y final.
##### 2. ¿Qué significa que una representación contigua tenga mejor localidad de memoria?
La mejor localidad de memoria significa que los datos están agrupados consecutivamente en el hardware físico (RAM). Esto permite que el procesador cargue bloques enteros de datos en la memoria caché ultrarrápida (L1/L2/L3) en una sola operación. Como resultado, iterar un arreglo es abrumadoramente más veloz en la práctica que saltar entre direcciones aleatorias dispersas en el *heap*, como ocurre al seguir los punteros de una lista enlazada.
##### 3. ¿Qué tipo de operaciones favorecen más a la representación enlazada?
Las estructuras enlazadas brillan en la inserción y eliminación puramente local. Una vez que se tiene la referencia o puntero a un nodo específico, agregar o quitar un elemento en esa posición es instantáneo ($O(1)$). Esto no obliga a empujar o desplazar masivamente la memoria subsiguiente, lo cual es el gran talón de Aquiles de las estructuras contiguas.
##### 4. En el benchmark, ¿qué comparación sirve mejor para discutir acceso aleatorio y cuál sirve mejor para discutir operaciones en extremos?
* **Acceso aleatorio:** La mejor comparación es ejecutar lecturas intermedias intensivas, como medir el tiempo de invocar `get(n/2)` miles de veces entre un `ArrayDeque` y una `DLList` o `LinkedDeque`. El `ArrayDeque` ganará de manera aplastante por el acceso directo.
* **Operaciones en extremos:** La mejor comparación es saturar la estructura inyectando y extrayendo simultáneamente por ambos lados (`addFirst`, `removeLast`). Aquí se evaluará si las operaciones de reserva de memoria dinámica por nodo (`LinkedDeque`) son más veloces que la sobrecarga algorítmica de reconstruir y copiar el arreglo entero cuando este agota su capacidad o se vacía demasiado (`ArrayDeque`).
##### 5. ¿Por qué el benchmark no debe leerse como prueba absoluta de superioridad de una estructura sobre otra?
Un benchmark no demuestra una superioridad universal porque el rendimiento depende críticamente del patrón de carga (workload) de cada problema. Si un software realiza un 90% de búsquedas y un 10% de inserciones, ganará una estructura contigua; si realiza un 90% de manipulaciones en los extremos o fragmentaciones internas, ganará una estructura enlazada. La elección correcta exige analizar el equilibrio operativo y el entorno del hardware, no solo revisar qué barra del gráfico es más baja.
##### 6. ¿Qué idea intenta mostrar `XorList` respecto al ahorro de punteros?
La `XorList` ilustra cómo conseguir los beneficios de navegación bidireccional de una lista doblemente enlazada utilizando la misma cantidad mínima de memoria que una lista simplemente enlazada. Lo logra colapsando los dos punteros (`prev` y `next`) en un único espacio de memoria que almacena la operación lógica *XOR* (o bit a bit) de ambas direcciones.
##### 7. ¿Qué desventaja práctica introduce una estructura como `XorList` aunque sea interesante desde el punto de vista del espacio?.
Aunque ahorra memoria, sacrifica usabilidad e introduce riesgos técnicos graves:
* **Recorridos forzosos:** Para calcular la dirección del nodo siguiente, es obligatorio conocer siempre la dirección del nodo anterior. Es imposible saltar al medio de la lista de forma aislada.
* **Incompatibilidad de recolección de basura:** En lenguajes de alto nivel con recolectores de basura, los punteros XORados se ven como enteros sin sentido, provocando que la memoria se libere accidentalmente por no reconocer los enlaces.
* **Dificultad de depuración:** Los *debuggers* convencionales colapsan al intentar inspeccionar la estructura de la lista, ya que el puntero compuesto no apunta a una dirección de memoria válida por sí solo.

#### Bloque 8 - Cierre comparativo y preparación de sustentación

* **Afirmación sobre representación:** Cuando pasamos a estructuras enlazadas, la representación física de la memoria deja de coincidir con el orden lógico de la secuencia; los datos se dispersan dinámicamente y la secuencia se sostiene únicamente mediante las referencias lógicas (punteros) entre los nodos independientes.
* **Afirmación sobre acceso por rango frente a acceso por posición:** Debido a esta desconexión física, perdemos el acceso aritmético por rango directo e instantáneo de los arreglos y pasamos a depender de un acceso por enlace, lo que nos obliga a recorrer la estructura eslabón por eslabón hasta descubrir la ubicación del elemento buscado.
* **Afirmación sobre inserciones y eliminaciones locales:** A cambio de esa penalidad en las búsquedas profundas, ganamos una inmensa ventaja matemática en las inserciones y eliminaciones locales; una vez hallada la referencia de trabajo, agregar o quitar un nodo cuesta un tiempo constante, evadiendo los costosos desplazamientos en bloque necesarios en la contigüidad.
* **Afirmación sobre complejidad de `SLList`, `DLList` y `SEList`:** Esta evolución lógica dicta su complejidad de acceso y localización: la `SLList` es económica y excelente para extremos, la `DLList` permite un recorrido acotado y simétrico en tiempo $O(1 + \min(i, n-i))$, y la `SEList` perfecciona esta búsqueda diluyendo el gasto espacial y bajando el costo asintótico a $O(1 + \min(i, n-i)/b)$ al avanzar a través de bloques de memoria preasignados.
* **Afirmación sobre reutilización mediante adaptadores o puentes:** Trabajar con secuencias abstraídas a nivel de nodos fomenta la construcción de patrones de diseño limpios: utilizamos **adaptadores** para reciclar clases completas limitando sus interfaces (construyendo un `LinkedStack` seguro apoyado en una lista enlazada) y **puentes** para exportar lógicas de ordenamiento de repositorios externos (como `DengList`) hacia nuestras estructuras base sin necesidad de reimplementar algoritmos desde cero para cada una.
* **Comparación entre representación contigua y enlazada:** En conclusión, este cambio marca un compromiso fundamental en estructuras de datos: la representación contigua siempre será imbatible en saltos instantáneos y la inercia de la localidad de caché del procesador, mientras que la representación enlazada sacrificará dicha contigüidad para reinar en entornos donde los patrones de manipulación, inserción o borrado fragmentarían severamente un arreglo nativo.

#### Autoevaluación breve

* **Qué podemos defender con seguridad:**
    * La diferencia fundamental entre memoria contigua (localidad de caché, acceso aritmético $O(1)$) y memoria enlazada (inserciones locales $O(1)$ sin desplazamiento masivo).
    * Las justificaciones de complejidad asintótica, como el costo $O(1 + \min(i, n-i))$ en una `DLList` gracias a la navegación simétrica bidireccional.
    * El diseño de adaptadores (`LinkedStack`, `LinkedQueue`, `LinkedDeque`) y cómo la elección de la estructura base (`SLList` vs `DLList`) define si las operaciones en los extremos pueden mantenerse estrictamente constantes.
    * La utilidad arquitectónica del patrón puente para integrar algoritmos complejos de `DengList` (como `stable_sort`) sobre las estructuras de Morin sin contaminar su código base.

* **Qué todavía confundimos (o requiere mayor cuidado reflexivo):**
    * El análisis amortizado exacto de las operaciones `spread()` y `gather()` dentro de la `SEList` cuando los bloques se colapsan o se dividen masivamente bajo mucho estrés de memoria.
    * La tensión entre la teoría (Big-O) y la práctica (Hardware): a veces cuesta interiorizar por qué una estructura con "peor" complejidad teórica en reasignación (como `ArrayDeque`) puede ejecutar operaciones más rápido en la vida real que una `LinkedDeque` debido a la arquitectura de la memoria caché del procesador.
    * El rastreo mental de los punteros en operaciones destructivas sin nodo centinela (ej. remover el último elemento en una `SLList`), donde es fácil olvidar actualizar el puntero `tail` si la lista queda vacía.

* **Qué evidencia usaríamos en una sustentación:**
    * **Para defender diseño de interfaces:** El archivo `demo_linked_adapters.cpp` para probar visualmente que una `SLList` puede ser forzada a comportarse estrictamente como una estructura LIFO o FIFO.
    * **Para defender el compromiso espacio/tiempo:** El archivo `demo_min_structures.cpp` (específicamente `MinStack` y `MinQueue`), evidenciando que estamos gastando deliberadamente un factor $O(N)$ extra de memoria en cada nodo para garantizar que la consulta `min()` responda siempre en tiempo $O(1)$.
    * **Para defender manipulación segura de punteros:** Mostrar la implementación línea por línea del método `reverse()` de la `SLList` (que no usa memoria auxiliar) o el método `addBefore(w, x)` de la `DLList` para demostrar cómo la existencia del nodo centinela (`dummy`) erradica los temidos *NullPointerExceptions* en los casos borde.
    * **Para defender la escalabilidad:** Los resultados de `stress_selist_week3.cpp`, que prueban empíricamente que la matemática detrás del tamaño de bloque ($b$) resiste torturas de inserciones y borrados masivos sin perder la integridad estructural.