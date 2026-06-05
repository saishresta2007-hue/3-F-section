class Twitter {
private:
    int timer;

    unordered_map<int, unordered_set<int>> following;
    unordered_map<int, vector<pair<int, int>>> tweets; 
    // {time, tweetId}

public:
    Twitter() {
        timer = 0;
    }

    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({timer++, tweetId});
    }

    vector<int> getNewsFeed(int userId) {
        priority_queue<pair<int, int>> pq; 
        // {time, tweetId}

        // User's own tweets
        for (auto &tweet : tweets[userId]) {
            pq.push(tweet);
        }

        // Followees' tweets
        for (int followee : following[userId]) {
            for (auto &tweet : tweets[followee]) {
                pq.push(tweet);
            }
        }

        vector<int> feed;

        while (!pq.empty() && feed.size() < 10) {
            feed.push_back(pq.top().second);
            pq.pop();
        }

        return feed;
    }

    void follow(int followerId, int followeeId) {
        following[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        following[followerId].erase(followeeId);
    }
};
