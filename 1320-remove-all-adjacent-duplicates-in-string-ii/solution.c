#include <stdlib.h>
#include <string.h>

typedef struct {
    char ch;
    int count;
} StackNode;

char* removeDuplicates(char* s, int k) {
    int n = strlen(s);

    StackNode *stack = (StackNode *)malloc(n * sizeof(StackNode));
    int top = -1;

    for (int i = 0; i < n; i++) {
        if (top >= 0 && stack[top].ch == s[i]) {
            stack[top].count++;

            if (stack[top].count == k) {
                top--;
            }
        } else {
            top++;
            stack[top].ch = s[i];
            stack[top].count = 1;
        }
    }

    char *result = (char *)malloc((n + 1) * sizeof(char));
    int idx = 0;

    for (int i = 0; i <= top; i++) {
        for (int j = 0; j < stack[i].count; j++) {
            result[idx++] = stack[i].ch;
        }
    }

    result[idx] = '\0';

    free(stack);
    return result;
}
