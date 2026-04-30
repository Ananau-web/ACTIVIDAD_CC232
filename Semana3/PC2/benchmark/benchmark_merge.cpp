#include <iostream>
#include <vector>
#include <chrono>
#include "MergeKLists.h"

// Función auxiliar para generar K listas largas para forzar a la CPU
std::vector<ListNode*> generateLargeTestData(int numLists, int elementsPerList) {
    std::vector<ListNode*> lists;
    for (int i = 0; i < numLists; i++) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        for (int j = 0; j < elementsPerList; j++) {
            // Genera números ordenados ascendentes
            tail->next = new ListNode(i + j * 2); 
            tail = tail->next;
        }
        lists.push_back(dummy.next);
    }
    return lists;
}

int main() {
    std::cout << "=================================================\n";
    std::cout << "      BENCHMARK: MERGE K SORTED LISTS            \n";
    std::cout << "=================================================\n\n";

    int K = 100;     // 100 listas
    int L = 500;     // 500 elementos por cada lista (Total: 50,000 nodos)
    
    std::cout << "Generando datos de prueba: " << K << " listas de " << L << " elementos cada una...\n";
    std::cout << "Total de nodos a procesar: " << K * L << "\n\n";

    Solution sol;

    // ---------------------------------------------------------
    // 1. Min-Heap (Tu solución óptima principal)
    // ---------------------------------------------------------
    auto lists1 = generateLargeTestData(K, L);
    auto start1 = std::chrono::high_resolution_clock::now();
    sol.mergeKLists(lists1);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> diff1 = end1 - start1;
    std::cout << "[Enfoque 1] Min-Heap O(N log k) - (Uso de Adaptadores):             " << diff1.count() << " ms\n";

    // ---------------------------------------------------------
    // 2. Fusión Secuencial (El peor caso para comparar)
    // ---------------------------------------------------------
    auto lists2 = generateLargeTestData(K, L);
    auto start2 = std::chrono::high_resolution_clock::now();
    sol.mergeKListsSequential(lists2);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> diff2 = end2 - start2;
    std::cout << "[Enfoque 2] Fusion Secuencial O(N * k) - (Costo alto por enlaces):  " << diff2.count() << " ms\n";


    std::cout << "\nBenchmark finalizado.\n";
    return 0;
}
