#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

struct Node {
    int data;
    vector<Node*> children;
};

void parallel_BFS(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int level_size = q.size();
        vector<Node*> current_level;

        // Copy current level nodes
        for (int i = 0; i < level_size; ++i) {
            current_level.push_back(q.front());
            q.pop();
        }

        vector<Node*> next_level;

        // Process current level nodes in parallel
        #pragma omp parallel for
        for (int i = 0; i < current_level.size(); ++i) {
            Node* current = current_level[i];

            // Print node data
            #pragma omp critical
            { 
                cout << current->data << " ";
            }

            // Push children into next_level
            #pragma omp critical
            {
                for (int j = 0; j < current->children.size(); ++j) {
                    next_level.push_back(current->children[j]);
                }
            }
        }

        // Add all next_level nodes to the queue
        for (int i = 0; i < next_level.size(); ++i) {
            q.push(next_level[i]);
        }
    }
}

int main() {
    // Create a sample N-ary tree
    Node* root = new Node;
    root->data = 1;

    Node* child1 = new Node;
    child1->data = 2;

    Node* child2 = new Node;
    child2->data = 3;

    Node* grandchild = new Node;
    grandchild->data = 4;

    child2->children.push_back(grandchild);

    root->children.push_back(child1);
    root->children.push_back(child2);

    cout << "Parallel BFS Output: ";
    parallel_BFS(root);
    cout << endl;

    return 0;
}

