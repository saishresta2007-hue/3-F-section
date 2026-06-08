#include <stdlib.h>

typedef struct Node {
    long long key;
    int count;
    struct Node *next;
} Node;

#define SIZE 40009

int hash(long long key) {
    long long h = key % SIZE;
    if (h < 0) h += SIZE;
    return (int)h;
}

int getCount(Node **table, long long key) {
    int idx = hash(key);
    Node *curr = table[idx];

    while (curr) {
        if (curr->key == key)
            return curr->count;
        curr = curr->next;
    }

    return 0;
}

void add(Node **table, long long key) {
    int idx = hash(key);
    Node *curr = table[idx];

    while (curr) {
        if (curr->key == key) {
            curr->count++;
            return;
        }
        curr = curr->next;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->count = 1;
    node->next = table[idx];
    table[idx] = node;
}

int subarraySum(int* nums, int numsSize, int k) {
    Node *table[SIZE] = {0};

    long long prefix = 0;
    int ans = 0;

    add(table, 0);  // prefix sum before starting

    for (int i = 0; i < numsSize; i++) {
        prefix += nums[i];

        ans += getCount(table, prefix - k);

        add(table, prefix);
    }

    return ans;
}
