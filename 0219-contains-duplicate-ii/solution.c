#include <stdbool.h>
#include <stdlib.h>

// Structure for hash map elements
typedef struct Node {
    int key;
    int index;
    struct Node* next;
} Node;

#define HASH_SIZE 20011 // A prime number close to the input size limits

// Hash function to map negative and positive keys safely
int getHash(int key) {
    long long k = key;
    int hash = k % HASH_SIZE;
    if (hash < 0) {
        hash += HASH_SIZE;
    }
    return hash;
}

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    // Allocate memory for hash table buckets
    Node** hashTable = (Node**)calloc(HASH_SIZE, sizeof(Node*));
    bool found = false;

    for (int i = 0; i < numsSize; i++) {
        int hash = getHash(nums[i]);
        Node* curr = hashTable[hash];
        
        // Search if the value already exists in the bucket
        while (curr != NULL) {
            if (curr->key == nums[i]) {
                // If it matches, check the distance constraint
                if (i - curr->index <= k) {
                    found = true;
                    break;
                }
                // Update to the latest index for this duplicate
                curr->index = i; 
                break;
            }
            curr = curr->next;
        }

        if (found) break;

        // If it's a new element in this hash chain, insert it at the head
        if (curr == NULL) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->key = nums[i];
            newNode->index = i;
            newNode->next = hashTable[hash];
            hashTable[hash] = newNode;
        }
    }

    // Free the allocated memory to avoid leaks
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* curr = hashTable[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(hashTable);

    return found;
}

