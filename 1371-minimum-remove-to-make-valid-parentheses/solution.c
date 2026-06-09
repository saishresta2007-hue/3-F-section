#include <stdlib.h>
#include <string.h>

char* minRemoveToMakeValid(char* s) {
    int n = strlen(s);

    int *stack = (int *)malloc(n * sizeof(int));
    char *remove = (char *)calloc(n, sizeof(char));

    int top = -1;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            stack[++top] = i;
        } else if (s[i] == ')') {
            if (top >= 0) {
                top--;
            } else {
                remove[i] = 1;
            }
        }
    }

    while (top >= 0) {
        remove[stack[top--]] = 1;
    }

    char *ans = (char *)malloc((n + 1) * sizeof(char));
    int k = 0;

    for (int i = 0; i < n; i++) {
        if (!remove[i]) {
            ans[k++] = s[i];
        }
    }

    ans[k] = '\0';

    free(stack);
    free(remove);

    return ans;
}
