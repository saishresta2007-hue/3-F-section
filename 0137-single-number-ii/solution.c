int singleNumber(int* nums, int numsSize) {
    unsigned int result = 0;

    for (int i = 0; i < 32; i++) {
        int count = 0;

        for (int j = 0; j < numsSize; j++) {
            if (((unsigned int)nums[j] >> i) & 1)
                count++;
        }

        if (count % 3)
            result |= (1U << i);
    }

    return (int)result;
}
