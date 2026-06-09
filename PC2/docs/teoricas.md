#  Merge K Sorted Lists (LeetCode 23)

Este documento detalla la resolución del problema utilizando un enfoque de **Min-Heap (Priority Queue)**, optimizando la complejidad temporal y espacial frente a métodos tradicionales, cumpliendo con los requerimientos de la PC2.

## 1. Respuestas a Preguntas de la Rúbrica

### ¿Qué guardas en el heap?
En el heap se almacenan **punteros a los nodos (`ListNode*`)**. Es crucial guardar el puntero completo y no solo el valor entero, ya que esto nos permite acceder al siguiente elemento de la lista (`node->next`) una vez que el actual es extraído y procesado.

### ¿Cuándo insertas el siguiente nodo?
La inserción ocurre inmediatamente después de realizar un `pop()` del heap. Si el nodo que acabamos de extraer tiene un sucesor (es decir, `minNode->next != nullptr`), insertamos ese **nodo sucesor** en el heap. Esto garantiza que el heap siempre tenga, como máximo, un representante de cada lista.

### ¿Por qué es mejor que fusionar todo secuencialmente?
* **Fusión Secuencial:** Tiene una complejidad de **$O(N \cdot k)$**. Al fusionar la Lista 1 con la 2, luego el resultado con la 3, y así sucesivamente, los elementos de las primeras listas se recorren de forma redundante múltiples veces.
* **Enfoque Min-Heap:** Al usar un heap, cada uno de los $N$ nodos totales entra y sale del heap **exactamente una vez**. Esto reduce drásticamente el trabajo redundante, permitiendo que el algoritmo sea escalable para cientos de listas.

### ¿Qué complejidad total obtienes?
* **Complejidad Temporal:** **$O(N \log k)$**, donde $N$ es el número total de nodos y $k$ es la cantidad de listas. La operación de reordenar el heap tras cada extracción/inserción es logarítmica respecto a $k$.
* **Complejidad Espacial:** **$O(k)$**, ya que el heap solo necesita mantener en memoria un nodo por cada lista activa.

## 2. Detalles de Implementación 

### Criterio de Extracción Mínima
Para la implementación en C++, se utilizó el adaptador de contenedor `std::priority_queue` junto con un **functor de comparación personalizado** llamado `CompareNode`.

```cpp
struct CompareNode {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val; // Define el comportamiento de un Min-Heap
    }
};
```
Este criterio asegura que el nodo con el valor numérico más bajo siempre esté en la parte superior (top) del heap, permitiendo una extracción eficiente en tiempo constante $O(1)$.
### Comparativa de Rendimiento (Benchmark)
Como se demostró en los resultados del benchmark_merge.exe, el uso de estructuras de datos avanzadas (Min-Heap) reduce el tiempo de ejecución a casi la mitad en comparación con la fusión secuencial, validando empíricamente la superioridad de la complejidad logarítmica sobre la lineal en este problema.