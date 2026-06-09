## Actividad 4-CC232

### Integrantes
- RYDELL JONEL MOSQUERA HUAYHUA

#### Bloque 1 - Núcleo conceptual de la semana

Responde:

##### 1. Diferencia entre acceso LIFO y acceso FIFO
El acceso LIFO (Last-In, First-Out) funciona bajo la premisa de "lo último que llega es lo primero que se atiende". Imagina una pila de platos: solo puedes retirar el que pusiste al final (el de arriba) sin desmoronar el resto. Por otro lado, el acceso FIFO (First-In, First-Out) sigue la lógica de "el primero que llega es el primero en salir", tal como una fila en el banco; se respeta estrictamente el orden de llegada.

##### 2. Stack y "lo último pendiente"
Una pila (Stack) resuelve estos problemas porque mantiene un registro de estados en orden inverso. Cuando un proceso se interrumpe para atender un sub-proceso (como en una llamada a función o un paréntesis abierto), el estado actual se "guarda" arriba. Al terminar la tarea más reciente, la estructura nos devuelve automáticamente lo que dejamos pendiente inmediatamente antes, permitiendo retomar el hilo exacto de ejecución.

##### 3. Queue y procesos de espera
La cola (Queue) es el modelo ideal para la justicia y el orden cronológico. En sistemas de computación (como una cola de impresión o procesamiento de paquetes de red), garantiza que ninguna solicitud se quede olvidada al fondo mientras llegan nuevas. Modela la atención porque separa el momento de la "llegada" del momento del "procesamiento", manteniendo la integridad de la secuencia temporal.

##### 4. Reemplazar recursión implícita por estructura explícita
Cuando una función se llama a sí misma, el sistema utiliza una pila interna (pila de llamadas o call stack) de forma "invisible" para el programador. Reemplazar esto significa que tú, como programador, creas manualmente un objeto Stack en tu código y gestionas qué datos entran y salen. Esto da más control sobre la memoria y evita errores de "Stack Overflow" en procesos muy profundos.

##### 5. Información mínima para reconstruir una solución parcial
Para que una pila permita reconstruir un camino o solución, debe almacenar el Estado del Sistema en cada paso. Esto incluye:

Posición o valor actual: (ej. coordenadas en un laberinto).

Opciones restantes: Qué caminos o decisiones aún no se han explorado desde ese punto exacto para poder volver si la ruta actual falla.

##### 6. Conversión de base: Recursiva vs. Iterativa
Comparten: La lógica matemática (divisiones sucesivas por la base y obtención del residuo).

Cambio en el control: En la recursiva, los residuos se imprimen al "regresar" de la recursión (aprovechando la pila del sistema). En la iterativa, los residuos se generan en orden inverso al que deben mostrarse, por lo que se deben guardar en una pila manual para luego invertirlos al salir.

