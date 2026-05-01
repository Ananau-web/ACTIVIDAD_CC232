## PC2 - CC232

### Estudiante
- **Nombre:** Rydell Jonel Mosquera Huayhua
- **Código:** 20232690K
- **Problema asignado:** LeetCode 23 - Merge k Sorted Lists
- **Enlace:** https://leetcode.com/problems/merge-k-sorted-lists/

### Referencia oficial
- **Archivo de asignación:** [Problemas-Evaluacion2.csv](https://github.com/kapumota/CC-232/blob/main/Practicas/Practica2_CC232/Problemas-Evaluacion2.csv)

### Tema principal
- **Semana:** Semana 3 (Listas enlazadas y adaptadores) / Semana 4 (Priority Queue)
- **Estructura o técnica principal:** Min-Heap (Priority Queue) y Divide and Conquer

### Resumen de la solución
Para fusionar $k$ listas de forma eficiente, utilizo un **Min-Heap**. Primero, inserto la cabeza de cada lista en el heap. En cada paso, extraigo el nodo con el valor más pequeño (raíz del heap) y lo conecto a la lista resultante. Si el nodo extraído tiene un sucesor, este entra al heap. Esto evita comparar todos los elementos entre sí, logrando una fusión óptima.
Si buscamos optimizar también el uso de la memoria, podemos aplicar el paradigma de Divide y Vencerás, similar al concepto de **Merge Sort**.

### Complejidad
- **Tiempo:** $O(N \log k)$, donde $N$ es el total de nodos en todas las listas y $k$ el número de listas. Cada inserción y extracción en el heap cuesta $O(\log k)$.
- **Espacio:** $O(k)$ para almacenar los punteros en el heap, ya que el heap contiene como máximo un nodo (la cabeza actual) por cada una de las $k$ listas.

### Invariante o idea clave
El Min-Heap siempre mantiene en su raíz el elemento más pequeño de entre todas las cabezas de las listas disponibles en ese momento. Esto asegura que, al extraerlos, la lista resultante siempre crezca manteniendo el orden ascendente.

### Archivos relevantes y Estructura del Proyecto
El repositorio sigue la estructura exigida para mantener el código modular y fácil de probar:
```text
📂 PC2/
├── 📁 benchmark/   # Código para el análisis empírico de tiempos (bench_merge.cpp)
├── 📁 demos/       # Código del visualizador animado paso a paso en consola (demo_merge.cpp)
├── 📁 docs/        # Documentación teórica y justificaciones algorítmicas
├── 📁 include/     # Archivos de cabecera (.h) con la implementación del Min-Heap y la lógica (MergeKLists.h)
├── 📁 resultados/  # Archivo de análisis (Analisis.md) con los resultados de las pruebas de rendimiento
├── 📁 tests/       # Archivo principal de pruebas para validar los casos borde y típicos (main.cpp)
├── 📁 video/       # Contiene el archivo de texto con el enlace a la grabación de la evaluación
└── 📄 CMakeLists.txt # Archivo de configuración central para compilar todo el proyecto
```

### Compilación
```bash
cmake -S . -B build
cmake --build build
```
### Ejecución
```Bash
./build/test_merge.exe
./build/bench_merge.exe
./build/demo_merge.exe
```
### Casos de prueba
1. **Caso de desbalance extremo:** Entrada: `[[1, 2, 3, ..., 10000], [5], [10]]` (Una lista masiva y varias listas de un solo elemento). Salida esperada: `[1, 2, 3, 5, 10, ... , 10000]`. *Justifica la eficiencia de la complejidad logarítmica frente a la fusión secuencial.*
2. **Caso de alta fragmentación:** Entrada: 100 listas diferentes, pero cada una con solo 1 o 2 elementos. Ej: `[[10], [1], [5, 6], [0], [2], ..., [99]]`. Salida esperada: Arreglo fusionado de todos los elementos. *Pone a prueba el límite de memoria espacial O(k) y la estructura inicial del Min-Heap.*
3. **Caso de colisiones y dominio negativo:** Entrada: `[[-10, -5, -1, 0, 0, 2], [-5, -2, 0, 1], [-10, -5, 0]]`. Salida esperada: `[-10, -10, -5, -5, -5, -2, -1, 0, 0, 0, 0, 1, 2]`. *Valida la solidez del criterio de comparación con números menores a cero y alta densidad de duplicados.*
4. **Caso de tamaños irregulares (Caso Borde):** Entrada: `[[], [1,2], [0]]`. Salida esperada: `[0,1,2]`. *Demuestra el manejo robusto de la estructura al combinar listas vacías con listas de tamaños pequeños sin generar errores de segmentación.*

### Historial de Commits

A continuación se detalla el progreso del desarrollo del proyecto, evidenciando la implementación progresiva de las estructuras de datos, pruebas y documentación.

```git
git commit -m "Agrega enlace al video de sustentacion en Google Drive"

git commit -m "Implementación del Divide and Conquer y SRC"

git commit -m "Actualiza README.md con correcciones y agrega carpeta docs para documentación adicional"

git commit -m "Integración de demos interactivos, benchmarks, análisis de rendimiento y mejoras en la cabecera .h"

git commit -m "Estructura base de Merge k Sorted Lists, pruebas y configuracion de CMake"
"
git commit  -m "Actividad 2 y 3"
```

### Declaración de autoría
Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, 
ejecutarlo y modificarlo sin ayuda externa durante la grabación.