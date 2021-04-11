//
// Created by yan on 2021/3/12.
// 桶排

#include <iostream>
#include <random>
#include <ctime>
#include <list>

void bucketSort(double *array, int length) {
    std::list<double> temp[length];
    for (int i = 0; i < length; ++i) {
        temp[int(length * array[i])].push_back(array[i]);
    }
    for (int i = 0; i < length; ++i) {
        temp[i].sort();
    }
    for (int i = 0, j = 0; i < length; ++i) {
        while (temp[j].empty()) {
            j++;
        }
        array[i] = temp[j].front();
        temp[j].pop_front();
    }
}

void test() {
    const double MAX = 1;
    std::mt19937 mt(std::time(nullptr));
    std::uniform_real_distribution<double> dist(0, MAX);
    const int SIZE = 15;
    double array[SIZE];
    for (double &i : array) {
        i = dist(mt);
    }
    printf("Array: \n");
    for (double &i : array) {
        printf("%f\t", i);
    }
    printf("\n");
    bucketSort(array, SIZE);
    printf("Sorted: \n");
    for (double &i : array) {
        printf("%f\t", i);
    }
}

int main() {
    test();
    return 0;
}
