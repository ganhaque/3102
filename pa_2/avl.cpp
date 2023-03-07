#include <cstddef>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <algorithm>

using namespace std;

// AVL Tree Node
struct Node {
  int key;
  int data;
  int mindata;
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
Node* newNode(int key, int data) {
  Node* node = new Node();
  node->key = key;
  node->data = data;
  node->mindata = data;
  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;
  node->height = 1;
  return node;
}

void recalc_mindata(Node* node) {
  if (node == NULL) { // if node DNE, do nothing
    return;
  }

  // cout << "Recalc-ing node" << node->key << endl;

  node->mindata = node->data;
  if (node->left) {
    recalc_mindata(node->left);
    // cout << "current node: " << node->key << ", " << "left: " << node->left->mindata << endl;
    node->mindata = min(node->mindata, node->left->mindata);
  }
  if (node->right) {
    recalc_mindata(node->right);
    // cout << "current node: " << node->key << ", " << "right: " << node->right->mindata << endl;
    node->mindata = min(node->mindata, node->right->mindata);
  }
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

  recalc_mindata(y);

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

  recalc_mindata(y);

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
Node* insert(Node* node, int key, int data) {
  // Perform normal BST insertion
  if (node == NULL) { // found null
    return newNode(key, data);
  }
  if (key < node->key) { // go down left subtree
    node->left = insert(node->left, key, data);
    node->left->parent = node;
  }
  else if (key > node->key) { // go down right subtree
    // cout << "go down right subtree" << endl;
    node->right = insert(node->right, key, data);
    node->right->parent = node;
  }
  else { // key value already existed
    if (data < node->data) {
      node->data = data;
      while(node->parent) {
        if (node->parent->mindata > data) {
          node->parent->mindata = data;
        }
        else {
          break;
        }
      }
    }
    return node;
  }

  // Update mindata
  recalc_mindata(node);

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
  // recalc_mindata(node);
  // cout << "unchanged" << endl;
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
  cout << root->key << ", " << root->data << ", " << root->mindata << endl;
  printTree(root->left, depth+1);
}

int rangeMinSoFar(Node* node, int k1, int k2, int minSoFar = INT_MAX) {
  if (node == NULL) {
    return minSoFar;
  }
  if (node->key > k2) {
    return rangeMinSoFar(node->left, k1, k2, minSoFar);
  }
  if (node->key < k1) {
    return rangeMinSoFar(node->right, k1, k2, minSoFar);
  }

  // if within range
  minSoFar = min(minSoFar, node->mindata);
  minSoFar = min(minSoFar, rangeMinSoFar(node->right, k1, k2, minSoFar));
  minSoFar = min(minSoFar, rangeMinSoFar(node->left, k1, k2, minSoFar));
  return minSoFar;
}

int RangeMin(Node* node, int k1, int k2) {
  // if node DNE, return infinity/maximum possible value for type int
  if (node == NULL) {
    return INT_MAX;
  }
  // if current node's key is > k2, its right sub-tree is also > k2, search left
  if (node->key > k2) {
    // cout << "key is " << node->key << " range min go left" << endl;
    return RangeMin(node->left, k1, k2);
  }
  // if current node's key is < k1, its left sub-tree is also < k1, search right
  if (node->key < k1) {
    // cout << "key is " << node->key << " range min go right" << endl;
    return RangeMin(node->right, k1, k2);
  }
  // if key is within range, get the min of current, left, and right's valid sub-tree mindata
  // if (node->key >= k1 && node->key <= k2) {
  int minDat = min(node->data, RangeMin(node->left, k1, k2));
  minDat = min(minDat, RangeMin(node->right, k1, k2));
  // cout << "minDat of current key " << node->key << " is " << minDat << endl;
  return minDat;
  // }
}

// Driver function
int main() {
  Node* root = NULL;

  // create a sample binary search tree
  ifstream infile("inputFile.txt");
  // error checking
  if (!infile.is_open()) {
    cerr << "Unable to open input file." << endl;
    return -1;
  }

  // first line is number of instruction
  int numInstructions;
  infile >> numInstructions;

  // heap.printHeap();
  string instruction;

  for (int i = 0; i < numInstructions; i++) {
    infile >> instruction;
    if (instruction == "IN") {
      // cout << "in";
      int key;
      int data;
      infile >> key;
      infile >> data;
      root = insert(root, key, data);
      cout << "new tree:" << endl;
      printTree(root);
      cout << endl;
    }
    else if (instruction == "RMQ") {
      int i, newKey;
      int k1, k2;
      infile >> k1;
      infile >> k2;
      cout << RangeMin(root, k1, k2) << endl;
      // cout << rangeMinSoFar(root, k1, k2) << endl;
    }
  }

  // cout << "finale:" << endl;
  // recalc_mindata(root);
  // printTree(root);

  return 0;
}
