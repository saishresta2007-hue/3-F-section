#include <stdlib.h>
#include <stdio.h>

char* getPermutation(int n, int k) {
    int factorial[10];
    factorial[0] = 1;

    for (int i = 1; i <= n; i++) {
        factorial[i] = factorial[i - 1] * i;
    }

    int nums[9];
    for (int i = 0; i < n; i++) {
        nums[i] = i + 1;
    }

    char *result = (char *)malloc((n + 1) * sizeof(char));
    result[n] = '\0';

    k--;  // Convert to 0-based indexing

    for (int i = 0; i < n; i++) {
        int index = k / factorial[n - 1 - i];
        result[i] = nums[index] + '0';

        for (int j = index; j < n - 1 - i; j++) {
            nums[j] = nums[j + 1];
        }

        k %= factorial[n - 1 - i];
    }

    return result;
}
