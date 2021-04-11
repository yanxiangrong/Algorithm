//
// Created by yan on 2021/3/11.
// 求解逆序对

#include <iostream>
#include <random>
#include <ctime>

#define INF 0x7FFFFFFF

long long int gCount = 0;

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
            if (i != n1) {
                gCount += j + q - k; // 累加后面的元素个数，即总交换次数
            }
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

int test() {
    std::mt19937 mt(std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, 100);
    const int SIZE = 4;
    int array[SIZE];
    for (int &i : array) {
        i = dist(mt);
    }
    printf("INF: %d\n", INF);
    printf("Array: \n");
    for (int &i : array) {
        printf("\t%d ", i);
    }
    gCount = 0;
    mergeSort(array, 0, SIZE);
    printf("\n");
    printf("Count: %d\n", gCount);
    return 0;
}

int main() {
    return test();
//    const int MAX_SIZE = 500'000;
//    int n = 0;
//    int array[MAX_SIZE];
//    std::cin >> n;
//    for (int i = 0; i < n; ++i) {
//        std::cin >> array[i];
//    }
//    mergeSort(array, 0, n);
//    std::cout << gCount << std::endl;
//    return 0;
}
