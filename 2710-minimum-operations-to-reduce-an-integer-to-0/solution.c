int min(int a, int b) {
    return a < b ? a : b;
}

int minOperations(int n) {
    if (n == 0) return 0;

    if ((n & (n - 1)) == 0)
        return 1;

    int lowbit = n & -n;

    return 1 + min(
        minOperations(n - lowbit),
        minOperations(n + lowbit)
    );
}
