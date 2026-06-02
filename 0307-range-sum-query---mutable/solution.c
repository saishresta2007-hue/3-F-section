#include <stdlib.h>

typedef struct {
    int n;
    int *tree;
    int *arr;
} NumArray;

static void build(NumArray *obj, int node, int l, int r) {
    if (l == r) {
        obj->tree[node] = obj->arr[l];
        return;
    }

    int mid = (l + r) / 2;

    build(obj, node * 2, l, mid);
    build(obj, node * 2 + 1, mid + 1, r);

    obj->tree[node] = obj->tree[node * 2] +
                      obj->tree[node * 2 + 1];
}

static void updateSeg(NumArray *obj, int node, int l, int r,
                      int idx, int val) {
    if (l == r) {
        obj->arr[idx] = val;
        obj->tree[node] = val;
        return;
    }

    int mid = (l + r) / 2;

    if (idx <= mid)
        updateSeg(obj, node * 2, l, mid, idx, val);
    else
        updateSeg(obj, node * 2 + 1, mid + 1, r, idx, val);

    obj->tree[node] = obj->tree[node * 2] +
                      obj->tree[node * 2 + 1];
}

static int query(NumArray *obj, int node, int l, int r,
                 int ql, int qr) {
    if (qr < l || ql > r)
        return 0;

    if (ql <= l && r <= qr)
        return obj->tree[node];

    int mid = (l + r) / 2;

    return query(obj, node * 2, l, mid, ql, qr) +
           query(obj, node * 2 + 1, mid + 1, r, ql, qr);
}

NumArray* numArrayCreate(int* nums, int numsSize) {
    NumArray *obj = (NumArray *)malloc(sizeof(NumArray));

    obj->n = numsSize;
    obj->arr = (int *)malloc(numsSize * sizeof(int));

    for (int i = 0; i < numsSize; i++)
        obj->arr[i] = nums[i];

    obj->tree = (int *)calloc(4 * numsSize, sizeof(int));

    build(obj, 1, 0, numsSize - 1);

    return obj;
}

void numArrayUpdate(NumArray* obj, int index, int val) {
    updateSeg(obj, 1, 0, obj->n - 1, index, val);
}

int numArraySumRange(NumArray* obj, int left, int right) {
    return query(obj, 1, 0, obj->n - 1, left, right);
}

void numArrayFree(NumArray* obj) {
    free(obj->tree);
    free(obj->arr);
    free(obj);
}
