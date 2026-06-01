#include <stdlib.h>

int cmp(const void *a, const void *b) {
    long long x = *(int *)a;
    long long y = *(int *)b;

    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int longestConsecutive(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    qsort(nums, numsSize, sizeof(int), cmp);

    int longest = 1;
    int current = 1;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == nums[i - 1]) {
            continue;  // skip duplicates
        }
        else if (nums[i] == nums[i - 1] + 1) {
            current++;
        }
        else {
            if (current > longest)
                longest = current;
            current = 1;
        }
    }

    if (current > longest)
        longest = current;

    return longest;
}

