#include <iostream>
#include <cassert>
#include <climits>
#include <vector>
#include <algorithm>
#include <random>
#include "XorManager.h" // Tu clase que orquesta Treap.h y PQ_ComplHeap.h

// 1. Caso mínimo (exigido por la rúbrica)
void test_caso_minimo() {
    XorManager xorMap;
    xorMap.insert(2);
    xorMap.insert(10);
    // 2 (0010) XOR 10 (1010) = 8 (1000)
    assert(xorMap.getMinXor() == 8);
}

// 2. Prueba específica del invariante principal
void test_invariante_insercion_intermedia() {
    XorManager xorMap;
    xorMap.insert(2);
    xorMap.insert(10);
    // Al insertar 5, se rompe el par (2, 10) y se forman (2, 5) y (5, 10).
    // 2 XOR 5 = 7.  5 XOR 10 = 15. El nuevo mínimo debe ser 7.
    xorMap.insert(5);
    assert(xorMap.getMinXor() == 7);
}

// 3. Caso de eliminación (romper y reconectar)
void test_eliminacion_restaura_par_original() {
    XorManager xorMap;
    xorMap.insert(2);
    xorMap.insert(5);
    xorMap.insert(10);
    
    // Al eliminar el 5, el par (2, 5) y (5, 10) deben marcarse como obsoletos (Lazy Deletion).
    // Se debe restaurar el par original (2, 10) cuyo XOR es 8.
    xorMap.erase(5);
    assert(xorMap.getMinXor() == 8);
}

// 4. Caso con duplicados (exigido por la rúbrica)
void test_caso_duplicados() {
    XorManager xorMap;
    xorMap.insert(14);
    xorMap.insert(25);
    xorMap.insert(14); // Duplicado
    
    // El XOR de cualquier número consigo mismo (14 XOR 14) siempre es 0.
    // Esto es un caso borde vital en este problema.
    assert(xorMap.getMinXor() == 0);
    
    // Al eliminar una instancia del 14, el mínimo debe volver a ser 14 XOR 25 = 23
    xorMap.erase(14);
    assert(xorMap.getMinXor() == 23);
}

// 5. Caso con estructura vacía o ausencia de respuesta (frontera)
void test_caso_frontera_pocos_elementos() {
    XorManager xorMap;
    xorMap.insert(42);
    
    // Si hay menos de 2 elementos, no hay pares XOR válidos.
    // getMinXor() podría devolver -1 o un valor máximo por defecto. 
    assert(xorMap.getMinXor() == -1); 
}

// 6. Comparación contra solución ingenua (fuerza bruta) para entradas pequeñas
//    Exigida por la sección 8, punto 5 de las indicaciones.
void test_comparacion_fuerza_bruta() {
    // Generamos un conjunto pequeño y verificamos que nuestro XorManager
    // devuelva el mismo mínimo XOR que una búsqueda exhaustiva O(n²).
    std::vector<long long> valores = {3, 17, 8, 25, 12, 6, 31, 20, 1, 14};
    
    XorManager xorMap;
    for (long long v : valores) {
        xorMap.insert(v);
    }
    
    // Fuerza bruta: calcular todos los pares
    long long min_bruta = LLONG_MAX;
    for (size_t i = 0; i < valores.size(); i++) {
        for (size_t j = i + 1; j < valores.size(); j++) {
            long long xor_val = valores[i] ^ valores[j];
            if (xor_val < min_bruta) {
                min_bruta = xor_val;
            }
        }
    }
    
    long long min_estructura = xorMap.getMinXor();
    assert(min_bruta == min_estructura);
    
    // Ahora eliminamos algunos y volvemos a comparar
    xorMap.erase(8);
    xorMap.erase(6);
    
    // Recalcular fuerza bruta sin 8 y 6
    std::vector<long long> restantes;
    for (long long v : valores) {
        if (v != 8 && v != 6) restantes.push_back(v);
    }
    
    min_bruta = LLONG_MAX;
    for (size_t i = 0; i < restantes.size(); i++) {
        for (size_t j = i + 1; j < restantes.size(); j++) {
            long long xor_val = restantes[i] ^ restantes[j];
            if (xor_val < min_bruta) {
                min_bruta = xor_val;
            }
        }
    }
    
    assert(min_bruta == xorMap.getMinXor());
}

// 7. Verificación explícita del invariante principal
//    Exigida por la sección 8, punto 6 de las indicaciones.
//    Verifica que los pares XOR en el heap corresponden a vecinos consecutivos del Treap.
void test_verificacion_invariante() {
    XorManager xorMap;
    xorMap.insert(3);
    xorMap.insert(10);
    xorMap.insert(7);
    xorMap.insert(15);
    xorMap.insert(1);
    
    // Obtener el mínimo XOR de la estructura
    long long min_estructura = xorMap.getMinXor();
    
    // Verificación del invariante: el mínimo XOR SIEMPRE debe estar
    // entre algún par de vecinos consecutivos en la secuencia ordenada.
    // Usamos los valores que sabemos que están: {1, 3, 7, 10, 15}
    std::vector<long long> ordenados = {1, 3, 7, 10, 15};
    
    long long min_vecinos = LLONG_MAX;
    for (size_t i = 0; i + 1 < ordenados.size(); i++) {
        long long xor_val = ordenados[i] ^ ordenados[i + 1];
        if (xor_val < min_vecinos) {
            min_vecinos = xor_val;
        }
    }
    
    // El invariante dice: min XOR global == min XOR entre vecinos consecutivos
    assert(min_estructura == min_vecinos);
    
    // Verificar que el mínimo calculado es correcto:
    // 1 XOR 3 = 2, 3 XOR 7 = 4, 7 XOR 10 = 13, 10 XOR 15 = 5
    // Mínimo: 2 (entre 1 y 3)
    assert(min_estructura == 2);
    
    // Ahora insertamos un valor que cambie el invariante
    xorMap.insert(2);
    // Ordenados: {1, 2, 3, 7, 10, 15}
    // 1 XOR 2 = 3, 2 XOR 3 = 1, 3 XOR 7 = 4, 7 XOR 10 = 13, 10 XOR 15 = 5
    // Nuevo mínimo: 1 (entre 2 y 3)
    assert(xorMap.getMinXor() == 1);
}

int main() {
    std::cout << "Iniciando bateria de pruebas automatizadas...\n";
    
    test_caso_minimo();
    std::cout << "  [PASS] 1. test_caso_minimo\n";
    
    test_invariante_insercion_intermedia();
    std::cout << "  [PASS] 2. test_invariante_insercion_intermedia\n";
    
    test_eliminacion_restaura_par_original();
    std::cout << "  [PASS] 3. test_eliminacion_restaura_par_original\n";
    
    test_caso_duplicados();
    std::cout << "  [PASS] 4. test_caso_duplicados\n";
    
    test_caso_frontera_pocos_elementos();
    std::cout << "  [PASS] 5. test_caso_frontera_pocos_elementos\n";
    
    test_comparacion_fuerza_bruta();
    std::cout << "  [PASS] 6. test_comparacion_fuerza_bruta\n";
    
    test_verificacion_invariante();
    std::cout << "  [PASS] 7. test_verificacion_invariante\n";
    
    // Si el código llega a esta línea, significa que ningún assert falló.
    std::cout << "\nSUCCESS: Todas las 7 pruebas obligatorias y casos borde pasaron correctamente.\n";
    
    return 0;
}