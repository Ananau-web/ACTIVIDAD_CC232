## Actividad 2-CC232

### Integrantes
- RYDELL JONEL MOSQUERA HUAYHUA
- ANGEL JESUS NAVARRO RUIZ

#### Bloque 1 - Núcleo conceptual de la semana
##### 1. Memoria Contigua
Significa que todos los elementos de la estructura se almacenan en un único bloque de memoria ininterrumpido. La disposición lógica de los elementos corresponde de forma exacta y directa a su disposición física secuencial en la memoria del sistema.

##### 2. Acceso Directo O(1)
El acceso a `A[i]` es $O(1)$ porque, al estar alojado en memoria contigua, no se necesita recorrer secuencialmente los elementos previos para encontrar el dato buscado. La computadora encuentra la dirección exacta aplicando una fórmula: suma la dirección de inicio del bloque con el desplazamiento (índice multiplicado por el tamaño del elemento).

##### 3. Tamaño (Size) vs. Capacidad (Capacity)
* **Size**: Representa la cantidad real de elementos válidos que la secuencia contiene actualmente (plano lógico).
* **Capacity**: Indica el total de celdas o espacio de memoria reservado internamente, el cual puede ser mayor al tamaño para permitir crecimiento futuro (plano físico).

##### 4. Limitaciones del Resize
Un arreglo dinámico no puede crecer "en el mismo sitio" porque no hay garantía de que la memoria física ubicada inmediatamente después esté libre. Por ello, al agotarse la capacidad, se debe reservar un bloque nuevo en otro lugar, copiar los datos y liberar el anterior.

##### 5. Costo Amortizado O(1)
Duplicar la capacidad asegura que, tras pagar el costo $O(n)$ de redimensionar, existan suficientes celdas libres para realizar muchas inserciones baratas ($O(1)$) antes del próximo redimensionamiento. Al distribuir el costo total de las expansiones entre todas las operaciones de una secuencia, el costo promedio resulta constante.

##### 6. ArrayStack vs. DengVector
* **Comparten**: Ambos usan un arreglo dinámico de respaldo contiguo y estrategias de redimensionamiento.
* **Diferencias**: `ArrayStack` es una implementación minimalista orientada a la interfaz `List` básica. `DengVector` tiene una intención didáctica más profunda, enfocándose en el control del ciclo de vida (copia profunda, operadores de asignación) y ofreciendo un repertorio algorítmico más rico como búsqueda y deduplicación.

##### 7. Optimización de FastArrayStack
`FastArrayStack` mejora el rendimiento práctico sustituyendo los bucles `for` explícitos por rutinas especializadas de bajo nivel como `std::copy` o `std::copy_backward`. Aunque no cambia la complejidad asintótica, acelera la ejecución empírica de forma significativa.

##### 8. Idea Espacial de RootishArrayStack
Su idea central es minimizar el desperdicio de memoria. En lugar de un solo arreglo que duplica su tamaño (desperdiciando hasta $O(n)$), divide los elementos en múltiples bloques de tamaño creciente.

##### 9. Bloques de Tamaño 1, 2, 3...
Se utilizan bloques con progresión aritmética para que la capacidad total crezca de forma controlada. Esto limita el desperdicio de espacio únicamente al último bloque, resultando en un desperdicio de solo $O(\sqrt{n})$ respecto al total de elementos.

##### 10. Representación, Costo y Desperdicio
Existe un compromiso (*trade-off*) constante:
* La **representación** de arreglo simple da acceso rápido ($O(1)$) pero es rígida.
* Mantener la contigüidad ante cambios estructurales implica un alto **costo temporal** por desplazamientos.
* Para reducir la frecuencia de estos costos (redimensionamiento), se acepta un margen de **desperdicio espacial** (capacidad excedente).

#### Bloque 2 - Demostración y trazado guiado
##### 1. En `demo_array_basico.cpp`, ¿qué deja claro sobre arreglo, longitud y asignación?

Sobre el arreglo nos deja claro que es de tamaño fijo definido, la longitud (length) refleja cuantos elementos contiene y la asignación no copia, sino que hace una transferencia en donde b deja de tener sus valores iniciales y pasa a apuntar al mismo bloque de memoria que tenía a.


##### 2. En `demo_arraystack_explicado.cpp`, ¿qué operación muestra mejor el costo por desplazamientos?

