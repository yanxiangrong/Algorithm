//
// Created by yan on 2021/3/11.
// 堆排序

#include <iostream>
#include <random>
#include <ctime>

typedef struct {
    int *data;
    int heapSize;
    int length;
} Heap;

int left(int i) {
    return i * 2;
}

int right(int i) {
    return i * 2 + 1;
}

void exchange(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

void maxHeapify(Heap *heap, int i) {
    int l = left(i);
    int r = right(i);
    int largest;
    if (l <= heap->heapSize and heap->data[l] > heap->data[i]) {
        largest = l;
    } else {
        largest = i;
    }
    if (r <= heap->heapSize and heap->data[r] > heap->data[largest]) {
        largest = r;
    }
    if (largest != i) {
        exchange(heap->data[i], heap->data[largest]);
        maxHeapify(heap, largest);
    }
}

void maxHeapifyPlus(Heap *heap, int i) {
    while (true) {
        int l = left(i);
        int r = right(i);
        int largest;
        if (l <= heap->heapSize and heap->data[l] > heap->data[i]) {
            largest = l;
        } else {
            largest = i;
        }
        if (r <= heap->heapSize and heap->data[r] > heap->data[largest]) {
            largest = r;
        }
        if (largest != i) {
            exchange(heap->data[i], heap->data[largest]);
            i = largest;
        } else {
            break;
        }
    }
}

void buildMaxHeap(Heap *heap) {
    heap->heapSize = heap->length;
    for (int i = heap->length / 2; i > 0; --i) {
//        maxHeapify(heap, i);
        maxHeapifyPlus(heap, i);
    }
}

void heapsort(int *array, int size) {
    Heap heap;
    heap.data = array - 1;
    heap.length = size;
    buildMaxHeap(&heap);
    for (int i = heap.length; i > 1; --i) {
        exchange(heap.data[1], heap.data[i]);
        heap.heapSize--;
        maxHeapify(&heap, 1);
    }
}

int test() {
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
    heapsort(array, SIZE);
    printf("Sorted: \n");
    for (int &i : array) {
        printf("%d\t", i);
    }
    printf("\n");
    return 0;
}

int main() {
    test();
}