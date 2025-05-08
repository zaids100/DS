#include<iostream>
#include<stdlib.h>
#include<omp.h>
#include<chrono> // For timing
using namespace std;
using namespace std::chrono;

void mergesort(int a[], int i, int j);
void merge(int a[], int i1, int j1, int i2, int j2);

void mergesort(int a[], int i, int j)
{
    int mid;
    if (i < j)
    {
        mid = (i + j) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergesort(a, i, mid);
            }

            #pragma omp section
            {
                mergesort(a, mid + 1, j);
            }
        }

        merge(a, i, mid, mid + 1, j);
    }
}

void merge(int a[], int i1, int j1, int i2, int j2)
{
    int temp[1000];
    int i, j, k;
    i = i1;
    j = i2;
    k = 0;

    while (i <= j1 && j <= j2)
    {
        if (a[i] < a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
        }
    }

    while (i <= j1)
    {
        temp[k++] = a[i++];
    }

    while (j <= j2)
    {
        temp[k++] = a[j++];
    }

    for (i = i1, j = 0; i <= j2; i++, j++)
    {
        a[i] = temp[j];
    }
}

int main()
{
    int *a, n, i;

    cout << "\nEnter total number of elements: ";
    cin >> n;

    a = new int[n];

    cout << "\nEnter elements: ";
    for (i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    // Start time measurement
    auto start = high_resolution_clock::now();

    // Perform mergesort
    mergesort(a, 0, n - 1);

    // End time measurement
    auto stop = high_resolution_clock::now();

    // Calculate duration
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\nSorted array is: ";
    for (i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }

//    cout << "\nTime taken by mergesort: " << duration.count() << " microseconds" << endl;

    delete[] a; // Free the allocated memory
    return 0;
}

 /*
  * MERGE SORT IMPLEMENTATION (SEQUENTIAL VS PARALLEL)
  * ===============================================
  *
  * Overview:
  * ---------
  * This program implements both sequential and parallel versions of the Merge Sort algorithm.
  * It demonstrates the performance benefits of parallel processing by sorting a large array
  * of random integers using both approaches and comparing their execution times.
  *
  * Key Technologies:
  * ----------------
  * 1. OpenMP (#pragma omp)
  *    - A parallel programming API for shared-memory multiprocessing
  *    - Used for parallelizing computationally intensive tasks
  *    - Examples: parallel for loops, sections, tasks
  *    - Other applications: matrix multiplication, image processing
  *
  * 2. Chrono Library
  *    - High-precision timing functionality
  *    - Used for performance measurement
  *    - Provides nanosecond-level accuracy
  *
  * Data Structures:
  * ---------------
  * 1. Vector<int>
  *    - Dynamic array implementation
  *    - Used for main array and temporary storage
  *    - Allows dynamic resizing during merge operations
  *
  * Complexity Analysis:
  * ------------------
  * Time Complexity:
  * - Sequential: O(n log n) - standard merge sort
  * - Parallel: O(n log n / p) where p is number of processors
  *
  * Space Complexity:
  * - O(n) for temporary arrays during merging
  *
  * Parallel Performance Factors:
  * ---------------------------
  * 1. Array Size: Larger arrays benefit more from parallelization
  * 2. Hardware Threads: Performance scales with available cores
  * 3. Overhead: Thread creation and management costs
  * 4. Memory Access Patterns: Cache efficiency impacts performance
  *
  * Q&A Section:
  * -----------
  * Q1: What is OpenMP and how is it used here?
  * A1: OpenMP is a parallel programming API. Here it's used via #pragma omp parallel sections
  *     to split merge sort recursion into parallel tasks.
  *
  * Q2: Why use vector instead of array?
  * A2: Vectors provide dynamic sizing needed for merge operations and are exception-safe.
  *
  * Q3: What's the minimum array size for parallel efficiency?
  * A3: Generally, arrays should be >10000 elements for parallel overhead to be worthwhile.
  *
  * Q4: How does the merge function work?
  * A4: It combines two sorted subarrays by comparing elements and creating a temporary sorted array.
  *
  * Q5: Why use chrono instead of time.h?
  * A5: Chrono provides higher precision and type-safe duration calculations.
  *
  * Q6: What's the purpose of arr_copy?
  * A6: It maintains an identical array for fair comparison between sequential and parallel versions.
  *
  * Q7: How does parallel speedup scale?
  * A7: Theoretically linear with cores, but practically sub-linear due to overhead and memory bottlenecks.
  *
  * Q8: What's the significance of sections vs parallel for?
  * A8: Sections create independent task blocks, while parallel for distributes loop iterations.
  *
  * Q9: How is thread safety ensured?
  * A9: Each thread works on separate array sections, preventing data races.
  *
  * Q10: What limits parallel performance?
  * A10: Memory bandwidth, thread overhead, and load balancing are key limiters.
  *
  * Q11: How to optimize the parallel version?
  * A11: Use task scheduling, adjust grain size, and optimize memory access patterns.
  *
  * Q12: Why use (r-l)/2 instead of /2 directly?
  * A12: Prevents integer overflow for large arrays and maintains proper indexing.
  *
  * Q13: What's the base case for recursion?
  * A13: When l >= r, meaning the subarray has 1 or 0 elements.
  *
  * Q14: How does load balancing work?
  * A14: OpenMP runtime distributes tasks across threads, but subarray sizes may vary.
  *
  * Q15: What's the impact of cache locality?
  * A15: Better cache usage improves performance; sequential access patterns are preferred.
  *
  * Q16: Can this be further parallelized?
  * A16: Yes, the merge operation itself could be parallelized for additional speedup.
  *
  * Q17: Why use srand(time(0))?
  * A17: Ensures different random numbers on each run for realistic testing.
  *
  * Q18: What's the memory overhead?
  * A18: O(n) extra space for temporary arrays during merging, plus thread stack space.
  */
 