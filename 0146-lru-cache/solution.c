typedef struct Node {
    int key;
    int value;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    int capacity;
    int size;
    Node** map;
    Node* head;
    Node* tail;
} LRUCache;

Node* createNode(int key, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void removeNode(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void insertAtTail(LRUCache* obj, Node* node) {
    node->prev = obj->tail->prev;
    node->next = obj->tail;

    obj->tail->prev->next = node;
    obj->tail->prev = node;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* obj = (LRUCache*)malloc(sizeof(LRUCache));

    obj->capacity = capacity;
    obj->size = 0;

    obj->map = (Node**)calloc(10001, sizeof(Node*));

    obj->head = createNode(0, 0);
    obj->tail = createNode(0, 0);

    obj->head->next = obj->tail;
    obj->tail->prev = obj->head;

    return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
    if (obj->map[key] == NULL)
        return -1;

    Node* node = obj->map[key];

    removeNode(node);
    insertAtTail(obj, node);

    return node->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    if (obj->map[key] != NULL) {
        Node* node = obj->map[key];
        node->value = value;

        removeNode(node);
        insertAtTail(obj, node);
        return;
    }

    if (obj->size == obj->capacity) {
        Node* lru = obj->head->next;

        removeNode(lru);
        obj->map[lru->key] = NULL;

        free(lru);
        obj->size--;
    }

    Node* node = createNode(key, value);
    insertAtTail(obj, node);

    obj->map[key] = node;
    obj->size++;
}

void lRUCacheFree(LRUCache* obj) {
    Node* curr = obj->head;

    while (curr) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }

    free(obj->map);
    free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 * lRUCachePut(obj, key, value);
 * lRUCacheFree(obj);
 */
