#include <iostream>
#include <vector>
#include "MergeKLists.h"

// Función auxiliar para imprimir la lista con formato visual
void printList(ListNode* head) {
    while (head) {
        std::cout << "[" << head->val << "]" << (head->next ? " -> " : "");
        head = head->next;
    }
    std::cout << "\n\n";
}

// Función auxiliar para generar las listas de prueba frescas cada vez
std::vector<ListNode*> createTestLists() {
    ListNode* l1 = new ListNode(1, new ListNode(4, new ListNode(5)));
    ListNode* l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
    ListNode* l3 = new ListNode(2, new ListNode(6));
    return {l1, l2, l3};
}


int main() {
    Solution sol;
    std::cout << "=================================================\n";
    std::cout << "   TEST: MERGE K SORTED LISTS    \n";
    std::cout << "=================================================\n\n";

    // ---------------------------------------------------------
    // Prueba 1: Min-Heap (La solución principal)
    // ---------------------------------------------------------
    std::cout << "[Enfoque 1] Min-Heap O(N log k) - (Uso de Adaptadores):\n";
    std::vector<ListNode*> lists1 = createTestLists();
    ListNode* result1 = sol.mergeKLists(lists1);
    std::cout << "Resultado: ";
    printList(result1);

    // ---------------------------------------------------------
    // Prueba 2: Fusión Secuencial
    // ---------------------------------------------------------
    std::cout << "[Enfoque 2] Fusion Secuencial O(N * k) - (Costo alto por enlaces):\n";
    std::vector<ListNode*> lists2 = createTestLists();
    ListNode* result2 = sol.mergeKListsSequential(lists2);
    std::cout << "Resultado: ";
    printList(result2);
    
    /* ===================================================================
        3. RETO : Divide and Conquer usando ADT Cola (Queue)
        ===================================================================
    */
    
    std::cout << "[Enfoque 3] Divide and Conquer usando ADT Cola (Queue) O(N* log k) - (Reutilización de mergeTwoLists):\n";
    std::vector<ListNode*> lists3 = createTestLists();
    ListNode* result3 = sol.mergeKListsDivideAndConquerQueue(lists3);
    std::cout << "Resultado: ";
    printList(result3);
    
    


    std::cout << "Todas las pruebas finalizaron correctamente.\n";
    return 0;
}
    
    