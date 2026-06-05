from collections import deque

class Solution:
    def canFinish(self, numCourses, prerequisites):
        graph = [[] for _ in range(numCourses)]
        indegree = [0] * numCourses

        for course, pre in prerequisites:
            graph[pre].append(course)
            indegree[course] += 1

        q = deque()

        for i in range(numCourses):
            if indegree[i] == 0:
                q.append(i)

        completed = 0

        while q:
            node = q.popleft()
            completed += 1

            for neighbor in graph[node]:
                indegree[neighbor] -= 1
                if indegree[neighbor] == 0:
                    q.append(neighbor)

        return completed == numCourses
