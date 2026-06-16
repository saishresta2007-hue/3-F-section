#include <stdlib.h>
#include <string.h>

char* processStr(char* s) {
    int cap = 16;
    int len = 0;
    char *res = (char *)malloc(cap);

    for (int i = 0; s[i] != '\0'; i++) {
        char ch = s[i];

        if (ch >= 'a' && ch <= 'z') {
            if (len + 1 >= cap) {
                while (len + 1 >= cap) cap *= 2;
                res = (char *)realloc(res, cap);
            }
            res[len++] = ch;
        }
        else if (ch == '*') {
            if (len > 0) len--;
        }
        else if (ch == '#') {
            int oldLen = len;

            if (len + oldLen + 1 >= cap) {
                while (len + oldLen + 1 >= cap) cap *= 2;
                res = (char *)realloc(res, cap);
            }

            memcpy(res + len, res, oldLen);
            len += oldLen;
        }
        else if (ch == '%') {
            for (int l = 0, r = len - 1; l < r; l++, r--) {
                char tmp = res[l];
                res[l] = res[r];
                res[r] = tmp;
            }
        }
    }

    res[len] = '\0';
    return res;
}
