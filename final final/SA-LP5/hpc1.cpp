#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// ----------------------------
// Parallel BFS (No atomics)
// ----------------------------
void parallelBFS(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> visited(n, 0); // Use int instead of bool
    vector<int> frontier;

    visited[start] = 1;
    frontier.push_back(start);

    cout << "Parallel BFS: ";

    while (!frontier.empty()) {
        vector<int> next_frontier;

        #pragma omp parallel
        {
            vector<int> local_next;

            #pragma omp for nowait
            for (int i = 0; i < frontier.size(); ++i) {
                int u = frontier[i];

                #pragma omp critical
                cout << u << " ";

                for (int v : graph[u]) {
                    #pragma omp critical
                    {
                        if (visited[v] == 0) {
                            visited[v] = 1;
                            local_next.push_back(v);
                        }
                    }
                }
            }

            #pragma omp critical
            next_frontier.insert(next_frontier.end(), local_next.begin(), local_next.end());
        }

        frontier = next_frontier;
    }

    cout << endl;
}

// ----------------------------
// Parallel DFS using OpenMP tasks
// ----------------------------
void parallelDFSUtil(const vector<vector<int>>& graph, int node, vector<int>& visited) {
    bool alreadyVisited;

    // Check and set visited inside critical section
    #pragma omp critical
    {
        alreadyVisited = visited[node];
        if (!alreadyVisited) {
            visited[node] = 1;
            cout << node << " ";
        }
    }

    if (alreadyVisited) return;

    #pragma omp parallel for
    for (int i = 0; i < graph[node].size(); ++i) {
        int v = graph[node][i];

        if (!visited[v]) {
            #pragma omp task
            parallelDFSUtil(graph, v, visited);
        }
    }

    #pragma omp taskwait
}

void parallelDFS(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> visited(n, 0); // Use int instead of bool

    cout << "Parallel DFS: ";

    #pragma omp parallel
    {
        #pragma omp single
        parallelDFSUtil(graph, start, visited);
    }

    cout << endl;
}

// ----------------------------
// Main function
// ----------------------------
int main() {
    vector<vector<int>> graph = {
        {1, 2},    // 0
        {0, 3, 4}, // 1
        {0, 4},    // 2
        {1, 5},    // 3
        {1, 2, 5}, // 4
        {3, 4}     // 5
    };

    int startNode = 0;

    parallelBFS(graph, startNode);
    parallelDFS(graph, startNode);

    return 0;
}
