# Análisis de Rendimiento (Benchmark)

Al ejecutar el benchmark con 100 listas de 500 elementos (50,000 nodos en total), se obtuvieron los siguientes tiempos:

* **[Enfoque 1] Min-Heap O(N log k):** 23.404 ms
* **[Enfoque 2] Fusión Secuencial O(N * k):** 43.0254 ms
* **[RETO VIVO] Divide & Conquer O(N log k):** XX.XX ms

## Conclusión Técnica
La Fusión Secuencial resulta ser la más ineficiente debido a la redundancia al recorrer múltiples veces los mismos enlaces de los nodos iniciales. El enfoque principal utilizando un **Min-Heap** (Priority Queue) reduce el tiempo drásticamente a un comportamiento logarítmico. 

Adicionalmente, el reto utilizando el **ADT Cola (Queue)** demuestra que es posible alcanzar la misma complejidad óptima de O(N log k) mediante la técnica de Divide and Conquer, reciclando la función de fusión de dos listas y emparejándolas de forma iterativa sin necesidad de usar estructuras de árbol pesado.