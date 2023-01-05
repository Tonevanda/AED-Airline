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
    int nAirlines;
    vector<Node> nodes; // The list of nodes being represented
    unordered_map<string,int> airportIndex; //maps the airport codes to the index of the airport(node) in the vector nodes
    unordered_map<string,Airline> airlineCodes; //maps the airline codes to the airlines
    unordered_map<string,vector<Airport>> cityAirports; //maps the city name to the airports in that city
public:
    /**
     * Graph constructor. Creates a Graph object with the number of nodes provided and vector "nodes" with nodes+1 size.
     * @param nodes
     */
    Graph(int nodes);
    /**
     * Returns the total number of flights in the Graph object.
     * Time-complexity -> O(1)
     * @return Int with total number of flights
     */
    int getNFlights()const;   //n of flights/airports/airlines??
    /**
     * Returns the total number os Airports in the Graph object.
     * Time-complexity -> O(1)
     * @return Int with total number of Airports
     */
    int getNAirports()const;
    /**
     * Returns the total number of Airlines in the Graph object.
     * Time-complexity -> O(1)
     * @return Int with total number of Airlines
     */
    int getNAirlines()const;
    /**
     * Breadth-First Search -> Traverses through the Graph and updates the distance field of every node based on the minimum number of flights it takes to get there.
     * Time-complexity -> O(|V|+|E|)
     * @param v
     * @return Int with biggest diameter starting at node v
     */
    int bfs(int v);
    /**
     * Applies the bfs algorithm to find the shortest possible path between two nodes.
     * Time-complexity -> O(n(|V|+|E|))
     * @param start
     * @param end
     * @param permittedAirlines
     */
    void getShortestPath(const string& start,const string& end);  //base case not used
    /**
     * Applies the bfs algorithm to find the shortest possible path between two nodes, but only through the Airlines provided in the permittedAirlines vector.
     * Time-complexity -> O((n^2)*(|V|+|E|))
     * @param start
     * @param end
     * @param permittedAirlines
     */
    void getShortestFilteredPath(const string& start,const string& end,const set<string>& permittedAirlines);
    /**
     * Applies the bfs algorithm to find the shortest possible path between a list of airports as a starting point and a single Airport as the finishing point.
     * Time-complexity -> O((n^2)*(|V|+|E|))
     * @param airports
     * @param end
     * @param permittedAirlines
     */
    void getShortestPathFromList(const list<int>& airports,const string& end);
    /**
     * Applies the bfs algorithm to find the shortest possible path between a list of airports as a starting point and a single Airport as the finishing point, but only through the Airlines provided in the permittedAirlines vector.
     * Time-complexity -> O((n^3)*(|V|+|E|))
     * @param airports
     * @param end
     * @param permittedAirlines
     */
    void getShortestFilteredPathFromList(const list<int>& airports,const string& end,const set<string>& permittedAirlines);
    /**
     * Reads the airlines.csv file and, line by line, creates an Airline object with the information provided in the file and inserts into the map "airlineCodes" the Airline code as the key and the Airline object as the value. It also keeps count of the number of Airlines it reads and attributes that value to nAirlines in the Graph.
     * Time-complexity -> O(n)
     * @param file
     */
    void getAirlines(string file);
    /**
     * Reads the flights.csv file and, line by line, checks if there is already a flight from that source Airport to the same target Airport-if there is then it adds the airline of that flight to the list of airlines of that flight, if there isn't then it connects the two airports through the addEdge method. It also keeps count of the number of flights it reads and attributes that value to nFlights in the Graph.
     * Time-complexity -> O(n)
     * @param file
     */
    void getFlights(string file);
    /**
     * Adds a new flight from the src node to the dest node with the "airline" airline in the list of airlines.
     * Time-complexity -> O(1)
     * @param src
     * @param dest
     * @param airline
     */
    void addEdge(int src, int dest, const Airline& airline);
    /**
     * Traverses the given queue and adds to the vector nodes each Airport and adds to the map airportIndex the Airport code as a key and the index of the Airport in the vector nodes as the value.
     * Time-complexity -> O(n)
     * @param airports
     */
    void addAirports(queue<Airport> airports);
    /**
     * Adds to the cityAirports map the name of a city as a key and a vector with every airport in that city as a value.
     * Time-complexity -> O(n)
     */
    void addCityAirports();
    /**
     * Loops through the vector of airports in the cityAirports respective to the provided city and prints every airport in it.
     * Time-complexity -> O(n)
     * @param city
     */
    void showCityAirports(const string& city);
    /**
     * Prints the number of articulation points.
     * Time-complexity -> O((|V|^2)+|E|)
     * @param permittedAirlines
     */
    void articulationPoints(const set<string>& permittedAirlines);  //articulation points
    /**
     *  Searches the graph through dfs for the sake of determining the articulation points.
     * Time-complexity -> O(|V|+|E|)
     * @param v
     * @param node_stack
     * @param res
     * @param index
     */
    void dfsArt(int v, stack<int>* node_stack, list<int>* res, int index); //articulation points whole graph
    /**
     * Searches the graph through dfs for the sake of determining the articulation points when only using the user defined airlines.
     * Time-complexity -> O(|V|+(|E|^2))
     * @param v
     * @param node_stack
     * @param res
     * @param index
     * @param permittedAirlines
     */
    void dfsFilteredArt(int v, stack<int>* node_stack, list<int>* res,int index, const set<string>& permittedAirlines); //articulation points
    /**
     * Prints the path from an airport to another including the intermediate steps and airlines used.
     * Time-complexity -> O(n)
     * @param end
     */
    void printPath(const string& end);
    /**
     * Shows the flights available in an airport.
     * Time-complexity -> O(|E|)
     * @param airport
     */
    void getAvailableFlights(const string& airport);
    /**
     * Shows the possible airports reachable directly from an airport.
     * Time-complexity -> O(|E|)
     * @param airport
     */
    void getDestinations(const string& airport);
    /**
     * Shows the countries,cities and airports (including paths) reachable with a certain amount of flights starting from an airport.
     * Time-complexity -> O((n^2)*(|V|+|E|))
     * @param start
     * @param maxFlights
     */
    void getStats(const string& start,int maxFlights); //reachable stat with max flights per starting  airport
    /**
     * Resets some graph variables to ensure no errors in other functions.
     * Time-complexity -> O(n)
     */
    void clearData();
    /**
     * Calculates the graph diameter.
     * Time-complexity -> O(n*(|V|+|E|))
     */
    void calculateDiameter();  //diametro
    /**
     * Shows the top k airports with the most flights in descending order.
     * Time-complexity -> O(nlog(n)+n)
     * @param k
     */
    void airportMostFlights(int k); // top-k with most flights
    /**
     * Check whether an airport exists or not.
     * Time-complexity -> O(1)
     * @param airport
     * @return True if airport exists and false otherwise
     */
    bool isValidAirport(string airport);
    /**
     * Check whether an airline exists or not.
     * Time-complexity -> O(1)
     * @param airline
     * @return True if airline exists and false otherwise
     */
    bool isValidAirline(string airline);
    /**
     * Check whether an City exists/has an airport or not.
     * Time-complexity -> O(1)
     * @param city
     * @return True if city exists and false otherwise
     */
    bool isValidCity(string city);
    /**
     * Return the airports that are less than (range) kilometers from the position determined by the latitude and longitude.
     * Time-complexity -> O(n)
     * @param latitude
     * @param longitude
     * @param range
     * @return The airports in that area in the form of a list of the index in nodes
     */
    list<int> getCloseAirports(double latitude, double longitude, int range);
    /**
     * Return airportindex which is a map where the key is the airport code and the value is the index of that airport in nodes.
     * Time-complexity -> O(1)
     * @return airportindex-a map where the key is the airport code and the value is the index of that airport in nodes
     */
    unordered_map<string,int> getAirports();
    /**
     * Return airlineCodes which is a map where the key is the airline code and the value is the Airline object with the correspondent code.
     * Time-complexity -> O(1)
     * @return airlineCodes-a map where the key is the airline code and the value is the Airline object with the correspondent code
     */
    unordered_map<string,Airline> getAirlineCodes();
    /**
     * Return cityAirports which is a map where the key is the city name and the value is the vector with the airport objects in the city.
     * Time-complexity -> O(1)
     * @return cityAirports-a map where the key is the city name and the value is the vector with the airport objects in the city
     */
    unordered_map<string,vector<Airport>> getCityAirports();
    /**
     * Compares nodes for the sake of sorting. If the numeric value of the size of the flights vector in n1 is higher than that of n2 it returns true, else it returns false.
     * Time-complexity -> O(1)
     * @param n1
     * @param n2
     * @return True if node n1 has more flights than node n2
     */
    bool static compare(Node n1, Node n2);
};

#endif


#endif //PROJETO_AED_2_GRAPH_H
