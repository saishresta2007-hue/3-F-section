class Solution {
public:
    bool checkDivisibility(int n) {
        int x = n;
        int sumDigits = 0;
        int prodDigits = 1;

        while (x > 0) {
            int d = x % 10;
            sumDigits += d;
            prodDigits *= d;
            x /= 10;
        }

        return n % (sumDigits + prodDigits) == 0;
    }
};
