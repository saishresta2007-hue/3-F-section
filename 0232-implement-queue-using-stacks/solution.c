#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int inStack[100];
    int outStack[100];
    int topIn;
    int topOut;
} MyQueue;

MyQueue* myQueueCreate() {
    MyQueue* obj = (MyQueue*)malloc(sizeof(MyQueue));
    obj->topIn = -1;
    obj->topOut = -1;
    return obj;
}

void pushToOut(MyQueue* obj) {
    if (obj->topOut == -1) {
        while (obj->topIn != -1) {
            obj->outStack[++obj->topOut] =
                obj->inStack[obj->topIn--];
        }
    }
}

void myQueuePush(MyQueue* obj, int x) {
    obj->inStack[++obj->topIn] = x;
}

int myQueuePop(MyQueue* obj) {
    pushToOut(obj);
    return obj->outStack[obj->topOut--];
}

int myQueuePeek(MyQueue* obj) {
    pushToOut(obj);
    return obj->outStack[obj->topOut];
}

bool myQueueEmpty(MyQueue* obj) {
    return (obj->topIn == -1 && obj->topOut == -1);
}

void myQueueFree(MyQueue* obj) {
    free(obj);
}
