#include <cstddef>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <limits.h>
using namespace std;

// Definition for a binary tree node.
struct Node {
  int key;
  int data;
  int mindata;
  Node* left;
  Node* right;
  Node* parent;
  // Node(int x) : key(x), left(NULL), right(NULL), parent(NULL) {}
};

// Function to create a new node
Node* newNode(int key, int data) {
  Node* node = new Node();
  node->key = key;
  node->data = data;
  node->mindata = data;
  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;
  // node->height = 1;
  return node;
}


// Helper function for searching for a node in the tree.
Node* searchNode(Node* node, int key) {
  if (!node) {
    return NULL;
  }
  if (node->key == key) {
    return node;
  }
  else if (key < node->key) {
    return searchNode(node->left, key);
  }
  else {
    return searchNode(node->right, key);
  }
}

// Helper function for searching for the existence a node in the tree.
bool searchHelper(Node* node, int key) {
  if (!node) {
    return false;
  }
  if (node->key == key) {
    return true;
  } else if (key < node->key) {
    return searchHelper(node->left, key);
  } else {
    return searchHelper(node->right, key);
  }
}


// traversals
// preorder
void preorder(Node* node) {
  if (node == NULL) {
    return;
  }
  printf("%d ", node->key);
  preorder(node->left);
  preorder(node->right);
}
// inorder
void inorder(Node* node) {
  if (node == NULL) {
    return;
  }
  inorder(node->left);
  printf("%d ", node->key);
  inorder(node->right);
}

// Helper function for inserting a node into the tree.
Node* insert(Node* node, int key, int data) {
  if (!node) {
    return newNode(key, data);
  }
  if (data < node->mindata) {
    node->mindata = data;
  }
  if (key < node->key) {
    node->left = insert(node->left, key, data);
    node->left->parent = node;
  }
  else if (key > node->key) {
    node->right = insert(node->right, key, data);
    node->right->parent = node;
  }
  else { // same key
    node->data = data;
    // if (data < node->data) {
    //   node->data = data;
    //   while(node->parent) {
    //     if (node->parent->mindata > data) {
    //       node->parent->mindata = data;
    //     }
    //     else {
    //       break;
    //     }
    //   }
    // }

  }
  return node;
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

int RangeMinNaive(Node* node, int k1, int k2, int minSoFar) {
  // if node DNE, return infinity/maximum possible value for type int
  if (node == NULL) {
    return INT_MAX;
  }
  if (k1 <= node->key && node->key <= k2) {
    return min(node->data, minSoFar);
  }
  // if current node's key is > k2, its right sub-tree is also > k2, search left
  if (node->key > k2) {
    // cout << "key is " << node->key << " range min go left" << endl;
    return RangeMinNaive(node->left, k1, k2, minSoFar);
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

// print tree but rotated 90 degree anti-clockwise
void printTree(Node* root, int depth = 0) {
  if (root == NULL) {
    return;
  }
  printTree(root->right, depth+1);
  for (int i = 0; i < depth; i++) {
    cout << "    ";
  }
  // cout << root->key << endl;
  cout << root->key << ", " << root->data << ", " << root->mindata << endl;
  printTree(root->left, depth+1);
}

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
      // cout << "key is " << key << endl;
      root = insert(root, key, data);
      // cout << "new tree:" << endl;
      // printTree(root);
      // cout << endl;
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

