# Actividad 1- CC232

### Integrantes
- Rydell Jonel Mosquera Huayhua
- Joel Gustavo Carhuarica Aguilar

#### Bloque 1 - Núcleo conceptual de Semana1

1. Expliquen con sus palabras la diferencia entre **problema**, **algoritmo**, **ADT** e **implementación**.

   **Problema**: Es la **especificación**, lo que necesita ser resuelto. Define entrada, salida, precondiciones y postcondiciones. Por ejemplo: "Dado un arreglo de enteros, producir un arreglo con los mismos elementos en orden no-decreciente." Lo importante es _qué_ se debe lograr, no _cómo_.

   **Algoritmo**: es la estrategia conceptual para resolver el problema. Es un secuencia finita de pasos que transforma la entrada en salida. Como  `bubble_sort`, el algoritmo repite pasadas comparando elementos adyacentes e intercambiándolos, reduciendo gradualmente el rango hasta que no hay cambios. El algoritmo es independiente de lenguaje o máquina.

   **ADT**: es la interfaz lógica, un conjunto de operaciones con sus especificaciones. Define qué puedes hacer sin decir cómo

   **Implementación** : Es la realización concreta del ADT usando estructuras de datos específicas. como el demo_adt_secuencia.cpp que hay dos implementaciones del ADT 
   Problema → Algoritmo (estrategia conceptual) → ADT (interfaz) → Implementación (código real + estructura de datos).

2. En `bubble_sort.cpp`, expliquen qué observable conecta correctitud y costo.


   * **Correctitud:** Es la propiedad de un algoritmo o función de cumplir rigurosamente con la especificación del problema (hacer exactamente lo que debe hacer).
   * **Costo:** Es una medida de los recursos que consume la ejecución, evaluados principalmente en **tiempo** (cantidad de operaciones o pasos matemáticos) y **espacio** (memoria RAM adicional requerida).

   1. 'changed': Demuestra que el arreglo está ordenado al no haber inversiones 
   (correctitud) y se usa para interrumpir el ciclo prematuramente (costo).

   2. 'lastSwapIndex': Marca la frontera donde los elementos a la derecha ya están 
      en su posición final (correctitud) y se usa para acortar el rango del bucle 
      en la siguiente iteración, evitando evaluar elementos ordenados (costo).

   3. 'swaps': Representa la resolución de cada inversión individual (correctitud) 
      y refleja el costo directo de las operaciones de escritura en memoria (costo).
3. En `power.cpp`, expliquen por qué `power` mejora la idea de una versión ingenua.

   Mejora la versión ingenua porque utiliza el algoritmo de Exponenciación Binaria, reduciendo la complejidad temporal a $O(\log n)$. En lugar de multiplicar paso a paso, este algoritmo divide el tamaño del problema a la mitad en cada iteración, realizando solo unas $\log n$ multiplicaciones en total.
4. En `fibonacci.cpp`, expliquen por qué una función puede ser correcta y aun así ser una mala elección práctica.

   Es correcta porque es la traducción exacta y literal de la definición matemática de la sucesión de Fibonacci ($F_n = F_{n-1} + F_{n-2}$). Si le pasas un número `n`, te devolverá el resultado correcto sin lugar a dudas. Pasa todas las pruebas lógicas y matemáticas.
   El problema radica en la **eficiencia (Complejidad de Tiempo y Espacio)**. En la práctica, no solo nos importa _qué_ respuesta nos da la computadora, sino _cuánto tiempo_ y _cuánta memoria_ le toma encontrarla.
   Su tiempo de ejecución crece a un ritmo exponencial de **$O(2^n)$
5. En `count_ones.cpp`, expliquen por qué el tamaño de entrada no siempre coincide con el valor numérico.

   Si miras la función, **no hay bucles**. Llama a la macro `ROUND` exactamente 5 veces.
   ¿Por qué 5? Porque el tamaño de la entrada es de 32 bits, y en un enfoque de "divide y vencerás", el número de pasos es el logaritmo en base 2 de la cantidad de bits ($\log_2(32) = 5$).
   No importa si le pasas un `0` o un `4,294,967,295`. El algoritmo siempre dará exactamente los mismos 5 pasos. Su complejidad temporal es **$O(1)$** respecto al valor del número, porque lo que realmente está procesando es el tamaño constante del registro de bits.
