typedef long long ll;

typedef struct {
    ll val;
    ll cnt;
} Node;

typedef struct {
    Node *dq;
    int head, tail;
    ll cur;
    int isMax;
} Agg;

static void aggInit(Agg *a, int n, int isMax) {
    a->dq = (Node *)malloc(sizeof(Node) * (n + 5));
    a->head = a->tail = 0;
    a->cur = 0;
    a->isMax = isMax;
}

static void aggAdd(Agg *a, ll x) {
    ll cnt = 1;

    if (a->isMax) {
        while (a->tail > a->head &&
               a->dq[a->tail - 1].val <= x) {
            a->tail--;
            a->cur -= a->dq[a->tail].val * a->dq[a->tail].cnt;
            cnt += a->dq[a->tail].cnt;
        }
    } else {
        while (a->tail > a->head &&
               a->dq[a->tail - 1].val >= x) {
            a->tail--;
            a->cur -= a->dq[a->tail].val * a->dq[a->tail].cnt;
            cnt += a->dq[a->tail].cnt;
        }
    }

    a->dq[a->tail++] = (Node){x, cnt};
    a->cur += x * cnt;
}

static void aggRemoveOne(Agg *a) {
    a->cur -= a->dq[a->head].val;

    if (a->dq[a->head].cnt == 1) {
        a->head++;
    } else {
        a->dq[a->head].cnt--;
    }
}

static void calcLessThan(
    int *nums,
    int n,
    long long limit,
    long long *cntOut,
    long long *sumOut
) {
    int *maxDQ = (int *)malloc(sizeof(int) * (n + 5));
    int *minDQ = (int *)malloc(sizeof(int) * (n + 5));

    int maxH = 0, maxT = 0;
    int minH = 0, minT = 0;

    Agg maxAgg, minAgg;
    aggInit(&maxAgg, n, 1);
    aggInit(&minAgg, n, 0);

    ll cnt = 0;
    ll sumRanges = 0;

    int L = 0;

    for (int R = 0; R < n; R++) {
        int x = nums[R];

        while (maxT > maxH && nums[maxDQ[maxT - 1]] <= x)
            maxT--;
        maxDQ[maxT++] = R;

        while (minT > minH && nums[minDQ[minT - 1]] >= x)
            minT--;
        minDQ[minT++] = R;

        aggAdd(&maxAgg, x);
        aggAdd(&minAgg, x);

        while ((ll)nums[maxDQ[maxH]] - nums[minDQ[minH]] >= limit) {
            if (maxDQ[maxH] == L) maxH++;
            if (minDQ[minH] == L) minH++;

            aggRemoveOne(&maxAgg);
            aggRemoveOne(&minAgg);
            L++;
        }

        cnt += (R - L + 1);
        sumRanges += (maxAgg.cur - minAgg.cur);
    }

    *cntOut = cnt;
    *sumOut = sumRanges;

    free(maxDQ);
    free(minDQ);
    free(maxAgg.dq);
    free(minAgg.dq);
}

long long maxTotalValue(int* nums, int numsSize, int k) {
    int n = numsSize;

    ll totalSub = (ll)n * (n + 1) / 2;

    ll tmpCnt, totalRangeSum;
    calcLessThan(nums, n, (ll)4e18, &tmpCnt, &totalRangeSum);

    ll lo = 0, hi = 1000000000LL;

    while (lo < hi) {
        ll mid = (lo + hi + 1) >> 1;

        ll cntLess, sumDummy;
        calcLessThan(nums, n, mid, &cntLess, &sumDummy);

        ll cntGE = totalSub - cntLess;

        if (cntGE >= k)
            lo = mid;
        else
            hi = mid - 1;
    }

    ll T = lo;

    ll cntLessTp1, sumLessTp1;
    calcLessThan(nums, n, T + 1, &cntLessTp1, &sumLessTp1);

    ll cntGT = totalSub - cntLessTp1;
    ll sumGT = totalRangeSum - sumLessTp1;

    return sumGT + (ll)(k - cntGT) * T;
}

