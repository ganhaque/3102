#include <cstddef>
#include <cstdio>
#include <iostream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
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
TreeNode* insertHelperNode(TreeNode* root, TreeNode* node) {
  if (!root) {
    return node;
  }
  if (node->val < root->val) {
    root->left = insertHelperNode(root->left, node);
    root->left->parent = root;
  }
  else {
    root->right = insertHelperNode(root->right, node);
    root->right->parent = root;
  }
  return root;
}
void insertNode(TreeNode* root, TreeNode* node) {
  if (root->val > node->val) {
    if ( root->left ) {
      insertNode(root->left, node);
    }
    else {
      root->left = node;
    }
  }
  else if (root->val < node->val) {
    if ( root->right ) {
      insertNode(root->right, node);
    }
    else {
      root->right = node;
    }
  }
}

// Helper function for inserting a node into the tree.
TreeNode* insertHelper(TreeNode* root, int key) {
  if (!root) {
    return new TreeNode(key);
  }
  if (key < root->val) {
    root->left = insertHelper(root->left, key);
    root->left->parent = root;
  }
  else {
    root->right = insertHelper(root->right, key);
    root->right->parent = root;
  }
  return root;
}
TreeNode* insertHelperC(TreeNode* root, int key) {
  if (!root) {
    // return new TreeNode(key);
    struct TreeNode* new_node = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    new_node->val = key;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
  }
  if (key < root->val) {
    root->left = insertHelper(root->left, key);
  }
  else {
    root->right = insertHelper(root->right, key);
  }
  return root;
}

// Helper function to delete a node from the tree.
TreeNode* deleteNodeHelper(TreeNode* root, int key) {
  // base case
  if (!root) {
    return root;
  }

  // If the key to be deleted is smaller than the root's key,
  // then it lies in left subtree
  if (key < root->val) {
    root->left = deleteNodeHelper(root->left, key);
  }
  // If the key to be deleted is greater than the root's key,
  // then it lies in right subtree
  else if (key > root->val) {
    root->right = deleteNodeHelper(root->right, key);
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
    root->right = deleteNodeHelper(root->right, temp->val);
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
  root = insertHelper(root, 10);
  root = insertHelper(root, 7);
  root = insertHelper(root, 15);
  root = insertHelper(root, 3);
  root = insertHelper(root, 9);
  root = insertHelper(root, 12);
  root = insertHelper(root, 20);
  root = insertHelper(root, 8);
  root = insertHelper(root, 11);

  printTree(root);
  
  // search and print the minimum and maximum node values
  TreeNode* minNode = findMin(root);
  TreeNode* maxNode = findMax(root);
  cout << "Minimum node value: " << minNode->val << endl;
  cout << "Maximum node value: " << maxNode->val << endl;
  
  // search for node with value 12
  TreeNode* node12 = searchNode(root, 12);
  if (node12) {
    cout << "Node with value 12 found." << endl;
  } else {
    cout << "Node with value 12 not found." << endl;
  }
  
  // search for node with value 100
  bool found100 = searchHelper(root, 100);
  if (found100) {
    cout << "Node with value 100 found." << endl;
  } else {
    cout << "Node with value 100 not found." << endl;
  }
  
  // find the predecessor and successor of node with value 9
  TreeNode* node9 = searchNode(root, 9);
  TreeNode* pred9 = findPredecessor(node9);
  TreeNode* succ9 = findSuccessor(node9);
  if (pred9) {
    cout << "Predecessor of node with value 9: " << pred9->val << endl;
  } else {
    cout << "No predecessor found for node with value 9." << endl;
  }
  if (succ9) {
    cout << "Successor of node with value 9: " << succ9->val << endl;
  } else {
    cout << "No successor found for node with value 9." << endl;
  }

  cout << "test inorder:" << endl;
  inorder(root);
  printf("\n");
  cout << "test preorder:" << endl;
  preorder(root);
  printf("\n");
  
  // delete the node with value 7 from the tree
  root = deleteNodeHelper(root, 7);

cout << "Binary search tree after deleting node with value 7:" << endl;
  printTree(root);
  inorder(root);
  printf("\n");

  cout << "test preorder:" << endl;
  preorder(root);
  printf("\n");
  
  return 0;
}
