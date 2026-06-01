



#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0)
        return abs(a);
    return gcd(b, a % b);
}

int maxPoints(int** points, int pointsSize, int* pointsColSize) {
    if (pointsSize <= 2)
        return pointsSize;

    int result = 0;

    for (int i = 0; i < pointsSize; i++) {
        int slopes[600][3]; // dx, dy, count
        int size = 0;
        int localMax = 0;

        for (int j = i + 1; j < pointsSize; j++) {
            int dx = points[j][0] - points[i][0];
            int dy = points[j][1] - points[i][1];

            int g = gcd(dx, dy);
            dx /= g;
            dy /= g;

            if (dx < 0) {
                dx = -dx;
                dy = -dy;
            } else if (dx == 0) {
                dy = 1;
            } else if (dy == 0) {
                dx = 1;
            }

            int found = -1;

            for (int k = 0; k < size; k++) {
                if (slopes[k][0] == dx && slopes[k][1] == dy) {
                    found = k;
                    break;
                }
            }

            if (found == -1) {
                slopes[size][0] = dx;
                slopes[size][1] = dy;
                slopes[size][2] = 2;
                if (localMax < 2)
                    localMax = 2;
                size++;
            } else {
                slopes[found][2]++;
                if (slopes[found][2] > localMax)
                    localMax = slopes[found][2];
            }
        }

        if (localMax > result)
            result = localMax;
    }

    return result;
}