La operación que mejor muestra el costo por desplazamientos es add(1, 15), porque al insertar en una posición intermedia obliga a mover hacia la derecha todos los elementos desde el índice i hasta n-1 para abrir espacio — el propio demo lo explicita con el mensaje "se desplazan a la derecha los elementos desde i hasta n-1". Aunque remove(0) también desplaza, add en una posición media ilustra más claramente por qué el costo es O(n - i): mientras más al inicio se inserte, más elementos hay que mover, y en el peor caso — insertar en la posición 0 — se mueven los n elementos completos.

##### 3. En `demo_fastarraystack.cpp`, ¿qué cambia en la implementación aunque no cambie la 
complejidad asintótica?

FastArrayStack cambia la implementación de movimiento de elementos usando std::copy_backward y std::copy en lugar de bucles for manuales, pero mantiene los mismos criterios de resize() y la misma complejidad asintótica.

##### 4. En `demo_rootisharraystack_explicado.cpp`, ¿qué ejemplo explica mejor el mapeo de índice lógico a bloque y offset?

El ejemplo que mejor explica el mapeo es print_location(s, 2), porque a diferencia de locate(0) que es trivial y locate(5) que es el último elemento, el índice lógico 2 obliga a una traducción real: no vive en el bloque 2 sino en el bloque 1 offset 1, demostrando que bloque y offset no se leen directamente del índice sino que se calculan con la fórmula de la raíz cuadrada — que es precisamente la idea central de RootishArrayStack.

##### 5. En `demo_deng_vector.cpp`, ¿qué observable permite defender el crecimiento de `capacity`?

El observable es la impresión de size y capacity en cada insert, que muestra que la capacidad no crece en cada inserción sino en saltos — típicamente duplicándose — mientras size crece de uno en uno. Eso evidencia directamente el costo amortizado O(1): la mayoría de inserciones son baratas y solo ocasionalmente se paga el costo de copiar todo el arreglo.


##### 6. En `demo_stl_vector_contraste.cpp`, ¿qué similitud conceptual observan con `DengVector`?

Ambos muestran el mismo patrón: capacity crece en saltos que se duplican mientras size avanza de uno en uno, confirmando que DengVector reimplementa la misma estrategia de crecimiento amortizado de std::vector — no es una decisión arbitraria sino el estándar de la industria.

##### 7. ¿Qué demo sirve mejor para defender **amortización** y cuál sirve mejor para defender **uso de espacio**?

La demo que mas sirve para defender amortización es demo_deng_vector.cpp porque imprime size y capacity en cada insert mostrando como la capacidad crece en saltos.
La demo que mejor sirve para defender uso de espacio es demo_rootisharraystack_explicado/cpp porque explica la idea de bloques de tamaño y muestra como el mapeo de índices reduce el desperdicio espacial.

#### Bloque 3-Pruebas públicas, stress y correctitud
##### 1. ¿Qué operaciones mínimas valida la prueba pública para `ArrayStack`?
La prueba pública en test_public_week2.cpp valida la operaciones de inserción al final (add(x)), inserción por índice (add(i,x)), obtención del tamaño (size()), lectura por índice (get(i)) y eliminación por índice (remove(i))
##### 2. ¿Qué operaciones mínimas valida la prueba pública para `FastArrayStack`?
Para FastArrayStack, valida la inserción por índice usando el tamaño actual como posición(add(s.size(), x )) y add(i, x), la obtención del tamaño (size()), la lectura (get(i)) y la eliminación (remove(i))
##### 3. ¿Qué operaciones mínimas valida la prueba pública para `RootishArrayStack`?
La prueba pública para RootishArrayStack valida las operaciones de inserción al final (add(x)), inserción por índice (add(i,x)), obtención del tamaño (size()), lectura por índice (get(i)) y eliminación por índice (remove(i)). Además, dado su diseño basado en bloques, también verifica el correcto funcionamiento de la distribución de elementos en los bloques internos y el cálculo de la capacidad total.
##### 4. ¿Qué sí demuestra una prueba pública sobre una estructura?
Una prueba pública demuestra que la estructura cumple con su contrato/interfaz pública: que las operaciones básicas (inserción, eliminación, acceso, tamaño) funcionan correctamente para casos típicos y que la estructura se comporta según las especificaciones esperadas. Valida el comportamiento externo observable sin importar cómo esté implementada internamente.
##### 5. ¿Qué no demuestra una prueba pública?
Una prueba pública no demuestra aspectos internos como la correctitud de las invariantes de la estructura, el manejo eficiente de memoria, el cumplimiento de complejidades algorítmicas específicas (O(1), O(log n), etc.), ni el comportamiento en casos extremos o boundary conditions no cubiertos. Tampoco valida que la implementación sea correcta a nivel interno: puede haber fugas de memoria, errores en el manejo de estados intermedios, o violaciones de las pre/post-condiciones que no son visibles desde la interfaz pública. Las pruebas públicas solo verifican el comportamiento observable externo, no la calidad interna de la implementación.
##### 6. En `resize_stress_week2.cpp`, ¿qué comportamiento intenta estresar sobre crecimiento, reducción o estabilidad?
Esta prueba intenta estresar forzando ciclos masivos de redimensionamiento de memoria interna:
* **Crecimiento:** Se insertan secuencias largas de elementos (e.g., cientos o miles de inserciones consecutivas) para obligar a las estructuras a llamar a sus métodos de expansión subyacentes múltiples veces.
* **Reducción:** A continuación, se eliminan de forma masiva grandes bloques de elementos para desencadenar reducciones de capacidad o eliminación de bloques internos.
* **Estabilidad:** Verifica que, a pesar de estas agresivas reubicaciones de memoria, los datos restantes sigan siendo correctos y accesibles en sus índices correspondientes (por ejemplo, validando `v[i] == i + 700`).
##### 7. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes y complejidad?
Pasar pruebas es insuficiente porque estas son de naturaleza empírica y finita: solo aseguran que el estado de salida es el esperado para una entrada exacta. Un código muy ineficiente podría pasar estas pruebas si los datos son pocos. La explicación de **invariantes** demuestra matemáticamente el *por qué* la lógica siempre funciona sin importar la entrada, y el análisis de **complejidad** asegura que el diseño cumpla con los límites teóricos de escalabilidad, aspectos que una prueba funcional básica no puede validar intrínsecamente.


