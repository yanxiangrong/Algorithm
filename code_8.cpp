//
// Created by yan on 2021/3/12.
// 计数排序

#include <iostream>
#include <random>
#include <ctime>

void countingSort(const int *array, int *result, int length, int k) {
    int temp[k];
    for (int i = 0; i < k; ++i) {
        temp[i] = 0;
    }
    for (int i = 0; i < length; ++i) {
        temp[array[i]]++;
    }
    for (int i = 1; i < k; ++i) {
        temp[i] = temp[i] + temp[i - 1];
    }
    for (int i = length - 1; i >= 0; --i) {
        result[temp[array[i]] - 1] = array[i];
        temp[array[i]]--;
    }
}

void test() {
    const int MAX = 100;
    std::mt19937 mt(std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, MAX);
    const int SIZE = 15;
    int array[SIZE], result[SIZE];
    for (int &i : array) {
        i = dist(mt);
    }
    printf("Array: \n");
    for (int &i : array) {
        printf("%d\t", i);
    }
    printf("\n");
    countingSort(array, result, SIZE, MAX + 1);
    printf("Sorted: \n");
    for (int &i : result) {
        printf("%d\t", i);
    }
}

int main() {
    test();
    return 0;
}