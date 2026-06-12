# PC3 - CC232

## Estudiante

- **Nombre:** Rydell Jonel Mosquera Huayhua
- **Código:** 20232690K
- **Repositorio:** [ACTIVIDAD_CC232/PC3](https://github.com/Ananau-web/ACTIVIDAD_CC232/tree/main/PC3)
- **Problema asignado:** AtCoder ABC308 G - Minimum Xor Pair
- **Enlace oficial:** https://atcoder.jp/contests/abc308/tasks/abc308_g

## Referencia oficial

- CSV: https://github.com/kapumota/CC-232/blob/main/Practicas/Practica3_CC232/Problemas-Evaluacion3.csv

## Relación con Semanas 4-6

- **Semana principal:** Semana 5 (BST, predecesor/sucesor, Treap)
- **Apoyo:** Semana 6 (PQ_ComplHeap, min-heap, lazy deletion)
- **Librería usada:** `include/Semana6/Treap.h` y `include/Semana6/PQ_ComplHeap.h`

## Qué resuelve el problema

Hay un conjunto dinámico de enteros. Llegan tres tipos de operaciones: insertar un número, eliminar un número, y consultar cuál es el par con XOR más pequeño entre todos los elementos actuales del conjunto.

La solución ingenua sería recalcular todos los pares en cada consulta (O(n²)), pero con hasta 200k operaciones eso no alcanza.

La idea que usé es que si los elementos están ordenados, el XOR mínimo entre cualquier par siempre aparece entre dos vecinos directos en ese orden. Si tengo a < b < c, entonces b XOR c ≤ a XOR c porque b y c comparten más bits altos. Nunca necesito calcular XOR entre elementos que no son adyacentes.

Entonces uso dos estructuras:
- **Treap** (de Semana 6) para mantener los números ordenados y encontrar predecesor/sucesor en O(log n)
- **LazyHeap** propio, que es un min-heap construido sobre `PQ_ComplHeap` con lazy deletion, para guardar los XOR entre vecinos directos

Cuando inserto un número nuevo busco sus vecinos antes de insertarlo, marco como obsoleto el par anterior entre ellos, y agrego los dos pares nuevos. Cuando elimino, hago lo inverso: marco obsoletos los pares del elemento eliminado y reconecto a sus ex-vecinos. Los duplicados los manejo con un `unordered_map` de frecuencias porque el Treap no acepta repetidos.

## Invariante

En cualquier momento, el heap guarda XOR entre vecinos directos del Treap (más algunos obsoletos que no se han limpiado todavía). El XOR mínimo real siempre está entre alguno de esos pares de vecinos. El `clean()` de LazyHeap saca los obsoletos de la raíz antes de devolver el mínimo, así que `getMin()` siempre devuelve un valor válido.

Para asegurar esto, se implementó el método `printNeighborXors()` en `XorManager`. Este recorre el Treap en inorden, imprime el XOR de cada par vecino, y verifica mediante un `assert` que el mínimo entre esos pares coincide exactamente con el valor que devuelve `getMinXor()`.

## Complejidad

- `insert`: O(log n) — predecesor y sucesor en Treap + push al heap + `treap.add`
- `erase`: O(log n) — vecinos + marcar obsoletos + `treap.remove`
- `getMinXor`: O(log n) amortizado — el `clean()` puede limpiar varios obsoletos pero cada uno fue insertado una sola vez antes

Total para m operaciones: **O(m log n)**

Espacio: O(n) para Treap + O(n) para heap + O(n) para el mapa de frecuencias

## Archivos

- `include/XorManager.h` — interfaz de la clase principal
- `include/LazyHeap.h` — min-heap con lazy deletion encima de PQ_ComplHeap
- `src/XorManager.cpp` — implementación de insert, erase y búsqueda de vecinos
- `tests/main.cpp` — 7 pruebas con assert
- `demos/traza_reto.cpp` — traza del reto grabado (pares que se crean y destruyen)
- `docs/respuestas_obligatorias.md` — respuestas a las preguntas del video
- `docs/bitacora.md` — proceso de desarrollo
- `resultados/` — evidencia de compilación, pruebas y casos borde

## Limpieza del repositorio

No hay builds ni ejecutables versionados. Para verificar:

```bash
git ls-files | grep -E "(^build/|cmake-build|\.exe$|\.out$|\.o$|CMakeCache)"
```

El `.gitignore` excluye `build/`, ejecutables, objetos y archivos de CMake.

## Compilación

```bash
cmake -S . -B build
cmake --build build
```

## Ejecución

```bash
./build/test_pc3
./build/demo_traza
ctest --test-dir build
```

## Pruebas

7 pruebas en `tests/main.cpp`, todas con assert:

| # | qué prueba | resultado |
|---|---|---|
| 1 | insert(2), insert(10) → minXor = 8 | pasa |
| 2 | insertar 5 entre 2 y 10 → minXor = 7 | pasa |
| 3 | insertar 2,5,10, eliminar 5 → minXor = 8 | pasa |
| 4 | insert(14) dos veces → minXor = 0, luego erase(14) → 23 | pasa |
| 5 | insert(42) solo → minXor = -1 | pasa |
| 6 | 10 valores, comparar contra fuerza bruta O(n²) | pasa |
| 7 | mínimo entre vecinos del treap == getMinXor() | pasa |

Casos borde documentados en `resultados/casos_borde.txt`.

## Evidencia Git

El historial muestra actividades de Semana 5 y Semana 6 previas a la PC3, seguidas de commits de la práctica en días distintos.

```bash
git log --date=short --pretty=format:"%ad - %h - %s"
git log --date=short --pretty=format:"%ad" | sort | uniq -c
```

## Declaración de autoría

Entiendo el código que entregué. Puedo explicar cómo funciona `getPredecessor()`, por qué `LazyHeap` necesita el mapa de obsoletos, qué pasa si me olvido de reconectar vecinos en `erase()`, y cómo el mapa de frecuencias resuelve el problema de los duplicados con el Treap.
