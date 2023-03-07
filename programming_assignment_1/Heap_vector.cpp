#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Class for 3-ary min heap
class Heap {
  private:
    vector<int> heap; // underlying array for the heap

    int parent(int i) {
      return (i - 1) / 3;
    }

    int kthChild(int i, int k) {
      return 3 * i + k;
    }

    void minHeapify(int i) {
      int smallest = i;

      // compare w/ its children
      for (int k = 1; k <= 3; k++) {
        int child = kthChild(i, k);
        if (child < heap.size() && heap[child] < heap[smallest]) {
          smallest = child;
        }
      }

      // if it is not the smallest, swap it down w/ the smallest
      if (smallest != i) {
        swap(heap[i], heap[smallest]);
        minHeapify(smallest);
      }
    }

  public:
    // constructor
    Heap() {}

    void insert(int key) {
      heap.push_back(key);
      int i = heap.size() - 1;

      // float
      while (i > 0 && heap[i] < heap[parent(i)]) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
      }
    }

    // decrease the key of a node at a given index to a new value
    void decreaseKey(int i, int newKey) {
      heap[i] = newKey;

      // propagate the node up until the parent is smaller or we reach the root
      while (i > 0 && heap[i] < heap[parent(i)]) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
      }
    }

    // extract the minimum key from the heap and return its value
    int extractMin() {
      // error checking
      if (heap.empty()) {
        cerr << "Heap is empty." << endl;
        return -1;
      }

      int root = heap[0];
      heap[0] = heap.back();
      heap.pop_back();

      minHeapify(0);

      return root;
    }

    void printHeap() {
      for (int i = 0; i < heap.size(); i++) {
        cout << heap[i] << " ";
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

    Heap heap;

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

