# Análisis de Rendimiento (Benchmark)

Al ejecutar el benchmark con 100 listas de 500 elementos (50,000 nodos en total), se obtuvieron los siguientes tiempos empíricos:

* **[Enfoque 1] Min-Heap O(N log k):** 7.1669 ms
* **[Enfoque 2] Fusión Secuencial O(N * k):** 29.7949 ms
* **[RETO VIVO] Divide & Conquer O(N log k):** 1.9791 ms

## Conclusión Técnica

1. **La Fusión Secuencial** es, como se esperaba teóricamente, el método más deficiente (casi 30 ms). Su complejidad O(N * k) provoca que el algoritmo repita recorridos sobre los mismos enlaces una y otra vez a medida que la lista combinada crece.
2. **El Min-Heap (Priority Queue)** demuestra la superioridad matemática de O(N log k), reduciendo el tiempo a 7.16 ms al evitar comparaciones redundantes y procesar directamente los mínimos.
3. **El Divide & Conquer (ADT Cola)**, a pesar de tener la misma complejidad teórica O(N log k) que el Min-Heap, resultó ser el más rápido en la práctica (1.97 ms). Esto se debe a que la operación `mergeTwoLists` ejecuta un bucle continuo altamente optimizado y amigable con la caché del procesador, evitando el "overhead" constante de rebalanceo de árbol que sufre el heap en cada inserción/extracción.