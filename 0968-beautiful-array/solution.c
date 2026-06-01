/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* beautifulArray(int n, int* returnSize) {
    int *arr = (int*)malloc(sizeof(int));
    arr[0] = 1;
    int size = 1;

    while (size < n) {
        int *temp = (int*)malloc(sizeof(int) * n);
        int newSize = 0;

        // Generate odd numbers
        for (int i = 0; i < size; i++) {
            int val = 2 * arr[i] - 1;
            if (val <= n)
                temp[newSize++] = val;
        }

        // Generate even numbers
        for (int i = 0; i < size; i++) {
            int val = 2 * arr[i];
            if (val <= n)
                temp[newSize++] = val;
        }

        free(arr);
        arr = temp;
        size = newSize;
    }

    *returnSize = n;
    return arr;
}
