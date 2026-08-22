class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();

        auto count = [&](long long x) -> long long {
            long long res = 0;

            for (int mask = 1; mask < (1 << n); mask++) {
                long long l = 1;
                bool valid = true;
                int bits = 0;

                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        bits++;

                        long long g = gcd(l, (long long)coins[i]);
                        long long nxt = l / g;

                        if (nxt > x / coins[i]) {
                            valid = false;
                            break;
                        }

                        l = nxt * coins[i];
                    }
                }

                if (!valid || l > x) continue;

                long long add = x / l;

                if (bits & 1) res += add;
                else res -= add;
            }

            return res;
        };

        long long lo = 1, hi = 1e15;

        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;

            if (count(mid) >= k)
                hi = mid;
            else
                lo = mid + 1;
        }

        return lo;
    }
};
