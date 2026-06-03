class LFUCache {
private:
    struct Node {
        int key, value, freq;
        Node(int k, int v) : key(k), value(v), freq(1) {}
    };

    int capacity;
    int minFreq;

    unordered_map<int, list<Node>::iterator> keyTable;
    unordered_map<int, list<Node>> freqTable;

    void updateFreq(list<Node>::iterator it) {
        int key = it->key;
        int value = it->value;
        int freq = it->freq;

        freqTable[freq].erase(it);

        if (freqTable[freq].empty()) {
            freqTable.erase(freq);
            if (minFreq == freq)
                minFreq++;
        }

        freq++;
        freqTable[freq].push_front(Node(key, value));
        freqTable[freq].front().freq = freq;
        keyTable[key] = freqTable[freq].begin();
    }

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        minFreq = 0;
    }

    int get(int key) {
        if (!keyTable.count(key))
            return -1;

        auto it = keyTable[key];
        int value = it->value;

        updateFreq(it);
        return value;
    }

    void put(int key, int value) {
        if (capacity == 0)
            return;

        if (keyTable.count(key)) {
            auto it = keyTable[key];
            it->value = value;
            updateFreq(it);
            return;
        }

        if ((int)keyTable.size() >= capacity) {
            auto &lst = freqTable[minFreq];
            auto node = lst.back();

            keyTable.erase(node.key);
            lst.pop_back();

            if (lst.empty())
                freqTable.erase(minFreq);
        }

        minFreq = 1;
        freqTable[1].push_front(Node(key, value));
        keyTable[key] = freqTable[1].begin();
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
