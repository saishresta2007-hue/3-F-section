#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int reductionOperations(int* nums, int numsSize) {
    // Sort the array in ascending order
    qsort(nums, numsSize, sizeof(int), compare);
    
    int ops = 0;
    int distinct_counts = 0;
    
    // Count operations based on index transitions
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != nums[i - 1]) {
            distinct_counts++;
        }
        ops += distinct_counts;
    }
    
    return ops;
}

