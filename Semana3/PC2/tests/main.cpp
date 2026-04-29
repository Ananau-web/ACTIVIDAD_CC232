#include <iostream>
#include <vector>
#include "MergeKLists.h"

// Función auxiliar para imprimir la lista resultante
void printList(ListNode* head) {
    while (head) {
        std::cout << head->val << (head->next ? " -> " : "");
        head = head->next;
    }
    std::cout << "\n\n";
}

// Función auxiliar para generar las listas de prueba frescas cada vez
// Esto es vital porque las funciones de fusión modifican los punteros originales
std::vector<ListNode*> createTestLists() {
    ListNode* l1 = new ListNode(1, new ListNode(4, new ListNode(5)));
    ListNode* l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
    ListNode* l3 = new ListNode(2, new ListNode(6));
    return {l1, l2, l3};
}

int main() {
    Solution sol;
    std::cout << "=================================================\n";
    std::cout << "   TEST: MERGE K SORTED LISTS (COMPLEJIDADES)    \n";
    std::cout << "=================================================\n\n";

    // Prueba 1: Min-Heap (La solución principal)
    std::cout << "[Enfoque 1] Min-Heap O(N log k):\n";
    std::vector<ListNode*> lists1 = createTestLists();
    ListNode* result1 = sol.mergeKLists(lists1);
    std::cout << "Resultado: ";
    printList(result1);

    // Prueba 2: Fuerza Bruta (Ordenar todo al final)
    std::cout << "[Enfoque 2] Fuerza Bruta Sort O(N log N):\n";
    std::vector<ListNode*> lists2 = createTestLists();
    ListNode* result2 = sol.mergeKListsBruteForceSort(lists2);
    std::cout << "Resultado: ";
    printList(result2);

    // Prueba 3: Fusión Secuencial
    std::cout << "[Enfoque 3] Fusion Secuencial O(N * k):\n";
    std::vector<ListNode*> lists3 = createTestLists();
    ListNode* result3 = sol.mergeKListsSequential(lists3);
    std::cout << "Resultado: ";
    printList(result3);

    
    return 0;
}