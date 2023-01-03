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
#include <stack>
#include <unordered_map>
#include "Airport.h"
#include "Airline.h"
#include <set>

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
        int low;
        int num;
        bool inStack;
        bool isArt;
        Airport airport;
        vector<vector<int>> path;
        vector<vector<Airline>> pathAirlines;
    };

    int n; //number of nodes
    vector<Node> nodes; // The list of nodes being represented
    unordered_map<string,int> airportIndex; //maps the airport codes to the index of the airport(node) in the vector nodes
    unordered_map<string,Airline> airlineCodes; //maps the airline codes to the airlines
    unordered_map<string,vector<Airport>> cityAirports; //maps the city name to the airports in that city
public:
    Graph(int nodes);
    void addEdge(int src, int dest, const Airline& airline);
    void addAirports(queue<Airport> airports);
    void addCityAirports();
    void showCityAirports(const string& city);
    unordered_map<string,int> getAirports();
    unordered_map<string,Airline> getAirlineCodes() ;
    void getAirlines(string file);
    int getFlights(string file);
    void dfsArt(int v, stack<int>* node_stack, list<int>* res, int index);
    void dfsFilteredArt(int v, stack<int>* node_stack, list<int>* res,int index, const set<string>& permittedAirlines);
    void bfs(int v);
    void articulationPoints(const set<string>& permittedAirlines);
    void printPath(const string& end);
    void getShortestPath(const string& start,const string& end);
    void getAvailableFlights(const string& airport);
    void getDestinations(const string& airport);
    void getShortestFilteredPath(const string& start,const string& end,const set<string>& permittedAirlines);
    void getShortestFilteredPathFromCity(string city,const string& end,const set<string>& permittedAirlines);
    void getCloseAirports(double latitude, double longitude, int kilometers);
    void getStats(const string& start,int nFlights);
};

#endif


#endif //PROJETO_AED_2_GRAPH_H