#### Bloque 4-Vector como puente entre teoría y código


##### 1. ¿Qué papel cumplen `_size`, `_capacity` y `_elem`?
* **`_elem`**: Es el puntero que apunta al arreglo interno (bloque contiguo) donde se almacenan físicamente los datos.
* **`_size`**: Registra el número real de elementos válidos contenidos en la secuencia (el tamaño lógico).
* **`_capacity`**: Indica cuántas celdas de memoria se han reservado físicamente en total. Esta separación de roles es lo que hace posible el crecimiento dinámico sin tener que reasignar memoria en cada inserción.

##### 2. ¿Cuándo debe ejecutarse `expand()`?
Debe ejecutarse cuando la capacidad actual se agota y existe riesgo de un *overflow*. En el código, esto ocurre explícitamente en el método `insert` cuando la estructura detecta que se ha quedado sin espacio (`_size == _capacity`), forzando la reserva de un bloque más grande (usualmente el doble).

##### 3. ¿Por qué `insert(r, e)` necesita desplazar elementos?
Un arreglo requiere obligatoriamente el uso de memoria contigua. Por lo tanto, al insertar un elemento en la posición o rango `r`, todos los elementos ya existentes que están a su derecha (el sufijo `[r, _size)`) deben desplazarse una posición hacia la derecha para hacerle un espacio físico al nuevo elemento sin sobrescribir información previa. 

##### 4. ¿Qué diferencia conceptual hay entre `remove(r)` y `remove(lo, hi)`?
* **`remove(lo, hi)`** es la operación estructural principal que elimina todo un intervalo, desplazando el sufijo restante una sola vez hacia la izquierda para cubrir el hueco.
* **`remove(r)`** se diseña como un **caso particular** de la eliminación por intervalo (eliminando desde `r` hasta `r + 1`). Esta conceptualización evita repetir innecesariamente múltiples desplazamientos si se pretendiera eliminar un intervalo quitando elemento por elemento.

##### 5. ¿Qué evidencia de copia profunda aparece en la demo?
La evidencia de la copia profunda (deep copy) se refleja en el control estricto de la memoria a través de métodos de clonación de la estructura. En `DengVector.h`, esto se materializa mediante el método `copyFrom()`, el cual se invoca explícitamente en el **constructor por copia** y en el **operador de asignación** (`operator=`). Esto asegura que el nuevo vector instancie su propia área de almacenamiento y copie los elementos, previniendo errores al modificar vectores que de otra forma compartirían el mismo bloque interno.

##### 6. ¿Por qué `traverse()` es una buena interfaz didáctica?
`traverse()` es didácticamente excelente porque materializa la idea abstracta de que el vector no es un simple receptáculo de datos, sino que soporta un procesamiento estructurado de toda la colección. Permite recorrer el vector y aplicar una misma acción, función o transformación a cada elemento de manera uniforme (mediante punteros a función u objetos función).

