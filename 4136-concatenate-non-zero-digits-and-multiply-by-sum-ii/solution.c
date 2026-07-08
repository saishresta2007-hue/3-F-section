#include <stdlib.h>
#include <string.h>

#define MOD 1000000007LL

static int lowerBound(int *arr, int n, int target) {
    int l = 0, r = n;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] < target)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

static int upperBound(int *arr, int n, int target) {
    int l = 0, r = n;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] <= target)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sumAndMultiply(char* s, int** queries, int queriesSize,
                    int* queriesColSize, int* returnSize) {
    int m = strlen(s);

    long long *digitPrefix = (long long *)malloc((m + 1) * sizeof(long long));

    int *nzPos = (int *)malloc(m * sizeof(int));
    int *nzDigit = (int *)malloc(m * sizeof(int));

    digitPrefix[0] = 0;
    int nzCount = 0;

    for (int i = 0; i < m; i++) {
        int d = s[i] - '0';
        digitPrefix[i + 1] = digitPrefix[i] + d;

        if (d != 0) {
            nzPos[nzCount] = i;
            nzDigit[nzCount] = d;
            nzCount++;
        }
    }

    long long *pow10 = (long long *)malloc((nzCount + 1) * sizeof(long long));
    long long *prefVal = (long long *)malloc((nzCount + 1) * sizeof(long long));

    pow10[0] = 1;
    for (int i = 1; i <= nzCount; i++)
        pow10[i] = (pow10[i - 1] * 10) % MOD;

    prefVal[0] = 0;
    for (int i = 1; i <= nzCount; i++)
        prefVal[i] = (prefVal[i - 1] * 10 + nzDigit[i - 1]) % MOD;

    int *ans = (int *)malloc(sizeof(int) * queriesSize);

    for (int i = 0; i < queriesSize; i++) {
        int l = queries[i][0];
        int r = queries[i][1];

        long long sum = digitPrefix[r + 1] - digitPrefix[l];

        int left = lowerBound(nzPos, nzCount, l);
        int right = upperBound(nzPos, nzCount, r) - 1;

        long long x = 0;

        if (left <= right) {
            int len = right - left + 1;
            x = (prefVal[right + 1] -
                 (prefVal[left] * pow10[len]) % MOD + MOD) % MOD;
        }

        ans[i] = (int)((x * (sum % MOD)) % MOD);
    }

    free(digitPrefix);
    free(nzPos);
    free(nzDigit);
    free(pow10);
    free(prefVal);

    *returnSize = queriesSize;
    return ans;
}
