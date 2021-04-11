//
// Created by yan on 2021/3/12.
// 堆


#include <iostream>
#include <random>

typedef struct {
    int *data;
    int heapSize;
    int length;
} Heap;

int parent(int i) {
    return i / 2;
}

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
        maxHeapify(heap, i);
    }
}

int heapMaximum(Heap *heap) {
    return heap->data[1];
}

int heapExtractMax(Heap *heap) {
    if (heap->heapSize < 1) throw "heap underflow";
    int max = heap->data[1];
    heap->data[1] = heap->data[heap->heapSize];
    heap->heapSize--;
    maxHeapify(heap, 1);
    return max;
}

void heapIncreaseKey(Heap *heap, int i, int key) {
    if (key < heap->data[i]) throw "new key is smaller than";
    heap->data[i] = key;
    while (i > 1 and heap->data[parent(i)] < heap->data[i]) {
        exchange(heap->data[parent(i)], heap->data[i]);
        i = parent(i);
    }
}

void maxHeapInsert(Heap *heap, int key) {
    heap->heapSize++;
    heap->data[heap->heapSize] = INT32_MIN;
    heapIncreaseKey(heap, heap->heapSize, key);
}

void heapInit(Heap *heap, int *memory) {
    heap->heapSize = 0;
    heap->length = 0;
    heap->data = memory - 1;
}
