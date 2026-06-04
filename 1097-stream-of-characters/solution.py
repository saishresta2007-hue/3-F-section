from collections import deque

class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_word = False


class StreamChecker:

    def __init__(self, words):
        self.root = TrieNode()
        self.stream = deque()
        self.max_len = 0

        for word in words:
            self.max_len = max(self.max_len, len(word))
            node = self.root

            for ch in reversed(word):
                if ch not in node.children:
                    node.children[ch] = TrieNode()
                node = node.children[ch]

            node.is_word = True

    def query(self, letter):
        self.stream.append(letter)

        if len(self.stream) > self.max_len:
            self.stream.popleft()

        node = self.root

        for ch in reversed(self.stream):
            if ch not in node.children:
                return False

            node = node.children[ch]

            if node.is_word:
                return True

        return False
