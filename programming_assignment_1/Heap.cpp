#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Class for 3-ary min heap
class Heap {
  private:
    // int arraySize;
    int heapSize;
    // int heapArray[1'000'000'001];
    int* heapArray;

    // helper functions
    int parent(int i) {
      return (i - 1) / 3;
    }

    int kthChild(int i, int k) {
      return 3 * i + k;
    }

    void swap(int &x, int &y) {
      int temp = x;
      x = y;
      y = temp;
    }

  public:
    // constructor
    Heap(int arraySize) {
      heapSize = 0;
      heapArray = new int[arraySize];
    }

    //methods
    void insert(int key) {
      // add key to array and update heap size
      heapArray[heapSize] = key;
      heapSize += 1;

      // sort
      int i = heapSize - 1;
      // swap up until reach root or not bigger than its parent
      while (i > 0 && heapArray[i] < heapArray[parent(i)]) {
        swap(heapArray[i], heapArray[parent(i)]);
        i = parent(i);
      }
    }

    // change the value at a given index to a new value
    void decreaseKey(int i, int newKey) {
      heapArray[i] = newKey;

      while (i > 0 && heapArray[i] < heapArray[parent(i)]) {
        swap(heapArray[i], heapArray[parent(i)]);
        i = parent(i);
      }
    }

    int extractMin() {
      // error checking
      if (heapSize == 0) {
        cerr << "no thoughts, heap empty." << endl;
        return -1;
      }

      // save the minimum key to return
      int minKey = heapArray[0];


      //update heap size
      heapSize--;

      // copy value of last node to root
      heapArray[0] = heapArray[heapSize];
      // don't need to remove last node since other methods would replace/ignore it anyways

      int i = 0;
      int child1 = kthChild(i, 1);

      // bubble/sink down
      while (child1 < heapSize) {
        // if child2 or 3 exist
        int child2 = min(kthChild(i, 2), heapSize - 1);
        int child3 = min(kthChild(i, 3), heapSize - 1);

        //find the smallest child between the three
        int smallestChild = child1;
        if (heapArray[child2] < heapArray[smallestChild]) {
          smallestChild = child2;
        }
        if (heapArray[child3] < heapArray[smallestChild]) {
          smallestChild = child3;
        }

        if (heapArray[i] > heapArray[smallestChild]) {
          swap(heapArray[i], heapArray[smallestChild]);
          i = smallestChild;
          child1 = 3 * i + 1;
        }
        else {
          break;
        }
      }
      return minKey;
    }

    void printHeap() {
      for (int i = 0; i < heapSize; i++) {
        cout << heapArray[i] << " ";
      }
      cout << endl;
    }
};
int main() {
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
  Heap heap(numInstructions);

  // heap.printHeap();
  string instruction;

  for (int i = 0; i < numInstructions; i++) {
    infile >> instruction;
    if (instruction == "IN") {
      int key;
      infile >> key;
      heap.insert(key);
      // heap.printHeap();
    } else if (instruction == "DK") {
      int i, newKey;
      infile >> i >> newKey;
      heap.decreaseKey(i, newKey);
      // heap.printHeap();
    } else if (instruction == "EM") {
      if ( i == numInstructions - 1 )  {
        // cout << "proc";
        cout << heap.extractMin() << endl;
      }
      else {
        heap.extractMin();
      }
      // heap.printHeap();
    }
  }

  return 0;
}

