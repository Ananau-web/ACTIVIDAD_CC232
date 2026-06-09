#pragma once
#include "PQ_ComplHeap.h"
#include <unordered_map>
#include <functional>

class LazyHeap {
private:
    // Al usar std::greater, el getMax() interno de PQ_ComplHeap nos devolverá el mínimo real.
    ods::PQ_ComplHeap<long long, std::greater<long long>> pq;
    std::unordered_map<long long, int> obsoletos;

    // Método privado para limpiar la basura en la raíz del Heap
    // Complejidad amortizada: O(log n) - extrae todos los obsoletos hasta encontrar uno válido
    void clean() {
        while (!pq.empty()) {
            long long current_min = pq.getMax(); // getMax() devuelve el min por std::greater
            
            // Validar existencia antes de usar el mapa (evita inserción accidental)
            if (obsoletos.count(current_min) && obsoletos[current_min] > 0) {
                obsoletos[current_min]--;
                pq.delMax(); // Extraemos el elemento obsoleto
            } else {
                break; // La raíz es un par XOR válido
            }
        }
    }

public:
    void push(long long val) {
        pq.insert(val);
    }

    void markAsObsolete(long long val) {
        obsoletos[val]++;
    }

    long long getMin() {
        clean(); // Siempre limpiamos antes de consultar
        if (pq.empty()) return -1; // Caso frontera
        return pq.getMax(); 
    }
};