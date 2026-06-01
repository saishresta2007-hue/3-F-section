#include <stdbool.h>
#include <ctype.h>

bool detectCapitalUse(char *word) {
    int i;

    // Case 1: All uppercase
    bool allUpper = true;
    for (i = 0; word[i]; i++) {
        if (!isupper(word[i])) {
            allUpper = false;
            break;
        }
    }
    if (allUpper) return true;

    // Case 2: All lowercase
    bool allLower = true;
    for (i = 0; word[i]; i++) {
        if (!islower(word[i])) {
            allLower = false;
            break;
        }
    }
    if (allLower) return true;

    // Case 3: First uppercase, rest lowercase
    if (isupper(word[0])) {
        for (i = 1; word[i]; i++) {
            if (!islower(word[i])) {
                return false;
            }
        }
        return true;
    }

    return false;
}
