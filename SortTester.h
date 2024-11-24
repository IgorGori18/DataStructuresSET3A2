#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
#include <string>
#include <numeric>

class SortTester {
 public:
  // Метод для замера времени выполнения
  long long measureTime(std::function<void(std::vector<int>&, int, int)> sortFunc, std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr, 0, arr.size() - 1);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
  }

  // Метод для усредненных замеров
  long long averageTime(std::function<void(std::vector<int>&, int, int)> sortFunc, std::vector<int>& arr, int runs) {
    long long total = 0;
    for (int i = 0; i < runs; ++i) {
      std::vector<int> temp = arr;  // Копия массива для каждого запуска
      total += measureTime(sortFunc, temp);
    }
    return total / runs;
  }
};