#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int isValid(char *s, int start, int len) {
    if (len > 1 && s[start] == '0')
        return 0;

    int num = 0;
    for (int i = 0; i < len; i++) {
        num = num * 10 + (s[start + i] - '0');
    }

    return num <= 255;
}

void backtrack(char *s, int n, int index, int part,
               char *path,
               char ***result, int *returnSize) {

    if (part == 4 && index == n) {
        path[strlen(path) - 1] = '\0';  // remove last dot

        (*result)[*returnSize] = (char *)malloc(strlen(path) + 1);
        strcpy((*result)[*returnSize], path);

        (*returnSize)++;
        return;
    }

    if (part == 4 || index == n)
        return;

    for (int len = 1; len <= 3 && index + len <= n; len++) {
        if (!isValid(s, index, len))
            continue;

        char temp[20];
        strncpy(temp, s + index, len);
        temp[len] = '\0';

        int oldLen = strlen(path);

        strcat(path, temp);
        strcat(path, ".");

        backtrack(s, n, index + len, part + 1,
                  path, result, returnSize);

        path[oldLen] = '\0'; // backtrack
    }
}

char **restoreIpAddresses(char *s, int *returnSize) {
    int n = strlen(s);

    char **result = (char **)malloc(1000 * sizeof(char *));
    *returnSize = 0;

    char path[20] = "";

    backtrack(s, n, 0, 0, path, &result, returnSize);

    return result;
}
