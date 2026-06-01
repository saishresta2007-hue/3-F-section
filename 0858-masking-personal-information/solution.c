#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* maskPII(char* s) {
    int len = strlen(s);

    // Check if email
    for (int i = 0; i < len; i++) {
        if (s[i] == '@') {
            char *res = (char *)malloc(len + 10);

            int at = i;
            int idx = 0;

            res[idx++] = tolower(s[0]);
            res[idx++] = '*';
            res[idx++] = '*';
            res[idx++] = '*';
            res[idx++] = '*';
            res[idx++] = '*';
            res[idx++] = tolower(s[at - 1]);

            for (int j = at; j < len; j++) {
                res[idx++] = tolower(s[j]);
            }

            res[idx] = '\0';
            return res;
        }
    }

    // Phone number
    char digits[14];
    int count = 0;

    for (int i = 0; i < len; i++) {
        if (isdigit(s[i])) {
            digits[count++] = s[i];
        }
    }

    digits[count] = '\0';

    int country = count - 10;
    char *res = (char *)malloc(25);
    int idx = 0;

    if (country > 0) {
        res[idx++] = '+';

        for (int i = 0; i < country; i++) {
            res[idx++] = '*';
        }

        res[idx++] = '-';
    }

    res[idx++] = '*';
    res[idx++] = '*';
    res[idx++] = '*';
    res[idx++] = '-';
    res[idx++] = '*';
    res[idx++] = '*';
    res[idx++] = '*';
    res[idx++] = '-';

    for (int i = count - 4; i < count; i++) {
        res[idx++] = digits[i];
    }

    res[idx] = '\0';
    return res;
}
