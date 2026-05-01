#pragma once
#include <vector>
#include <queue>
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 // max_heap 
// Criterio de extracción mínima (Pregunta de rúbrica)
struct CompareNode {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val; 
    }
};
// functor(objeto que actua como funcion )

class Solution {
public:
    // =====================================================================
    // 1. ENFOQUE BÁSICO: Fusión Secuencial - O(N * k)
    // Nos sirve como punto de comparación para explicar por qué el Heap es mejor
    // =====================================================================
    ListNode* mergeKListsSequential(std::vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        ListNode* result = lists[0];
        for (int i = 1; i < lists.size(); i++) {
            result = mergeTwoLists(result, lists[i]); 
        }
        return result;
    }

    // =====================================================================
    // 2. ENFOQUE ÓPTIMO PRINCIPAL: Min-Heap - O(N log k) 
    // =====================================================================
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        std::priority_queue<ListNode*, std::vector<ListNode*>, CompareNode> minHeap;
        
        // 1. ¿Qué guardas en el heap? -> Punteros a los nodos cabeza
        for (ListNode* listHead : lists) {
            if (listHead != nullptr) minHeap.push(listHead);
        }

        ListNode dummy(0);
        ListNode* tail = &dummy;
        
        while (!minHeap.empty()) {
            ListNode* minNode = minHeap.top(); // Extrae el mínimo
            minHeap.pop();
            
            tail->next = minNode;
            tail = tail->next;
            
            if (minNode->next != nullptr) minHeap.push(minNode->next);
        }
        return dummy.next;
    }

    // =====================================================================
    // 3. Divide and Conquer usando ADT Cola (Queue) O(N* log k)
    // =====================================================================
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0); // Nodo centinela
        ListNode* tail = &dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1; l1 = l1->next;
            } else {
                tail->next = l2; l2 = l2->next;
            }
            tail = tail->next; 
        }
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }

    ListNode* mergeKListsDivideAndConquerQueue(std::vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        
        std::queue<ListNode*> q;
        for (ListNode* list : lists) {
            if (list) q.push(list);
        }
        
        if (q.empty()) return nullptr;
       
        while (q.size() > 1) {
            ListNode* l1 = q.front(); q.pop();
            ListNode* l2 = q.front(); q.pop();
            
            // Explicación de reutilización: Se recicla mergeTwoLists
            ListNode* merged = mergeTwoLists(l1, l2);
            q.push(merged);
        }
        
        return q.front();
    }
};