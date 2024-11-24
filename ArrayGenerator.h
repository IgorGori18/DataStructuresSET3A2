#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

class ArrayGenerator {
  std::mt19937 rng;

 public:
  ArrayGenerator() : rng(std::random_device{}()) {}

  std::vector<int> generateRandom(size_t size, int minVal, int maxVal) {
    std::uniform_int_distribution<int> dist(minVal, maxVal);
    std::vector<int> arr(size);
    std::generate(arr.begin(), arr.end(), [&]() { return dist(rng); });
    return arr;
  }

  std::vector<int> generateReverseOrdered(size_t size) {
    std::vector<int> arr(size);
    std::iota(arr.begin(), arr.end(), 1);
    std::reverse(arr.begin(), arr.end());
    return arr;
  }

  std::vector<int> generateNearlySorted(size_t size, int swaps = 50) {
    std::vector<int> arr(size);
    std::iota(arr.begin(), arr.end(), 1);

    std::uniform_int_distribution<size_t> dist(0, size - 1);
    for (int i = 0; i < swaps; ++i) {
      std::swap(arr[dist(rng)], arr[dist(rng)]);
    }
    return arr;
  }
};