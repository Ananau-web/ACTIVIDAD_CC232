#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include "MergeKLists.h"

// Función para simular el "delay" de un visualizador animado
void pausar(int milisegundos) {
    Sleep(milisegundos);
}

// Función auxiliar para imprimir con etiquetas
void printVisual(ListNode* head, std::string etiqueta) {
    std::cout << "  " << etiqueta << ": ";
    if (!head) {
        std::cout << "[Vacio]\n";
        return;
    }
    while (head) {
        std::cout << "[" << head->val << "]" << (head->next ? " -> " : "");
        head = head->next;
    }
    std::cout << "\n";
}

// Visualizador paso a paso de la lógica central (Fusión de dos listas)
ListNode* visualizadorMergePasoAPaso(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;

    std::cout << "=== INICIANDO VISUALIZADOR DE PUNTEROS ===\n\n";
    pausar(1000);

    int paso = 1;
    while (l1 && l2) {
        std::cout << "-------------------------------------------------\n";
        std::cout << "PASO " << paso++ << ":\n";
        printVisual(l1, "Lista 1 actual");
        printVisual(l2, "Lista 2 actual");
        std::cout << "  -> Comparamos las cabezas: [" << l1->val << "] vs [" << l2->val << "]\n";
        
        pausar(2000); // Tiempo para absorber la comparación

        if (l1->val < l2->val) {
            std::cout << "  => [" << l1->val << "] es menor. Se extrae de Lista 1.\n";
            tail->next = l1;
            l1 = l1->next;
        } else {
            std::cout << "  => [" << l2->val << "] es menor. Se extrae de Lista 2.\n";
            tail->next = l2;
            l2 = l2->next;
        }
        
        tail = tail->next;
        
        // Desconectamos temporalmente para imprimir el progreso de la nueva lista
        ListNode* temp = tail->next;
        tail->next = nullptr;
        std::cout << "\n";
        printVisual(dummy.next, "NUEVA LISTA   ");
        tail->next = temp; // Reconectamos
        
        std::cout << "-------------------------------------------------\n\n";
        pausar(2500); // Tiempo para absorber el paso
    }

    std::cout << "=== FASE FINAL DE CONEXION ===\n";
    pausar(1000);
    if (l1) {
        std::cout << "  -> Lista 2 esta vacia. Anexamos el resto de Lista 1 de golpe.\n";
        tail->next = l1;
    } else {
        std::cout << "  -> Lista 1 esta vacia. Anexamos el resto de Lista 2 de golpe.\n";
        tail->next = l2;
    }
    
    pausar(1500);
    std::cout << "\n=================================================\n";
    printVisual(dummy.next, "RESULTADO FINAL");
    std::cout << "=================================================\n";

    return dummy.next;
}

int main() {
    std::cout << "\n=================================================================\n";
    std::cout << "          ALGO DEMO (VERSION CONSOLA): MERGE K LISTS             \n";
    std::cout << "=================================================================\n\n";

    // Creamos dos listas preparadas para la demostración visual
    ListNode* l1 = new ListNode(1, new ListNode(4, new ListNode(5)));
    ListNode* l2 = new ListNode(2, new ListNode(3, new ListNode(6)));

    // Ejecutamos la animación
    visualizadorMergePasoAPaso(l1, l2);

    return 0;
}