<h1 align="center">
    Homework 2
</h1>

<h4 align="center">Christian Che</h4>

1\.
Min-heap solution

Create a new empty min-heap and heapify with elements from B. The time complexity for this is $O(n)$ since we heapify n elements
```C++
minHeap = new empty min-heap
minHeap.heapify(B, B.size());
```

Next step is to find the minimum after k time. We can do this by calling extractMin k times and storing it inside an array to return. The time complexity of this is $O(k log n)$ since extractMin has the time complexity of log n, and it is called k times
```C++
arr = new empty array with size k
for(int i = 0; i < arr.size(); i++)  {
  arr[i] = minHeap.extractMin();
}
return arr;
```

Adding up the two steps, we end up with a time complexity of $O(n + k log n)$

---

2\.

| variable | description |
|----------|-------------|
start | the starting index of the desired portion (the i of B[i..j])
sum | keep track of the sum of the portion
Y | the required sum of portion
B | the input/given array

Here's the pseudo-code for the algorithm.
```C++
int sum = 0;
int start = 0;

for (int j = 0; j < B.size(); j++) {
  sum += B[j];
  while (sum > Y) {
    sum -= B[start];
    start += 1;
  }
  if (sum == Y) {
    return start, j;
  }
}
return -1, -1; // there are no contiguous portion w/ sum == Y
```
The loop update the sum, then if the sum is greater than Y, shrink down the portion from the left (update sum and start). Then check whether the sum of the portion is == Y. The algorithm will return -1, -1 if there are no valid contiguous portion (except when Y = 0, which would return 1,0, but Y should not be 0 anyway since the array only has positive integers).

The time complexity of this algorithm is $O(n)$. The `for` loop go through all elements inside B, which has the time complexity of $O(n)$. Although the `while` loop is inside another loop, it is bounded by n (the total number of times it is executed is at-most n times). $O(n + n) = O(2n) = O(n)$

---

3\.

Here's the algorithm implementation in C++.

```C++
void rangeReport(Node* node, int k1, int k2) {
  if (node == NULL) { // if node DNE, do nothing
    return;
  }
  if (node->key > k1) { // if key of current node is more than k1, recursive call the left sub-tree
    rangeReport(node->left, k1, k2);
  }
  if (node->key >= k1 && node->key <= k2) { // if within range, print the node's key
    cout << node->key << " ";
  }
  if (node->key < k2) {// if key of current node is less than k2, recursive call the right sub-tree
    rangeReport(node->right, k1, k2);
  }
}
```
The time complexity of the algorithm is $O(log n + output)$ because the algorithm only search the nodes and sub-trees that are potentially within the range k1 to k2 (sub-trees that will not yield any results are not explored) and output is just the time to print out the nodes' key.

---

4\.

Here's the implementation of `recalc_mindata` in C++

```C++
void recalc_mindata(Node* node) {
  if (node == NULL) { // if node DNE, do nothing
    return;
  }

  recalc_mindata(node->left);
  recalc_mindata(node->right);

  node->mindata = min(node->data, node->left->data, node->right->data);
}
```

To maintain the mindata field during a node rotation, make a call to recalc_mindata() with the rotated node's parent as input

Here's the implementation of `RangeMin` in C++
```C++
int RangeMin(Node* node, int k1, int k2) {
  // if node DNE, return infinity/maximum possible value for type int
  if (node == NULL) {
    return INT_MAX;
  }
  // if current node's key is > k2, its right sub-tree is also > k2, search left
  if (node->key > k2) {
    return RangeMin(node->left, k1, k2);
  }
   // if current node's key is < k1, its left sub-tree is also < k1, search right
  if (node->key < k1) {
    return RangeMin(node->right, k1, k2);
  }
  // if key is within range, get the min of current, left, and right's valid sub-tree mindata
  if (node->key >= k1 && node->key <= k2) {
    return min(node->mindata, RangeMin(node->left, k1, k2), RangeMin(node->right, k1, k2));
  }
}
```

Similar to question 3, the time complexity of the algorithm is $O(log n)$ because the algorithm only search the nodes and sub-trees that have the keys that are potentially within the range k1 to k2 (sub-trees that will not yield any results are not explored)

---

5\.

Here's the implementation of the algorithm in C++

```C++
int kthSmallest(int* arr, int n, int k) {
  // base case
  if (n == 1) {
    return arr[0];
  }

  // findMedian is the given function
  int median = findMedian(arr, n);

  // split the array into 2, one with elements <= median, and one with elements > median
  int right[n/2];
  int left[n - n/2];

  int leftIndex = 0;
  int rightIndex = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i] <= median) {
      left[leftIndex] = arr[i];
      leftIndex += 1;
    }
    else {
      right[rightIndex] = arr[i];
      rightIndex += 1;
    }
  }

  // if the size of left >= k, recursive call left
  if (leftIndex >= k) {
    return kthSmallest(left, leftIndex, k);
  }
  // if the size of left < k, recursive call right
  else {
    return kthSmallest(right, rightIndex, k - leftIndex);
  }
}
```

Assuming the median calculation does not factor into the time complexity calculation, the time complexity of the algorithm is $O(n)$. The number of elements the algorithm goes through can be written as $n + n/2 + n/4 + ... + n/n$ since the array is guaranteed to be about halved each recursive call.

Simplifying the expression, we get $n(1/2 + 1/4 + ... + 1/n)$.

$(1/2 + 1/4 + ... + 1/n)$ is a geometric series that has the sum of 1 $\implies$ the final time complexity is

$O(n*1) = O(n)$
