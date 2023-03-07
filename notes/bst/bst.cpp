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

class BST {
  private:
    TreeNode* root;

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
        return findMin( root->right );
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
        return findMax( root->left );
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
    // void insertNode(TreeNode* root, TreeNode* node) {
    //   if (root->val > node->val) {
    //     if ( root->left ) {
    //       insertNode(root->left, node);
    //     }
    //     else {
    //       root->left = node;
    //     }
    //   }
    //   else if (root->val < node->val) {
    //     if ( root->right ) {
    //       insertNode(root->right, node);
    //     }
    //     else {
    //       root->right = node;
    //     }
    //   }
    // }

    // Helper function for inserting a node into the tree.
    TreeNode* insertHelper(TreeNode* root, int key) {
      if (!root) {
        return new TreeNode(key);
      }
      if (key < root->val) {
        root->left = insertHelper(root->left, key);
      }
      else {
        root->right = insertHelper(root->right, key);
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


    // Helper function for deleting a node from the tree.
    TreeNode* deleteHelper(TreeNode* root, int key) {
      if (!root) {
        return NULL;
      }
      if (key < root->val) {
        root->left = deleteHelper(root->left, key);
        if (root->left) {
          root->left->parent = root;
        }
      }
      else if (key > root->val) {
        root->right = deleteHelper(root->right, key);
        if (root->right) {
          root->right->parent = root;
        }
      }
      else {
        // Case 1: Node has no children.
        if (!root->left && !root->right) {
          delete root;
          root = NULL;
        }
        // Case 2: Node has one child.
        else if (!root->left || !root->right) {
          TreeNode* temp = root->left ? root->left : root->right;
          temp->parent = root->parent;
          delete root;
          root = temp;
        }
        // Case 3: Node has two children.
        else {
          TreeNode* temp = findMin(root->right);
          root->val = temp->val;
          root->right = deleteHelper(root->right, temp->val);
          if (root->right) {
            root->right->parent = root;
          }
        }
      }
      return root;
    }


    // Helper function for deleting a node from the tree.
    TreeNode* deleteHelperOld(TreeNode* root, int val) {
      // if (!root) {
      //   return NULL;
      // }
      if (root == NULL) {
        return NULL;
      }
      if (val < root->val) {
        root->left = deleteHelper(root->left, val);
      } else if (val > root->val) {
        root->right = deleteHelper(root->right, val);
      } else {
        // Found the node to delete.
        if (!root->left && !root->right) {
          // Case 1: Node has no children.
          delete root;
          root = NULL;
        } else if (!root->left) {
          // Case 2: Node has one child (right child).
          TreeNode* temp = root;
          root = root->right;
          delete temp;
        } else if (!root->right) {
          // Case 2: Node has one child (left child).
          TreeNode* temp = root;
          root = root->left;
          delete temp;
        } else {
          // Case 3: Node has two children.
          // Find the minimum value in the right subtree (or maximum value in the left subtree).
          TreeNode* temp = root->right;
          while (temp->left) {
            temp = temp->left;
          }
          root->val = temp->val;
          root->right = deleteHelper(root->right, temp->val);
        }
      }
      return root;
    }

  public:
    // constructor
    BST() : root(NULL) {}

    // Public function for inserting a node into the tree.
    void insert(int val) {
      root = insertHelper(root, val);
    }

    // Public function for searching for a node in the tree.
    // bool search(int val) {
    //   return searchHelper(root, val);
    // }

    // Public function for deleting a node from the tree.
    void deleteNode(int val) {
      root = deleteHelper(root, val);
    }

    // Check if a node exists in the tree.
    bool search(int key) {
      return searchHelper(root, key);
    }

    // Find the node with the minimum value in the tree.
    TreeNode* findMinimum() {
      return findMin(root);
    }

    // Find the node with the maximum value in the tree.
    TreeNode* findMaximum() {
      return findMax(root);
    }

    // search for a node successor
    TreeNode* successor(TreeNode* node) {
      return findSuccessor(node);
    }

    // search for a node predecessor
    TreeNode* predecessor(TreeNode* node) {
      return findPredecessor(node);
    }

    // traversals
    // preorder
    void preorderTraversal() {
      preorder(root);
      printf("\n");
    }

    // inorder
    void inorderTraversal() {
      inorder(root);
      printf("\n");
    }
};
int main() {
  BST bst;

  // insert some nodes
  bst.insert(8);
  bst.insert(3);
  bst.insert(1);
  bst.insert(6);
  bst.insert(7);
  bst.insert(10);
  bst.insert(14);
  bst.insert(4);

  // print the minimum and maximum values
  printf("Minimum value: %d\n", bst.findMinimum()->val);
  printf("Maximum value: %d\n", bst.findMaximum()->val);

  // print whether certain nodes are in the tree or not
  printf("%d is%s in the tree.\n", 6, bst.search(6) ? "" : " not");
  printf("%d is%s in the tree.\n", 5, bst.search(5) ? "" : " not");

  // perform traversals
  printf("Preorder traversal: ");
  bst.preorderTraversal();
}

