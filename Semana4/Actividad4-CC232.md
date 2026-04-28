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

##### 3. En `demo_paren_rpn.cpp`, ¿qué relación observas entre paréntesis balanceados, RPN y valor final?

##### 4. En `demo_nqueens.cpp`, ¿qué significan `solutions` y `checks`, y por qué no miden lo mismo?

##### 5. En `demo_maze.cpp`, ¿qué muestra la secuencia de coordenadas sobre el camino encontrado?

##### 6. En `demo_bank.cpp`, ¿qué representa cada lista impresa en cada instante `t`?

##### 7. En `demo_capitulo4_panorama.cpp`, ¿qué salida resume mejor la idea de que una misma semana reúne estructuras y aplicaciones?