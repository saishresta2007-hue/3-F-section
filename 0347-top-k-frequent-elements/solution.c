#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
    int cap;
} Bucket;

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    int offset = 10000;
    int range = 20001;

    int *freq = (int *)calloc(range, sizeof(int));

    // Count frequencies
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i] + offset]++;
    }

    // Create buckets
    Bucket *buckets = (Bucket *)calloc(numsSize + 1, sizeof(Bucket));

    for (int i = 0; i < range; i++) {
        if (freq[i] > 0) {
            int f = freq[i];

            if (buckets[f].cap == 0) {
                buckets[f].cap = 2;
                buckets[f].arr = (int *)malloc(2 * sizeof(int));
            } else if (buckets[f].size == buckets[f].cap) {
                buckets[f].cap *= 2;
                buckets[f].arr = (int *)realloc(
                    buckets[f].arr,
                    buckets[f].cap * sizeof(int)
                );
            }

            buckets[f].arr[buckets[f].size++] = i - offset;
        }
    }

    int *result = (int *)malloc(k * sizeof(int));
    int idx = 0;

    for (int f = numsSize; f >= 1 && idx < k; f--) {
        for (int j = 0; j < buckets[f].size && idx < k; j++) {
            result[idx++] = buckets[f].arr[j];
        }
    }

    *returnSize = k;

    for (int i = 0; i <= numsSize; i++) {
        free(buckets[i].arr);
    }
    free(buckets);
    free(freq);

    return result;
}
