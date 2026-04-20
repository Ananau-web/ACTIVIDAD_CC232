#include <iostream>
#include <vector>
#include <chrono>
#include <random>



// --- EXPERIMENTO STL: reserve() vs sin reserve() ---
void benchmarkReserve(int N) {
    std::cout << "\n--- EXPERIMENTO STL: push_back con vs sin reserve() ---\n";
    std::cout << "Insertando " << N << " elementos...\n";

    // Prueba SIN reserve
    auto start_no_res = std::chrono::high_resolution_clock::now();
    std::vector<int> vec_no_res;
    for (int i = 0; i < N; ++i) {
        vec_no_res.push_back(i);
    }
    auto end_no_res = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_no_res = end_no_res - start_no_res;

    // Prueba CON reserve
    auto start_res = std::chrono::high_resolution_clock::now();
    std::vector<int> vec_res;
    vec_res.reserve(N); // ¡La magia ocurre aquí!
    for (int i = 0; i < N; ++i) {
        vec_res.push_back(i);
    }
    auto end_res = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_res = end_res - start_res;

    std::cout << "Tiempo SIN reserve: " << time_no_res.count() << " ms\n";
    std::cout << "Tiempo CON reserve: " << time_res.count() << " ms\n";
    std::cout << "Mejora: " << time_no_res.count() / time_res.count() << "x mas rapido.\n";
}

int main() {
    // 1. Configurar el tamaño de la prueba (N grande para ver la diferencia)
    const int N = 10000000; // 10 millones de elementos

    // 2. Ejecutar el experimento complementario de la STL
    benchmarkReserve(N);

    // 3. (Aquí iría el benchmark de su problema principal: Kadane vs Divide y Vencerás)
    // ...

    return 0;
}