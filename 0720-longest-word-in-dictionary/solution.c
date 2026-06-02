    
    
    
    #include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

char* longestWord(char** words, int wordsSize) {
    qsort(words, wordsSize, sizeof(char *), cmp);

    char *valid[1000];
    int validSize = 0;

    char *ans = "";

    for (int i = 0; i < wordsSize; i++) {
        int len = strlen(words[i]);

        int ok = (len == 1);

        if (!ok) {
            char prefix[31];
            strcpy(prefix, words[i]);
            prefix[len - 1] = '\0';

            for (int j = 0; j < validSize; j++) {
                if (strcmp(valid[j], prefix) == 0) {
                    ok = 1;
                    break;
                }
            }
        }

        if (ok) {
            valid[validSize++] = words[i];

            if (len > (int)strlen(ans))
                ans = words[i];
        }
    }

    return ans;
}
