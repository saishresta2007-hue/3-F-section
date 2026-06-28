#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll val;
    int cnt;
} Node;

int cmp(const void *a, const void *b) {
    ll x = *(ll *)a;
    ll y = *(ll *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int getCount(Node *freq, int m, ll x) {
    int l = 0, r = m - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (freq[mid].val == x) return freq[mid].cnt;
        if (freq[mid].val < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return 0;
}

int maximumLength(int* nums, int numsSize) {
    ll *a = (ll *)malloc(sizeof(ll) * numsSize);
    for (int i = 0; i < numsSize; i++)
        a[i] = nums[i];

    qsort(a, numsSize, sizeof(ll), cmp);

    Node *freq = (Node *)malloc(sizeof(Node) * numsSize);
    int m = 0;

    for (int i = 0; i < numsSize; ) {
        int j = i;
        while (j < numsSize && a[j] == a[i]) j++;

        freq[m].val = a[i];
        freq[m].cnt = j - i;
        m++;
        i = j;
    }

    int ans = 1;

    /* Handle 1 separately */
    int ones = getCount(freq, m, 1);
    if (ones > 0) {
        int t = (ones % 2 == 0) ? ones - 1 : ones;
        if (t > ans) ans = t;
    }

    for (int i = 0; i < m; i++) {
        ll x = freq[i].val;
        if (x == 1) continue;

        ll cur = x;
        int len = 0;
        int broken = 0;

        while (getCount(freq, m, cur) >= 2) {
            len += 2;

            if (cur > 1000000000LL / cur) {
                len--;          // no next square possible
                broken = 1;
                break;
            }

            ll nxt = cur * cur;
            if (getCount(freq, m, nxt) == 0) {
                len--;          // cannot extend further
                broken = 1;
                break;
            }

            cur = nxt;
        }

        if (!broken) {
            if (getCount(freq, m, cur) > 0)
                len++;
        }

        if (len > ans)
            ans = len;
    }

    free(a);
    free(freq);
    return ans;
}
