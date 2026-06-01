#include <stdlib.h>

void heapifyDown(int heap[], int size, int i) {
    while (1) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && heap[left] > heap[largest])
            largest = left;

        if (right < size && heap[right] > heap[largest])
            largest = right;

        if (largest == i)
            break;

        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;

        i = largest;
    }
}

void heapifyUp(int heap[], int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[parent] >= heap[i])
            break;

        int temp = heap[parent];
        heap[parent] = heap[i];
        heap[i] = temp;

        i = parent;
    }
}

void push(int heap[], int *size, int value) {
    heap[*size] = value;
    (*size)++;
    heapifyUp(heap, *size - 1);
}

int pop(int heap[], int *size) {
    int top = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    heapifyDown(heap, *size, 0);
    return top;
}

int lastStoneWeight(int* stones, int stonesSize) {
    int heap[31];
    int size = 0;

    for (int i = 0; i < stonesSize; i++)
        push(heap, &size, stones[i]);

    while (size > 1) {
        int y = pop(heap, &size); // largest
        int x = pop(heap, &size); // second largest

        if (y != x)
            push(heap, &size, y - x);
    }

    return size == 0 ? 0 : heap[0];
}    

