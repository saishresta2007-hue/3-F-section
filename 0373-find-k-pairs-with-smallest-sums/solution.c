#include <stdlib.h>

typedef struct {
    int i, j;
    long long sum;
} Node;

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(Node heap[], int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;

        if (heap[parent].sum <= heap[idx].sum)
            break;

        swap(&heap[parent], &heap[idx]);
        idx = parent;
    }
}

void heapifyDown(Node heap[], int size, int idx) {
    while (1) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size && heap[left].sum < heap[smallest].sum)
            smallest = left;

        if (right < size && heap[right].sum < heap[smallest].sum)
            smallest = right;

        if (smallest == idx)
            break;

        swap(&heap[idx], &heap[smallest]);
        idx = smallest;
    }
}

void push(Node heap[], int *size, Node val) {
    heap[*size] = val;
    (*size)++;
    heapifyUp(heap, *size - 1);
}

Node pop(Node heap[], int *size) {
    Node top = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    heapifyDown(heap, *size, 0);
    return top;
}

int** kSmallestPairs(int* nums1, int nums1Size,
                     int* nums2, int nums2Size,
                     int k,
                     int* returnSize,
                     int** returnColumnSizes) {

    Node *heap = (Node *)malloc(sizeof(Node) * (k + 1));
    int heapSize = 0;

    int initial = nums1Size < k ? nums1Size : k;

    for (int i = 0; i < initial; i++) {
        Node node;
        node.i = i;
        node.j = 0;
        node.sum = (long long)nums1[i] + nums2[0];
        push(heap, &heapSize, node);
    }

    int **result = (int **)malloc(sizeof(int *) * k);
    *returnColumnSizes = (int *)malloc(sizeof(int) * k);

    int count = 0;

    while (heapSize > 0 && count < k) {
        Node cur = pop(heap, &heapSize);

        result[count] = (int *)malloc(sizeof(int) * 2);
        result[count][0] = nums1[cur.i];
        result[count][1] = nums2[cur.j];
        (*returnColumnSizes)[count] = 2;
        count++;

        if (cur.j + 1 < nums2Size) {
            Node next;
            next.i = cur.i;
            next.j = cur.j + 1;
            next.sum = (long long)nums1[cur.i] + nums2[cur.j + 1];
            push(heap, &heapSize, next);
        }
    }

    *returnSize = count;
    free(heap);
    return result;
}
