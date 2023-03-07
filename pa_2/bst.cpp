#include <cstddef>
#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  int data;
  int mindata;
  TreeNode* left;
  TreeNode* right;
  TreeNode* parent;
  TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
};

// Helper function to find the node with the minimum value in the tree.
TreeNode* findMin(TreeNode* root) {
  if (!root) {
    return NULL;
  }
  while (root->left != NULL) {
    root = root->left;
  }
  return root;
}

TreeNode* findMax(TreeNode* root) {
  if (!root) {
    return NULL;
  }
  while (root->right != NULL) {
    root = root->right;
  }
  return root;
}

// Helper function for searching for a node in the tree.
TreeNode* searchNode(TreeNode* node, int val) {
  if (!node) {
    return NULL;
  }
  if (node->val == val) {
    return node;
  }
  else if (val < node->val) {
    return searchNode(node->left, val);
  }
  else {
    return searchNode(node->right, val);
  }
}

// Helper function for searching for the existence a node in the tree.
bool searchHelper(TreeNode* node, int val) {
  if (!node) {
    return false;
  }
  if (node->val == val) {
    return true;
  } else if (val < node->val) {
    return searchHelper(node->left, val);
  } else {
    return searchHelper(node->right, val);
  }
}

// search for a node successor
TreeNode* findSuccessor(TreeNode* node) {
  // Case 1: has right child. Find the minimum in the right subtree
  if (node-> right != NULL) {
    return findMin(node->right);
  }
  // Case 2: no right child. Find the first ancestor whose left child is also an ancestor.
  TreeNode* temp = node;
  // loop until temp is on the left of temp->parent or reach root
  while (temp->parent != NULL && temp == temp->parent->right) {
    temp = temp->parent;
  }
  return temp->parent;
}

// search for a node successor
TreeNode* findPredecessor(TreeNode* node) {
  // Case 1: has left child. Find the maximum in the left subtree
  if (node-> left != NULL) {
    return findMax(node->left);
  }
  // Case 2: no left child. Find the first ancestor whose right child is also an ancestor.
  TreeNode* temp = node;
  // loop until temp is on the right of temp->parent or reach root
  while (temp->parent != NULL && temp == temp->parent->left) {
    temp = temp->parent;
  }
  return temp->parent;
}

// traversals
// preorder
void preorder(TreeNode* node) {
  if (node == NULL) {
    return;
  }
  printf("%d ", node->val);
  preorder(node->left);
  preorder(node->right);
}
// inorder
void inorder(TreeNode* node) {
  if (node == NULL) {
    return;
  }
  inorder(node->left);
  printf("%d ", node->val);
  inorder(node->right);
}

// Helper function for inserting a node into the tree.
TreeNode* insertKey(TreeNode* root, int key) {
  if (!root) {
    return new TreeNode(key);
  }
  if (key < root->val) {
    root->left = insertKey(root->left, key);
    root->left->parent = root;
  }
  else {
    root->right = insertKey(root->right, key);
    root->right->parent = root;
  }
  return root;
}

// Helper function to delete a node from the tree.
TreeNode* deleteKey(TreeNode* root, int key) {
  // base case
  if (!root) {
    return root;
  }

  // If the key to be deleted is smaller than the root's key,
  // then it lies in left subtree
  if (key < root->val) {
    root->left = deleteKey(root->left, key);
  }
  // If the key to be deleted is greater than the root's key,
  // then it lies in right subtree
  else if (key > root->val) {
    root->right = deleteKey(root->right, key);
  }
  // if key is same as root's key, then This is the node
  // to be deleted
  else {
    // node with only one child or no child
    if (!root->left) {
      TreeNode* temp = root->right;
      free(root);
      return temp;
    }
    else if (!root->right) {
      TreeNode* temp = root->left;
      free(root);
      return temp;
    }

    // node with two children: Get the inorder successor (smallest
    // in the right subtree)
    TreeNode* temp = findMin(root->right);

    // Copy the inorder successor's content to this node
    root->val = temp->val;

    // Delete the inorder successor
    root->right = deleteKey(root->right, temp->val);
  }
  return root;
}

// print tree but rotated 90 degree anti-clockwise
void printTree(TreeNode* root, int depth = 0) {
  if (root == NULL) {
    return;
  }
  printTree(root->right, depth+1);
  for (int i = 0; i < depth; i++) {
    cout << "    ";
  }
  cout << root->val << endl;
  printTree(root->left, depth+1);
}

int main() {
  TreeNode* root = NULL;

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

  // Heap heap(1'000'001);
  // the heap maximum size is if all instruction are IN
  // Heap heap(numInstructions);

  // heap.printHeap();
  string instruction;

  for (int i = 0; i < numInstructions; i++) {
    infile >> instruction;
    if (instruction == "IN") {
      int key;
      int data;
      infile >> key;
      infile >> data;
      // heap.insert(key);
      // heap.printHeap();
    } else if (instruction == "DK") {
      int i, newKey;
      infile >> i >> newKey;
      // heap.decreaseKey(i, newKey);
      // heap.printHeap();
    } else if (instruction == "EM") {
      if ( i == numInstructions - 1 )  {
        // cout << "proc";
        // cout << heap.extractMin() << endl;
      }
      else {
        // heap.extractMin();
      }
      // heap.printHeap();
    }
  }

  return 0;
}
