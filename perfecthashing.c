#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100

struct Node {
    int key;
    struct Node* next;
};

struct Bucket {
    struct Node* chain;
};

struct PerfectHashTable {
    int size;
    struct Bucket* table;
};

struct HashFunction {
    int a;
    int b;
};

int hash(struct HashFunction hf, int key, int size) {
    return ((hf.a * key + hf.b) % INT_MAX) % size;
}

struct PerfectHashTable* createPerfectHashTable(int* keys, int n) {
    struct PerfectHashTable* pht = (struct PerfectHashTable*)malloc(sizeof(struct PerfectHashTable));
    pht->size = n * n; // Size of the hash table is the square of the number of keys

    // Allocate memory for the hash table
    pht->table = (struct Bucket*)malloc(pht->size * sizeof(struct Bucket));

    // Initialize buckets
    for (int i = 0; i < pht->size; i++) {
        pht->table[i].chain = NULL;
    }

    // Generate hash functions for each bucket
    struct HashFunction* hashFunctions = (struct HashFunction*)malloc(pht->size * sizeof(struct HashFunction));

    for (int i = 0; i < pht->size; i++) {
        hashFunctions[i].a = rand() % (pht->size - 1) + 1; // a should be non-zero and less than the size
        hashFunctions[i].b = rand() % pht->size;
    }

    // Insert keys into the perfect hash table
    for (int i = 0; i < n; i++) {
        int h1 = hash(hashFunctions[i], keys[i], pht->size);

        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->key = keys[i];
        newNode->next = pht->table[h1].chain;
        pht->table[h1].chain = newNode;
    }

    free(hashFunctions);
    return pht;
}

void printPerfectHashTable(struct PerfectHashTable* pht) {
    printf("Perfect Hash Table:\n");

    for (int i = 0; i < pht->size; i++) {
        printf("%d: ", i);
        struct Node* current = pht->table[i].chain;

        while (current != NULL) {
            printf("%d -> ", current->key);
            current = current->next;
        }

        printf("NULL\n");
    }
}

int main() {
    int n;

    printf("Enter the number of keys: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAXN) {
        printf("Invalid number of keys. Exiting.\n");
        return 1;
    }

    int* keys = (int*)malloc(n * sizeof(int));

    printf("Enter the keys:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &keys[i]);
    }

    struct PerfectHashTable* pht = createPerfectHashTable(keys, n);
    printPerfectHashTable(pht);

    // Free memory
    for (int i = 0; i < pht->size; i++) {
        struct Node* current = pht->table[i].chain;
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(pht->table);
    free(pht);
    free(keys);

    return 0;
}

