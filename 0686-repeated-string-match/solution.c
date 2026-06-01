    
#include <string.h>
#include <stdlib.h>

int repeatedStringMatch(char *a, char *b) {
    int lenA = strlen(a);
    int lenB = strlen(b);

    int maxLen = lenB + 2 * lenA;
    char *str = (char *)malloc(maxLen + 1);
    str[0] = '\0';

    int count = 0;

    while (strlen(str) < lenB) {
        strcat(str, a);
        count++;
    }

    if (strstr(str, b) != NULL) {
        free(str);
        return count;
    }

    strcat(str, a);
    count++;

    if (strstr(str, b) != NULL) {
        free(str);
        return count;
    }

    free(str);
    return -1;
}
