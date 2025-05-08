#include <iostream>
#include <omp.h>
#include <climits>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Function to find the minimum value in an array using parallel reduction
void min_reduction(int arr[], int n) {
    int min_value = INT_MAX;
    #pragma omp parallel for reduction(min: min_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }
    cout << "Minimum value: " << min_value << endl;
}

// Function to find the maximum value in an array using parallel reduction
void max_reduction(int arr[], int n) {
    int max_value = INT_MIN;
    #pragma omp parallel for reduction(max: max_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    cout << "Maximum value: " << max_value << endl;
}

// Function to calculate the sum of elements in an array using parallel reduction
void sum_reduction(int arr[], int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    cout << "Sum: " << sum << endl;
}

// Function to calculate the average of elements in an array using parallel reduction
void average_reduction(int arr[], int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    double average = (double)sum / n;  // Fixed average calculation
    cout << "Average: " << average << endl;
}

int main() {
    int n;
    cout << "\nEnter the total number of elements: ";
    cin >> n;
    
    int *arr = new int[n];
    cout << "\nEnter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    auto start = high_resolution_clock::now();
    
    min_reduction(arr, n);
    max_reduction(arr, n);
    sum_reduction(arr, n);
    average_reduction(arr, n);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken for all reductions: " << duration.count() << " ms" << endl;
    
    delete[] arr;
    return 0;
}

 /*
  * Program Overview:
  * This program demonstrates parallel computation of basic array operations (min, max, sum, average)
  * using OpenMP for parallel processing. It generates a random array and performs these operations
  * while measuring execution time.
  *
  * Key Technologies:
  * 1. OpenMP (Open Multi-Processing):
  *    - A parallel programming API for shared memory multiprocessing
  *    - Uses pragma directives for parallelization
  *    - Example: #pragma omp parallel for reduction(op : var)
  *    - Other uses: parallel regions, critical sections, atomic operations
  *
  * 2. Chrono Library:
  *    - High-resolution timing functionality
  *    - Used for performance measurement
  *    - Provides various clock types and duration measurements
  *
  * Data Structures:
  * - std::vector<int>: Dynamic array storing integers
  *   - Contiguous memory allocation
  *   - Random access O(1)
  *   - Dynamic resizing capability
  *
  * Complexity Analysis:
  * Time Complexity:
  * - Sequential: O(n) for all operations
  * - Parallel: O(n/p) where p is number of threads
  * Space Complexity: O(n) for input vector
  *
  * Parallel Performance Factors:
  * 1. Thread Overhead: Creation and management cost
  * 2. Data Locality: Cache utilization
  * 3. Load Balancing: Even distribution of work
  * 4. Reduction Operations: Combining partial results
  * 5. Vector Size: Affects parallelization benefit
  *
  * Q&A Section:
  * Q1: What is OpenMP reduction clause?
  * A1: Reduction manages shared variables in parallel regions by applying an operation
  *     Example: #pragma omp parallel for reduction(+ : sum)
  *
  * Q2: Why use vector instead of array?
  * A2: Vector provides dynamic sizing, bounds checking, and RAII benefits
  *
  * Q3: How does parallel minimum finding work?
  * A3: Each thread finds local minimum, reduction combines using min operation
  *
  * Q4: What's the benefit of high_resolution_clock?
  * A4: Provides finest granularity for time measurement, crucial for performance analysis
  *
  * Q5: Why initialize min_val/max_val with first element?
  * A5: Avoids potential race conditions and ensures valid comparison start
  *
  * Q6: How does parallel reduction affect performance?
  * A6: Reduces thread synchronization overhead by combining local results efficiently
  *
  * Q7: What's the ideal array size for parallelization?
  * A7: Generally >10000 elements to overcome thread overhead costs
  *
  * Q8: Why use float for average calculation?
  * A8: Provides decimal precision for non-integer results
  *
  * Q9: How to control number of threads?
  * A9: Use omp_set_num_threads() or OMP_NUM_THREADS environment variable
  *
  * Q10: What affects parallel speedup?
  * A10: Hardware cores, data size, memory bandwidth, thread overhead
  *
  * Q11: Why measure duration for each operation?
  * A11: Helps analyze performance benefits of parallelization
  *
  * Q12: How to handle false sharing?
  * A12: Use padding or ensure thread-local data alignment
  *
  * Q13: Why use rand() % 10000?
  * A13: Limits random numbers to reasonable range for testing
  *
  * Q14: What's the purpose of fixed and setprecision?
  * A14: Controls floating-point output format for readability
  *
  * Q15: How to optimize parallel performance?
  * A15: Adjust chunk size, minimize critical sections, ensure good load balance
  *
  * Q16: Why separate functions for each operation?
  * A16: Modular design, easier testing and maintenance
  *
  * Q17: What's the impact of cache coherence?
  * A17: Affects performance when multiple threads access shared data
  *
  * Q18: How to handle thread safety?
  * A18: OpenMP handles automatically for reduction operations
  */