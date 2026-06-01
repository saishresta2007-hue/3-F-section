#include <stdlib.h>
#include <stdbool.h>

int* closestPrimes(int left, int right, int* returnSize) {
    *returnSize = 2;

    int *ans = (int *)malloc(2 * sizeof(int));
    ans[0] = -1;
    ans[1] = -1;

    bool *isPrime = (bool *)malloc((right + 1) * sizeof(bool));

    for (int i = 0; i <= right; i++)
        isPrime[i] = true;

    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= right; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= right; j += i) {
                isPrime[j] = false;
            }
        }
    }

    int prevPrime = -1;
    int minGap = right - left + 1;

    for (int i = left; i <= right; i++) {
        if (isPrime[i]) {
            if (prevPrime != -1) {
                int gap = i - prevPrime;

                if (gap < minGap) {
                    minGap = gap;
                    ans[0] = prevPrime;
                    ans[1] = i;
                }
            }
            prevPrime = i;
        }
    }

    free(isPrime);
    return ans;
}
