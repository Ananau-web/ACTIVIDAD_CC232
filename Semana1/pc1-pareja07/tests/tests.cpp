#include "solution.hpp"
#include <iostream>
#include <vector>
#include <cassert>


// ---------------------------------------------------------
// PRUEBAS UNITARIAS: Maximum Subarray
// ---------------------------------------------------------

void test_caso_normal() {
    Solution sol;
    std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    assert(sol.maxSubArrayKadane(nums) == 6);
    assert(sol.maxSubArrayDivideAndConquer(nums) == 6);
    std::cout << "[OK] test_caso_normal pasado.\n";
}

void test_todos_negativos() {
    Solution sol;
    std::vector<int> nums = {-5, -2, -9, -1, -7};
    assert(sol.maxSubArrayKadane(nums) == -1);
    assert(sol.maxSubArrayDivideAndConquer(nums) == -1);
    std::cout << "[OK] test_todos_negativos pasado.\n";
}

void test_un_solo_elemento() {
    Solution sol;
    std::vector<int> nums = {5};
    assert(sol.maxSubArrayKadane(nums) == 5);
    assert(sol.maxSubArrayDivideAndConquer(nums) == 5);
    std::cout << "[OK] test_un_solo_elemento pasado.\n";
}

void test_disenado_por_la_pareja() {
    Solution sol;
    std::vector<int> nums = {100, -50, 100, -200, 500};
    assert(sol.maxSubArrayKadane(nums) == 500);
    assert(sol.maxSubArrayDivideAndConquer(nums) == 500);
    std::cout << "[OK] test_disenado_por_la_pareja pasado.\n";
}

int main() {
    std::cout << "--- INICIANDO BATERIA DE PRUEBAS ---\n";
    test_caso_normal();
    test_todos_negativos();
    test_un_solo_elemento();
    test_disenado_por_la_pareja();
    std::cout << "--- TODAS LAS PRUEBAS PASARON EXITOSAMENTE ---\n";
    return 0;
}