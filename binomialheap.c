#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in a binomial heap
struct Node {
    int key;                // Key of the node
    int degree;             // Degree of the node (order of the binomial tree)
    struct Node* parent;    // Pointer to the parent node
    struct Node* child;     // Pointer to the leftmost child node
    struct Node* sibling;   // Pointer to the next sibling node
};

// Function to create a new node with a given key
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->degree = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// Function to merge two binomial trees of the same order
struct Node* binomialHeapMerge(struct Node* h1, struct Node* h2) {
    // If one of the heaps is empty, return the other heap
    if (h1 == NULL) {
        return h2;
    } else if (h2 == NULL) {
        return h1;
    }

    struct Node* head = NULL;  // Head of the merged heap
    struct Node* tail = NULL;  // Tail of the merged heap
    struct Node* prev = NULL;  // Pointer to the previous node in the merged heap
    struct Node* current1 = h1; // Pointer to the current node in the first heap
    struct Node* current2 = h2; // Pointer to the current node in the second heap

    // Merge the heaps until one of them becomes empty
    while (current1 != NULL && current2 != NULL) {
        if (current1->degree <= current2->degree) {
            if (tail == NULL) {
                head = current1;
            } else {
                tail->sibling = current1;
            }
            tail = current1;
            current1 = current1->sibling;
        } else {
            if (tail == NULL) {
                head = current2;
            } else {
                tail->sibling = current2;
            }
            tail = current2;
            current2 = current2->sibling;
        }
        tail->sibling = NULL;
    }

    // If there are remaining nodes in the first heap, append them to the merged heap
    while (current1 != NULL) {
        tail->sibling = current1;
        tail = current1;
        current1 = current1->sibling;
        tail->sibling = NULL;
    }

    // If there are remaining nodes in the second heap, append them to the merged heap
    while (current2 != NULL) {
        tail->sibling = current2;
        tail = current2;
        current2 = current2->sibling;
        tail->sibling = NULL;
    }

    return head;
}

int main() {
    // Example usage
    struct Node* heap1 = createNode(1);
    heap1->sibling = createNode(5);

    struct Node* heap2 = createNode(2);
    heap2->sibling = createNode(3);

    printf("Heap 1:\n");
    struct Node* current1 = heap1;
    while (current1 != NULL) {
        printf("%d ", current1->key);
        current1 = current1->sibling;
    }

    printf("\nHeap 2:\n");
    struct Node* current2 = heap2;
    while (current2 != NULL) {
        printf("%d ", current2->key);
        current2 = current2->sibling;
    }

    struct Node* mergedHeap = binomialHeapMerge(heap1, heap2);

    printf("\nMerged Heap:\n");
    struct Node* currentMerged = mergedHeap;
    while (currentMerged != NULL) {
        printf("%d ", currentMerged->key);
        currentMerged = currentMerged->sibling;
    }

    return 0;
}
