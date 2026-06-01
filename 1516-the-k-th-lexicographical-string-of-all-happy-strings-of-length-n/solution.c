    
#include <stdlib.h>
#include <string.h>

void backtrack(int n, int k, char *curr, int pos,
               int *count, char *result) {
    if (result[0] != '\0')
        return;

    if (pos == n) {
        (*count)++;

        if (*count == k) {
            strcpy(result, curr);
        }
        return;
    }

    char letters[] = {'a', 'b', 'c'};

    for (int i = 0; i < 3; i++) {
        if (pos > 0 && curr[pos - 1] == letters[i])
            continue;

        curr[pos] = letters[i];
        curr[pos + 1] = '\0';

        backtrack(n, k, curr, pos + 1, count, result);
    }
}

char* getHappyString(int n, int k) {
    char *result = (char *)malloc((n + 1) * sizeof(char));
    result[0] = '\0';

    char curr[11];
    int count = 0;

    backtrack(n, k, curr, 0, &count, result);

    return result;
}
