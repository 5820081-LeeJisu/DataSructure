#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* right, * left;
} TreeNode;

typedef struct ThreadNode {
    int data;
    int thread;
    struct ThreadNode* right, * left;
} ThreadNode;

TreeNode* new_node(int key) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->data = key;
    temp->right = temp->left = NULL;
    return temp;
}

ThreadNode* new_thread_node(int key) {
    ThreadNode* temp = (ThreadNode*)malloc(sizeof(ThreadNode));
    temp->data = key;
    temp->right = temp->left = NULL;
    temp->thread = 0;
    return temp;
}

TreeNode* insert_node(TreeNode* root, int key) {
    if (root == NULL) {
        return new_node(key);
    }
    if (root->data == NULL)
        return root;
    else if (root->data < key)
        root->right = insert_node(root->right, key);
    else
        root->left = insert_node(root->left, key);

    return root;
}

void insert_thread_node(ThreadNode** root, int key) {
    if (*root == NULL) {
        *root = new_thread_node(key);
        (*root)->thread = 1;
        (*root)->right = NULL;
        return;
    }

    ThreadNode* current = *root;
    ThreadNode* newNode = new_thread_node(key);

    while (current != NULL) {
        if (key < current->data) {
            if (current->left == NULL) {
                current->left = newNode;
                newNode->thread = 1;
                newNode->right = current;
                break;
            }
            else {
                current = current->left;
            }
        }
        else {
            if (current->thread == 1) {
                current->thread = 0;
                newNode->thread = 1;
                newNode->right = current->right;
                current->right = newNode;
                break;
            }
            else {
                current = current->right;
            }
        }
    }
}

TreeNode* GenerateBinaryTree(int inputData[]) {
    TreeNode* root = NULL;
    for (int i = 0; i < 15; i++) {
        root = insert_node(root, inputData[i]);
    }
    return root;
}

ThreadNode* GenerateThreadTree(int inputData[]) {
    ThreadNode* root = NULL;
    for (int i = 0; i < 15; i++) {
        insert_thread_node(&root, inputData[i]);
    }
    return root;
}

ThreadNode* find_successor(ThreadNode* root) {
    ThreadNode* pright = root->right;

    if (pright == NULL || root->thread == 1)
        return pright;
    while (pright->left != NULL)
        pright = pright->left;

    return pright;
}

void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* r;
    r = root;
    while (r->left)
        r = r->left;
    do {
        printf("%d ", r->data);
        r = find_successor(r);
    } while (r);
}

int main() {
    int size = 0;
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };

    TreeNode* root = GenerateBinaryTree(inputData);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);

    ThreadNode* troot = GenerateThreadTree(inputData);
    printf("\nThread tree inorder: ");
    ThreadTreeInOrder(troot);

    free(root);
    free(troot);
    return 0;
}
