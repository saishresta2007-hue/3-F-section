long long mergeSort(int* nums, int left, int right, int* temp) {
    if (left >= right)
        return 0;

    int mid = left + (right - left) / 2;
    long long count = 0;

    count += mergeSort(nums, left, mid, temp);
    count += mergeSort(nums, mid + 1, right, temp);

    // Count reverse pairs
    int j = mid + 1;
    for (int i = left; i <= mid; i++) {
        while (j <= right && (long long)nums[i] > 2LL * nums[j]) {
            j++;
        }
        count += (j - (mid + 1));
    }

    // Merge step
    int i = left;
    j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j])
            temp[k++] = nums[i++];
        else
            temp[k++] = nums[j++];
    }

    while (i <= mid)
        temp[k++] = nums[i++];

    while (j <= right)
        temp[k++] = nums[j++];

    for (i = left; i <= right; i++)
        nums[i] = temp[i];

    return count;
}

int reversePairs(int* nums, int numsSize) {
    int* temp = (int*)malloc(sizeof(int) * numsSize);

    long long result = mergeSort(nums, 0, numsSize - 1, temp);

    free(temp);
    return (int)result;
}