6. En `demo_adt_secuencia.cpp`, expliquen por qué la misma interfaz puede convivir con representaciones distintas.

   Porque utilizamos el concepto de abstracción y polimorfismo. La interfaz (`IntSequence`) solo define **qué** operaciones se pueden hacer (como add, remove o get), dejando que cada clase decida el **cómo**.
   Esto hace que el código cliente (la función `run_scenario`) dependa únicamente de la interfaz general, permitiendo que por debajo convivan distintas representaciones en memoria (como el arreglo estático en `FixedArraySequence` o el arreglo dinámico en `VectorSequence`) sin que el programa principal note la diferencia o tenga que ser modificad

#### Bloque 2 - Demos y trazado guiado

   | Archivo | Salida u observable importante | Idea algorítmica | Argumento de costo |
   | :--- | :--- | :--- | :--- |
   | `demo_bubblesort.cpp` | Contadores impresos de **"Comparaciones"** e **"Intercambios"**, y el momento exacto en que el bucle se detiene prematuramente. | Si en una pasada completa no hubo intercambios, el arreglo ya está ordenado (Early Exit). Usar la frontera del último intercambio reduce el área de trabajo. | Evita realizar el peor caso teórico $O(n^2)$ siempre. En arreglos casi ordenados, el costo se desploma acercándose al mejor caso $O(n)$. |
   | `demo_power.cpp` | El **número de multiplicaciones** ejecutadas (o tiempo en microsegundos) al elevar una base a un exponente muy grande. | **Exponenciación Binaria (Rápida):** En lugar de multiplicar $x$ por sí mismo $n$ veces, se usa la propiedad $x^n = (x^{n/2})^2$. | Transforma una complejidad de tiempo lineal $O(n)$ en una logarítmica **$O(\log n)$**, aplastando el número de operaciones necesarias. |
   | `demo_fibonacci.cpp` | La **diferencia abismal de tiempos** en consola al calcular, por ejemplo, `Fibonacci(40)` con distintos métodos. | Evitar el recálculo de subproblemas superpuestos. El enfoque iterativo (o Programación Dinámica) memoriza estados previos en lugar de ramificarse a ciegas. | Demuestra la diferencia catastrófica entre un costo de tiempo exponencial **$O(2^n)$** (inviable) y uno lineal **$O(n)$** (instantáneo). |
   | `demo_countones.cpp` | La impresión lado a lado del **valor decimal** (ej. `361`) y su representación binaria mediante **`std::bitset<16>(x)`**. | **Manipulación de bits:** Usar operaciones a nivel de procesador (como `n & (n-1)` de Kernighan) para contar bits encendidos saltándose los ceros. | Demuestra que el tiempo de ejecución en hardware depende del **tamaño en bits** del tipo de dato, y es independiente de la magnitud del número decimal. |

1. En `demo_bubblesort.cpp`, ¿qué salida sirve para defender costo y no solo resultado?

   La salida que defiende el costo es la línea que imprime las estadísticas del `BubbleStats` (**comparaciones, intercambios y último swap**). Mientras que imprimir el arreglo final `[1, 2, 3, 4, 5, 8]` solo demuestra la correctitud matemática (el resultado), contar las comparaciones y los intercambios nos da una métrica empírica del esfuerzo computacional (el costo). Además, el valor del 'último swap' evidencia que la optimización funcionó, demostrando que el algoritmo evitó comparaciones redundantes en el sufijo que ya estaba ordenado, mejorando el costo en el mejor de los casos respecto a una versión ingenua.
2. En `demo_power.cpp`, ¿qué comparación concreta muestra una mejora algorítmica?

   La comparación concreta que demuestra la mejora algorítmica es contrastar las llamadas a `powerBF` frente a `power`, y `power2BF_I` frente a `power2`. Aunque la salida en consola (`demo_power.cpp`) solo muestra que todas retornan el mismo resultado para garantizar la correctitud matemática, esta comparación valida las optimizaciones teóricas del código: demuestra la transición de un algoritmo ingenuo de costo lineal $O(n)$ en `powerBF`, a una exponenciación binaria de costo logarítmico $O(\log n)$ en `power`. La mejora es máxima al comparar las versiones de base 2, donde se pasa de usar bucles a lograr un tiempo constante $O(1)$ mediante el desplazamiento directo de bits
