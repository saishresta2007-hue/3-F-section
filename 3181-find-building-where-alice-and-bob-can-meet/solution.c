#include <stdlib.h>

typedef struct {
    int threshold;
    int idx;
} HeapNode;

typedef struct {
    HeapNode *arr;
    int size;
} MinHeap;

static void swap(HeapNode *a, HeapNode *b) {
    HeapNode t = *a;
    *a = *b;
    *b = t;
}

static void push(MinHeap *h, int threshold, int idx) {
    int i = h->size++;
    h->arr[i].threshold = threshold;
    h->arr[i].idx = idx;

    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->arr[p].threshold <= h->arr[i].threshold) break;
        swap(&h->arr[p], &h->arr[i]);
        i = p;
    }
}

static HeapNode pop(MinHeap *h) {
    HeapNode res = h->arr[0];
    h->arr[0] = h->arr[--h->size];

    int i = 0;
    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest = i;

        if (l < h->size &&
            h->arr[l].threshold < h->arr[smallest].threshold)
            smallest = l;

        if (r < h->size &&
            h->arr[r].threshold < h->arr[smallest].threshold)
            smallest = r;

        if (smallest == i) break;

        swap(&h->arr[i], &h->arr[smallest]);
        i = smallest;
    }

    return res;
}

typedef struct QueryNode {
    int threshold;
    int qid;
    struct QueryNode *next;
} QueryNode;

int* leftmostBuildingQueries(int* heights, int heightsSize,
                             int** queries, int queriesSize,
                             int* queriesColSize,
                             int* returnSize) {
    *returnSize = queriesSize;

    int *ans = (int *)malloc(sizeof(int) * queriesSize);

    QueryNode **bucket =
        (QueryNode **)calloc(heightsSize, sizeof(QueryNode *));

    for (int i = 0; i < queriesSize; i++) {
        int a = queries[i][0];
        int b = queries[i][1];

        if (a > b) {
            int t = a;
            a = b;
            b = t;
        }

        if (a == b) {
            ans[i] = b;
        } else if (heights[a] < heights[b]) {
            ans[i] = b;
        } else {
            ans[i] = -1;

            QueryNode *node =
                (QueryNode *)malloc(sizeof(QueryNode));

            node->threshold = heights[a];
            node->qid = i;
            node->next = bucket[b];
            bucket[b] = node;
        }
    }

    MinHeap heap;
    heap.arr = (HeapNode *)malloc(sizeof(HeapNode) * queriesSize);
    heap.size = 0;

    for (int i = 0; i < heightsSize; i++) {

        while (heap.size > 0 &&
               heap.arr[0].threshold < heights[i]) {
            HeapNode cur = pop(&heap);
            ans[cur.idx] = i;
        }

        QueryNode *p = bucket[i];
        while (p) {
            push(&heap, p->threshold, p->qid);
            p = p->next;
        }
    }

    for (int i = 0; i < heightsSize; i++) {
        QueryNode *p = bucket[i];
        while (p) {
            QueryNode *tmp = p;
            p = p->next;
            free(tmp);
        }
    }

    free(bucket);
    free(heap.arr);

    return ans;
}
