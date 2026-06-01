#include <stdlib.h>

int* smallerNumbersThanCurrent(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;

    int count[101] = {0};

    // Count frequency of each number
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }

    // Prefix sum: count[i] = numbers <= i
    for (int i = 1; i <= 100; i++) {
        count[i] += count[i - 1];
    }

    int* ans = (int*)malloc(numsSize * sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 0)
            ans[i] = 0;
        else
            ans[i] = count[nums[i] - 1];
    }

    return ans;
}