3. En `demo_fibonacci.cpp`, ¿qué crecimiento se vuelve defendible?

   El crecimiento que se vuelve defendible en la práctica es el crecimiento lineal $O(n)$. El archivo `demo_fibonacci.cpp` demuestra que el algoritmo recursivo ingenuo sufre de un crecimiento exponencial $O(2^n)$ debido al recálculo constante de subproblemas superpuestos, lo cual es computacionalmente indefendible. Sin embargo, al utilizar iteración (`fibI`), paso de estado por referencia (`fib(n, prev)`) o guardar el estado interno en un objeto (clase `Fib`), logramos transformar el algoritmo. Este nuevo enfoque asegura un crecimiento lineal $O(n)$ que sí es defendible, ya que el tiempo de ejecución aumenta de forma proporcional a la entrada, permitiendo escalar a números inmensos utilizando una cantidad mínima de recursos
4. En `demo_countones.cpp`, ¿qué ejemplo ayuda más a distinguir valor numérico de tamaño en bits?

   El ejemplo que mejor ilustra esta distinción es la salida generada por la instrucción `std::bitset<16>(x)`. Al imprimir en consola `x = 361 = 0000000101101001`, el programa expone ambos conceptos simultáneamente: '361' es el valor numérico (la magnitud matemática), mientras que la cadena de 16 ceros y unos revela el verdadero tamaño de la entrada para la máquina. Esto demuestra visualmente que la complejidad de estos algoritmos a nivel de hardware depende de la cantidad física de bits que componen el tipo de dato (el tamaño de la entrada), y es completamente independiente de la magnitud de la cifra decimal que representan.

#### Bloque 3 - Pruebas públicas y preparación de sustentación


1. ¿Qué funciones o ideas están verificando las pruebas públicas?

   - `sum` (versiones recursiva / iterativa / rango): suma de elementos, casos base vacíos.
   - `power`, `powerBF`, `power2BF`, `power2` (y variantes iterativas): potencia de 2^10 = 1024.
   - `fib`, `fibI`, `fib(n, prev)`: Fibonacci(10)=55 y valor anterior.
   - `Fib` (ADT/iteración de Fibonacci): estado inicial y valor.
   - Posiblemente también `count_ones`, `gcd`, `hanoi`, etc. en el extra (se asume por nombre y criterio de semana)

2. ¿Qué sí demuestra una prueba pública?
   - Demuestra que el código produce el output correcto para los casos de prueba especificados.
   - Demuestra que el código produce el output correcto para los casos de prueba especificados.
   - Muestra que no se rompió la implementación básica (sanity check).
   - Muestra el cumplimiento de una parte de la especificación.
   - Muestra comportamiento concreto que debe cumplir el alumno (y lo hace).
3. ¿Qué no demuestra una prueba pública?
   - No demuestra correctitud para todos los casos posibles
   - No demuestra ausencia de bugs en casos no cubiertos 
   - No demuestra implementación óptima; puede pasar un algoritmo lento que solo cumpla los pocos casos
4. Elijan **una** pregunta de `preguntas_semana1.md` y respóndanla bien.
5. Usen la rúbrica para autoevaluarse en:

   * comprensión conceptual,
   * sustentación de correctitud,
   * análisis de eficiencia.

   **55. Por qué [power(a, n)]**

   - Especificación: [power(a, n)]  `powerBF` hace multiplicaciones repetidas [n] veces (O(n)).
   - `power` implementa exponenciación rápida por “dividir y conquistar”:
      - si n par, calcula `power(a, n/2)` una vez y eleva cuadrado;
      - si n impar, multiplica por [a]  además.
   - Correctitud: por inducción sobre [n], mantiene [a^n].
   - Costo: `power` usa O(log n) multiplicaciones frente a O(n) de `powerBF`.
   - Entonces para n grandes hay mejora algorítmica clara, con misma salida.


#### Bloque 4 - Puente corto con Proyecto0


