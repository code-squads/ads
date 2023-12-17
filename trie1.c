#include<stdio.h>
#include<stdlib.h>

#define ALPHABET_SIZE 26

struct TrieNode{
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
};

struct TrieNode* createNode(){
    struct TrieNode *newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if(newNode){
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

void insert(struct TrieNode *root, const char* word){
    struct TrieNode *current = root;
    while(*word){
        int index = *word - 'a';
        if(!current->children[index]){
            current->children[index] = createNode();
        }
        current = current->children[index];
        word++;
    }
    current->isEndOfWord = 1;
}

int search(struct TrieNode *root, const char* word){
    struct TrieNode *current = root;
    while(*word){
        int index = *word - 'a';
        if(!current->children[index]){
            return 0;
        }
        current = current->children[index];
        word++;
    }
    return current && current->isEndOfWord;
}

int main(){
    struct TrieNode *root = createNode();
    int op;
    while(op!=3){
        printf("1. Insert\n2.Search\n3.Exit\nEnter your Operation: ");
        scanf("%d",&op);
        if(op==1){
            char word[100];
            printf("Enter the word to be the inserted: ");
            scanf("%s",word);
            insert(root,word);
            continue;
        }
        else if(op==2){
            char word_search[100];
            printf("Enter the word to be the searched: ");
            scanf("%s",word_search);
            printf("Search for %s: %s\n",word_search,search(root,word_search)?"Found":"Not Found");
            continue;
        }
        else if(op==3){
            printf("Thankyou!!");
            break;
        }
    }
}
// 1. Insert
// 2.Search
// 3.Exit
// Enter your Operation: 1
// Enter the word to be the inserted: apple
// 1. Insert
// 2.Search
// 3.Exit
// Enter your Operation: 1
// Enter the word to be the inserted: mango
// 1. Insert
// 2.Search
// 3.Exit
// Enter your Operation: 2
// Enter the word to be the searched: app
// Search for app: Not Found
// 1. Insert
// 2.Search
// 3.Exit
// Enter your Operation: 2
// Enter the word to be the searched: apple