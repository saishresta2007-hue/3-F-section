#include <stdio.h>

long long maxTotalValue(int* nums, int numsSize, int k) {
    int minVal = nums[0], maxVal = nums[0];
    
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < minVal) minVal = nums[i];
        if (nums[i] > maxVal) maxVal = nums[i];
    }
    
    return (long long)k * (maxVal - minVal);
}
