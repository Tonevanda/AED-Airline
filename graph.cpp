#include "graph.h"
#include "Airport.h"
#include "Airline.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <set>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num) : n(num), nodes(num+1) {}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, const Airline& airline) {
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

void Graph::addCityAirports(){
    unordered_map<string,vector<Airport>> temp;
    for(int i = 1; i<=n;i++){
        if(temp.find(nodes[i].airport.getCity()) == temp.end()){
            vector<Airport> airports;
            airports.push_back(nodes[i].airport);
            temp.insert({nodes[i].airport.getCity(),airports});
        }
        else{
            temp[nodes[i].airport.getCity()].push_back(nodes[i].airport);
        }
    }
    cityAirports = temp;
}


void Graph::showCityAirports(const string& city){
    for(Airport airport : cityAirports[city]){
        cout << airport.getCode() << ", " << airport.getName() << ", " << airport.getCity() << ", ";
    }
    cout << endl;
}



unordered_map<string,int> Graph::getAirports(){return airportIndex;}

unordered_map<string,Airline> Graph::getAirlineCodes() { return airlineCodes;}

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
    airlineCodes=index;
    fout.close();
}
int Graph::getFlights(string file){
    cout<<"Reading flights file...\n";
    ifstream fout;
    file="../"+file;
    fout.open(file);
    string tempstream,source,target,airline;
    getline (fout, tempstream);
    queue<Airport> airports;
    int counter=0;
    while (getline (fout, tempstream)) {
        stringstream it_stream(tempstream);
        getline(it_stream,source,',');
        getline(it_stream,target,',');
        getline(it_stream,airline,'\r');
        //if(airportIndex[Source] < 1 || airportIndex[Source]>n || Target<1 || Airline>n) return;
        bool found=false;
        for(auto &e : nodes[airportIndex[source]].flights) {
            if (e.dest == airportIndex[target]) {
                e.airlines.push_back(airlineCodes[airline]);
                found=true;
            }
        }
        if(!found)addEdge(airportIndex[source], airportIndex[target], airlineCodes[airline]);
        counter++;
    }
    cout << "Finished reading.\n";
    fout.close();
    return counter;
}

void Graph::articulationPoints(const set<string>& permittedAirlines) {
    list<int> res;
    for (Node& node : nodes) {
        node.visited = false;
        node.inStack = false;
        node.isArt = false;
    }
    stack<int> node_stack;

    for (int i = 1; i < nodes.size(); i++) {
        if (!nodes[i].visited)
            if(permittedAirlines.empty())
                dfsArt(i, &node_stack, &res,1);
            else dfsFilteredArt(i, &node_stack, &res, 1, permittedAirlines);
    }

    /*for(auto it = res.begin();it!=res.end();it++){
        cout << nodes[*it].airport.getCode() << "\n";
    }
     */
    cout << res.size() << endl;
    for(auto it = res.begin();it!=res.end();it++){
        cout << nodes[*it].airport.getCode() << endl;
    }
}

void Graph::dfsArt(int v, stack<int>* node_stack, list<int>* res, int index) {
    nodes[v].visited = true;
    nodes[v].low = index;
    nodes[v].num = index;
    index++;
    nodes[v].inStack = true;
    node_stack->push(v);

    int count = 0;
    for (auto e : nodes[v].flights) {
        int w = e.dest;
        if (!nodes[w].visited) {
            count++;
            dfsArt(w, node_stack, res, index);
            nodes[v].low = min(nodes[v].low, nodes[w].low);
        }
        else if (nodes[w].inStack) {
            nodes[v].low = min(nodes[v].low, nodes[w].num);
        }

        if (nodes[v].num != 1 && !nodes[v].isArt && nodes[w].low >= nodes[v].num) {
            res->push_back(v);
            nodes[v].isArt = true;
        }
        else if (!nodes[v].isArt && nodes[v].num == 1 && count > 1) {
            res->push_back(v);
            nodes[v].isArt = true;
        }
    }
    res->sort();
}

