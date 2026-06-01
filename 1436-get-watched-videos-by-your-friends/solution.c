#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *name;
    int freq;
} Video;

static int cmp(const void *a, const void *b) {
    Video *v1 = (Video *)a;
    Video *v2 = (Video *)b;

    if (v1->freq != v2->freq)
        return v1->freq - v2->freq;

    return strcmp(v1->name, v2->name);
}

char **watchedVideosByFriends(
    char ***watchedVideos, int watchedVideosSize,
    int *watchedVideosColSize,
    int **friends, int friendsSize,
    int *friendsColSize,
    int id, int level,
    int *returnSize) {

    bool visited[100] = {false};
    int queue[100];
    int front = 0, rear = 0;

    queue[rear++] = id;
    visited[id] = true;

    int currLevel = 0;

    while (front < rear && currLevel < level) {
        int sz = rear - front;

        for (int i = 0; i < sz; i++) {
            int person = queue[front++];

            for (int j = 0; j < friendsColSize[person]; j++) {
                int f = friends[person][j];

                if (!visited[f]) {
                    visited[f] = true;
                    queue[rear++] = f;
                }
            }
        }

        currLevel++;
    }

    /* People currently in queue[from front to rear-1]
       are exactly at distance = level */
    Video vids[10000];
    int videoCount = 0;

    for (int i = front; i < rear; i++) {
        int person = queue[i];

        for (int j = 0; j < watchedVideosColSize[person]; j++) {
            char *video = watchedVideos[person][j];

            int k;
            for (k = 0; k < videoCount; k++) {
                if (strcmp(vids[k].name, video) == 0) {
                    vids[k].freq++;
                    break;
                }
            }

            if (k == videoCount) {
                vids[videoCount].name = video;
                vids[videoCount].freq = 1;
                videoCount++;
            }
        }
    }

    qsort(vids, videoCount, sizeof(Video), cmp);

    char **ans = (char **)malloc(videoCount * sizeof(char *));
    for (int i = 0; i < videoCount; i++) {
        ans[i] = vids[i].name;
    }

    *returnSize = videoCount;
    return ans;
}
