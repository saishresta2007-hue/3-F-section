#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} MaxHeap;

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void heapifyUp(MaxHeap *h, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (h->data[parent] >= h->data[idx])
            break;

        swap(&h->data[parent], &h->data[idx]);
        idx = parent;
    }
}

void heapifyDown(MaxHeap *h, int idx) {
    while (1) {
        int largest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < h->size &&
            h->data[left] > h->data[largest])
            largest = left;

        if (right < h->size &&
            h->data[right] > h->data[largest])
            largest = right;

        if (largest == idx)
            break;

        swap(&h->data[idx], &h->data[largest]);
        idx = largest;
    }
}

void push(MaxHeap *h, int val) {
    h->data[h->size] = val;
    h->size++;
    heapifyUp(h, h->size - 1);
}

int pop(MaxHeap *h) {
    int top = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    heapifyDown(h, 0);
    return top;
}

bool isPossible(int* target, int targetSize) {
    if (targetSize == 1)
        return target[0] == 1;

    MaxHeap heap;
    heap.data = (int *)malloc(sizeof(int) * targetSize);
    heap.size = 0;

    long long total = 0;

    for (int i = 0; i < targetSize; i++) {
        push(&heap, target[i]);
        total += target[i];
    }

    while (1) {
        int maxVal = pop(&heap);
        long long rest = total - maxVal;

        if (maxVal == 1 || rest == 1) {
            free(heap.data);
            return true;
        }

        if (rest == 0 || rest >= maxVal) {
            free(heap.data);
            return false;
        }

        int prev = maxVal % rest;

        if (prev == 0) {
            free(heap.data);
            return false;
        }

        total = rest + prev;
        push(&heap, prev);
    }
}
