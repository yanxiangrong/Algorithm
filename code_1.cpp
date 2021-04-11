//
// Created by yan on 2021/3/10.
// 归并排序，及使用插入排序优化

#include <iostream>
#include <random>
#include <ctime>

#define INF 0x7FFFFFFF

void insertionSort(int *array, int p, int r) {
    for (int i = p + 1; i < r; ++i) {
        int key = array[i];
        int j = i - 1;
        while (j >= p and array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void merge(int *array, int p, int q, int r) {
    int n1 = q - p;
    int n2 = r - q;
    int left[n1 + 1];
    int right[n2 + 1];
    for (int i = 0; i < n1; ++i) {
        left[i] = array[p + i];
    }
    for (int j = 0; j < n2; ++j) {
        right[j] = array[q + j];
    }
    left[n1] = INF;
    right[n2] = INF;
    int i = 0, j = 0;
    for (int k = p; k < r; ++k) {
        if (left[i] <= right[j]) {
            array[k] = left[i];
            i++;
        } else {
            array[k] = right[j];
            j++;
        }
    }
}

void mergeSort(int *array, int p, int r) {
    if (p < r - 1) {
        int q = (p + r) / 2;
        mergeSort(array, p, q);
        mergeSort(array, q, r);
        merge(array, p, q, r);
    }
}

void mergeSortPlus(int *array, int p, int r) {
    int d = r - p;
    if (d > 1) {
        if (d <= 10) { // 在网上查询得 10 效率最高
            insertionSort(array, p, r);
        } else {
            int q = (p + r) / 2;
            mergeSort(array, p, q);
            mergeSort(array, q, r);
            merge(array, p, q, r);
        }
    }
}

int main() {
//    std::random_device rd;
//    std::mt19937 mt(rd());
    std::mt19937 mt(std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, 100);
    const int SIZE = 20;
    int array[SIZE];
    for (int &i : array) {
        i = dist(mt);
    }
    printf("INF: %d\n", INF);
    printf("Array: \n");
    for (int &i : array) {
        printf("\t%d ", i);
    }
    mergeSort(array, 0, SIZE);
//    insertionSort(array, 0, SIZE);
//    mergeSortPlus(array, 0, SIZE);
    printf("\n");
    printf("Sorted: \n");
    for (int &i : array) {
        printf("\t%d ", i);
    }
    return 0;
}
