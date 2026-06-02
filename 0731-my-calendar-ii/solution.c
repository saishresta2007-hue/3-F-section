#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int start;
    int end;
} Interval;

typedef struct {
    Interval books[1000];
    Interval overlaps[1000];
    int bookCount;
    int overlapCount;
} MyCalendarTwo;

MyCalendarTwo* myCalendarTwoCreate() {
    MyCalendarTwo* obj = (MyCalendarTwo*)malloc(sizeof(MyCalendarTwo));
    obj->bookCount = 0;
    obj->overlapCount = 0;
    return obj;
}

bool myCalendarTwoBook(MyCalendarTwo* obj, int start, int end) {
    // Check for triple booking
    for (int i = 0; i < obj->overlapCount; i++) {
        if (start < obj->overlaps[i].end &&
            end > obj->overlaps[i].start) {
            return false;
        }
    }

    // Record new double-booked intervals
    for (int i = 0; i < obj->bookCount; i++) {
        int s = start > obj->books[i].start ? start : obj->books[i].start;
        int e = end < obj->books[i].end ? end : obj->books[i].end;

        if (s < e) {
            obj->overlaps[obj->overlapCount].start = s;
            obj->overlaps[obj->overlapCount].end = e;
            obj->overlapCount++;
        }
    }

    // Add booking
    obj->books[obj->bookCount].start = start;
    obj->books[obj->bookCount].end = end;
    obj->bookCount++;

    return true;
}

void myCalendarTwoFree(MyCalendarTwo* obj) {
    free(obj);
}

/**
 * Your MyCalendarTwo struct will be instantiated and called as such:
 * MyCalendarTwo* obj = myCalendarTwoCreate();
 * bool param_1 = myCalendarTwoBook(obj, start, end);
 * myCalendarTwoFree(obj);
 */