##### 7. ¿Qué ventaja tiene implementar un vector propio antes de depender de `std::vector`?
Implementar un vector propio tiene un inmenso valor formativo, ya que obliga a lidiar con problemas centrales del diseño algorítmico que los contenedores prefabricados como `std::vector` ocultan de la vista del programador. Enseña la diferencia práctica entre interfaz abstracta e implementación interna, expone la necesidad de gestionar manualmente la memoria dinámica (destructores, fugas), resalta la importancia de la copia profunda y obliga a razonar usando análisis amortizado para entender el costo real de las operaciones.

#### Bloque 5 - RootishArrayStack: espacio y mapeo

##### 1. ¿Cómo se distribuyen los elementos entre bloques?
Los elementos no se almacenan en un único arreglo gigante, sino que se organizan en una lista de múltiples arreglos más pequeños (bloques) de tamaños progresivos. Específicamente, el bloque 0 tiene capacidad para 1 elemento, el bloque 1 para 2 elementos, el bloque 2 para 3, y en general, el bloque $b$ tiene capacidad para $b+1$ elementos.
##### 2. ¿Por qué con `r` bloques la capacidad total es `r(r+1)/2`?
Porque la capacidad total es simplemente la suma de las capacidades de todos los bloques creados hasta el momento. Dado que los bloques tienen capacidades que siguen la secuencia $1, 2, 3, \\dots, r$, esta suma corresponde a la progresión aritmética (o suma de Gauss), cuya fórmula matemática exacta es $\\frac{r(r+1)}{2}$.
##### 3. ¿Qué problema resuelve `i2b(i)`?
Resuelve el problema de traducción entre el mundo lógico y la memoria física. Dado un índice lógico global `i` (la posición aparente del elemento en la lista continua), determina matemáticamente a qué bloque físico `b` pertenece. Para lograrlo, despeja $b$ usando la ecuación cuadrática inversa de la capacidad, lo que se refleja en la fórmula matemática `(-3.0 + sqrt(9 + 8*i)) / 2.0`.
##### 4. ¿Qué información produce `locate(i)` en la versión explicada?
Basado en los objetivos didácticos del repositorio, `locate(i)` expone la dupla que detalla el mapeo interno: calcula y devuelve tanto el **bloque** (`b`) donde se encuentra el elemento, como el **offset** o índice local (`j`) que dicho elemento ocupa dentro de ese bloque en particular.
##### 5. ¿Qué se gana en espacio frente a `ArrayStack`?
Se gana una drástica reducción del espacio desperdiciado en memoria. Mientras que `ArrayStack` (que duplica su capacidad al crecer) puede llegar a desperdiciar un espacio proporcional al total de elementos ($O(n)$), `RootishArrayStack` solo desperdicia espacio en su último bloque. Esto acota el desperdicio al tamaño de ese último bloque, logrando una eficiencia donde el espacio extra es de orden $O(\\sqrt{n})$.
##### 6. ¿Qué se conserva igual respecto a la interfaz?
A pesar de su compleja representación interna, se conserva intacta la interfaz de una lista (ADT List). Hacia el usuario exterior, ofrece exactamente las mismas operaciones: `size()`, `get(i)`, `set(i, x)`, `add(i, x)` y `remove(i)`.
##### 7. ¿Qué parte les parece más difícil de defender oralmente: el mapeo, el análisis espacial o el costo amortizado de `grow/shrink`?
El **mapeo `i2b(i)`** suele ser la parte más difícil de explicar y defender oralmente. A diferencia del análisis espacial o amortizado (que pueden ilustrarse con analogías intuitivas como "solo sobra el último bloque" o "el costo duro se reparte entre muchas inserciones"), explicar el mapeo exige que el interlocutor visualice una deducción algebraica en el aire. Explicar oralmente cómo la inecuación cuadrática $\\frac{b(b+1)}{2} \\le i$ deriva en la aplicación de la fórmula resolvente de segundo grado con raíz cuadrada y el uso de un techo (`ceil`), resulta bastante abstracto sin el apoyo de una pizarra o notación matemática formal.

#### Bloque 6-Refuerzo de lectura

##### 1. ¿Qué aporta `operator[]` a la idea de vector?

