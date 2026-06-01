#include <stdlib.h>

int* findErrorNums(int* nums, int numsSize, int* returnSize) {
    *returnSize = 2;

    int* ans = (int*)malloc(2 * sizeof(int));
    int* freq = (int*)calloc(numsSize + 1, sizeof(int));

    int duplicate = -1, missing = -1;

    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
    }

    for (int i = 1; i <= numsSize; i++) {
        if (freq[i] == 2)
            duplicate = i;
        else if (freq[i] == 0)
            missing = i;
    }

    ans[0] = duplicate;
    ans[1] = missing;

    free(freq);
    return ans;
}
