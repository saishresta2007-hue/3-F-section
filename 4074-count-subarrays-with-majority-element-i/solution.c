long long countMajoritySubarrays(int* nums, int numsSize, int target) {
    int prefix[1001];
    prefix[0] = 0;

    for (int i = 0; i < numsSize; i++) {
        int val = (nums[i] == target) ? 1 : -1;
        prefix[i + 1] = prefix[i] + val;
    }

    long long ans = 0;

    for (int i = 0; i < numsSize; i++) {
        for (int j = i; j < numsSize; j++) {
            if (prefix[j + 1] - prefix[i] > 0)
                ans++;
        }
    }

    return ans;
}
