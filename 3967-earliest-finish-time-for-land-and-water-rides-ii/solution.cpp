class Solution {
public:
    long long earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration,
                                 vector<int>& waterStartTime, vector<int>& waterDuration) {
        
        auto solveDirection = [&](const vector<int>& startA,
                                  const vector<int>& durA,
                                  const vector<int>& startB,
                                  const vector<int>& durB) -> long long {
            
            int m = startB.size();

            vector<pair<int,int>> ridesB(m);
            for (int i = 0; i < m; i++) {
                ridesB[i] = {startB[i], durB[i]};
            }

            sort(ridesB.begin(), ridesB.end());

            vector<int> opens(m);
            vector<long long> prefMinDur(m), suffMinOpenPlusDur(m);

            for (int i = 0; i < m; i++) {
                opens[i] = ridesB[i].first;
            }

            for (int i = 0; i < m; i++) {
                long long d = ridesB[i].second;
                if (i == 0) prefMinDur[i] = d;
                else prefMinDur[i] = min(prefMinDur[i - 1], d);
            }

            for (int i = m - 1; i >= 0; i--) {
                long long val = 1LL * ridesB[i].first + ridesB[i].second;
                if (i == m - 1) suffMinOpenPlusDur[i] = val;
                else suffMinOpenPlusDur[i] = min(suffMinOpenPlusDur[i + 1], val);
            }

            long long best = LLONG_MAX;

            for (int i = 0; i < (int)startA.size(); i++) {
                long long finishA = 1LL * startA[i] + durA[i];

                int pos = upper_bound(opens.begin(), opens.end(), finishA) - opens.begin() - 1;

                long long cur = LLONG_MAX;

                if (pos >= 0) {
                    cur = min(cur, finishA + prefMinDur[pos]);
                }

                if (pos + 1 < m) {
                    cur = min(cur, suffMinOpenPlusDur[pos + 1]);
                }

                best = min(best, cur);
            }

            return best;
        };

        long long landThenWater =
            solveDirection(landStartTime, landDuration,
                           waterStartTime, waterDuration);

        long long waterThenLand =
            solveDirection(waterStartTime, waterDuration,
                           landStartTime, landDuration);

        return min(landThenWater, waterThenLand);
    }
};
