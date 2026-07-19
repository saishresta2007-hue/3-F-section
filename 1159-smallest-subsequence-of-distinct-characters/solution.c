#include <string.h>
#include <stdlib.h>

char* smallestSubsequence(char* s) {
    int last[26];
    int used[26] = {0};
    int i;

    for (i = 0; i < 26; i++)
        last[i] = -1;

    int n = strlen(s);

    // Last occurrence of each character
    for (i = 0; i < n; i++)
        last[s[i] - 'a'] = i;

    char *stack = (char *)malloc((n + 1) * sizeof(char));
    int top = -1;

    for (i = 0; i < n; i++) {
        int c = s[i] - 'a';

        if (used[c])
            continue;

        while (top >= 0 &&
               stack[top] > s[i] &&
               last[stack[top] - 'a'] > i) {
            used[stack[top] - 'a'] = 0;
            top--;
        }

        stack[++top] = s[i];
        used[c] = 1;
    }

    stack[top + 1] = '\0';
    return stack;
}
