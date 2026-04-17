#include <bits/stdc++.h>
using namespace std;

class DAG {
private:
    int vertices;
    vector<vector<int>> adj;

public:
    DAG(int v) {
        vertices = v;
        adj.resize(v);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void topologicalSort() {
        vector<int> indegree(vertices, 0);

        // Calculate indegree
        for (int u = 0; u < vertices; u++) {
            for (int v : adj[u]) {
                indegree[v]++;
            }
        }

        queue<int> q;

        // Add nodes with indegree 0
        for (int i = 0; i < vertices; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> order;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);

            for (int v : adj[u]) {
                indegree[v]--;
                if (indegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // Check for cycle
        if (order.size() != vertices) {
            cout << "Graph is not a DAG (cycle detected)\n";
        } else {
            cout << "Topological Order: ";
            for (int x : order) {
                cout << x << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    DAG dag(6);

    dag.addEdge(5, 2);
    dag.addEdge(5, 0);
    dag.addEdge(4, 0);
    dag.addEdge(4, 1);
    dag.addEdge(2, 3);
    dag.addEdge(3, 1);

    dag.topologicalSort();

    return 0;
}