### Insertion in BST
```C
void Insert( Node *x, Node *z ) {
  if ( x->key > z->key ) {
    if ( x->left ) Insert( x->left, z );
    else x->left = z ;
  }
  else if ( x->key < z->key ) {
    if ( x->right ) Insert( x->right, z );
    else x->right = z ;
  }
}
```
Then, insertion is done by Insert(r, z), where r = pointer to root of BST


### Deletion in BST

Let N be a node to be deleted

1. Case 1: N is a leaf, just remove N
2. Case 2: N has 1 child, connect N's parent to its child
2. Case 3: N has 2 child, swap N with its successor, then remove N

### Traversals

Visit orders

Preorder
- root -> left -> right
```C
Preorder(Node *x){
  if (x==NULL) return;
  Print(x);
  Preorder(x->left);
  Preorder(x->right);
}
```

Inorder
- left -> root -> right
```C
Inorder(Node *x){
  if (x==NULL) return;
  Inorder(x->left);
  Print(x);
  Inorder(x->right);
}
```

Postorder
- left -> right -> root

### Predecessor & Successor

#### Finding successor of a given node N

If N has a right child, then successor is the smallest key in N's right subtree (go right then follow the leftmost path until you reach leaf node)

Otherwise, successor would be the first ancestor of N whose left child is also an ancestor of N (go up toward root, if there is node X such that N is the left child of X, then the successor is X, if reach root w/o such a node, then no successor)



### Rotation

After rotation, the inorder traversal ordering remains unchanged.