1. ¿Qué diferencia observable deja `demo_const_refs.cpp` entre lectura, modificación y copia?

      1. Lectura (sum_readonly)

         Se pasa el vector presumiblemente por referencia constante (const std::vector<int>&).
         La consola imprime el resultado de la suma (6), pero no hay ningún cambio en el estado del vector. Si imprimiéramos original inmediatamente después, seguiría siendo {1, 2, 3}. Esto prueba empíricamente que la función solo "leyó" la memoria sin alterarla.

   2. Modificación In-place (append_in_place)

         Se pasa el vector por referencia mutable (std::vector<int>&).
         La consola imprime despues de append_in_place... {1, 2, 3, 4}. La evidencia aquí es que la función no devolvió una variable nueva, sino que inyectó el número 4 directamente en la memoria de la variable original, alterando su estado para el resto del programa.

   3. Copia (appended_copy)

         Se pasa el vector por valor (std::vector<int>) o por referencia constante devolviendo una nueva instancia.

         Esta es la prueba definitiva porque la consola muestra dos estados distintos conviviendo al mismo tiempo:

         1. Imprime original demostrando que quedó intacto ({1, 2, 3, 4}).

         2. Imprime la nueva variable copied, que tiene su propia línea de tiempo ({1, 2, 3, 4, 99}).
         Esto prueba que el programa duplicó el espacio en memoria (con el costo de rendimiento que eso implica) para proteger el dato original y trabajar sobre un clon.
2. En `bench_vector_growth.cpp`, ¿qué cambia con `reserve`?

   - Sin reserve: El vector crece dinámicamente. Al agotarse su capacidad, 
      debe pedir más memoria, copiar todos los elementos existentes al nuevo 
      espacio y liberar la memoria antigua. Estas reasignaciones repetidas 
      disparan el costo de tiempo de ejecución.
   - Con reserve(n): Pre-asigna todo el espacio en memoria en un solo paso 
      antes de entrar al bucle. Los push_back() subsiguientes son operaciones 
      directas en memoria ya asegurada, sin interrupciones ni copias ocultas.
   - Observable: El benchmark demostrará que el tiempo promedio medido en 
      microsegundos se reduce drásticamente al utilizar reserve().

3. En `bench_vector_ops.cpp`, ¿por qué `push_back`, `insert(begin())` e `insert(middle)` no cuestan lo mismo?

   La diferencia radica en la naturaleza de "memoria contigua" del std::vector:
   1. push_back (Final): O(1). Se coloca el elemento en el siguiente espacio 
   vacío. Como no hay elementos a su derecha, requiere CERO desplazamientos.

   2. insert en begin() (Inicio): O(n). Para insertar en la posición 0, la CPU 
   debe desplazar TODOS los elementos existentes una posición hacia la derecha 
   para "hacer espacio". Es el peor caso posible.
   3. insert en middle (Medio): O(n). Para insertar en la mitad, se desplaza 
   al 50% de los elementos (la mitad derecha). Toma aproximadamente la mitad 
   del tiempo que insertar al inicio, pero sigue siendo drásticamente más 
   lento que push_back.

4. En `bench_cache_effects.cpp`, ¿qué intuición deja sobre localidad de memoria?

   Este benchmark demuestra que la complejidad algorítmica O(N) no cuenta 
   toda la historia. El hardware moderno penaliza severamente los saltos 
   en memoria debido a cómo funciona la Caché de la CPU.
   1. Vector Secuencial: Al tener los datos contiguos y leerlos en orden, 
   maximizamos los "Cache Hits" (aciertos de caché). La CPU carga bloques 
   enteros y procesa a velocidad máxima.

   2. Vector Aleatorio: Al saltar por índices desordenados, destruimos la 
   Localidad Espacial. La CPU sufre constantes "Cache Misses", teniendo que 
   viajar a la RAM lenta por cada número.
   3. std::list (Lista Enlazada): Sus nodos están fragmentados aleatoriamente 
   en el Heap. Seguir punteros obliga a dar saltos constantes en la memoria, 
   resultando en un rendimiento tan pobre como el acceso aleatorio.
   CONCLUSIÓN: Para máximo rendimiento, prefiere estructuras de memoria 
   contigua (std::vector) y recórrelas en orden secuencial.
#### Bloque 5 - Extensión breve con Ejercicios0