void Graph::dfsFilteredArt(int v, stack<int>* node_stack, list<int>* res, int index, const set<string>& permittedAirlines) {
    nodes[v].visited = true;
    nodes[v].low = index;
    nodes[v].num = index;
    index++;
    nodes[v].inStack = true;
    node_stack->push(v);

    int count = 0;
    for (const auto& e : nodes[v].flights) {
        int w = e.dest;
        for (const Airline& airline: e.airlines) {
            if(permittedAirlines.find(airline.getCode())!=permittedAirlines.end()) {
                if (!nodes[w].visited) {
                    count++;
                    dfsFilteredArt(w, node_stack, res, index, permittedAirlines);
                    nodes[v].low = min(nodes[v].low, nodes[w].low);
                } else if (nodes[w].inStack) {
                    nodes[v].low = min(nodes[v].low, nodes[w].num);
                }

                if (nodes[v].num != 1 && !nodes[v].isArt && nodes[w].low >= nodes[v].num) {
                    res->push_back(v);
                    nodes[v].isArt = true;
                } else if (!nodes[v].isArt && nodes[v].num == 1 && count > 1) {
                    res->push_back(v);
                    nodes[v].isArt = true;
                }
            }
        }
    }
    res->sort();
}

/*
void Graph::dfs(int v) {
    nodes[v].visited = true;
    for (const auto& e : nodes[v].flights) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}
*/
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
        for (const auto& e : nodes[u].flights) {
            cout<<nodes[u].distance;
            int w = e.dest;
            if (!nodes[w].visited || nodes[w].distance==nodes[u].distance + 1) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
                for(const auto& it:nodes[u].path){
                    vector<int>temp=it;
                    temp.push_back(w);
                    nodes[w].path.push_back(temp);
                }
            }
        }
    }
}

void Graph::getStats(const string& start,int finalpos){
    int v=airportIndex[start];
    for (int i=1; i<=n; i++) {
        nodes[i].visited = false;
        nodes[i].distance = -1;
    }
    queue<int> q; // queue of unvisited nodes
    set<int> availableAirports;
    set<string> availableCities;
    set<string> availableCountries;
    q.push(v);
    nodes[v].distance = 0;
    nodes[v].visited = true;
    nodes[v].path.clear();
    nodes[v].path.push_back({v});
    availableAirports.insert(v);
    availableCities.insert(nodes[v].airport.getCity());
    availableCountries.insert(nodes[v].airport.getCountry());
    while (!q.empty()) { // while there are still unvisited nodes
        int current = q.front(); q.pop();
        if(nodes[current].distance==finalpos){break;}
        for (const auto& flight : nodes[current].flights) {
            int nextNode = flight.dest;
            if (!nodes[nextNode].visited || nodes[nextNode].distance==nodes[current].distance + 1) {
                q.push(nextNode);
                nodes[nextNode].visited = true;
                nodes[nextNode].distance = nodes[current].distance + 1;
                availableAirports.insert(nextNode);
                availableCities.insert(nodes[nextNode].airport.getCity());
                availableCountries.insert(nodes[nextNode].airport.getCountry());
                for(const auto& airline: flight.airlines){      //iterate over every airline in an edge(flight)
                    for(const auto& pathIt:nodes[current].path){   //iterate over every path(vector with nodes) and add itself
                        vector<int>temp=pathIt;             //to the end of every path
                        temp.push_back(nextNode);
                        nodes[nextNode].path.push_back(temp);
                    }
                    if(nodes[current].pathAirlines.empty()){  //if the vector of vector of airlines is empty
                        vector<Airline>temp2;                 //creates an empty vector, adds itself to it and adds that
                        temp2.push_back(airline);             //vector to the list of pathAirlines
                        nodes[nextNode].pathAirlines.push_back(temp2);
                    }
                    else{
                        for(const auto& airlines:nodes[current].pathAirlines){ //iterate over every path of airlines in the vector pathAirlines
                            vector<Airline>temp2=airlines;              //create vector equal to the vector of airlines and adds itself to it
                            temp2.push_back(airline);                   //then adds that vector to the list of pathAirlines
                            nodes[nextNode].pathAirlines.push_back(temp2);
                        }
                    }
                }
            }
        }
    }
    //print: n1:airport in city,country (repeated)
    //print: n2:city in country         (repeated)
    //print: n3:country                 (repeated)
    //print n1 airports,n2 cities and n3 country
    int n1=1;
    for(auto it: availableAirports){
        cout<<n1<<": "<<nodes[it].airport.getCode()<<", "<<nodes[it].airport.getCode()<<", "<<nodes[it].airport.getCity()<<", "<<nodes[it].airport.getCountry()<<endl;
        n1++;
    }
    int n2=1;
    for(const auto& it: availableCities){
        cout<<n2<<": "<<it<<endl;
        n2++;
    }
    int n3=1;
    for(const auto& it: availableCountries){
        cout<<n3<<": "<<it<<endl;
        n3++;
    }
    cout<<"Total: "<<n1<<" Airports, "<<n2<<" Cities, "<<n3<<" Countries"<<endl;
}

