//
// Created by João Lourenço on 28/12/2022.
//

#ifndef PROJETO_AED_2_GRAPH_H
#define PROJETO_AED_2_GRAPH_H

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include "Airport.h"

using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        //int distance;
        list<string> airlines;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes) nodes[i].adj
        bool visited;   // As the node been visited on a search?
        int distance;
        string code; //map[nodes[1].code]
    };

    int n;// Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirected; true: directed
    vector<Node> nodes; // The list of nodes being represented
    unordered_map<string, Airport> airports;
    //unordered_map<string, int> codes;
public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    void addEdge(int src, int dest, string airline);

    void addAirlineToFlight(int src, int dest, string airline);

    void dfs(int v);

    void bfs(int v);
};

#endif


#endif //PROJETO_AED_2_GRAPH_H
