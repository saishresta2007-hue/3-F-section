/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *next;
 *     struct Node *random;
 * };
 */

struct Node* copyRandomList(struct Node* head) {
    if (head == NULL)
        return NULL;

    struct Node *curr = head;

    // Step 1: Insert copied nodes after original nodes
    while (curr) {
        struct Node *copy = (struct Node *)malloc(sizeof(struct Node));
        copy->val = curr->val;
        copy->next = curr->next;
        copy->random = NULL;

        curr->next = copy;
        curr = copy->next;
    }

    // Step 2: Set random pointers for copied nodes
    curr = head;
    while (curr) {
        if (curr->random)
            curr->next->random = curr->random->next;

        curr = curr->next->next;
    }

    // Step 3: Separate the two lists
    curr = head;
    struct Node *copyHead = head->next;

    while (curr) {
        struct Node *copy = curr->next;

        curr->next = copy->next;

        if (copy->next)
            copy->next = copy->next->next;

        curr = curr->next;
    }

    return copyHead;
}
