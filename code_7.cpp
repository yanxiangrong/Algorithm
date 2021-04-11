//
// Created by yan on 2021/3/12.
// 快速排序

#include <iostream>
#include <random>
#include <ctime>

void exchange(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

int partition(int *array, int p, int r) {
    int x = array[r];
    int i = p;
    for (int j = p; j < r; ++j) {
        if (array[j] <= x) {
            exchange(array[i], array[j]);
            i++;
        }
    }
    exchange(array[i], array[r]);
    return i;
}

void quickSort(int *array, int p, int r) {
    if (p < r) {
        int q = partition(array, p, r);
        quickSort(array, p, q - 1);
        quickSort(array, q + 1, r);
    }
}

void quickSort(int *array, int length) {
    quickSort(array, 0, length - 1);
}

void test() {
    std::mt19937 mt(std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, 100);
    const int SIZE = 15;
    int array[SIZE];
    for (int &i : array) {
        i = dist(mt);
    }
    printf("Array: \n");
    for (int &i : array) {
        printf("%d\t", i);
    }
    printf("\n");
    quickSort(array, SIZE);
    printf("Sorted: \n");
    for (int &i : array) {
        printf("%d\t", i);
    }
}

int main() {
    test();
    return 0;
}