#include "graph.h"
#include "Airport.h"
#include "Airline.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num) : n(num), nodes(num+1) {

}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, Airline airline) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    list<Airline> airlines;
    airlines.push_back(airline);
    nodes[src].adj.push_back({dest, airlines});
}

void Graph::addAirlineToFlight(int src, int dest, Airline airline) {
    if(src < 1 || src>n || dest<1 || dest>n) return;
    for(auto e : nodes[src].adj) {
        if (e.dest == dest) {
            e.airlines.push_back(airline);
            return;
        }
    }
    addEdge(src, dest, airline);
}

unordered_map<string,int> Graph::addAirports(queue<Airport> airports){
    unordered_map<string, int> index;
    int count = 1;
    while (!airports.empty()){
        nodes[count].airport = airports.front();
        airports.pop();
        count++;
    }
}

// Depth-First Search: example implementation
void Graph::dfs(int v) {
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}

// Breadth-First Search: example implementation
void Graph::bfs(int v) {
    for (int i=1; i<=n; i++) {nodes[i].visited = false; nodes[i].distance = -1;}
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].distance = 0;
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
            }
        }
    }
}

