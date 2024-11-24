#include <iostream>
#include <vector>
#include "ArrayGenerator.h"
#include "sortTester.h"


void insertionSort(std::vector<int>& arr, int left, int right) {
  for (int i = left + 1; i <= right; i++) {
    int key = arr[i];
    int j = i - 1;
    while (j >= left && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

void merge(std::vector<int>& arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  std::vector<int> L(n1), R(n2);
  for (int i = 0; i < n1; i++) L[i] = arr[left + i];
  for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) arr[k++] = L[i++];
    else arr[k++] = R[j++];
  }

  while (i < n1) arr[k++] = L[i++];
  while (j < n2) arr[k++] = R[j++];
}

void mergeInsertionSort(std::vector<int>& arr, int left, int right, int threshold) {
  if (left >= right) return;

  if (right - left + 1 <= threshold) {
    insertionSort(arr, left, right);
  } else {
    int mid = left + (right - left) / 2;
    mergeInsertionSort(arr, left, mid, threshold);
    mergeInsertionSort(arr, mid + 1, right, threshold);
    merge(arr, left, mid, right);
  }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
  if (left >= right) return;

  int mid = left + (right - left) / 2;
  mergeSort(arr, left, mid);
  mergeSort(arr, mid + 1, right);
  merge(arr, left, mid, right);
}

void hybridSort(std::vector<int>& arr, int left, int right, int threshold) {
  mergeInsertionSort(arr, left, right, threshold);
}


int main() {
  const int size = 10000;  // Размер массивов
  const int minValue = 0, maxValue = 10000;
  const int runs = 5;      // Количество повторов для усреднения
  const std::vector<int> thresholds = {5, 10, 20, 30, 50};  // Значения threshold

  ArrayGenerator generator;
  SortTester tester;

  // Генерация массивов
  std::vector<int> randomArray = generator.generateRandom(size, minValue, maxValue);
  std::vector<int> reverseArray = generator.generateReverseOrdered(size);
  std::vector<int> nearlySortedArray = generator.generateNearlySorted(size);

  // Тестирование стандартного Merge Sort
  std::cout << "Testing Standard Merge Sort:\n";
  std::cout << "Random Array: " << tester.averageTime(mergeSort, randomArray, runs) << " ms\n";
  std::cout << "Reverse Array: " << tester.averageTime(mergeSort, reverseArray, runs) << " ms\n";
  std::cout << "Nearly Sorted Array: " << tester.averageTime(mergeSort, nearlySortedArray, runs) << " ms\n";

  // Тестирование гибридного Merge Sort
  std::cout << "\nTesting Hybrid Merge + Insertion Sort:\n";
  for (int threshold : thresholds) {
    auto hybridSortWrapper = [threshold](std::vector<int>& arr, int left, int right) {
      hybridSort(arr, left, right, threshold);
    };

    std::cout << "Threshold = " << threshold << "\n";
    std::cout << "Random Array: " << tester.averageTime(hybridSortWrapper, randomArray, runs) << " ms\n";
    std::cout << "Reverse Array: " << tester.averageTime(hybridSortWrapper, reverseArray, runs) << " ms\n";
    std::cout << "Nearly Sorted Array: " << tester.averageTime(hybridSortWrapper, nearlySortedArray, runs) << " ms\n";
  }

  return 0;
}