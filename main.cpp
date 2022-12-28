#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graph.h"
#include "Airport.h"

int addAirports(string file){
    cout<<"Reading Airports file...\n";
    ifstream fout;
    file="../"+file;
    fout.open(file);
    string tempstream,airportCode,airportName,airportCity,airportCountry,airportLatitude,airportLongitude;
    getline (fout, tempstream);
    int numAirports=0;
    while (getline (fout, tempstream)) {
        stringstream it_stream(tempstream);
        getline(it_stream,airportCode,',');
        getline(it_stream,airportName,',');
        getline(it_stream,airportCity,',');
        getline(it_stream,airportCountry,',');
        getline(it_stream,airportLatitude,',');
        getline(it_stream,airportLongitude,'\r');

        float latitude = stof(airportLatitude);
        float longitude = stof(airportLongitude);
        Airport airport = Airport(airportCode,airportName,airportCity,airportCountry,latitude,longitude);
        numAirports++;
    }
    cout << "Finished reading.\n";
    fout.close();
    return numAirports;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    int sizeGraph = addAirports("dataset/airports.csv");
    Graph airportGraph = Graph(sizeGraph,true);
    vector<vector<int>> adjacencyMatrix(sizeGraph, vector<int>(sizeGraph,0));
    //read flights and add edge
    //also create a map<code,int> that maps the airport code to the number of the node
    //because nodes[2] is the node numbered 2 but we cant do nodes["cdg"] because "cdg" is not an index
    //so to access a node using its code we need to map the codes to the position of the nodes in the vector nodes
    //.....
    //check in the adjacency matrix if the edge already exists, for example:
    // if airport 1 goes to airport 2 check if adjacencyMatrix[1][2] is 1
    //if it is then call addAirlineToFlight(1,2,nameoftheairline) otherwise just call addEdge like usual
    cout << "Got here";
    return 0;
}
