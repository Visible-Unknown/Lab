#include <iostream>
#include <vector>

using namespace std;

class Graph {
    int V; 
    vector<vector<int>> adj;

public:
    Graph(int V);
    void addEdge(int v, int w);
    void DFS(int start);
    void DFSUtil(int node, vector<bool>& visited);
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::DFSUtil(int node, vector<bool>& visited) {
    visited[node] = true; 
    cout << node << " "; 

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            DFSUtil(neighbor, visited);
        }
    }
}

void Graph::DFS(int start) {
    vector<bool> visited(V, false); 
    cout << "DFS Traversal: ";
    DFSUtil(start, visited);
    cout << endl;
}

int main() {
    Graph g(6); 
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    int startNode = 0;
    g.DFS(startNode);

    return 0;
}
