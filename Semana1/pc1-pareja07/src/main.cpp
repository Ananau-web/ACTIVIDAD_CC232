#include "solution.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <chrono> 

int main() {
    Solution sol;

    // ====================================================================
    // PARTE 1: PRUEBA DE CORRECTITUD (Caso clásico de LeetCode)
    // ====================================================================
    std::cout << "====================================================\n";
    std::cout << "  PARTE 1: PRUEBA DE CORRECTITUD (N = 9) \n";
    std::cout << "====================================================\n";
    
    std::vector<int> nums_small = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << "Arreglo original: { ";
    for (int num : nums_small) {
        std::cout << num << " ";
    }
    std::cout << "}\n\n";

    int resKadaneSmall = sol.maxSubArrayKadane(nums_small);
    int resDivideSmall = sol.maxSubArrayDivideAndConquer(nums_small);
    
    std::cout << "[Metodo 1] Kadane            -> Resultado = " << resKadaneSmall << "\n";
    std::cout << "[Metodo 2] Divide y Venceras -> Resultado = " << resDivideSmall << "\n";
    
    if (resKadaneSmall == resDivideSmall) {
        std::cout << "-> ¡Exito! Ambos algoritmos coinciden en el caso base.\n\n";
    }

    // ====================================================================
    // PARTE 2: PRUEBA DE RENDIMIENTO (Carga masiva con Cronometro)
    // ====================================================================
    std::cout << "====================================================\n";
    std::cout << "  PARTE 2: PRUEBA DE RENDIMIENTO (N = 1,000,000) \n";
    std::cout << "====================================================\n";
    
    const int N = 1000000; // 1 millon de elementos
    std::vector<int> nums_large;
    nums_large.reserve(N); 

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1000, 1000);

    for (int i = 0; i < N; ++i) {
        nums_large.push_back(dis(gen));
    }

    std::cout << "Procesando un arreglo masivo de 1,000,000 elementos...\n\n";

    // --- Medir Kadane ---
    auto start_kadane = std::chrono::high_resolution_clock::now();
    int resKadaneLarge = sol.maxSubArrayKadane(nums_large);
    auto end_kadane = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_kadane = end_kadane - start_kadane;

    // --- Medir Divide y Vencerás ---
    auto start_divide = std::chrono::high_resolution_clock::now();
    int resDivideLarge = sol.maxSubArrayDivideAndConquer(nums_large);
    auto end_divide = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_divide = end_divide - start_divide;
    
    // --- Resultados ---
    std::cout << "[Metodo 1] Kadane (O(N)) tardo:            " << time_kadane.count() << " ms\n";
    std::cout << "[Metodo 2] Divide y Venceras (O(N log N)) tardo: " << time_divide.count() << " ms\n";
    
    if (resKadaneLarge == resDivideLarge) {
        std::cout << "\n-> ¡Exito! Ambos algoritmos coinciden bajo carga extrema.\n\n";
    }

    return 0;
}