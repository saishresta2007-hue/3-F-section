#include <stdlib.h>

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = numsSize - k + 1;
    int *result = (int *)malloc((*returnSize) * sizeof(int));

    int *deque = (int *)malloc(numsSize * sizeof(int));
    int front = 0, back = 0;

    int idx = 0;

    for (int i = 0; i < numsSize; i++) {
        // Remove indices outside the window
        while (front < back && deque[front] <= i - k) {
            front++;
        }

        // Maintain decreasing order in deque
        while (front < back && nums[deque[back - 1]] <= nums[i]) {
            back--;
        }

        deque[back++] = i;

        // Window is ready
        if (i >= k - 1) {
            result[idx++] = nums[deque[front]];
        }
    }

    free(deque);
    return result;
}
