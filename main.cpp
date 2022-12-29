#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graph.h"
#include "Airport.h"

queue<Airport> getAirports(string file){
    cout<<"Reading Airports file...\n";
    ifstream fout;
    file="../"+file;
    fout.open(file);
    string tempstream,airportCode,airportName,airportCity,airportCountry,airportLatitude,airportLongitude;
    getline (fout, tempstream);
    queue<Airport> airports;
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
        airports.push(airport);
    }
    cout << "Finished reading.\n";
    fout.close();
    return airports;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    queue<Airport> airports = getAirports("dataset/airports.csv");
    int sizeGraph = airports.size();
    Graph airportGraph = Graph(sizeGraph);
    airportGraph.addAirports(airports);
    airportGraph.getAirlines("dataset/airlines.csv");
    airportGraph.getFlights("dataset/flights.csv");
    airportGraph.bfs(airportGraph.getAirports()["DXB"]);
    airportGraph.printpath();
    //for(auto n : airportGraph.)

    //read flights.csv and add edge
    //also create a map<code,int> that maps the airport code to the number of the node nodes["cdg"] map<string,int>
    //because nodes[2] is the node numbered 2 but we cant do nodes["cdg"] because "cdg" is not an index
    //so to access a node using its code we need to map the codes to the position of the nodes in the vector nodes
    //.....
    //check in the adjacency matrix if the edge already exists, for example:
    // if airport 1 goes to airport 2 check if adjacencyMatrix[1][2] is 1
    //if it is then call addAirlineToFlight(1,2,nameoftheairline) otherwise just call addEdge like usual
    cout << "Got here";
    return 0;
}
