class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int half = n / 2;

        int diff = 0;
        int Lq = 0, Rq = 0;

        for (int i = 0; i < half; i++) {
            if (num[i] == '?')
                Lq++;
            else
                diff += num[i] - '0';
        }

        for (int i = half; i < n; i++) {
            if (num[i] == '?')
                Rq++;
            else
                diff -= num[i] - '0';
        }

        if ((Lq + Rq) & 1) return true;

        return diff != (Rq - Lq) * 9 / 2;
    }
};
