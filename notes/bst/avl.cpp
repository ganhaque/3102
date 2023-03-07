#include <iostream>

using namespace std;

// AVL Tree Node
struct Node {
  int key;
  Node* left;
  Node* right;
  Node* parent;
  int height;
};

// Function to get the height of a node
int height(Node* node) {
  if (node == NULL) {
    return 0;
  }
  return node->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
  return (a > b) ? a : b;
}

// Function to create a new node
Node* newNode(int key) {
  Node* node = new Node();
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;
  node->height = 1;
  return node;
}

// Function to perform a right rotation
Node* rightRotate(Node* x) {
    Node* y = x->left;
    Node* temp = y->right;

    // Perform rotation
    y->right = x;
    x->left = temp;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Update parent pointers
    y->parent = x->parent;
    x->parent = y;
    if (temp != NULL) {
        temp->parent = x;
    }

    // Return new root
    return y;
}

// Function to perform a left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;

    // Perform rotation
    y->left = x;
    x->right = temp;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Update parent pointers
    y->parent = x->parent;
    x->parent = y;
    if (temp != NULL) {
        temp->parent = x;
    }

    // Return new root
    return y;
}

// Function to get the balance factor of a node
int getBalance(Node* node) {
  if (node == NULL) {
    return 0;
  }
  return height(node->left) - height(node->right);
}

// Function to insert a node into the AVL tree
// The insert function takes in a node pointer and a key value to insert into the AVL tree. It first performs a normal BST insertion by recursively traversing down the tree until it finds a NULL pointer, and then creates a new node with the given key value.
//
// If the key value already exists in the tree, the function simply returns the node pointer without performing any insertions.
//
// After the normal BST insertion, the function updates the height of the current node and calculates its balance factor. If the node becomes unbalanced (i.e., balance factor is greater than 1 or less than -1), the function performs one of the four possible rotations to rebalance the tree.
//
// Finally, the function returns the (possibly modified) node pointer.
Node* insert(Node* node, int key) {
  // Perform normal BST insertion
  if (node == NULL) { // found null
    return newNode(key);
  }
  if (key < node->key) { // go down left subtree
    node->left = insert(node->left, key);
    node->left->parent = node;
  }
  else if (key > node->key) { // go down right subtree
    node->right = insert(node->right, key);
    node->right->parent = node;
  }
  else { // key value already existed
    return node;
  }

  // Update height of this node
  node->height = 1 + max(height(node->left), height(node->right));

  // Get the balance factor of this node
  int balance = getBalance(node);

  // If this node becomes unbalanced, then there are 4 cases

  // Left Left Case
  if (balance > 1 && key < node->left->key) {
    return rightRotate(node);
  }

  // Right Right Case
  if (balance < -1 && key > node->right->key) {
    return leftRotate(node);
  }

  // Left Right Case
  if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Right Left Case
  if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  // Return the (unchanged) node pointer
  return node;
}

// Function to print the AVL tree in inorder traversal
void inorder(Node* root) {
  if (root != NULL) {
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
  }
}
void rangeReport(Node* node, int k1, int k2) {
  if (node == NULL) {
    return;
  }
  if (node->key > k1) {
    rangeReport(node->left, k1, k2);
  }
  if (node->key >= k1 && node->key <= k2) { // if within range
    cout << node->key << " ";
  }
  if (node->key < k2) {
    rangeReport(node->right, k1, k2);
  }
}

void printTree(Node* root, int depth = 0) {
  if (root == NULL) {
    return;
  }
  printTree(root->right, depth+1);
  for (int i = 0; i < depth; i++) {
    cout << "    ";
  }
  cout << root->key << endl;
  printTree(root->left, depth+1);
}

// Driver function
int main() {
  Node* root = NULL;
  // Insert nodes into the AVL tree
  root = insert(root, 10);
  root = insert(root, 20);
  cout << root->right->height << endl;
  root = insert(root, 30);
  root = insert(root, 40);
  root = insert(root, 50);
  root = insert(root, 25);

  // Print the AVL tree in inorder traversal
  cout << "Inorder traversal of the AVL tree: " << endl;
  inorder(root);
  cout << endl;
  printTree(root);
  cout << "Range report test:" << endl;
  rangeReport(root, 10, 30);

  return 0;
}
