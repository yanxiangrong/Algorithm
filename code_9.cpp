//
// Created by yan on 2021/3/12.
// 基数排序

#include <iostream>
#include <random>
#include <ctime>

void exchange(int *&a, int *&b) {
    int *c = a;
    a = b;
    b = c;
}

int digitsNum(int x) {
    int d = 0;
    while (x != 0) {
        d++;
        x /= 10;
    }
    return d;
}

int getDigit(int x, int i) {
    int a = 0;
    while (i--) {
        a = x % 10;
        x /= 10;
    }
    return a;
}

void countingSortMod(const int *array, int *result, int length, int digitN) {
    const int k = 10;
    int temp[k];
    for (int & i : temp) {
        i = 0;
    }
    for (int i = 0; i < length; ++i) {
        temp[getDigit(array[i], digitN)]++;
    }
    for (int i = 1; i < k; ++i) {
        temp[i] = temp[i] + temp[i - 1];
    }
    for (int i = length - 1; i >= 0; --i) {
        result[temp[getDigit(array[i], digitN)] - 1] = array[i];
        temp[getDigit(array[i], digitN)]--;
    }
}

void radixSort(int *array, int length, int d) {
    int newArr[length];
    int *temp = newArr;
    bool isExchanged = false;
    for (int i = 1; i <= d; ++i) {
        countingSortMod(array, temp, length, i);
        exchange(array, temp);
        isExchanged = !isExchanged;
    }
    if (isExchanged) {
        for (int j = 0; j < length; ++j) {
            temp[j] = array[j];
        }
    }
}

void test() {
    const int MAX = 1000;
    std::mt19937 mt(std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, MAX);
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
    radixSort(array, SIZE, digitsNum(MAX - 1));
    printf("Sorted: \n");
    for (int &i : array) {
        printf("%d\t", i);
    }
}

int main() {
    test();
    return 0;
}