1. Según `Ejercicios0.md`, ¿cuál es el orden correcto antes de optimizar?
   1. Primero: Elegir bien el algoritmo.

   2. Luego: Verificar que el programa sea correcto.

   3. Después: Medir el rendimiento.

   4. Finalmente: Explorar optimizaciones más avanzadas del compilador.

2. ¿Qué quiere mostrar `stl_optimizacion_demostracion.cpp` con `reserve`, `nth_element`, `partial_sort` y `lower_bound`?

   `std::vector::reserve` (Gestión de Memoria):
     antes de empezar, le dices al sistema operativo: _"Oye, voy a necesitar espacio para N elementos, dámelo todo ahora"_.
    reserve es decirle al sistema: "No me des el producto    todavía, pero asegúrame el almacén porque viene un cargamento grande y no quiero andar cambiando de local cada cinco minutos".
      `std::nth_element` (El k-ésimo menor o la Mediana)
    actúa como un filtro inteligente: coloca el elemento k-ésimo exactamente donde le corresponde en el arreglo ordenado y deja todos los menores a su izquierda y los mayores a su derecha, sin molestarse en ordenar completamente ninguno de los dos lados.

      `std::partial_sort` (El problema del Top-K)
    ordena solamente los primeros 𝐾
    K elementos como si fueran los mejores del arreglo, dejando el resto sin ordenar completo y así reduce el trabajo cuando solo necesitas el Top-K.
      `std::lower_bound` (El poder del orden previo)
     Si tu arreglo **ya está ordenado**, usar `std::lower_bound` ejecuta una Búsqueda Binaria impecable bajo el capó. Corta el arreglo por la mitad repetidamente hasta dar con el número.
3. ¿Qué tipo de evidencia puede producir `resolver_ejercicios0_v4.2.sh`?

   - **1. Evidencia Ejecutiva (El Reporte Final):** Genera automáticamente el archivo `reporte_ejercicios0.md`, el cual contiene tablas comparativas en Markdown que resumen el éxito de compilación, tiempos de ejecución y tamaños de binarios. Es el artefacto principal para la toma de decisiones.
      
   - **2. Métricas de Rendimiento y Costo:** Extrae los tiempos exactos de ejecución de la CPU (vía `/usr/bin/time`) y el tamaño de los ejecutables en bytes para evaluar el costo de las optimizaciones. Además, genera perfiles de ejecución (`gprof.txt`) para identificar matemáticamente los _hotspots_ o cuellos de botella del código.
      
   - **3. Correctitud y Seguridad de Memoria:** A través de las salidas estándar (`*.stdout.txt`) garantiza que las optimizaciones agresivas no alteren el resultado matemático. Simultáneamente, los logs de los _Sanitizers_ (ASan, UBSan, TSan) proveen evidencia forense sobre la ausencia de accesos inválidos a memoria, desbordamientos numéricos o colisiones de hilos (_data races_).
      
   - **4. Calidad y Cobertura de Pruebas:** Produce reportes de _Coverage_ estadístico (`gcov_summary.txt` y `*.gcov`) que certifican el porcentaje exacto de líneas de código, ramas lógicas y condiciones que fueron puestas a prueba de manera efectiva.
      
   - **5. Auditoría y Trazabilidad del Compilador:** Conserva un registro absoluto de los procesos de construcción (`*.compile.log` y `*.link.log`). El conteo automatizado de _warnings_ bajo distintos niveles de optimización (como variables no inicializadas reveladas en `-O2`) sirve como prueba de un código limpio y robusto.
4. ¿Qué limitaciones de entorno menciona `INSTRUCCIONES_Ejercicios0_v4.2.md`?
   - **Fallo en Sanitizers:** Herramientas como ASan, UBSan o TSan pueden no enlazar (linkear) correctamente al intentar compilar,de modo que la compilación se rompe antes de generar binarios utilizables.
      
   - **Problemas con `gcov` (Cobertura):** gcov puede requerir ajustes extras o configuración especial del compilador/entorno para producir resultados válidos.
      
   - **Fallo en `gprof` (Profiling):** Es común que directamente falle al ejecutarse o que genere archivos de perfil vacíos o inútiles.

