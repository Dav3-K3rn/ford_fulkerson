from collections import defaultdict

class Graph:
    def __init__(self, vertices):
        self.V = vertices  # Number of vertices in the graph
        self.graph = defaultdict(lambda: defaultdict(int))  # Adjacency list with capacities

    def add_edge(self, u, v, w):
        self.graph[u][v] += w  # Add edge from u to v with capacity w

    def bfs(self, s, t, parent):
        visited = [False] * self.V  # Track visited vertices
        queue = [s]  # Initialize queue for BFS
        visited[s] = True  # Mark the source as visited
        
        while queue:
            u = queue.pop(0)  # Dequeue a vertex

            for v in self.graph[u]:  # Iterate through neighbors
                if not visited[v] and self.graph[u][v] > 0:  # Check for available capacity
                    queue.append(v)  # Enqueue the vertex
                    visited[v] = True  # Mark as visited
                    parent[v] = u  # Store the path
                    if v == t:  # If we reached the sink
                        return True  # Path found
        return False  # No path found

    def ford_fulkerson(self, source, sink):
        parent = [-1] * self.V  # Initialize parent array for path reconstruction
        max_flow = 0  # Initialize maximum flow

        while self.bfs(source, sink, parent):  # While there is an augmenting path
            path_flow = float('Inf')  # Initialize path flow
            s = sink  # Start from the sink
            
            # Find the maximum flow through the path found
            while s != source:
                u = parent[s]
                path_flow = min(path_flow, self.graph[u][s])  # Update path flow
                s = parent[s]  # Move to the previous vertex

            # Update residual capacities of the edges and reverse edges
            v = sink
            while v != source:
                u = parent[v]
                self.graph[u][v] -= path_flow  # Update forward edge
                self.graph[v][u] += path_flow  # Update reverse edge
                v = parent[v]

            max_flow += path_flow  # Add path flow to the total flow

        return max_flow  # Return the maximum flow value


# Example usage
if __name__ == "__main__":
    g = Graph(6)
    g.add_edge(0, 1, 16)  # Add edges with capacities
    g.add_edge(0, 2, 13)
    g.add_edge(1, 2, 10)
    g.add_edge(1, 3, 12)
    g.add_edge(2, 1, 4)
    g.add_edge(2, 4, 14)
    g.add_edge(3, 2, 9)
    g.add_edge(3, 5, 20)
    g.add_edge(4, 3, 7)
    g.add_edge(4, 5, 4)

    print("The maximum possible flow is:", g.ford_fulkerson(0, 5))  # Output the maximum flow