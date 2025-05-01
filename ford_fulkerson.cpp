#include <iostream>
#include <list>
#include <limits.h>
#include <string.h>
using namespace std;

class Graph {
    int V; // Number of vertices
    list<pair<int, int>>* adj; // Adjacency list with capacities

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    bool bfs(int s, int t, int parent[]);
    int fordFulkerson(int source, int sink);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<pair<int, int>>[V]; // Initialize adjacency list
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w)); // Add edge from u to v with capacity w
}

bool Graph::bfs(int s, int t, int parent[]) {
    bool visited[V]; // Track visited vertices
    memset(visited, 0, sizeof(visited)); // Initialize visited array
    list<int> queue; // Initialize queue for BFS
    queue.push_back(s); // Start from the source
    visited[s] = true; // Mark the source as visited

    while (!queue.empty()) {
        int u = queue.front(); // request a vertex
        queue.pop_front();

        for (auto pair : adj[u]) { // Iterate through neighbors
            int v = pair.first;
            int capacity = pair.second;

            if (!visited[v] && capacity > 0) { // Check for available capacity
                queue.push_back(v); // queue up the vertex
                visited[v] = true; // Mark as visited
                parent[v] = u; // Store the path
                if (v == t) {
                    return true; // Path found
                }
            }
        }
    }
    return false; // No path found
}

int Graph::fordFulkerson(int source, int sink) {
    int parent[V]; // Initialize parent array for path reconstruction
    int max_flow = 0; // Initialize maximum flow

    while (bfs(source, sink, parent)) { // While there is an augmenting path
        int path_flow = INT_MAX; // Initialize path flow
        int s = sink; // Start from the sink

        // Find the maximum flow through the path found
        while (s != source) {
            int u = parent[s];
            path_flow = min(path_flow, adj[u].find(s)->second); // Update path flow
            s = parent[s]; // Move to the previous vertex
        }

        // Update residual capacities of the edges and reverse edges
        s = sink;
        while (s != source) {
            int u = parent[s];
            adj[u].find(s)->second -= path_flow; // Update forward edge
            // Update reverse edge
            bool found_reverse = false;
            for (auto& pair : adj[s]) {
                if (pair.first == u) {
                    pair.second += path_flow; // Update reverse edge
                    found_reverse = true;
                    break;
                }
            }
            if (!found_reverse) {
                adj[s].push_back(make_pair(u, path_flow)); // Add reverse edge if it doesn't exist
            }
            s = parent[s];
        }

        max_flow += path_flow; // Add path flow to total flow
    }
    return max_flow; // Return the maximum flow value
}

// Example usage
int main() {
    Graph g(6);
    g.addEdge(0, 1, 16); // Add edges with capacities
    g.addEdge(0, 2, 13);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 12);
    g.addEdge(2, 1, 4);
    g.addEdge(2, 4, 14);
    g.addEdge(3, 2, 9);
    g.addEdge(3, 5, 20);
    g.addEdge(4, 3, 7);
    g.addEdge(4, 5, 4);

    cout << "The maximum possible flow is: " << g.fordFulkerson(0, 5) << endl; // Output the maximum flow
    return 0;
}