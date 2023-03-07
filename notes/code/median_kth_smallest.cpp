#include <algorithm>
#include <iostream>

using namespace std;

int findMedian(int* arr, int n) {
  return 0;
}

int kthSmallest(int* arr, int n, int k) {
  // base case
  if (n == 1) {
    return arr[0];
  }

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

int main() {
  return 0;
}
