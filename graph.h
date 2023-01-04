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
        vector<Airline> airlines;
    };

    struct Node {
        list<Edge> flights; // The list of outgoing edges (to adjacent nodes)
        bool visited;// As the node been visited on a search?
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
    int nFlights;
    vector<Node> nodes; // The list of nodes being represented
    unordered_map<string,int> airportIndex; //maps the airport codes to the index of the airport(node) in the vector nodes
    unordered_map<string,Airline> airlineCodes; //maps the airline codes to the airlines
    unordered_map<string,vector<Airport>> cityAirports; //maps the city name to the airports in that city
public:
    Graph(int nodes);
    void getAirlines(string file);
    void getFlights(string file);
    void addEdge(int src, int dest, const Airline& airline);
    void addAirports(queue<Airport> airports);
    void addCityAirports();
    void showCityAirports(const string& city);
    void articulationPoints(const set<string>& permittedAirlines);
    void dfsArt(int v, stack<int>* node_stack, list<int>* res, int index);
    void dfsFilteredArt(int v, stack<int>* node_stack, list<int>* res,int index, const set<string>& permittedAirlines);
    int bfs(int v);
    void getShortestPath(const string& start,const string& end);
    void getShortestFilteredPath(const string& start,const string& end,const set<string>& permittedAirlines);
    void getShortestFilteredPathFromList(list<int> airports,const string& end,const set<string>& permittedAirlines);
    void printPath(const string& end);
    void getAvailableFlights(const string& airport);
    void getDestinations(const string& airport);
    void getStats(const string& start,int maxFlights);
    void clearData();
    int getNFlights()const;
    void calculateDiameter();
    list<int> getCloseAirports(double latitude, double longitude, int kilometers);
    unordered_map<string,int> getAirports();
    unordered_map<string,Airline> getAirlineCodes();
    unordered_map<string,vector<Airport>> getCityAirports();
};

#endif


#endif //PROJETO_AED_2_GRAPH_H
