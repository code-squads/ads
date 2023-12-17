#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
 
#define FILTER_SIZE 1000
 
typedef struct {
    uint8_t *array;
    size_t size;
} BloomFilter;
 
void initializeFilter(BloomFilter *filter, size_t size) {
    filter->array = (uint8_t *)calloc((size + 7) / 8, sizeof(uint8_t));
    filter->size = size;
}
 
void addElement(BloomFilter *filter, const char *element) {
    // Implement a hash function (e.g., djb2)
    unsigned long hash = 5381;
    int c;
    while ((c = *element++) != 0)
        hash = ((hash << 5) + hash) + c;
 
    // Set corresponding bits in the array
    hash %= filter->size;
    filter->array[hash / 8] |= (1 << (hash % 8));
}
 
int isElementPresent(BloomFilter *filter, const char *element) {
    // Implement the same hash function as in addElement
    unsigned long hash = 5381;
    int c;
    while ((c = *element++) != 0)
        hash = ((hash << 5) + hash) + c;
 
    // Check if all corresponding bits are set
    hash %= filter->size;
    return (filter->array[hash / 8] & (1 << (hash % 8))) != 0;
}
 
void freeFilter(BloomFilter *filter) {
    free(filter->array);
}
 
int main() {
    BloomFilter filter;
    char element[50];
 
    printf("Enter the size of the Bloom filter: ");
    size_t size;
    scanf("%zu", &size);
 
    initializeFilter(&filter, size);
 
    printf("Enter elements to add to the Bloom filter (enter 'done' to stop):\n");
    while (1) {
        scanf("%s", element);
        if (strcmp(element, "done") == 0) {
            break;
        }
        addElement(&filter, element);
    }
 
    printf("Enter elements to check in the Bloom filter (enter 'done' to stop):\n");
    while (1) {
        scanf("%s", element);
        if (strcmp(element, "done") == 0) {
            break;
        }
        if (isElementPresent(&filter, element)) {
            printf("%s is probably in the set.\n", element);
        } else {
            printf("%s is definitely not in the set.\n", element);
        }
    }
 
    freeFilter(&filter);
 
    return 0;
}