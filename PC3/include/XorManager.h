#pragma once

#include <unordered_map>
#include <string>
#include "Treap.h"      // Librería de la Semana 6
#include "LazyHeap.h"   // Tu Min-Heap personalizado

class XorManager {
private:
    ods::Treap<long long> treap;
    LazyHeap* minXorHeap;
    std::unordered_map<long long, int> freq; // CRÍTICO: El mapa para duplicados
    bool debug_mode;

    // CRÍTICO: Declaración de los métodos auxiliares que usas en el .cpp
    bool getPredecessor(long long x, long long& result) const;
    bool getSuccessor(long long x, long long& result) const;

public:
    XorManager(bool debug = false);
    ~XorManager();

    void insert(long long val);
    void erase(long long val);
    long long getMinXor();
    
    void printTrace(const std::string& action, long long val, long long pred, long long succ) const;
    void setDebugMode(bool mode) { debug_mode = mode; }
};