# Directorio `src/`

Esta carpeta se incluye para cumplir estrictamente con la estructura de directorios solicitada en la evaluación de la PC2.

Sin embargo, debido a las decisiones de diseño arquitectónico tomadas para este proyecto, no contiene archivos `.cpp` de implementación central por las siguientes razones:

1. **Cumplimiento de la Regla 3.4 (Uso de cabeceras):** Se estipula el uso exclusivo de archivos de cabecera `.h`. Por ello, la lógica central de las estructuras de datos y algoritmos (Min-Heap, Divide and Conquer, y las clases `ListNode`) ha sido implementada bajo el paradigma *header-only* dentro del directorio `include/MergeKLists.h`.
2. **Modularidad de Ejecutables:** Para mantener el principio de responsabilidad única, los archivos `.cpp` que contienen las funciones `main()` han sido ubicados semánticamente en sus respectivas carpetas según su propósito:
   - Las pruebas de correctitud están en `tests/main.cpp`.
   - Las pruebas empíricas de rendimiento están en `benchmark/benchmark_merge.cpp`.
   - El visualizador de trazas en vivo está en `demos/demo_merge.cpp`.

