#include<stdio.h>
#include<stdlib.h>

#define ALPHABET_SIZE 26

struct TrieNode{
    struct TrieNode *children[100];
    int isEndOfWord;
};

struct TrieNode* createNode(){
    struct TrieNode *newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    newNode->isEndOfWord = 0;
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

int isLeafNode(struct TrieNode *node){
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if(node->children[i]){
            return 0;
        }
    }
    return 1;
}

int delete(struct TrieNode *root, const char* word){
    struct TrieNode *current = root;
    struct TrieNode *path[100];
    int pathIndex = 0;
    
    while(*word){
        int index = *word - 'a';
        if(!current->children[index]){
            return 0;
        }
        path[pathIndex++] = current;
        current = current->children[index];
        word++;
    }
    
    if(!current->isEndOfWord){
        return 0;
    }
    current->isEndOfWord = 0;
    
    if(isLeafNode(current)){
        for (int i = pathIndex-1; i >=0; i--) {
            int index = word[i] - 'a';
            free(path[i]->children[index]);
            path[i]->children[index] = NULL;
            
            if(!isLeafNode(path[i])){
                break;
            }
        }
    }
    return 1;
}

int main(){
    struct TrieNode *root = createNode();
    int op;
    while(op!=3){
        printf("1.Insert\n2.Delete\n3.Exit\nEnter your operation: ");
        scanf("%d",&op);
        
        if(op==1){
            printf("Enter the word to insert: ");
            char word[100];
            scanf("%s",word);
            insert(root,word);
        }
        else if(op==2){
            printf("Enter the word to delete: ");
            char word_delete[100];
            scanf("%s",word_delete);
            printf("Delete %s: %s",word_delete,delete(root, word_delete)?"Success":"Not Found");
        }
        else if(op==3){
            break;
        }
    }
}
// 1.Insert
// 2.Delete
// 3.Exit
// Enter your operation: 1
// Enter the word to insert: apple
// 1.Insert
// 2.Delete
// 3.Exit
// Enter your operation: 1
// Enter the word to insert: mango
// 1.Insert
// 2.Delete
// 3.Exit
// Enter your operation: 2
// Enter the word to delete: app
// Delete app: Not Found1.Insert
// 2.Delete
// 3.Exit
// Enter your operation: 2
// Enter the word to delete: apple
// Delete apple: Success1.Insert