void Graph::getShortestPath(const string& start,const string& end){
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
        for (const auto& flight : nodes[current].flights) {
            int nextNode = flight.dest;
            if(nextNode==airportIndex[end]){finalpos=nodes[current].distance + 1;}
            if (!nodes[nextNode].visited || nodes[nextNode].distance==nodes[current].distance + 1) {
                q.push(nextNode);
                nodes[nextNode].visited = true;
                nodes[nextNode].distance = nodes[current].distance + 1;
                for(const auto& airline: flight.airlines){      //iterate over every airline in an edge(flight)
                    for(const auto& pathIt:nodes[current].path){   //iterate over every path(vector with nodes) and add itself
                        vector<int>temp=pathIt;             //to the end of every path
                        temp.push_back(nextNode);
                        nodes[nextNode].path.push_back(temp);
                    }
                    if(nodes[current].pathAirlines.empty()){  //if the vector of vector of airlines is empty
                        vector<Airline>temp2;                 //creates an empty vector, adds itself to it and adds that
                        temp2.push_back(airline);             //vector to the list of pathAirlines
                        nodes[nextNode].pathAirlines.push_back(temp2);
                    }
                    else{
                        for(const auto& airlines:nodes[current].pathAirlines){ //iterate over every path of airlines in the vector pathAirlines
                            vector<Airline>temp2=airlines;              //create vector equal to the vector of airlines and adds itself to it
                            temp2.push_back(airline);                   //then adds that vector to the list of pathAirlines
                            nodes[nextNode].pathAirlines.push_back(temp2);
                        }
                    }
                }
            }
        }
    }
    printPath(end);
}

void Graph::getShortestFilteredPath(const string& start,const string& end,const set<string>& permittedAirlines){
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
        for (const auto& flight : nodes[current].flights) {
            int nextNode = flight.dest;
            if(nextNode==airportIndex[end]){finalpos=nodes[current].distance + 1;}
            if ((!nodes[nextNode].visited || nodes[nextNode].distance==nodes[current].distance + 1)) {
                bool hasValidAirline=false;
                for(const auto& airline: flight.airlines){      //iterate over every airline in an edge(flight)
                    if(permittedAirlines.find(airline.getCode()) != permittedAirlines.end()) {
                        hasValidAirline=true;
                        for (const auto &pathIt: nodes[current].path) {   //iterate over every path(vector with nodes) and add itself
                            vector<int> temp = pathIt;             //to the end of every path
                            temp.push_back(nextNode);
                            nodes[nextNode].path.push_back(temp);
                        }
                        if (nodes[current].pathAirlines.empty()) {  //if the vector of vector of airlines is empty
                            vector<Airline> temp2;                 //creates an empty vector, adds itself to it and adds that
                            temp2.push_back(airline);             //vector to the list of pathAirlines
                            nodes[nextNode].pathAirlines.push_back(temp2);
                        } else {
                            for (const auto &airlines: nodes[current].pathAirlines) { //iterate over every path of airlines in the vector pathAirlines
                                vector<Airline> temp2 = airlines;              //create vector equal to the vector of airlines and adds itself to it
                                temp2.push_back(airline);                   //then adds that vector to the list of pathAirlines
                                nodes[nextNode].pathAirlines.push_back(temp2);
                            }
                        }
                    }
                }
                if(hasValidAirline){
                    q.push(nextNode);
                    nodes[nextNode].visited = true;
                    nodes[nextNode].distance = nodes[current].distance + 1;
                }
            }
        }
    }
    printPath(end);
}
void Graph::getShortestFilteredPathFromCity(string city,const string& end,const set<string>& permittedAirlines){
    vector<int> startingPoints;
    for (int i=1; i<=n; i++) {
        nodes[i].visited = false;
        nodes[i].distance = -1;
        if(nodes[i].airport.getCity()==city){
            startingPoints.push_back(i);
        }
    }
    for(auto v:startingPoints){
        int finalpos=INT_MAX;
        queue<int> q; // queue of unvisited nodes
        q.push(v);
        nodes[v].distance = 0;
        nodes[v].visited = true;
        nodes[v].path.clear();
        nodes[v].path.push_back({v});
        while (!q.empty()) { // while there are still unvisited nodes
            int current = q.front(); q.pop();
            if(nodes[current].distance==finalpos){break;}
            for (const auto& flight : nodes[current].flights) {
                int nextNode = flight.dest;
                if(nextNode==airportIndex[end]){
                    if(!nodes[nextNode].pathAirlines.empty() && nodes[nextNode].path.front().size()>nodes[current].path.front().size()+1){
                        nodes[nextNode].pathAirlines.clear();
                    }
                    else if(!nodes[nextNode].pathAirlines.empty() && nodes[nextNode].path.front().size()<nodes[current].path.front().size()+1){
                        break;
                    }
                    finalpos=nodes[current].distance + 1;
                }
                if ((!nodes[nextNode].visited || nodes[nextNode].distance==nodes[current].distance + 1)) {
                    bool hasValidAirline=false;
                    for(const auto& airline: flight.airlines){      //iterate over every airline in an edge(flight)
                        if(permittedAirlines.find(airline.getCode()) != permittedAirlines.end()) {
                            hasValidAirline=true;
                            for (const auto &pathIt: nodes[current].path) {   //iterate over every path(vector with nodes) and add itself
                                vector<int> temp = pathIt;             //to the end of every path
                                temp.push_back(nextNode);
                                nodes[nextNode].path.push_back(temp);
                            }
                            if (nodes[current].pathAirlines.empty()) {  //if the vector of vector of airlines is empty
                                vector<Airline> temp2;                 //creates an empty vector, adds itself to it and adds that
                                temp2.push_back(airline);             //vector to the list of pathAirlines
                                nodes[nextNode].pathAirlines.push_back(temp2);
                            } else {
                                for (const auto &airlines: nodes[current].pathAirlines) { //iterate over every path of airlines in the vector pathAirlines
                                    vector<Airline> temp2 = airlines;              //create vector equal to the vector of airlines and adds itself to it
                                    temp2.push_back(airline);                   //then adds that vector to the list of pathAirlines
                                    nodes[nextNode].pathAirlines.push_back(temp2);
                                }
                            }
                        }
                    }
                    if(hasValidAirline){
                        q.push(nextNode);
                        nodes[nextNode].visited = true;
                        nodes[nextNode].distance = nodes[current].distance + 1;
                    }
                }
            }
        }
        for (int i=1; i<=n; i++) {
            nodes[i].visited = false;
            nodes[i].distance = -1;
            if(i!=airportIndex[end]){
                nodes[i].path.clear();
                nodes[i].pathAirlines.clear();
            }
        }
    }
    printPath(end);
}
void Graph::getAvailableFlights(const string& airport){
    int count = 1;
    set<string> airlineCount;
    for(const auto& destination : nodes[airportIndex[airport]].flights){
        for(const auto& airline : destination.airlines) {
            airlineCount.insert(airline.getCode());
            cout << count << ": using " << airline.getCode() << " airlines to go to " << nodes[destination.dest].airport.getCode()<<endl;
            count++;
        }
    }
    cout << "Number of different airlines: " << airlineCount.size() << "\n";
}

