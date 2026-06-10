#include "XorManager.h"
#include <iostream>

XorManager::XorManager(bool debug) : debug_mode(debug), minXorHeap(new LazyHeap()) {}

XorManager::~XorManager() {
    delete minXorHeap;
}

// Encuentra el número más grande que sea menor que x
// Necesitamos esto para calcular XOR con vecinos cuando insertas/eliminas
// El treap mantiene inorden, así que buscamos como en BST normal
bool XorManager::getPredecessor(long long x, long long& result) const {
    ods::Treap<long long>::Node* current = treap.root();
    ods::Treap<long long>::Node* pred = nullptr;
    
    while (current != nullptr) {
        if (current->key < x) {
            pred = current; // Candidato: seguimos a la derecha por si hay algo mayor
            current = current->right;
        } else {
            current = current->left; // Demasiado grande, vamos izquierda
        }
    }
    
    if (pred) {
        result = pred->key;
        return true;
    }
    return false;
}

// El siguiente número (el más pequeño mayor que x)
// También lo necesitamos para mantener las parejas XOR actualizadas
bool XorManager::getSuccessor(long long x, long long& result) const {
    ods::Treap<long long>::Node* succ = treap.upperBound(x);
    if (succ) {
        result = succ->key;
        return true;
    }
    return false;
}

void XorManager::insert(long long val) {
    // Si ya existe el valor, solo incrementamos el contador
    // (No queremos duplicados en el treap, pero sí rastreamos frecuencia)
    if (freq[val] > 0) {
        freq[val]++;
        minXorHeap->push(0); // val ^ val siempre es 0, así que agregamos ese al heap
        if (debug_mode) std::cout << "Duplicado detectado: " << val << ". Insertando XOR 0 al heap.\n";
        return;
    }
    freq[val] = 1;

    // Buscamos los vecinos ANTES de insertar, porque después ya estarían dentro del treap
    long long pred, succ;
    bool has_pred = getPredecessor(val, pred);
    bool has_succ = getSuccessor(val, succ);

    if (debug_mode) printTrace("Insertando", val, has_pred ? pred : -1, has_succ ? succ : -1);

    // Si existe tanto predec como sucesor, la pareja actual (pred,succ) desaparece del heap
    if (has_pred && has_succ) {
        minXorHeap->markAsObsolete(pred ^ succ);
    }

    // Ahora creamos dos parejas nuevas: (pred, val) y (val, succ)
    if (has_pred) minXorHeap->push(pred ^ val);
    if (has_succ) minXorHeap->push(val ^ succ);

    // Insertar en el treap (ya ordenado para futuras búsquedas de vecinos)
    treap.add(val);
}

void XorManager::erase(long long val) {
    if (freq[val] == 0) return; // No existe, nada que hacer

    // Si hay duplicados, solo descontamos
    // (El treap ya no lo tiene, pero el heap tiene el 0 registrado)
    if (freq[val] > 1) {
        freq[val]--;
        minXorHeap->markAsObsolete(0); // Quitamos uno de los ceros
        return;
    }
    freq[val] = 0;

    // Buscamos los vecinos para poder reconectarlos después de que se vaya val
    long long pred, succ;
    bool has_pred = getPredecessor(val, pred);
    bool has_succ = getSuccessor(val, succ);

    if (debug_mode) printTrace("Eliminando", val, has_pred ? pred : -1, has_succ ? succ : -1);

    // Quitamos las dos parejas en las que val participaba
    if (has_pred) minXorHeap->markAsObsolete(pred ^ val);
    if (has_succ) minXorHeap->markAsObsolete(val ^ succ);

    // Restauramos la conexión directa entre los vecinos (si existen ambos)
    if (has_pred && has_succ) {
        minXorHeap->push(pred ^ succ);
    }

    // Finalmente, sacamos val del treap
    treap.remove(val);
}

// Retorna el XOR mínimo posible entre cualquier pareja de elementos insertados
// El heap maneja la lazy deletion (marcados obsoletos pero aún en la estructura)
// así que simplemente sacamos hasta encontrar uno válido
long long XorManager::getMinXor() {
    return minXorHeap->getMin();
}

void XorManager::printTrace(const std::string& action, long long val, long long pred, long long succ) const {
    std::cout << action << " valor: " << val << " | Vecinos -> Pred: ";
    if (pred != -1) std::cout << pred; else std::cout << "Ninguno";
    std::cout << ", Succ: ";
    if (succ != -1) std::cout << succ; else std::cout << "Ninguno";
    std::cout << "\n";
}