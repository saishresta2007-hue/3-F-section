class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int originalOnes = 0;
        for (char c : s)
            if (c == '1') originalOnes++;

        string t = "1" + s + "1";

        vector<pair<char, int>> runs;
        for (char c : t) {
            if (runs.empty() || runs.back().first != c)
                runs.push_back({c, 1});
            else
                runs.back().second++;
        }

        int bestGain = 0;

        for (int i = 1; i + 1 < (int)runs.size(); i++) {
            if (runs[i].first == '1') {
                int leftZeros = runs[i - 1].second;
                int rightZeros = runs[i + 1].second;
                bestGain = max(bestGain, leftZeros + rightZeros);
            }
        }

        return originalOnes + bestGain;
    }
};
