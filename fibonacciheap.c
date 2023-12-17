#include <stdio.h>
#include <stdlib.h>

// Node structure for Fibonacci Heap
typedef struct Node {
    int key;
    struct Node* parent;
    struct Node* child;
    struct Node* left;
    struct Node* right;
    int degree;  // Degree of the node (number of children)
    int marked;  // Mark flag for cascading cuts
} Node;

// Function to create a new node with a given key
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->key = key;
        newNode->parent = NULL;
        newNode->child = NULL;
        newNode->left = newNode;
        newNode->right = newNode;
        newNode->degree = 0;
        newNode->marked = 0;
    }
    return newNode;
}

// Function to link two Fibonacci Heap trees of the same degree
void link(Node* root1, Node* root2) {
    root2->left->right = root2->right;
    root2->right->left = root2->left;

    root2->left = root2;
    root2->right = root2;

    root2->parent = root1;

    if (root1->child == NULL) {
        root1->child = root2;
    } else {
        root2->right = root1->child;
        root2->left = root1->child->left;
        root1->child->left->right = root2;
        root1->child->left = root2;
    }

    root1->degree++;
}

// Function to merge two Fibonacci Heaps
Node* mergeFibonacciHeaps(Node* heap1, Node* heap2) {
    if (heap1 == NULL) {
        return heap2;
    }

    if (heap2 == NULL) {
        return heap1;
    }

    Node* temp = heap1->right;
    heap1->right = heap2->right;
    heap2->right->left = heap1;
    heap2->right = temp;
    temp->left = heap2;

    return heap1;
}

// Function to perform the merge operation on two Fibonacci Heaps
Node* fibonacciHeapMerge(Node* heap1, Node* heap2) {
    Node* mergedHeap = mergeFibonacciHeaps(heap1, heap2);

    if (mergedHeap == NULL) {
        return NULL;
    }

    Node* minNode = mergedHeap;
    Node* current = mergedHeap->right;

    while (current != mergedHeap) {
        if (current->key < minNode->key) {
            minNode = current;
        }
        current = current->right;
    }

    return minNode;
}

// Function to print the elements of a Fibonacci Heap
void printFibonacciHeap(Node* minNode) {
    if (minNode == NULL) {
        printf("Heap is empty.\n");
        return;
    }

    printf("Fibonacci Heap elements: ");
    Node* current = minNode;
    do {
        printf("%d ", current->key);
        current = current->right;
    } while (current != minNode);
    printf("\n");
}

int main() {
    int key;
    Node* heap1 = NULL;
    Node* heap2 = NULL;

    // Get user input for the keys of the first Fibonacci Heap
    printf("Enter keys for the first Fibonacci Heap (enter -1 to stop):\n");
    while (1) {
        scanf("%d", &key);
        if (key == -1) {
            break;
        }
        Node* newNode = createNode(key);
        heap1 = mergeFibonacciHeaps(heap1, newNode);
    }

    // Get user input for the keys of the second Fibonacci Heap
    printf("Enter keys for the second Fibonacci Heap (enter -1 to stop):\n");
    while (1) {
        scanf("%d", &key);
        if (key == -1) {
            break;
        }
        Node* newNode = createNode(key);
        heap2 = mergeFibonacciHeaps(heap2, newNode);
    }

    // Merge the two Fibonacci Heaps
    Node* mergedHeap = fibonacciHeapMerge(heap1, heap2);

    // Print the merged Fibonacci Heap
    printFibonacciHeap(mergedHeap);

    // Free allocated memory (you would need to implement a proper free function)
    free(heap1);
    free(heap2);

    return 0;
}
