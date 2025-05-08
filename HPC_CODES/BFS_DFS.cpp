#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void parallel_bfs(vector<vector<int>> &graph, int startNode)
{
    vector<bool> visited(graph.size(), false);
    visited[startNode] = true;
    queue<int> q;
    q.push(startNode);
    cout << "BFS: ";
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        cout << node << " ";
#pragma omp parallel for
        for (auto nbr : graph[node])
        {
#pragma omp critical
            {
                if (!visited[nbr])
                {
                    visited[nbr] = true;
                    q.push(nbr);
                }
            }
        }
    }
}

void parallel_dfs(const vector<vector<int>>& graph, int startNode) {
    int n = graph.size();
    vector<bool> visited(n, false);
    stack<int> st;
    st.push(startNode);
    visited[startNode] = true;

    while (!st.empty()) {
        int node = st.top();
        st.pop();
        cout << node << " ";
        #pragma omp parallel for
        for (int i = 0; i < graph[node].size(); ++i) {
            int neighbor = graph[node][i];
            #pragma omp critical
            {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    st.push(neighbor);
                }
            }
        }
    }
}

int main()
{

    vector<vector<int>> graph = {{1, 2}, {0, 2}, {0, 1, 3}, {0, 2}};
    parallel_dfs(graph, 0);
}