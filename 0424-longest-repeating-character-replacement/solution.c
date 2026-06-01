int characterReplacement(char* s, int k) {
    int freq[26] = {0};
    int left = 0, maxFreq = 0, maxLen = 0;

    for (int right = 0; s[right] != '\0'; right++) {
        freq[s[right] - 'A']++;

        if (freq[s[right] - 'A'] > maxFreq)
            maxFreq = freq[s[right] - 'A'];

        while ((right - left + 1) - maxFreq > k) {
            freq[s[left] - 'A']--;
            left++;
        }

        int len = right - left + 1;
        if (len > maxLen)
            maxLen = len;
    }

    return maxLen;
} 
