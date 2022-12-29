#include "graph.h"
#include "Airport.h"
#include "Airline.h"
#include <fstream>
#include <sstream>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num) : n(num), nodes(num+1) {

}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, Airline airline) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    list<Airline> airlines;
    airlines.push_back(airline);
    nodes[src].flights.push_back({dest, airlines});
}

void Graph::addAirports(queue<Airport> airports){
    unordered_map<string, int> index;
    int count = 1;
    while (!airports.empty()){
        nodes[count].airport = airports.front();
        index.insert({airports.front().getCode(),count});
        airports.pop();
        count++;
    }
    airportIndex=index;
}

unordered_map<string,int> Graph::getAirports(){
    return airportIndex;
}
void Graph::getAirlines(string file){
    cout<<"Reading Airlines file...\n";
    unordered_map<string,Airline> index;
    ifstream fout;
    file="../"+file;
    fout.open(file);
    string tempstream,Code,Name,Callsign,Country;
    getline (fout, tempstream);
    queue<Airport> airports;
    while (getline (fout, tempstream)) {
        stringstream it_stream(tempstream);
        getline(it_stream,Code,',');
        getline(it_stream,Name,',');
        getline(it_stream,Callsign,',');
        getline(it_stream,Country,'\r');
        Airline airline = Airline(Code,Name,Callsign,Country);
        index.insert({Code,airline});
    }
    cout << "Finished reading.\n";
    airlines=index;
    fout.close();
}
void Graph::getFlights(string file){
    cout<<"Reading flights file...\n";
    ifstream fout;
    file="../"+file;
    fout.open(file);
    string tempstream,source,target,airline;
    getline (fout, tempstream);
    queue<Airport> airports;
    while (getline (fout, tempstream)) {
        stringstream it_stream(tempstream);
        getline(it_stream,source,',');
        getline(it_stream,target,',');
        getline(it_stream,airline,'\r');
        //if(airportIndex[Source] < 1 || airportIndex[Source]>n || Target<1 || Airline>n) return;
        bool found=false;
        for(auto e : nodes[airportIndex[source]].flights) {
            if (e.dest == airportIndex[target]) {
                e.airlines.push_back(airlines[airline]);
                found=true;
                break;
            }
        }
        if(!found)addEdge(airportIndex[source], airportIndex[target], airlines[airline]);
    }
    cout << "Finished reading.\n";
    fout.close();
}
// Depth-First Search: example implementation
void Graph::dfs(int v) {
    nodes[v].visited = true;
    for (auto e : nodes[v].flights) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}

// Breadth-First Search: example implementation
void Graph::bfs(int v) {
    for (int i=1; i<=n; i++) {
        nodes[i].visited = false;
        nodes[i].distance = -1;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].distance = 0;
    nodes[v].visited = true;
    nodes[v].path.clear();
    nodes[v].path.push_back({v});
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (auto e : nodes[u].flights) {
            cout<<nodes[u].distance;
            int w = e.dest;
            if (!nodes[w].visited || nodes[w].distance==nodes[u].distance + 1) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
                for(auto it:nodes[u].path){
                    vector<int>temp=it;
                    temp.push_back(w);
                    nodes[w].path.push_back(temp);
                }
            }
        }
    }
}

void Graph::printPath(){
    int counter=1;
    for(auto it:nodes[airportIndex["IST"]].path){
        cout<<"shortest path"<<counter<<":";
        for(auto temp:it){
            cout<<" -> "<<nodes[temp].airport.getName();
        }
        cout<<"\n";
        counter++;
    }
}