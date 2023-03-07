#include <iostream>
#include <vector>

using namespace std;

pair<int, pair<int, int>> max_subarray_sum(vector<int>& arr) {
    int max_so_far = arr[0];
    int max_ending_here = arr[0];
    int start_index = 0;
    int end_index = 0;
    int temp_index = 0;

    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > max_ending_here + arr[i]) {
            max_ending_here = arr[i];
            temp_index = i;
        }
        else {
            max_ending_here += arr[i];
        }

        if (max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
            start_index = temp_index;
            end_index = i;
        }
    }

    return make_pair(max_so_far, make_pair(start_index, end_index));
}

int main() {
    vector<int> arr = {3, 4, -6, 2, -4, 5, 6, -3, 8, -11, 3, 4};

    auto result = max_subarray_sum(arr);

    cout << "Maximum subarray sum: " << result.first << endl;
    cout << "Start index: " << result.second.first << endl;
    cout << "End index: " << result.second.second << endl;

    return 0;
}

