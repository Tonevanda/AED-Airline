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
#include "Airline.h"

using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        //int distance;
        vector<Airline> airlines;
    };

    struct Node {
        list<Edge> flights; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
        int distance;
        Airport airport;
        vector<vector<int>> path;
        vector<vector<Airline>> pathAirlines;
    };

    int n; //number of nodes
    vector<Node> nodes; // The list of nodes being represented
    unordered_map<string,int> airportIndex; //maps the airport codes to the index of the airport(node) in the vector nodes
    unordered_map<string,Airline> airlines; //maps the airline codes to the airlines

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes);

    void addEdge(int src, int dest, Airline airline);

    void addAirports(queue<Airport> airports);

    unordered_map<string,int> getAirports();

    void getAirlines(string file);

    void getFlights(string file);

    void dfs(int v);

    void bfs(int v);

    void printPath(string end);

    void getShortestPath(string start,string end);
};

#endif


#endif //PROJETO_AED_2_GRAPH_H
