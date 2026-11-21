
import java.util.*;

class Solution {
    public int[] findSubtreeSizes(int[] parent, String s) {
        int n = parent.length;

        List<Integer>[] children = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            children[i] = new ArrayList<>();
        }

        // Build the original tree
        for (int i = 1; i < n; i++) {
            children[parent[i]].add(i);
        }

        int[] newParent = parent.clone();

        // Store the nearest ancestor for each character
        int[] last = new int[26];
        Arrays.fill(last, -1);

        // Find the new parent using DFS
        dfs(0, children, s, last, newParent);

        // Build the modified tree
        List<Integer>[] newChildren = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            newChildren[i] = new ArrayList<>();
        }

        for (int i = 1; i < n; i++) {
            newChildren[newParent[i]].add(i);
        }

        // Calculate subtree sizes
        int[] answer = new int[n];
        calculateSize(0, newChildren, answer);

        return answer;
    }

    void dfs(int node, List<Integer>[] children, String s,
             int[] last, int[] newParent) {

        int ch = s.charAt(node) - 'a';
        int previous = last[ch];

        if (node != 0 && previous != -1) {
            newParent[node] = previous;
        }

        last[ch] = node;

        for (int child : children[node]) {
            dfs(child, children, s, last, newParent);
        }

        last[ch] = previous;
    }

    int calculateSize(int node, List<Integer>[] children,
                      int[] answer) {

        int size = 1;

        for (int child : children[node]) {
            size += calculateSize(child, children, answer);
        }

        answer[node] = size;
        return size;
    }
}

