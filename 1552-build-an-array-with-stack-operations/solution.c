/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>

char** buildArray(int* target, int targetSize, int n, int* returnSize) {
    char** result = (char**)malloc(200 * sizeof(char*));
    int k = 0;
    int current = 1;

    for (int i = 0; i < targetSize; i++) {
        while (current < target[i]) {
            result[k] = (char*)malloc(5);
            strcpy(result[k++], "Push");

            result[k] = (char*)malloc(4);
            strcpy(result[k++], "Pop");

            current++;
        }

        result[k] = (char*)malloc(5);
        strcpy(result[k++], "Push");
        current++;
    }

    *returnSize = k;
    return result;
}
