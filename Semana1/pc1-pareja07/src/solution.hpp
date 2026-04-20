#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>

class Solution {
public:
    // ENFOQUE 1: Algoritmo de Kadane (El Óptimo)
    int maxSubArrayKadane(const std::vector<int>& nums);

    // ENFOQUE 2: Divide y Vencerás (El Recursivo)
    int maxSubArrayDivideAndConquer(const std::vector<int>& nums);

    // Función principal requerida por LeetCode
    int maxSubArray(std::vector<int>& nums);

private:
    int DivideyVenceras(const std::vector<int>& nums, int left, int right);
    int maxCrossingSum(const std::vector<int>& nums, int left, int mid, int right);
};

#endif // SOLUTION_HPP