/*
 * Problem Statement:
 * Design and implement Parallel Breadth First Search based on existing algorithms using OpenMP.
 * Use a Tree or an undirected graph for BFS.
 *
 * How to run:
 * 1. Open terminal in the directory containing the file
 * 2. Compile: g++ -fopenmp 01_Parallel_BFS.cpp -o 01_Parallel_BFS
 *    (if above not worked): g++ 01_Parallel_BFS.cpp -o 01_Parallel_BFS
 *    (General command): g++ -fopenmp fileName.cpp -o fileName or g++ fileName.cpp -o fileName
 * 3. Run: ./01_Parallel_BFS or .\01_Parallel_BFS
 */

  /*
  * Parallel Breadth First Search (BFS) Implementation using OpenMP
  * =============================================================
  *
  * Overview:
  * ---------
  * This program implements a parallel version of the Breadth-First Search algorithm
  * for traversing graphs. It demonstrates both basic graph operations and parallel
  * processing concepts using OpenMP.
  *
  * Key Technologies:
  * ----------------
  * 1. OpenMP (#pragma omp)
  *    - A parallel programming API for shared-memory multiprocessing
  *    - Used here for parallel task execution and thread management
  *    - Examples in other contexts: parallel for loops, matrix multiplication
  *    - Directives used:
  *      #pragma omp parallel      // Creates parallel region with multiple threads
  *      #pragma omp single nowait // Single thread executes, others don't wait
  *      #pragma omp task          // Creates new task for parallel execution
  *      #pragma omp parallel for  // Distributes loop iterations among threads
  *
  * 2. STL Containers
  *    - vector<>: Dynamic arrays for adjacency lists
  *    - queue<>: FIFO data structure for BFS traversal
  *
  * Data Structures:
  * ---------------
  * 1. Graph (struct)
  *    - Adjacency list representation using vector<vector<int>>
  *    - Allows O(1) access to vertices and O(degree) traversal of neighbors
  *
  * 2. BFS-specific structures:
  *    - visited[]: Boolean array tracking visited vertices
  *    - queue: Maintains vertices to be explored
  *
  * Complexity Analysis:
  * -------------------
  * Time Complexity:
  * - Sequential: O(V + E) where V = vertices, E = edges
  * - Parallel: O((V + E)/p) theoretical, where p = number of processors
  *
  * Space Complexity:
  * - O(V + E) for adjacency list
  * - O(V) for visited array and queue
  *
  * Parallel Performance Factors:
  * ---------------------------
  * 1. Critical Section Overhead
  * 2. Load Balancing
  * 3. Graph Structure/Density
  * 4. Memory Access Patterns
  * 5. Thread Synchronization Cost
  *
  * Q&A Section:
  * -----------
  * Q1: What is BFS and why use it?
  * A1: BFS is a graph traversal algorithm that explores all vertices at the current
  *     depth before moving to vertices at the next depth level. Used in shortest
  *     path finding, web crawling, and network analysis.
  *
  * Q2: Why use adjacency lists over matrices?
  * A2: Adjacency lists are more space-efficient for sparse graphs O(V+E) vs O(V²),
  *     and provide faster iteration over neighbors.
  *
  * Q3: What does #pragma omp parallel for do?
  * A3: It distributes loop iterations across multiple threads, enabling parallel
  *     processing of independent operations.
  *
  * Q4: Why is the critical section necessary?
  * A4: To prevent race conditions when multiple threads try to update shared data
  *     (visited array and queue) simultaneously.
  *
  * Q5: What's the purpose of double-checking visited[v]?
  * A5: It's a performance optimization that reduces critical section contention
  *     by checking visited status before entering the critical section.
  *
  * Q6: How does parallel BFS differ from sequential BFS?
  * A6: Parallel BFS processes multiple neighbors concurrently, but requires
  *     synchronization for shared data access.
  *
  * Q7: What factors affect parallel performance?
  * A7: Graph structure, thread overhead, memory access patterns, load balancing,
  *     and critical section contention.
  *
  * Q8: Why use vector<bool> for visited array?
  * A8: It's space-efficient as it typically uses 1 bit per boolean instead of
  *     1 byte, though it may have performance tradeoffs.
  *
  * Q9: How does load balancing affect performance?
  * A9: Uneven distribution of edges among vertices can lead to some threads
  *     doing more work than others, reducing parallel efficiency.
  *
  * Q10: What's the impact of graph density on performance?
  * A10: Denser graphs have more edges to process but may suffer from increased
  *      critical section contention.
  *
  * Q11: How can we optimize the parallel implementation?
  * A11: Use larger grain sizes, minimize critical sections, employ better
  *      load balancing, and consider graph partitioning.
  *
  * Q12: What's the significance of the queue in BFS?
  * A12: The queue maintains the FIFO order necessary for level-by-level
  *      traversal characteristic of BFS.
  *
  * Q13: How does thread count affect performance?
  * A13: More threads can improve performance up to a point, after which
  *      overhead and contention may degrade performance.
  *
  * Q14: Why is the graph undirected?
  * A14: Each edge is bidirectional (u->v and v->u), suitable for applications
  *      like social networks or road systems.
  *
  * Q15: What are the memory access patterns in this implementation?
  * A15: Random access patterns when accessing adjacency lists and visited array,
  *      which can affect cache performance.
  *
  * Q16: What are the limitations of this implementation?
  * A16: - No handling of disconnected components
  *      - Potential overhead for small graphs
  *      - Memory contention in dense graphs
  *
  * Q17: What is the purpose of #pragma omp critical?
  * A17: Ensures mutual exclusion, allowing only one thread to execute a code block at a time,
  *      preventing race conditions in shared resource access.
  *
  * Q18: How does #pragma omp taskwait work in OpenMP?
  * A18: Forces the current thread to wait until all its child tasks complete,
  *      useful for synchronization points in the algorithm.
  *
  * Q19: What is the role of OMP_NUM_THREADS environment variable?
  * A19: Sets the default number of threads for parallel regions in OpenMP programs,
  *      allowing runtime control of parallelism level.
  *
  * Q20: How does #pragma omp atomic differ from critical?
  * A20: Provides faster, hardware-supported atomic operations for simple updates to shared variables,
  *      more efficient than critical sections for single operations.
  *
  * Q21: What is the purpose of #pragma omp barrier?
  * A21: Creates a synchronization point where all threads in a parallel region must wait
  *      before any can proceed, ensuring coordinated execution.
  *
  */