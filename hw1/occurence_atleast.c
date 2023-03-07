#include <stdio.h>
// #include <stdbool.h>

//left is 0
//right is n - 1, where n is the number of elements in the array (n = sizeof(array) / sizeof(array[0]) )
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
  _Bool midIsBiggerThanLeftOfMid = (array[mid] > array[left]);
  _Bool midIsBiggerThanRightOfMid = (array[mid] > array[right]);

  if (midIsBiggerThanRightOfMid) {
    if (midIsBiggerThanLeftOfMid) {
      return array[mid];
    }
    else { //the max is on the left side of mid
      return FindMaximum(array, left, mid-1);
    }
  }
  //the max is on the right otherwise
  return FindMaximum(array, mid + 1, right);
}

int countOccurence(int array[], int n, int k) {
  return 0;
}

int main() {
  int array[] = {1,2,3,4,10,9,8,7,6};
  int n = sizeof(array) / sizeof(array[0]);

  printf("The maximum is: %d\n", FindMaximum(array, 0, n - 1));
}

// Explanation in English
/* 
The function has 3 parameters, the array, n, and k. There are 4 local variables to the function, a counter,
a return value, a hashmap to store elements that were checked, and a hashmap to store the number of occurences
  */
