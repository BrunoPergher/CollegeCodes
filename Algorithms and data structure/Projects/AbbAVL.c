#include <stdio.h>
#include <stdlib.h>

// https://www.notion.so/Arvores-Binarias-6dec2b78b84a456a9040d5fc77f6393a

struct Node {
  int value;
  struct Node *left;
  struct Node *right;
  int height;
};

// Retorna Altura
int height(struct Node *N) {
  if (N == NULL) {
    return 0;
  }

  return N->height;
}

int max(int a, int b) { return (a > b) ? a : b; }

struct Node *newNode(int value) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;

  return (node);
}

// Rotação Para a Direita.
struct Node *rightRotate(struct Node *y) {
  struct Node *x = y->left;
  struct Node *z = x->right;

  //  3 -> y
  // 1  -> y left ou x
  //  2 -> x right ou z

  x->right = y;
  y->left = z;

  //  3 -> y
  // 2  -> y left ou x
  //  1 -> x right ou z

  // Calcula a altura
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

// Rotação Para a Esquerda.
struct Node *leftRotate(struct Node *x) {
  struct Node *y = x->right;
  struct Node *z = y->left;

  //  3     -> x
  //    4   -> x right ou Y
  //  2     -> y left ou z

  y->left = x;
  x->right = z;
  //  3     -> x
  //    2   -> x right ou Y
  //  4      -> y left ou z

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

// Fator de balanceamento
int getBalance(struct Node *N) {
  if (N == NULL) {
    return 0;
  }

  return height(N->left) - height(N->right);
}

// Inserir
struct Node *insertNode(struct Node *node, int value) {
  if (node == NULL) {
    return (newNode(value));
  }

  if (value <= node->value) {
    node->left = insertNode(node->left, value);
  } else if (value > node->value) {
    node->right = insertNode(node->right, value);
  } else {
    return node;
  }

  // Atualizando o balanceamento
  node->height = 1 + max(height(node->left), height(node->right));

  int balance = getBalance(node);
  // Pega o balanceamento

  // Rotação para direita
  if (balance > 1 && value < node->left->value) {
    return rightRotate(node);
  }

  // Rotação para esquerda
  if (balance < -1 && value > node->right->value) {
    return leftRotate(node);
  }

  // Rotação para esquerda e direita
  if (balance > 1 && value > node->left->value) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Rotação para direita e esquerda
  if (balance < -1 && value < node->right->value) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

struct Node *maxValueNode(struct Node *node) {
  struct Node *current = node;

  while (current->right != NULL) {
    current = current->right;
  }

  return current;
}

// Delete
struct Node *deleteNode(struct Node *root, int value) {
  if (root == NULL) {
    return root;
  }

  // Quando são folhas
  if (value < root->value) {
    root->left = deleteNode(root->left, value);
  } else if (value > root->value) {
    root->right = deleteNode(root->right, value);
  }

  // Quando não são folhas e precisa trocar
  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      struct Node *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else {
        *root = *temp;
      }

      free(temp);
    } else {
      struct Node *temp = maxValueNode(root->left);

      root->value = temp->value;

      root->left = deleteNode(root->left, temp->value);
    }
  }

  if (root == NULL) {
    return root;
  }

  // Atualiza o balanceamento
  root->height = 1 + max(height(root->left), height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0) {
    return rightRotate(root);
  }

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0) {
    return leftRotate(root);
  }

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

// Print the tree
void PrintTree(struct Node *root) {
  if (root != NULL) {
    printf(" %d (%i) \n", root->value, root->height);

    PrintTree(root->left);
    
    PrintTree(root->right);
  }
}

int main() {
  struct Node *root = NULL;

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

  PrintTree(root);

  return 0;
}