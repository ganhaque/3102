#include <stdio.h>

//left is 0
//right is n - 1, where n is the number of elements in the array
int FindMaximum(int array[], int left, int right) {
  //base case (array has 1 element)
  if (left == right) {
    return array[left];
  }

  // cases when the array has 2 elements
  if ( right == left + 1) {
    if (array[left] > array[right]) {
      return array[left];
    }
    else { // if (array[left] < array[right]) {
      return array[right];
    }
  }

  int mid = (left + right) / 2;
  _Bool midIsBiggerThanLeftOfMid = (array[mid] > array[mid - 1]);
  _Bool midIsBiggerThanRightOfMid = (array[mid] > array[mid + 1]);

  if (midIsBiggerThanRightOfMid) {
    if (midIsBiggerThanLeftOfMid) {
      //if mid is bigger than both its left and right elements, then it is the maximum
      return array[mid];
    }
    else { //the max is on the left side of mid
      return FindMaximum(array, left, mid-1);
    }
  }
  return FindMaximum(array, mid + 1, right);
}

int main() {
  // test array
  int array[] = {1,2,3,4,10,9,8,7,6,5,4,3,2,1};
  int n = sizeof(array) / sizeof(array[0]);

  printf("The maximum is: %d\n", FindMaximum(array, 0, n - 1));
}