##### 7. Verificación de paréntesis y aperturas pendientes
Es necesario almacenar las aperturas porque un paréntesis de cierre ) no es válido por sí solo; solo es válido si "cancela" al último paréntesis de apertura ( que aún no ha sido cerrado. La pila nos permite saber siempre cuál es el paréntesis más reciente que espera ser completado, asegurando que el orden de anidación sea correcto.

##### 8. Evaluador de expresiones: ¿Por qué dos pilas?
Se necesitan dos para separar la jerarquía de las operaciones:
Pila de Operandos (Números): Guarda los valores que esperan ser procesados.
*Pila de Operadores (+, , /, etc.): Guarda las operaciones pendientes.
Esto es vital porque los operadores tienen diferentes precedencias (la multiplicación va antes que la suma). La pila de operadores permite "aguantar" una suma hasta que confirmemos que no viene algo más importante después.

##### 9. N-Reinas y Laberinto como Backtracking
Ambos son problemas de búsqueda en un espacio de decisiones. Se consideran naturales para el backtracking porque implican "ensayo y error" sistemático:
Tomas una decisión (colocar una reina o avanzar a una celda).
Si llegas a un callejón sin salida, usas la pila para retroceder exactamente al punto anterior y probar la siguiente opción disponible.

##### 10. Simulación bancaria: ¿Pila o Cola?
Una simulación bancaria busca medir tiempos de espera reales. Si usáramos una pila, el último cliente en llegar sería atendido primero, dejando a los que llegaron temprano esperando indefinidamente (hambruna de procesos). La cola es la única que permite modelar el flujo de tiempo real y el rendimiento del servicio basado en el orden de llegada.

##### 11. Estructura auxiliar, estado parcial y correctitud
La estructura auxiliar (pila o cola) es el soporte físico donde reside el estado parcial (lo que hemos resuelto hasta ahora). La correctitud del algoritmo depende de que la estructura elegida coincida con la lógica del problema: si el problema requiere orden histórico y usamos una pila, el resultado será incorrecto porque procesaremos los datos en el sentido opuesto al necesario.

##### 12. Resolver un problema vs. Simular un proceso
Resolver un problema: Se enfoca en el resultado final. No importa tanto "cómo" se llega, siempre que la respuesta sea óptima o correcta (ej. encontrar la salida del laberinto).
Simular un proceso: Se enfoca en el comportamiento a través del tiempo. El objetivo es observar cómo interactúan los elementos y recolectar estadísticas (ej. saber cuánto tiempo promedio esperó una persona en el banco), sin que necesariamente haya una "solución" única al final.

#### Bloque 2 - Demostración y trazado guiado

Revisa:

- `Semana4/demos/demo_stack_queue.cpp`
- `Semana4/demos/demo_base_conversion.cpp`
- `Semana4/demos/demo_paren_rpn.cpp`
- `Semana4/demos/demo_nqueens.cpp`
- `Semana4/demos/demo_maze.cpp`
- `Semana4/demos/demo_bank.cpp`
- `Semana4/demos/demo_capitulo4_panorama.cpp`

Construye una tabla con cuatro columnas:

- Archivo
- Salida u observable importante
- Estructura o técnica central
- Qué concepto permite defender

Luego responde:


##### 1. En `demo_stack_queue.cpp`, ¿qué parte de la salida deja más clara la diferencia entre tope y frente?
- El Tope(Pila-LIFO): La salida muestra Tope de la pila = 9. Esto se debe a que el 9 es el ultimo elemento insertado mediante **stack.push(9)**. Es una pila, el acceso siempre es al elemento más reciente, ubicado en la parte "superior " o final del vertor interior
- El Frente (Cola - FIFO): La salida muestra Frente de la cola = 10. A diferencia de la pila, el 10 fue el primer elemento insertado mediante **queue.enqueue(10)**. En una cola, el acceso es al elemento más antiguo, ubicado al "inicio" de la estructura para respetar el orden de llegada.
##### 2. En `demo_base_conversion.cpp`, ¿qué observable permite afirmar que las versiones recursiva e iterativa producen la misma representación?
Al correr la demo, las dos funciones imprimen los mismos residuos en el mismo orden. Es decir, ves la misma cadena de números impresa en consola para ambas versiones. Esto demuestra empíricamente que hacer el trabajo "al revés" usando una pila manual da exactamente el mismo resultado que apoyarse en la pila de llamadas del sistema (recursión).

##### 3. En `demo_paren_rpn.cpp`, ¿qué relación observas entre paréntesis balanceados, RPN y valor final?
Los paréntesis balanceados garantizan que la expresión infija tiene sentido (las operaciones están bien agrupadas). Al pasarla a RPN (Notación Polaca Inversa), la expresión ya no necesita los paréntesis porque el orden de las operaciones queda dictado por la posición. Finalmente, calcular el valor final a partir de RPN es súper directo usando una pila: apilas números y cada vez que ves un operador, sacas los dos últimos números, los operas y metes el resultado.

##### 4. En `demo_nqueens.cpp`, ¿qué significan `solutions` y `checks`, y por qué no miden lo mismo?
`solutions` es el número de tableros válidos donde las N reinas no se atacan entre sí (es lo que buscamos). `checks` es la cantidad de veces que el algoritmo tuvo que comprobar si una casilla era segura. No miden lo mismo porque el algoritmo tiene que hacer muchísimos `checks` (ensayo y error, explorando caminos que no sirven) para encontrar unas cuantas `solutions`. Es la esencia del backtracking.

##### 5. En `demo_maze.cpp`, ¿qué muestra la secuencia de coordenadas sobre el camino encontrado?
Muestra el rastro que dejó la solución. Como usa una pila para el backtracking, la secuencia de coordenadas desde la entrada a la salida es exactamente el contenido final de la pila cuando encuentra el destino. Cada coordenada representa una celda válida del laberinto por donde el algoritmo avanzó sin tener que retroceder.

##### 6. En `demo_bank.cpp`, ¿qué representa cada lista impresa en cada instante `t`?
Representa la "foto" de la cola de clientes esperando en ese segundo exacto. Como es una simulación basada en tiempo, cada instante `t` muestra si alguien nuevo entró a la cola (se suma al final) o si alguien pasó a una ventanilla (sale del frente). Demuestra perfectamente cómo la estructura FIFO mantiene el orden de llegada.

##### 7. En `demo_capitulo4_panorama.cpp`, ¿qué salida resume mejor la idea de que una misma semana reúne estructuras y aplicaciones?
La salida donde muestra los ejemplos corriendo uno tras otro. Empieza mostrando las operaciones puras de las estructuras (Push/Pop en Stack y Enqueue/Dequeue en Queue) y luego, usando esas mismas estructuras base, resuelve problemas totalmente distintos como evaluar expresiones matemáticas o simular un banco. Esto comprueba que Stack y Queue no son solo teoría, sino herramientas para modelar problemas reales.

#### Bloque 3 - Pruebas públicas, pruebas internas y correctitud

##### 1. ¿Qué operaciones mínimas valida la prueba pública para `Stack`?
Valida el `push`, el `pop`, revisar el `peek` (tope) y asegurarse de que `isEmpty` y `size` cambien correctamente. Básicamente que funcione como LIFO.

##### 2. ¿Qué operaciones mínimas valida la prueba pública para `Queue`?
Valida `enqueue` (meter al final), `dequeue` (sacar del frente), `peek` (ver el frente) y también los contadores de tamaño. Comprueba la lógica FIFO.

##### 3. ¿Qué valida la prueba pública sobre conversión de base?
Chequea que al pasarle números básicos (como 10 a binario o hexadecimal) la cadena de texto de salida sea exactamente la esperada.

##### 4. ¿Qué valida la prueba pública sobre paréntesis balanceados?
Que la función booleana retorne true para casos simples como `(())` y false para desbalances típicos como `(()` o `())`.

##### 5. ¿Qué valida la prueba pública sobre evaluación de expresiones y RPN?
Que la conversión a Notación Polaca Inversa dé el string correcto y que el resultado numérico final cuadre, considerando la prioridad matemática.

##### 6. ¿Qué valida la prueba pública sobre `NQueens`?
Valida que para un tablero pequeño (ej. n=4 o n=8) la cantidad total de soluciones encontradas cuadre con el número matemático real conocido.

##### 7. ¿Qué valida la prueba pública sobre `Maze`?
Se asegura de que si le pasas un laberinto con salida obvia, el algoritmo de backtracking devuelva true y la ruta. Y si no hay salida, devuelva false.

##### 8. ¿Qué valida la prueba pública sobre `bestWindow` en la simulación bancaria?
Que el algoritmo de decisión realmente escoja la cola con menor tamaño (`size`) de entre todas las ventanillas disponibles en un instante dado.

##### 9. ¿Qué casos adicionales cubre la prueba interna y no aparecen de forma explícita en la pública?
Las internas prueban cosas como desbordar la capacidad del arreglo interno para ver si hace bien el `expand` dinámico. También revisan que no existan memory leaks.

##### 10. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes, estado y complejidad?
Porque las pruebas son un "caja negra"; solo ven que el input dio el output correcto. Pero si hiciste que un Stack funcione con costo `O(n)` en cada push, pasarás la prueba pero el diseño es terrible porque un push debe ser siempre `O(1)`.

##### 11. Da un ejemplo de un error conceptual que podría sobrevivir si solo se ejecutaran los casos mínimos.
Olvidarse de hacer `pop` cuando evalúas paréntesis cruzados. Si solo pruebas `((()))`, funcionaría, pero con combinaciones locas se podría llenar la pila sin limpiar la memoria.

#### Bloque 4 - Comparación recursivo vs iterativo

##### 1. En conversión de base, ¿qué papel juegan el cociente, el residuo y la pila?
El cociente achica el número original, el residuo es el nuevo dígito en esa base, y la pila sirve para guardar esos dígitos que salen "al revés" para poder imprimirlos en el orden correcto al final.

##### 2. ¿Por qué los residuos se apilan antes de formar la cadena final?
Porque al dividir sucesivamente, el primer residuo que obtienes es el dígito menos significativo (el de más a la derecha). Al apilarlos y luego sacarlos, aplicas LIFO e inviertes el orden, dejándolos en la lectura normal.

##### 3. ¿Qué cambia entre dejar que el call stack haga el trabajo y manejar una pila explícita?
Que el call stack del sistema operativo hace la inversión del orden "gratis", pero tiene riesgo de crashear por *stack overflow* si el proceso es gigante. Con la pila explícita tú controlas la RAM.

##### 4. En `parenRecursive`, ¿qué idea intenta capturar `divideParentheses`?
Busca partir el problema en partes más pequeñas cortando los bloques de paréntesis cerrados. Si está todo cerrado bien, lo divide y analiza la mitad interna recursivamente.

##### 5. ¿Qué limitación conceptual tiene la versión recursiva mostrada frente a la iterativa cuando aparecen `[]` y `{}`?
Escalar la recursiva a múltiples tipos de corchetes requiere meterle muchos más condicionales "if" feos, mientras que la iterativa con pila solo apila la llave de apertura y chequea fácil su pareja de cierre.

##### 6. En `parenIterative`, ¿por qué un cierre incorrecto puede detectarse apenas aparece?
Porque si estás leyendo un `]` y el tope de tu pila es un `(`, la incompatibilidad salta inmediatamente y cortas el chequeo retornando false de golpe.

##### 7. Compara ambas parejas de funciones: ¿en cuál caso la versión iterativa te parece más natural y en cuál la recursiva resulta más expresiva?
Para conversión de base, la recursiva es súper corta y expresiva. Pero para paréntesis, la iterativa con la pila se siente más natural porque físicamente estás "apilando" llaves abiertas y matándolas cuando llega su pareja.

##### Experimento 1

| Número | Base | Salida recursiva | Salida iterativa | ¿Coinciden? | Comentario |
|---|---|---|---|---|---|
| 10 | 2 | 1010 | 1010 | Sí | Caso básico binario |
| 255 | 16 | FF | FF | Sí | Conversión a hexa correcta |
| 73 | 8 | 111 | 111 | Sí | Octal perfecto |
| 0 | 2 | 0 | 0 | Sí | El caso cero no rompe ninguna |
| 1024 | 16 | 400 | 400 | Sí | Ambas funcionan igual para números grandes |

##### Experimento 2

| Expresión | Res. Recursivo | Res. Iterativo | ¿Coinciden? | Explicación del caso |
|---|---|---|---|---|
| "" | true | true | Sí | Cadena vacía está balanceada por defecto |
| "hola" | true | true | Sí | Sin paréntesis no hay desbalance |
| "((()))" | true | true | Sí | Anidamiento correcto simple |
| "(()" | false | false | Sí | Sobra una apertura |
| "[(])" | false | false | Sí | Cruce malo (el iterativo lo detecta al toque) |
| "{[()]}" | true | true | Sí | Mix de delimitadores cerrado perfectamente |
| "((...))"| true | true | Sí | Soportan cadenas largas |
| "())(" | false | false | Sí | Empieza cerrando antes de abrir, fatal |

#### Bloque 5 - Evaluación de expresiones y prioridad de operadores

##### 1. Explica qué información guarda `EvaluationResult`.
Guarda una estructura que empaqueta dos cosas a la vez: el valor numérico calculado y el string con la expresión traducida a Notación Polaca Inversa (RPN).

##### 2. Explica por qué primero se eliminan espacios.
Para no ensuciar la lógica del escáner al leer. Si dejas los espacios, tendrías que meter comprobaciones extra en todas partes del algoritmo.

##### 3. Explica cómo se detecta el signo menos unario.
Se distingue del menos de resta viendo el contexto: si hay un `-` al principio de todo o justo después de un paréntesis de apertura `(`, entonces es cambio de signo (unario) y no resta normal.

##### 4. Explica por qué el factorial se trata como operador unario y qué restricción impone el código.
Porque opera sobre un solo número a su izquierda (n!). La restricción usual es que solo trabaja con números enteros positivos, a diferencia del menos unario.

##### 5. Explica cómo la RPN se va construyendo durante la evaluación y no al final.
Mientras el algoritmo de Dijkstra lee la ecuación, cada vez que un operador es forzado a salir de la pila (por precedencia), se concatena instantáneamente al string RPN resultante.

##### 6. Explica qué significa la relación entre operador del tope y símbolo actual.
Es la guerra de precedencias. Si llega un `*` y en el tope hay un `+`, el `*` se apila porque es más fuerte. Si llega un `+` y el tope es `*`, el `*` tiene que resolverse primero, así que sale de la pila.

##### 7. Explica por qué una expresión mal formada debe terminar en error y no en un valor arbitrario.
Porque devolver un "0" o un valor falso por defecto es peligroso en matemáticas. Es mejor lanzar una excepción (error) que arruinar un cálculo más grande.

##### 8. ¿Qué ventaja conceptual tiene obtener a la vez el valor y la RPN?
Demuestra que entender la jerarquía de operadores para resolver la ecuación es exactamente la misma lógica necesaria para traducirla a formato RPN.

##### Experimento 3

| Expresión | RPN esperada | RPN obtenida | Valor esperado | Valor obtenido | Explicación |
|---|---|---|---|---|---|
| "3+5" | 3 5 + | 3 5 + | 8 | 8 | Simple suma |
| "2*3+4" | 2 3 * 4 + | 2 3 * 4 + | 10 | 10 | Mult gana prioridad |
| "(2+3)*4" | 2 3 + 4 * | 2 3 + 4 * | 20 | 20 | Paréntesis altera prioridad |
| "3+4*2/(1-5)^2"| 3 4 2 * 1 5 - 2 ^ / + | Igual | 3.5 | 3.5 | Anidamiento extremo correcto |
| "-5+2" | 5 ~ 2 + | 5 ~ 2 + | -3 | -3 | Menos unario (notado como ~) |
| "(3+)" | Error | Error | Error | Error | Expresión inválida capturada |

##### Extensión opcional

- **Símbolo agregado**: `%` (Módulo)
- **Aridad**: Binario (2 operandos)
- **Prioridad**: Igual a la multiplicación y división.
- **Casos válidos**: `10 % 3` (da 1)
- **Caso inválido**: `10 % 0` (lanza error por división cero)
- **Código modificado**: Añadido el caso `%` en el `switch` de precedencia y ejecución de operador.

#### Bloque 6 - Backtracking explícito: N-Reinas y laberinto

##### 1. En `Queen`, ¿qué significa que dos reinas entren en conflicto?
Significa que comparten la misma fila, la misma columna o las mismas diagonales.

##### 2. En `NQueens`, ¿qué representa exactamente la pila `solution`?
Es la memoria del tablero seguro actual. Cada elemento guarda las coordenadas `(fila, columna)` donde ya hemos colocado de forma segura una reina.

##### 3. ¿Qué significa avanzar en columna dentro de una fila y cuándo toca retroceder?
Avanzar es probar poner la reina en `col = 0`, luego `1`, etc. Toca retroceder (pop de la pila) cuando agotaste todas las columnas de esa fila y ninguna sirve, lo que significa que una reina puesta arriba limitó todo.

##### 4. ¿Por qué `checks` es una métrica útil para analizar la búsqueda?
Porque "cuántas soluciones hay" no refleja el esfuerzo. `checks` cuenta cada vez que intentaste ver si una casilla era válida, midiendo el desgaste real del algoritmo.

##### 5. ¿Qué cambia cuando `collectPlacements` vale `false`?
Deja de clonar y guardar los tableros ganadores en un vector, retornando solo el número total. Evita que la RAM explote cuando `n` es enorme.

##### 6. En `Maze`, ¿qué representa el estado `AVAILABLE`, `ROUTE`, `BACKTRACKED` y `WALL`?
- `AVAILABLE`: Celda libre que no pisamos aún.
- `ROUTE`: Celda que es parte del camino que estamos tomando ahora.
- `BACKTRACKED`: Celda que probamos pero nos llevó a un callejón sin salida (ruta muerta).
- `WALL`: Pared sólida inpasable.

##### 7. ¿Qué información codifican `incoming` y `outgoing`?
`incoming` te dice desde dónde llegaste a esa celda, y `outgoing` hacia dónde te moviste luego. Útil para dibujar el camino en una interfaz gráfica.

##### 8. ¿Por qué el algoritmo del laberinto marca y desmarca estado en lugar de solo "moverse"?
Si no marcara, caminaría en círculos infinitos. El desmarcado (backtrack a un estado anterior) es vital para no bloquear otras rutas posibles si venimos por otro lado.

##### 9. Compara N-Reinas y laberinto: ¿qué comparten como problemas de búsqueda y qué cambia en la representación del estado?
Ambos usan ensayo y error. La diferencia es que en N-Reinas el estado es global (una reina arriba invalida celdas hasta el fondo), y en el laberinto el estado es estrictamente local (solo ves a tus vecinos).

##### Experimento 4

| `n` | número de soluciones | número de `checks` | ¿crece rápido o lento? | comentario |
|---|---|---|---|---|
| 4 | 2 | ~110 | Normal | Fácil |
| 8 | 92 | ~15,000 | Rápido | Tablero de ajedrez típico |
| 10 | 724 | ~400,000 | Muy Rápido | Explosión combinatoria |
| 12 | 14,200 | ~15,000,000 | Exponencial | Ya se nota el tiempo de proceso |

1. **¿Qué patrón observas en el crecimiento de `checks`?** Crece de forma exponencial brutal. Subir `n` dispara los intentos a millones muy rápido.
2. **¿Por qué contar verificaciones no es lo mismo que contar soluciones?** Porque el 99% del tiempo el algoritmo está chocando y retrocediendo, el éxito es la excepción.
3. **¿Dónde aparece la "poda" en este código?** Cuando una reina choca, el algoritmo no sigue poniendo las demás a lo loco; corta ahí y pasa a la siguiente columna, ahorrando cálculos inútiles.

##### Experimento 5
- **Laberinto Claro**: Una línea recta. Longitud: 5, Retrocesos: 0. Fue directo.
- **Laberinto Sin Salida**: Rodeado de paredes. Longitud: 0, Retrocesos: Todos. Intentó todos los pasillos y regresó marcando todo como `BACKTRACKED`.
- **Laberinto con Retrocesos**: Un pasillo trampa largo. Avanzó, chocó con pared, hizo backtrack (pintando gris) y tomó la otra ruta real hacia la salida.

#### Bloque 7 - Simulación bancaria y experimentación con colas

##### 1. ¿Qué representa cada `Queue<Customer>` dentro del vector `windows`?
Cada elemento del vector es la fila de espera física enfrente de cada uno de los cajeros del banco.

##### 2. ¿Qué criterio usa `bestWindow` y qué decisión toma cuando hay empate?
Retorna el índice de la cola que tiene el menor `size()`. Si hay empate (ej. dos colas vacías), escoge la primera que leyó (la de más a la izquierda).

##### 3. ¿Qué significa que la simulación use una semilla (`seed`)?
Que usa un generador pseudo-aleatorio. Si le pasas la misma semilla hoy y mañana, los clientes van a llegar en los mismos segundos exactos, permitiendo repetir el experimento.

##### 4. ¿Qué relación debe cumplirse entre `totalArrivals` y `totalServed`, y por qué?
`totalServed` siempre debe ser menor o igual a `totalArrivals`. No puedes atender a más gente de la que entró.

##### 5. ¿Qué representa la línea de tiempo (`timeline`) en el resultado?
Es un ciclo for que actúa como el reloj del simulador (`for t = 0 to time`). Avanza el tiempo simulado segundo a segundo, revisando si llegan o salen clientes.

##### 6. ¿Por qué esta aplicación necesita colas y no pilas?
¡Porque si usaras una pila LIFO, el último cliente en llegar sería atendido primero, y los primeros que llegaron se quedarían a vivir en el banco! La cola da equidad y orden (FIFO).

##### 7. ¿Qué simplificación del mundo real introduce este simulador?
Asume que los clientes tienen paciencia infinita (no se hartan y se van) y que no hay "colados" ni gente cambiándose de fila a mitad del proceso.

##### 8. ¿Qué cambiaría si la política ya no fuera "cola más corta" sino otra?
Si fuera una "única cola gigante en serpentina" (como en aeropuertos), se aprovecharía mucho mejor el tiempo muerto de los cajeros. Si fuera aleatoria, un cajero podría tener 10 personas y el de al lado 0.

##### Experimento 6

| `nWin` | `servTime` | `seed` | `Arrivals` | `Served` | Colas finales | Observación |
|---|---|---|---|---|---|---|
| 3 | 5 | 123 | 20 | 18 | [0, 1, 1] | Flujo rápido, casi nadie quedó rezagado al final. |
| 1 | 5 | 123 | 20 | 8 | [12] | Un solo cajero produce un cuello de botella terrible. |
| 3 | 10 | 123 | 20 | 12 | [3, 2, 3] | Son muchos cajeros, pero son muy lentos; la cola crece. |

1. **¿Qué parámetro parece influir más en la congestión observable?** El número de ventanillas (`nWin`). Alterar la semilla mueve el flujo un poco, pero bajar las ventanillas destruye el tiempo de espera.
2. **¿Qué cambia cuando repites exactamente la misma semilla?** Nada. Es un universo calcado al anterior; los clientes llegan exactamente igual.
3. **¿Qué cambia cuando mantienes `nWin` y `servTime`, pero alteras la semilla?** El tráfico cambia. A veces llegan todos amontonados al principio, y otras veces llegan repartidos mejor.
4. **¿Qué evidencia usarías para defender que la cola más corta es una política razonable, aunque no necesariamente óptima?** Es razonable porque distribuye visualmente el peso, evitando colas larguísimas y otras vacías. No es óptima porque no sabemos el "tiempo" de los trámites: la cola corta podría tener clientes haciendo depósitos complejos de 1 hora.

#### Bloque 8 - Cierre comparativo y preparación de sustentación

**¿Qué cambia cuando pasamos de "usar pilas y colas como ADTs básicos" a "usarlas como mecanismos de control para resolver problemas"?**

El gran salto conceptual es darse cuenta de que las pilas y colas dejan de ser simplemente "bases de datos" para convertirse en **el motor que dirige la inteligencia del algoritmo**.
- Pasamos de ver a `LIFO` y `FIFO` como simples formas de guardar cosas, a usarlas como tácticas de navegación: `FIFO` nos sirve para controlar y administrar el tiempo de forma ordenada y justa (simuladores), y `LIFO` nos permite navegar dimensiones o espacios de decisión y poder retroceder (Backtracking).
- Entendemos que la recursión no es mágica, es solo el sistema operativo prestando su propia pila (call stack). Al pasarnos a una estructura explícita, nosotros decidimos cómo fluye el programa y libramos al sistema de crashear por *stack overflow*.
- Comprobamos que evaluar expresiones no es solo "leer caracteres", la Pila actúa como un traductor matemático capaz de aguantar el paso de un `+` hasta que un `*` se resuelva.
- Vimos que sin una Pila (`LIFO`), el laberinto y las N-Reinas serían imposibles, ya que no habría forma de recordar la última encrucijada válida al chocar con una pared.
- Entendemos que el simulador bancario requiere una Cola (`FIFO`) para preservar la realidad cronológica.
- Finalmente, al comparar algo tan simple como invertir la base binaria con algo tan duro como el Backtracking de Reinas, defendemos bajo correctitud experimental que estas estructuras son las verdaderas directoras de la lógica de programación moderna.