5. ¿Por qué esta parte no reemplaza la discusión de correctitud de Semana1?

   El uso de herramientas de testing empírico, profiling y sanitizers no reemplaza la discusión formal de correctitud matemática (como el análisis de invariantes de bucle de la Semana 1). Mientras que las herramientas del script validan que el código se comporta bien en memoria y produce resultados correctos **solo para los casos de prueba específicos que le proporcionamos**, no pueden garantizar el comportamiento del algoritmo para el dominio infinito de entradas. La discusión de correctitud de la Semana 1, basada en lógica e inducción matemática, es la única forma de probar de manera absoluta que el algoritmo subyacente es lógicamente infalible, independientemente de los casos de prueba, el compilador o la arquitectura del hardware.

### Bloque 6 - Cierre comparativo

Respondan esta pregunta final:

**¿Qué cambia cuando pasamos de defender correctitud básica en Semana1 a comparar implementaciones con evidencia experimental?**

   1. Afirmación de Especificación
   
      La especificación dicta el "contrato" inquebrantable de lo que debe lograr el programa (por ejemplo: "dado un conjunto de estudiantes, retornar los 50 con mejores notas"). En la etapa experimental, la especificación se mantiene como el faro inamovible; el objetivo ya no es cuestionar qué debe hacer el programa, sino evaluar empíricamente cuál de todas las herramientas (ej. std::sort vs std::partial_sort) cumple ese contrato de la manera más eficiente. 

   2. Afirmación de Correctitud
   
      En Semana 1 la correctitud se justifica con lógica formal e invariantes de bucle. En la etapa experimental se asume el diseño y se audita la implementación: se usan Sanitizers y cobertura para comprobar que el código no introduce UB, fugas o errores de memoria.

   3. Afirmación de Costo

      El costo deja de ser una abstracción asintótica ($O(n)$ o $O(n^2)$) y se convierte en una métrica física tangible: microsegundos, ciclos de reloj y operaciones del procesador. La evidencia experimental demuestra empíricamente que reducir el costo no depende de escribir bucles manuales más complejos, sino de aprovechar la Biblioteca Estándar (STL) y funciones predictivas como .reserve() para eliminar el peaje oculto del sistema operativo.

   4. Afirmación de Representación o Memoria
   
      Esta es la ruptura más grande con la teoría pura. La evidencia experimental demuestra que la representación en memoria es tan vital como el algoritmo mismo. Comprobamos empíricamente que mantener una estructura de datos de memoria contigua (std::vector) y explotar la localidad espacial para complacer a la memoria Caché de la CPU supera brutalmente a representaciones fragmentadas (std::list), incluso cuando matemáticamente comparten la misma complejidad $O(n)$. 

   5. Advertencia Metodológica
   
      Los benchmarks y pruebas empíricas solo hablan del comportamiento bajo casos y arquitecturas concretas. Tener un buen tiempo de ejecución o 100% de cobertura no garantiza que el programa sea correcto para todos los casos extremos no considerados.

### Autoevaluación (Versión Breve)

* **Qué podemos defender con seguridad:**
  * **Teoría + Práctica:** El análisis matemático valida el *diseño*; las pruebas (*sanitizers*) validan la *implementación*. Ambas son obligatorias.
  * **Importancia de la Caché:** La memoria contigua (`std::vector`) destroza en rendimiento a la fragmentada (`std::list`).
  * **Dominio STL:** Usar la herramienta correcta (`reserve`, `lower_bound`) impacta mucho más que hacer microajustes manuales.

* **Qué todavía confundimos:**
  * **La magia del compilador:** Predecir con exactitud las decisiones de la "caja negra" bajo niveles agresivos como `-O3` (inlining, loop unrolling).
  * **Herramientas densas:** Interpretar reportes complejos de perfiladores clásicos (`gprof`) o los errores del enlazador en LTO.

* **Qué evidencia usaríamos en una sustentación:**
  * **Métricas de Rendimiento:** Las tablas de tiempos (microsegundos) y tamaños (bytes) generadas por nuestro script automatizado.
  * **Observables algorítmicos:** Variables como `lastSwapIndex` o `changed` que demuestran empíricamente la reducción del costo en tiempo real.
  * **Certificaciones de Calidad:** Reportes de cobertura de `gcov` y logs limpios de ASan/UBSan que garanticen cero errores de memoria.

