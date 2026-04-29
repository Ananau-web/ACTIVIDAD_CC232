#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct CompareNode {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val; 
    }
};

class Solution {
public:
    // =====================================================================
    // 1. ENFOQUE MALO 1: Fuerza Bruta - O(N log N)
    // Extrae todos los valores, los ordena desde cero y crea una nueva lista.
    // =====================================================================
    ListNode* mergeKListsBruteForceSort(std::vector<ListNode*>& lists) {
        std::vector<int> allValues;
        for (ListNode* head : lists) {
            while (head != nullptr) {
                allValues.push_back(head->val);
                head = head->next;
            }
        }
        std::sort(allValues.begin(), allValues.end()); // O(N log N)
        
        ListNode nodoCentinela(0);
        ListNode* tail = &nodoCentinela;
        for (int val : allValues) {
            tail->next = new ListNode(val);
            tail = tail->next;
        }
        return nodoCentinela.next;
    }

    // =====================================================================
    // 2. ENFOQUE MALO 2: Fusión Secuencial - O(N * k)
    // Fusiona la lista 1 con la 2, luego el resultado con la 3, etc.
    // =====================================================================
    ListNode* mergeKListsSequential(std::vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        ListNode* result = lists[0];
        for (int i = 1; i < lists.size(); i++) {
            result = mergeTwoLists(result, lists[i]); // Reutiliza mergeTwoLists
        }
        return result;
    }

    // =====================================================================
    // 3. ENFOQUE ÓPTIMO 1: Min-Heap - O(N log k) 
    // =====================================================================
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        std::priority_queue<ListNode*, std::vector<ListNode*>, CompareNode> minHeap;
        for (ListNode* listHead : lists) {
            if (listHead != nullptr) minHeap.push(listHead);
        }
        
        ListNode nodoCentinela(0);
        ListNode* tail = &nodoCentinela;
        
        while (!minHeap.empty()) {
            ListNode* minNode = minHeap.top();
            minHeap.pop();
            
            tail->next = minNode;
            tail = tail->next;
            
            if (minNode->next != nullptr) minHeap.push(minNode->next);
        }
        return nodoCentinela.next;
    }

    // =====================================================================
    // 4. ENFOQUE ÓPTIMO 2: Divide and Conquer - O(N log k) 
    // =====================================================================
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode nodoCentinela(0);
        ListNode* tail = &nodoCentinela;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1; l1 = l1->next;
            } else {
                tail->next = l2; l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;
        return nodoCentinela.next;
    }

    ListNode* mergeKListsDivideAndConquer(std::vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        int step = 1;
        while (step < lists.size()) {
            for (int i = 0; i + step < lists.size(); i += step * 2) {
                lists[i] = mergeTwoLists(lists[i], lists[i + step]);
            }
            step *= 2;
        }
        return lists[0];
    }
};