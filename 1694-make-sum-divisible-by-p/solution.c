#include <stdlib.h>

typedef struct {
    long long key;
    int value;
    int used;
} HashNode;

int minSubarray(int* nums, int numsSize, int p) {
    long long total = 0;

    for (int i = 0; i < numsSize; i++) {
        total = (total + nums[i]) % p;
    }

    int rem = total;
    if (rem == 0)
        return 0;

    int size = 262144; // sufficiently large hash table
    HashNode* table = (HashNode*)calloc(size, sizeof(HashNode));

    long long prefix = 0;
    int ans = numsSize;

    // store remainder 0 at index -1
    long long key = 0;
    int idx = (int)(key % size);
    while (table[idx].used)
        idx = (idx + 1) % size;

    table[idx].used = 1;
    table[idx].key = key;
    table[idx].value = -1;

    for (int i = 0; i < numsSize; i++) {
        prefix = (prefix + nums[i]) % p;

        long long target = (prefix - rem + p) % p;

        idx = (int)(target % size);
        while (table[idx].used) {
            if (table[idx].key == target) {
                if (i - table[idx].value < ans)
                    ans = i - table[idx].value;
                break;
            }
            idx = (idx + 1) % size;
        }

        idx = (int)(prefix % size);
        while (table[idx].used && table[idx].key != prefix)
            idx = (idx + 1) % size;

        table[idx].used = 1;
        table[idx].key = prefix;
        table[idx].value = i;
    }

    free(table);

    return (ans == numsSize) ? -1 : ans;
}
