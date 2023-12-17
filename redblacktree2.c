#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct TreeNode {
    int data;
    int color; // 0 for red, 1 for black
    struct TreeNode* parent;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* root = NULL;

struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = value;
    newNode->color = RED; // New node is always red
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void leftRotate(struct TreeNode* currentNode) {
    struct TreeNode* rightChild = currentNode->right;
    currentNode->right = rightChild->left;
    if (rightChild->left != NULL)
        rightChild->left->parent = currentNode;
    rightChild->parent = currentNode->parent;
    if (currentNode->parent == NULL)
        root = rightChild;
    else if (currentNode == currentNode->parent->left)
        currentNode->parent->left = rightChild;
    else
        currentNode->parent->right = rightChild;
    rightChild->left = currentNode;
    currentNode->parent = rightChild;
}

void rightRotate(struct TreeNode* currentNode) {
    struct TreeNode* leftChild = currentNode->left;
    currentNode->left = leftChild->right;
    if (leftChild->right != NULL)
        leftChild->right->parent = currentNode;
    leftChild->parent = currentNode->parent;
    if (currentNode->parent == NULL)
        root = leftChild;
    else if (currentNode == currentNode->parent->left)
        currentNode->parent->left = leftChild;
    else
        currentNode->parent->right = leftChild;
    leftChild->right = currentNode;
    currentNode->parent = leftChild;
}

void fixInsert(struct TreeNode* newNode) {
    while (newNode != NULL && newNode->parent != NULL && newNode->parent->color == RED) {
        if (newNode->parent == newNode->parent->parent->left) {
            struct TreeNode* uncle = newNode->parent->parent->right;
            if (uncle != NULL && uncle->color == RED) {
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            } else {
                if (newNode == newNode->parent->right) {
                    newNode = newNode->parent;
                    leftRotate(newNode);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                rightRotate(newNode->parent->parent);
            }
        } else {
            struct TreeNode* uncle = newNode->parent->parent->left;
            if (uncle != NULL && uncle->color == RED) {
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            } else {
                if (newNode == newNode->parent->left) {
                    newNode = newNode->parent;
                    rightRotate(newNode);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                leftRotate(newNode->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void insert(int value) {
    struct TreeNode* newNode = createNode(value);
    struct TreeNode* parentNode = NULL;
    struct TreeNode* currentNode = root;

    while (currentNode != NULL) {
        parentNode = currentNode;
        if (newNode->data < currentNode->data)
            currentNode = currentNode->left;
        else
            currentNode = currentNode->right;
    }

    newNode->parent = parentNode;

    if (parentNode == NULL)
        root = newNode;
    else if (newNode->data < parentNode->data)
        parentNode->left = newNode;
    else
        parentNode->right = newNode;

    fixInsert(newNode);
}

void inOrder(struct TreeNode* node) {
    if (node != NULL) {
        inOrder(node->left);
        printf("(%d, %s) ", node->data, (node->color == RED) ? "RED" : "BLACK");
        inOrder(node->right);
    }
}

int main() {
    int op;
    while(op!=3){
        printf("1.Insert\n2.Display\n3.Exit\nEnter your operation:");
        scanf("%d",&op);
        if(op==1){
            int num;
            printf("Enter the element to insert:");
            scanf("%d",&num);
            insert(num);
        }
        else if(op==2){
            printf("In-order Traversal of Red-Black Tree: ");
            inOrder(root);
        }
        else if(op==3){
            break;
        }
    }
    return 0;
}