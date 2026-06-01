#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *licenseKeyFormatting(char *s, int k) {
    int n = strlen(s);

    // Count valid characters (excluding '-')
    int len = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] != '-')
            len++;
    }

    if (len == 0) {
        char *res = (char *)malloc(1);
        res[0] = '\0';
        return res;
    }

    // Number of dashes in result
    int groups = (len + k - 1) / k;
    int resultLen = len + groups - 1;

    char *res = (char *)malloc(resultLen + 1);

    // Store cleaned uppercase string
    char *clean = (char *)malloc(len + 1);
    int idx = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] != '-') {
            clean[idx++] = toupper(s[i]);
        }
    }
    clean[idx] = '\0';

    int firstGroup = len % k;
    if (firstGroup == 0)
        firstGroup = k;

    int pos = 0;
    int i = 0;

    // First group
    for (; i < firstGroup; i++)
        res[pos++] = clean[i];

    // Remaining groups
    while (i < len) {
        res[pos++] = '-';
        for (int j = 0; j < k; j++)
            res[pos++] = clean[i++];
    }

    res[pos] = '\0';

    free(clean);
    return res;
}
