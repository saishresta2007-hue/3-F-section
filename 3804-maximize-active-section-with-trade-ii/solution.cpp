#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class SparseTable {
    int n;
    vector<vector<int>> st;
public:
    SparseTable(const vector<int>& nums) {
        n = nums.size();
        if (n == 0) return;
        int max_log = log2(n) + 1;
        st.assign(n, vector<int>(max_log, 0));
        for (int i = 0; i < n; ++i) {
            st[i][0] = nums[i];
        }
        for (int j = 1; (1 << j) <= n; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        if (l > r || l < 0 || r >= n) return 0;
        int j = log2(r - l + 1);
        return max(st[l][j], st[r - (1 << j) + 1][j]);
    }
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int total_ones = 0;
        for (char c : s) if (c == '1') total_ones++;

        // Identify all continuous blocks of zeros
        struct Block {
            int start, end, len;
        };
        vector<Block> zero_blocks;
        vector<int> block_idx(n, -1);

        int i = 0;
        while (i < n) {
            if (s[i] == '0') {
                int start = i;
                while (i < n && s[i] == '0') i++;
                int end = i - 1;
                int len = end - start + 1;
                int idx = zero_blocks.size();
                zero_blocks.push_back({start, end, len});
                for (int k = start; k <= end; ++k) {
                    block_idx[k] = idx;
                }
            } else {
                i++;
            }
        }

        int m = zero_blocks.size();
        vector<int> merge_lengths(max(0, m - 1), 0);
        for (int j = 0; j < m - 1; ++j) {
            merge_lengths[j] = zero_blocks[j].len + zero_blocks[j + 1].len;
        }

        SparseTable st(merge_lengths);
        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int ql = q[0], qr = q[1];

            // Find the first zero block index that overlaps or starts after ql
            int first_blk = -1;
            int low = 0, high = m - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (zero_blocks[mid].end >= ql) {
                    first_blk = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            // Find the last zero block index that overlaps or ends before qr
            int last_blk = -1;
            low = 0, high = m - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (zero_blocks[mid].start <= qr) {
                    last_blk = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            // If no valid zero blocks or only one block exists in the range
            if (first_blk == -1 || last_blk == -1 || first_blk >= last_blk) {
                ans.push_back(total_ones);
                continue;
            }

            int max_gain = 0;

            // Case 1: The best internal merge fully within (first_blk, last_blk)
            if (first_blk + 1 <= last_blk - 1) {
                max_gain = max(max_gain, st.query(first_blk + 1, last_blk - 2));
            }

            // Case 2: Merge involving the left boundary block (which might be truncated)
            int left_len = zero_blocks[first_blk].end - max(ql, zero_blocks[first_blk].start) + 1;
            if (first_blk + 1 <= last_blk) {
                int next_len = (first_blk + 1 == last_blk) ? 
                               (min(qr, zero_blocks[last_blk].end) - zero_blocks[last_blk].start + 1) : 
                               zero_blocks[first_blk + 1].len;
                max_gain = max(max_gain, left_len + next_len);
            }

            // Case 3: Merge involving the right boundary block (which might be truncated)
            int right_len = min(qr, zero_blocks[last_blk].end) - zero_blocks[last_blk].start + 1;
            if (last_blk - 1 >= first_blk) {
                int prev_len = (last_blk - 1 == first_blk) ? 
                               (zero_blocks[first_blk].end - max(ql, zero_blocks[first_blk].start) + 1) : 
                               zero_blocks[last_blk - 1].len;
                max_gain = max(max_gain, prev_len + right_len);
            }

            ans.push_back(total_ones + max_gain);
        }

        return ans;
    }
};

