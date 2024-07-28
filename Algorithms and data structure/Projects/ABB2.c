#include <stdio.h>
#include <stdlib.h>

// https://www.notion.so/Arvores-Binarias-6dec2b78b84a456a9040d5fc77f6393a

struct node {
  int value;
  struct node *left, *right;
};

struct node *newNode(int item) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->value = item;
  temp->left = temp->right = NULL;
  return temp;
}

// Imprime a arvore pela esquerda
void printTree(struct node *root) {
  if (root != NULL) {
    printTree(root->left);
    printf(" %d ", root->value);
    printTree(root->right);
  }
}

struct node *insertNode(struct node *node, int value) {
  if (node == NULL) {
    return newNode(value);
  }

  // recursividade para percorrer a arvore esquerda ou direita
  if (value < node->value) {
    node->left = insertNode(node->left, value);
  } else {
    node->right = insertNode(node->right, value);
  }

  return node;
}

// menor valor
struct node *minValueNode(struct node *node) {
  struct node *current = node;

  while (current && current->left != NULL) {
    current = current->left;
  }

  return current;
}

struct node *deleteNode(struct node *root, int value) {
  if (root == NULL) {
    return root;
  }

  // esquerda se valor <  root
  if (value < root->value) {
    root->left = deleteNode(root->left, value);
  }

  // direita se for valor > root
  else if (value > root->value) {
    root->right = deleteNode(root->right, value);
  }

  else {
    // unico filho ou nenhum
    if (root->left == NULL) {
      struct node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      struct node *temp = root->left;
      free(root);
      return temp;
    }

    // se 2 filhos ou mais pega o menor na subtree da direita para substituir
    struct node *temp = minValueNode(root->right);

    // transfere as informações
    root->value = temp->value;

    // enfim deleta o valor
    root->right = deleteNode(root->right, temp->value);
  }

  return root;
}

int main() {
  struct node *root = NULL;

  root = insertNode(root, 15);
  root = insertNode(root, 25);
  root = insertNode(root, 35);
  root = insertNode(root, 45);
  root = insertNode(root, 65);
  root = insertNode(root, 55);
  root = insertNode(root, 44);
  root = insertNode(root, 34);
  root = insertNode(root, 24);
  root = insertNode(root, 10);
  root = insertNode(root, 15);
  root = deleteNode(root, 25);
  root = deleteNode(root, 35);
  root = deleteNode(root, 15);
  root = insertNode(root, 42);
  root = insertNode(root, 40);
  root = insertNode(root, 43);
  root = deleteNode(root, 44);
  root = insertNode(root, 60);
  root = insertNode(root, 70);
  root = insertNode(root, 50);
  root = insertNode(root, 67);
  root = insertNode(root, 64);
  root = deleteNode(root, 65);

  printTree(root);

  return 0;
}