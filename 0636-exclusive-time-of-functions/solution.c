#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int* exclusiveTime(int n, char** logs, int logsSize, int* returnSize) {
    int* result = (int*)calloc(n, sizeof(int));
    int stack[500];
    int top = -1;

    int prevTime = 0;

    for (int i = 0; i < logsSize; i++) {
        int id, time;
        char type[10];

        sscanf(logs[i], "%d:%[^:]:%d", &id, type, &time);

        if (strcmp(type, "start") == 0) {
            if (top != -1) {
                result[stack[top]] += time - prevTime;
            }

            stack[++top] = id;
            prevTime = time;
        }
        else { // "end"
            result[stack[top]] += time - prevTime + 1;
            top--;

            prevTime = time + 1;
        }
    }

    *returnSize = n;
    return result;
}
