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
    vector<Airline> airlines;
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
        for(auto &e : nodes[airportIndex[source]].flights) {
            if (e.dest == airportIndex[target]) {
                e.airlines.push_back(airlines[airline]);
                found=true;
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
/*
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
*/


void Graph::getShortestPath(string start,string end){
    cout<<airportIndex[start];
    int v=airportIndex[start];
    int finalpos=INT_MAX;
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
        int current = q.front(); q.pop();
        if(nodes[current].distance==finalpos){break;}
        for (auto e : nodes[current].flights) {
            int next = e.dest;
            if(next==airportIndex[end]){finalpos=nodes[current].distance + 1;}
            if (!nodes[next].visited || nodes[next].distance==nodes[current].distance + 1) {
                q.push(next);
                nodes[next].visited = true;
                nodes[next].distance = nodes[current].distance + 1;
                /*
                for(auto pathIt:nodes[current].path){
                    vector<int>temp=pathIt;
                    temp.push_back(next);
                    nodes[next].path.push_back(temp);
                }
                */
                for(auto airline: e.airlines){
                    //cout << airline.getCode() << " ";
                    for(auto pathIt:nodes[current].path){
                        vector<int>temp=pathIt;
                        temp.push_back(next);
                        nodes[next].path.push_back(temp);
                    }
                    if(nodes[current].pathAirlines.empty()){
                        vector<Airline>temp2;
                        temp2.push_back(airline);
                        nodes[next].pathAirlines.push_back(temp2);
                    }
                    else{
                        for(auto airlines:nodes[current].pathAirlines){
                            vector<Airline>temp2=airlines;
                            temp2.push_back(airline);
                            nodes[next].pathAirlines.push_back(temp2);
                        }
                    }

                }
            }
        }
    }
    /*
    int c=1;
    for(auto it:nodes[airportIndex["LGA"]].path){
        cout<<c<<" ";
        for(auto it2:it){
            cout<<nodes[it2].airport.getCode()<<" ";
        }
        cout<<"\n";
        c++;
    }*/
    printPath(end);
}

void Graph::printPath(string end) {
    int counter = 1;
    for(int i=0;i<nodes[airportIndex[end]].path.size();i++){
        cout << "Shortest Path " << counter << ": ";
        int tempc = 0;
        int temp=0;
        while(temp<nodes[airportIndex[end]].path[i].size()-1)
        {
            if(temp==nodes[airportIndex[end]].path[i].size()-2){
                cout <<"using "<< nodes[airportIndex[end]].pathAirlines[i][tempc].getCode()<<" airlines to go from "<<nodes[nodes[airportIndex[end]].path[i][temp]].airport.getCode() << " to "<<nodes[nodes[airportIndex[end]].path[i][++temp]].airport.getCode();
            }
            else{
                cout <<"using "<< nodes[airportIndex[end]].pathAirlines[i][tempc].getCode()<<" airlines to go from "<<nodes[nodes[airportIndex[end]].path[i][temp]].airport.getCode() << " to "<<nodes[nodes[airportIndex[end]].path[i][++temp]].airport.getCode()<<" and ";
            }

            /*
            if (tempc == nodes[airportIndex[end]].path[i].size()-1) {
                cout << nodes[temp].airport.getCode();
            } else {
                cout << nodes[airportIndex[end]].pathAirlines[i][tempc].getCode()<<" from "<<nodes[temp].airport.getCode() << " to ";
            }*/
            tempc++;
        }
        counter++;
        cout << "\n";
    }
    /*
    for (auto it: nodes[airportIndex[end]].path) {
        cout << "shortest path" << counter << ": ";
        int tempc = 1;
        for (auto temp: it) {
            if (tempc == it.size()) {
                cout << nodes[temp].airport.getName();
            } else {
                cout << nodes[temp].airport.getName() << " -> ";
            }
            tempc++;
            cout << "\n";
            counter++;
        }
    }*/
}