La sobrecarga del operador [ ] aporta una notación natural e intuitiva al programador, permitiendo recuperar el estilo de acceso directo de un arreglo clásico sin renunciar a la encapsulación y abstracción que ofrece el vector.
##### 2. ¿Qué supone `find(e)` sobre igualdad entre elementos?
Supone que es posible comparar los elementos almacenados buscando una coincidencia exacta ("un elemento igual a e"). Dado que se aplica en un vector no ordenado que carece de información estructural para descartar regiones, asume que debe realizarse mediante una búsqueda secuencial exhaustiva comparando elemento por elemento.
##### 3. ¿Qué muestra `traverse()` sobre procesamiento uniforme de toda la estructura?
Muestra una idea de alto nivel donde el vector no es visto solo como un lugar pasivo para almacenar datos, sino como una estructura capaz de soportar procesamiento uniforme, aplicando una misma acción o transformación a toda la colección completa.
##### 4. ¿Por qué esta lectura sirve como refuerzo natural de `DengVector` aunque no sea el centro exclusivo de la semana?
Sirve como un refuerzo teórico natural porque justifica con precisión las decisiones de diseño algorítmico que implementa DengVector. Explica los fundamentos de la separación entre interfaz e implementación, la diferencia crucial entre tamaño lógico y capacidad física, las estrategias de gestión dinámica (expansión/reducción) y justifica su eficiencia mediante el análisis amortizado.
#### Bloque 7 - Cierre comparativo
Cuando pasamos de usar un simple arreglo a diseñar una estructura dinámica, el cambio principal es que la **representación** física se separa de la lógica. Ahora la estructura diferencia entre la memoria total que hemos reservado (capacidad) y la cantidad de elementos que realmente estamos utilizando (tamaño).

Esto nos exige garantizar la **correctitud** interna: la estructura ahora tiene que cuidarse sola. Debe detectar si se va a llenar, expandirse a un arreglo nuevo, copiar los datos sin errores y, muy importante, liberar la memoria vieja para no dejar fugas.

A simple vista, copiar todo a un arreglo nuevo parece lento ($O(n)$). Sin embargo, aquí entra el **costo amortizado**: como la jugada es duplicar la capacidad en lugar de crecer poco a poco, estas expansiones masivas ocurren muy pocas veces. En promedio, el costo real de insertar un dato sigue siendo $O(1)$.

Esta gestión también optimiza el **uso de espacio**. Si empezamos a borrar muchos datos, la estructura se encoge sola (*shrink*) para que el espacio de memoria desperdiciada nunca supere una fracción $O(n)$ del tamaño actual.

Finalmente, esta evolución se nota al comparar tres estructuras clave de la semana:
* **`ArrayStack`**: Hace la gestión dinámica clásica moviendo los datos con bucles normales (uno por uno).
* **`FastArrayStack`**: Funciona igual que el anterior, pero mueve los bloques de memoria usando funciones nativas de bajo nivel (como `std::copy`), lo que lo hace muchísimo más rápido en la práctica.
* **`RootishArrayStack`**: Rompe el molde. En vez de depender de un solo arreglo gigante que se duplica, usa una lista de bloques de tamaños crecientes (1, 2, 3...). Esto reduce la memoria desperdiciada de $O(n)$ a solo $O(\sqrt{n})$, a cambio de requerir un cálculo matemático un poco más complejo para saber el índice.

#### Autoevaluación breve

* **Qué podemos defender con seguridad:**
  Tenemos muy clara la separación entre la **capacidad física** que reservamos en la memoria y el **tamaño lógico** que realmente usamos en la estructura. También podemos justificar sin problemas cómo la estrategia de duplicar el arreglo nos salva la vida para mantener un **costo amortizado de $O(1)$** en las inserciones. Además, entendemos bien la diferencia entre un `ArrayStack` clásico (que mueve elemento por elemento) y un `FastArrayStack` (que optimiza todo usando copias de memoria a bajo nivel).

* **Qué todavía confundimos (o nos cuesta explicar en la pizarra):**
  La matemática exacta del `RootishArrayStack`. Entendemos la genialidad de usar bloques de tamaño creciente para que la memoria desperdiciada baje a $O(\sqrt{n})$, pero hacer el cálculo manual para saber en qué bloque exacto cae el índice `i` (usando la fórmula de la raíz cuadrada rápida) todavía nos resulta un poco enredado de trazar mentalmente. También nos toca pensar dos veces los umbrales exactos para hacer el `shrink()` sin caer en el efecto rebote (expandir y reducir a cada rato).

* **Qué evidencia usaríamos en una sustentación:**
  Nos apoyaríamos directamente en el código de los *demos*. Para probar el impacto de la memoria, mostraríamos los tiempos de ejecución comparando `ArrayStack` vs. `FastArrayStack`; es la mejor forma de demostrar que, aunque en teoría (Big-O) ambas cuestan lo mismo, en la práctica el manejo de memoria hace una diferencia brutal. Además, usaríamos las pruebas de estrés (`resize_stress_week2.cpp`) para comprobar que nuestra gestión dinámica aguanta miles de operaciones seguidas sin romperse ni dejar fugas de memoria.