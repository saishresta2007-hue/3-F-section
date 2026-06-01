int waysToMakeFair(int* nums, int numsSize) {
    int totalEven = 0, totalOdd = 0;

    for (int i = 0; i < numsSize; i++) {
        if (i % 2 == 0)
            totalEven += nums[i];
        else
            totalOdd += nums[i];
    }

    int leftEven = 0, leftOdd = 0;
    int count = 0;

    for (int i = 0; i < numsSize; i++) {
        int newEven, newOdd;

        if (i % 2 == 0) {
            newEven = leftEven + (totalOdd - leftOdd);
            newOdd  = leftOdd + (totalEven - leftEven - nums[i]);
        } else {
            newEven = leftEven + (totalOdd - leftOdd - nums[i]);
            newOdd  = leftOdd + (totalEven - leftEven);
        }

        if (newEven == newOdd)
            count++;

        if (i % 2 == 0)
            leftEven += nums[i];
        else
            leftOdd += nums[i];
    }

    return count;
}
