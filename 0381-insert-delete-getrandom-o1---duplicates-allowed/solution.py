import random
from collections import defaultdict

class RandomizedCollection:

    def __init__(self):
        self.nums = []
        self.idx = defaultdict(set)

    def insert(self, val):
        present = len(self.idx[val]) > 0

        self.nums.append(val)
        self.idx[val].add(len(self.nums) - 1)

        return not present

    def remove(self, val):
        if not self.idx[val]:
            return False

        remove_idx = self.idx[val].pop()
        last_val = self.nums[-1]

        if remove_idx != len(self.nums) - 1:
            self.nums[remove_idx] = last_val

            self.idx[last_val].remove(len(self.nums) - 1)
            self.idx[last_val].add(remove_idx)

        self.nums.pop()

        return True

    def getRandom(self):
        return random.choice(self.nums)
