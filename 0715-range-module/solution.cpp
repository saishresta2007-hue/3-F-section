class RangeModule {
    map<int, int> intervals;

public:
    RangeModule() {
    }

    void addRange(int left, int right) {
        auto it = intervals.lower_bound(left);

        if (it != intervals.begin()) {
            auto prevIt = prev(it);
            if (prevIt->second >= left) {
                left = min(left, prevIt->first);
                right = max(right, prevIt->second);
                it = intervals.erase(prevIt);
            }
        }

        while (it != intervals.end() && it->first <= right) {
            right = max(right, it->second);
            it = intervals.erase(it);
        }

        intervals[left] = right;
    }

    bool queryRange(int left, int right) {
        auto it = intervals.upper_bound(left);

        if (it == intervals.begin())
            return false;

        --it;
        return it->second >= right;
    }

    void removeRange(int left, int right) {
        auto it = intervals.lower_bound(left);

        if (it != intervals.begin()) {
            auto prevIt = prev(it);

            if (prevIt->second > left) {
                int l = prevIt->first;
                int r = prevIt->second;

                prevIt->second = left;

                if (r > right)
                    intervals[right] = r;
            }
        }

        while (it != intervals.end() && it->first < right) {
            if (it->second <= right) {
                it = intervals.erase(it);
            } else {
                int r = it->second;
                intervals.erase(it);
                intervals[right] = r;
                break;
            }
        }
    }
};
