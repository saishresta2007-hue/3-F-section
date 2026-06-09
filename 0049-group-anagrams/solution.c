#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char **words;
    int size;
    int capacity;
} Group;

static int cmpChar(const void *a, const void *b) {
    return (*(char *)a) - (*(char *)b);
}

char *getKey(const char *s) {
    int len = strlen(s);
    char *key = (char *)malloc(len + 1);
    strcpy(key, s);
    qsort(key, len, sizeof(char), cmpChar);
    return key;
}

char ***groupAnagrams(char **strs, int strsSize,
                      int *returnSize,
                      int **returnColumnSizes) {
    Group *groups = (Group *)malloc(strsSize * sizeof(Group));
    int groupCount = 0;

    for (int i = 0; i < strsSize; i++) {
        char *key = getKey(strs[i]);

        int idx = -1;
        for (int j = 0; j < groupCount; j++) {
            if (strcmp(groups[j].key, key) == 0) {
                idx = j;
                break;
            }
        }

        if (idx == -1) {
            idx = groupCount++;

            groups[idx].key = key;
            groups[idx].size = 0;
            groups[idx].capacity = 4;
            groups[idx].words =
                (char **)malloc(groups[idx].capacity * sizeof(char *));
        } else {
            free(key);
        }

        if (groups[idx].size == groups[idx].capacity) {
            groups[idx].capacity *= 2;
            groups[idx].words = (char **)realloc(
                groups[idx].words,
                groups[idx].capacity * sizeof(char *));
        }

        groups[idx].words[groups[idx].size++] = strs[i];
    }

    char ***result = (char ***)malloc(groupCount * sizeof(char **));
    *returnColumnSizes = (int *)malloc(groupCount * sizeof(int));

    for (int i = 0; i < groupCount; i++) {
        result[i] = groups[i].words;
        (*returnColumnSizes)[i] = groups[i].size;
        free(groups[i].key);
    }

    free(groups);
    *returnSize = groupCount;

    return result;
}
