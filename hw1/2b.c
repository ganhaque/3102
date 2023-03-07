#include <stdio.h>

int main() {

  int n;
  printf("Enter n: ");
  scanf("%d", &n);
  // printf("n is now: %d\n", n);

  int i, j, z;
  int counter = 0;

  int A[1001];
  for(int z = 0; z <= 1000; z++){
    A[z] = z;
  }

  for (i = 1; i <= n; i++) {
    for (j = 0; j < n; j += i) {
      counter += 1;
      // printf("print: %d\n", A[j]);
    }
  }

  printf("counter: %d\n", counter);
}
