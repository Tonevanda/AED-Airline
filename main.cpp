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
    fout.close();
    return numAirports;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    int sizeGraph = addAirports("dataset/airports.csv");
    Graph airportGraph = Graph(sizeGraph,true);
    //read flights and add edge

    return 0;
}