void Graph::getDestinations(const string& airport){
    cout <<"Available destinations: \n";
    int count = 1;
    for(const auto& it:nodes[airportIndex[airport]].flights){
        cout << count << ":" << nodes[it.dest].airport.getCode() << " (" << nodes[it.dest].airport.getName() << ")\n" ;
        count++;
    }
}

void Graph::getCloseAirports(double latitude, double longitude, int kilometers) {
    int countAirport = 1;
    for(int i = 1; i<=n;i++){
        if(nodes[i].airport.isBetween(latitude, longitude, kilometers)){
            cout <<  countAirport << ": " << nodes[i].airport.getCode() << " | " << nodes[i].airport.getName() << " | " << nodes[i].airport.getCity() << ", " << nodes[i].airport.getCountry() <<endl;
            countAirport++;
        }
    }
}

void Graph::printPath(const string& end) {
    int counter = 1;
    for(int i=0;i<nodes[airportIndex[end]].path.size();i++){
        cout << "Shortest Path " << counter << ": ";
        int index=0;
        while(index<nodes[airportIndex[end]].path[i].size()-1){
            if(index==nodes[airportIndex[end]].path[i].size()-2){
                cout <<"using "<< nodes[airportIndex[end]].pathAirlines[i][index].getCode()<<" airlines to go from "<<nodes[nodes[airportIndex[end]].path[i][index]].airport.getCode() << " to "<<nodes[nodes[airportIndex[end]].path[i][++index]].airport.getCode();
            }
            else{
                cout <<"using "<< nodes[airportIndex[end]].pathAirlines[i][index].getCode()<<" airlines to go from "<<nodes[nodes[airportIndex[end]].path[i][index]].airport.getCode() << " to "<<nodes[nodes[airportIndex[end]].path[i][++index]].airport.getCode()<<" and ";
            }
        }
        counter++;
        cout << "\n";
    }
}