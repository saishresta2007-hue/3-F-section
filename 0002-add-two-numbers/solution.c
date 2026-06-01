/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    // 1. Create a dummy head node to build the result list easily
    struct ListNode dummy;
    struct ListNode* current = &dummy;
    dummy.next = NULL;
    
    int carry = 0;
    
    // 2. Loop as long as there are nodes to add or a carry remaining
    while (l1 != NULL || l2 != NULL || carry != 0) {
        int sum = carry;
        
        if (l1 != NULL) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->val;
            l2 = l2->next;
        }
        
        // Calculate new carry and current digit
        carry = sum / 10;
        int digit = sum % 10;
        
        // 3. Allocate space for the new result node
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = digit;
        newNode->next = NULL;
        
        // Link the new node and advance our pointer
        current->next = newNode;
        current = current->next;
    }
    
    return dummy.next;
}

