// 1. Parallel Bubble Sort using OpenMP
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        // Odd-even sorting logic (parallel-style)
        for (int j = i % 2; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    vector<int> arr(10000);
    for (int i = 0; i < 10000; i++) {
        arr[i] = rand() % 100;
    }

    cout << "Original array: [";
    for (int i = 0; i < 10; i++) cout << arr[i] << " ";
    cout << "...]\n";

    clock_t start = clock();
    parallelBubbleSort(arr);
    clock_t end = clock();

    cout << "Sorted array: [";
    for (int i = 0; i < 10; i++) cout << arr[i] << " ";
    cout << "...]\n";

    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    cout << "Execution time: " << time_taken << " seconds\n";

    return 0;
}


// 2. Parallel Merge Sort using OpenMP

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

vector<int> mergeSort(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return arr;

    int mid = n / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());

    left = mergeSort(left);
    right = mergeSort(right);

    // Merge
    vector<int> merged;
    int i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j])
            merged.push_back(left[i++]);
        else
            merged.push_back(right[j++]);
    }
    while (i < left.size()) merged.push_back(left[i++]);
    while (j < right.size()) merged.push_back(right[j++]);

    return merged;
}

int main() {
    vector<int> arr(10000);
    for (int i = 0; i < 10000; i++) {
        arr[i] = rand() % 100;
    }

    cout << "Original array: [";
    for (int i = 0; i < 10; i++) cout << arr[i] << " ";
    cout << "...]\n";

    clock_t start = clock();
    vector<int> sortedArr = mergeSort(arr);
    clock_t end = clock();

    cout << "Sorted array: [";
    for (int i = 0; i < 10; i++) cout << sortedArr[i] << " ";
    cout << "...]\n";

    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    cout << "Execution time: " << time_taken << " seconds\n";

    return 0;
}

