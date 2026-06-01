#include <stdlib.h>

int* finalPrices(int* prices, int pricesSize, int* returnSize) {
    *returnSize = pricesSize;

    int* answer = (int*)malloc(pricesSize * sizeof(int));
    int stack[500];
    int top = -1;

    for (int i = 0; i < pricesSize; i++) {
        answer[i] = prices[i];
    }

    for (int i = 0; i < pricesSize; i++) {
        while (top >= 0 && prices[stack[top]] >= prices[i]) {
            answer[stack[top]] -= prices[i];
            top--;
        }

        stack[++top] = i;
    }

    return answer;
}
