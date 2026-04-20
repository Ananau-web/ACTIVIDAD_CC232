#include "solution.hpp"
#include <algorithm>
#include <limits>

// ---------------------------------------------------------
// ENFOQUE 1: Algoritmo de Kadane (El Óptimo)
// Complejidad: Tiempo O(N), Espacio O(1)
// ---------------------------------------------------------
int Solution::maxSubArrayKadane(const std::vector<int>& nums) {
    int max_global = nums[0]; 
    int max_local = nums[0];  

    for (size_t i = 1; i < nums.size(); i++) {
        max_local = std::max(nums[i], max_local + nums[i]);
        if (max_local > max_global) {
            max_global = max_local;
        }
    }
    return max_global;
}

// ---------------------------------------------------------
// ENFOQUE 2: Divide y Vencerás (El Recursivo)
// Complejidad: Tiempo O(N log N), Espacio O(log N)
// ---------------------------------------------------------
int Solution::maxSubArrayDivideAndConquer(const std::vector<int>& nums) {
    return DivideyVenceras(nums, 0, nums.size() - 1);
}

// ---------------------------------------------------------
// Función principal requerida por LeetCode
// ---------------------------------------------------------
int Solution::maxSubArray(std::vector<int>& nums) {
    return maxSubArrayKadane(nums); 
}

// ---------------------------------------------------------
// Funciones Privadas auxiliares
// ---------------------------------------------------------
int Solution::DivideyVenceras(const std::vector<int>& nums, int left, int right) {
    if (left == right) return nums[left];

    int mid = left + (right - left) / 2;

    int left_sum = DivideyVenceras(nums, left, mid);
    int right_sum = DivideyVenceras(nums, mid + 1, right);
    int cross_sum = maxCrossingSum(nums, left, mid, right);

    return std::max({left_sum, right_sum, cross_sum});
}

int Solution::maxCrossingSum(const std::vector<int>& nums, int left, int mid, int right) {
    int sum = 0;
    int left_part = std::numeric_limits<int>::lowest();
    for (int i = mid; i >= left; i--) {
        sum += nums[i];
        if (sum > left_part) left_part = sum;
    }

    sum = 0;
    int right_part = std::numeric_limits<int>::lowest();
    for (int i = mid + 1; i <= right; i++) {
        sum += nums[i];
        if (sum > right_part) right_part = sum;
    }

    return left_part + right_part;
}