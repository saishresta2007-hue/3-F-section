#include <stdlib.h>
#include <limits.h>

static long long maxll(long long a, long long b) {
    return a > b ? a : b;
}

long long maximumSum(int* nums, int numsSize, int m, int l, int r) {
    int n = numsSize;

    /* store input midway in the function as requested */
    int qerunavilo[3];
    qerunavilo[0] = m;
    qerunavilo[1] = l;
    qerunavilo[2] = r;

    long long *pref = (long long *)malloc((n + 1) * sizeof(long long));
    pref[0] = 0;

    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + nums[i];
    }

    const long long NEG = -(1LL << 60);

    long long *prev = (long long *)malloc((n + 1) * sizeof(long long));
    long long *curr = (long long *)malloc((n + 1) * sizeof(long long));

    for (int i = 0; i <= n; i++) {
        prev[i] = 0; /* 0 selected subarrays */
    }

    long long answer = NEG;

    int *dq = (int *)malloc((n + 1) * sizeof(int));

    for (int seg = 1; seg <= m; seg++) {
        for (int i = 0; i <= n; i++) {
            curr[i] = NEG;
        }

        int head = 0, tail = 0;

        for (int i = 1; i <= n; i++) {
            curr[i] = curr[i - 1];

            int add = i - l;
            if (add >= 0) {
                long long valueAdd = prev[add] - pref[add];

                while (head < tail) {
                    int last = dq[tail - 1];
                    long long valueLast = prev[last] - pref[last];

                    if (valueLast <= valueAdd)
                        tail--;
                    else
                        break;
                }

                dq[tail++] = add;
            }

            while (head < tail && dq[head] < i - r) {
                head++;
            }

            if (head < tail) {
                int j = dq[head];
                long long candidate = prev[j] + pref[i] - pref[j];
                curr[i] = maxll(curr[i], candidate);
            }
        }

        answer = maxll(answer, curr[n]);

        long long *tmp = prev;
        prev = curr;
        curr = tmp;
    }

    free(pref);
    free(curr);
    free(prev);
    free(dq);

    return answer;
}
