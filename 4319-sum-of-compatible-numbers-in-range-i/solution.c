long long sumOfGoodIntegers(int n, int k) {
    long long sum = 0;

    int left = n - k;
    if (left < 1) {
        left = 1;
    }

    int right = n + k;

    for (int x = left; x <= right; x++) {
        if ((n & x) == 0) {
            sum += x;
        }
    }

    return sum;
}
