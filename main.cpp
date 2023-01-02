#include <iostream>
#include <string>
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

        double latitude = stod(airportLatitude);
        double longitude = stod(airportLongitude);
        Airport airport = Airport(airportCode,airportName,airportCity,airportCountry,latitude,longitude);
        airports.push(airport);
    }
    cout << "Finished reading.\n";
    fout.close();
    return airports;
}

void menuLocal(const Graph& airportGraph) {
    bool canRun = true;
    int n;
    while (canRun) {
        int input;
        cout << "Choose a starting point. \n"
                "1: Airport\n"
                "2: City\n"
                "3: Coordinates\n"
                "0: Return\n";
        while (!(cin >> input)) {
            cout << "Invalid input!\n\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Choose a starting point. \n"
                    "1: Airport\n"
                    "2: City\n"
                    "3: Coordinates\n"
                    "0: Return\n";
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        switch (input) {
            case 0:
                canRun = false;
                break;
            case 1:
                cout << "Input Airport Code:\n";
                while (!(cin >> input)) {
                    cout << "Invalid input!\n\n";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Input Airport Code:\n";
                }
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Choose a course of action.\n"
                        "1: Shortest path to another airport\n"
                        "2: Check information"
        }
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    queue<Airport> airports = getAirports("dataset/airports.csv");
    int sizeGraph = airports.size();
    Graph airportGraph = Graph(sizeGraph);
    airportGraph.addAirports(airports);
    airportGraph.getAirlines("dataset/airlines.csv");
    airportGraph.getFlights("dataset/flights.csv");
    menuLocal(airportGraph);
    //airportGraph.showCityAirports("Paris");

    //airportGraph.getShortestPath("CDG","LGA");

    //airportGraph.getAvailableFlights("CDG");

    //airportGraph.getDestinations("CDG");

    //set<string> permittedAirlines;

    //permittedAirlines.insert("AFR");
    //permittedAirlines.insert("DAL");

    //airportGraph.getShortestFilteredPath("CDG","LGA",permittedAirlines);

    //airportGraph.getCloseAirports(49.012779,2.550000,1000);

    //airportGraph.getStats("CDG",3);

    cout << "Got here";
    return 0;
}


/*
 * FAZER A CENA DOS PAISES E CIDADES
 * MENU
 *
 * EXTRA:
 * De quantos países diferentes?
 * Quantos aeroportos, cidades ou países são atingíveis usando um máximo de Y voos?
 *
 *
 */