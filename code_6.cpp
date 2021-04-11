//
// Created by yan on 2021/3/12.
// 优先队列

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

void minHeapify(Heap *heap, int i) {
    while (true) {
        int l = left(i);
        int r = right(i);
        int smallest;
        if (l <= heap->heapSize and heap->data[l] < heap->data[i]) {
            smallest = l;
        } else {
            smallest = i;
        }
        if (r <= heap->heapSize and heap->data[r] < heap->data[smallest]) {
            smallest = r;
        }
        if (smallest != i) {
            exchange(heap->data[i], heap->data[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
}

void buildMinHeap(Heap *heap) {
    heap->heapSize = heap->length;
    for (int i = heap->length / 2; i > 0; --i) {
        minHeapify(heap, i);
    }
}

int heapMinimum(Heap *heap) {
    return heap->data[1];
}

int heapExtractMin(Heap *heap) {
    if (heap->heapSize < 1) throw "heap underflow";
    int min = heap->data[1];
    heap->data[1] = heap->data[heap->heapSize];
    heap->heapSize--;
    minHeapify(heap, 1);
    return min;
}

void heapIncreaseKey(Heap *heap, int i, int key) {
    if (key > heap->data[i]) throw "new key is smaller than";
    heap->data[i] = key;
    while (i > 1 and heap->data[parent(i)] > heap->data[i]) {
        exchange(heap->data[parent(i)], heap->data[i]);
        i = parent(i);
    }
}

void minHeapInsert(Heap *heap, int key) {
    heap->heapSize++;
    heap->data[heap->heapSize] = INT32_MAX;
    heapIncreaseKey(heap, heap->heapSize, key);
}

void heapInit(Heap *heap, int *memory) {
    heap->heapSize = 0;
    heap->length = 0;
    heap->data = memory - 1;
}

int fun(int x, int a, int b, int c) {
    return a*x*x + b*x + c;
}

int main() {
    const int MAX_SIZE = 10'000;
    int n = 0;
    Heap heap;
    int mem[MAX_SIZE];
    int sum = 0;

    heapInit(&heap, mem);

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        minHeapInsert(&heap, value);
    }

    while (heap.heapSize > 1) {
        int one = heapExtractMin(&heap);
        int two = heapExtractMin(&heap);
        sum += one + two;
        minHeapInsert(&heap, one + two);
    }
    std::cout << sum << std::endl;

    return 0;
}