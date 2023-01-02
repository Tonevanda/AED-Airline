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


void menu(Graph& airportGraph,int nflights) {
    bool canRun = true;
    int n;
    set<string> permitedAirlines;
    while (canRun) {
        int input;
        cout << "Do you wish to specify airlines?\n"
                "1:Yes\n"
                "0:No";
        while (!(cin >> input)) {
            cout << "Invalid input!\n\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Do you wish to specify airlines?\n"
                    "1:Yes"
                    "0:No";
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');

        switch (input) {
            case 0:{
                string code;
                Airline airline;
                for(auto const & [code,airline]:airportGraph.getAirlineCodes()){
                    permitedAirlines.insert(code);
                }
                canRun = false;
                break;
            }
            case 1: {
                bool inputing = true;
                while (inputing) {
                    string inputAirline;
                    cout << "input the airline code\n";
                    while (!(cin >> input)) {
                        cout << "Invalid input!\n\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "input the airline code\n";
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    permitedAirlines.insert(inputAirline);
                    inputing = false;
                }
                break;
            }
        }
    }
    bool canRun1 = true;
    while (canRun1) {
        int input;
        cout << "Choose a starting point. \n"
                "1: Airport\n"
                "2: City\n"
                "3: Coordinates\n"
                "0: End Program\n";
        while (!(cin >> input)) {
            cout << "Invalid input!\n\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Choose a starting point. \n"
                    "1: Airport\n"
                    "2: City\n"
                    "3: Coordinates\n"
                    "0: End Program\n";
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        switch (input) {
            case 0:
                canRun1 = false;
                break;
            case 1: {
                string start;
                cout << "Input Airport Code:\n";
                while (!(cin >> start)) {
                    cout << "Invalid input!\n\n";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Input Airport Code:\n";
                }
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                bool canRun2 = true;
                while (canRun2) {
                    cout << "Choose a course of action.\n"
                            "1: Shortest path to another airport\n"
                            "2: Check information\n"
                            "0: Other starting point";
                    while (!(cin >> input)) {
                        cout << "Invalid input!\n\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "Choose a course of action.\n"
                                "1: Shortest path to another airport\n"
                                "2: Check information\n"
                                "0: Other starting point";
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    string end;
                    switch (input) {
                        case 0:
                            canRun2 = false;
                            break;
                        case 1:
                            cout << "Input Second Airport Code:\n";
                            while (!(cin >> end)) {
                                cout << "Invalid input!\n\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Input Second Airport Code:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            airportGraph.getShortestFilteredPath(start, end, permitedAirlines);
                            break;
                        case 2:
                            airportGraph.getAvailableFlights(start);
                            airportGraph.getDestinations(start);
                            break;
                    }
                }
            }
            case 2:{
                string start;
                cout << "Input City Name:\n";
                while (!(cin >> start)) {
                    cout << "Invalid input!\n\n";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Input City Name:\n";
                }
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
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
    int nflights = airportGraph.getFlights("dataset/flights.csv");
    //cout << nflights;
    airportGraph.addCityAirports();
    menu(airportGraph,nflights);

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

    //airportGraph.articulationPoints();

    cout << "Got here";
    return 0;
}


/*
 * FAZER A CENA DOS PAISES E CIDADES
 * MENU
 *
 * n airoportos:graph.n,n airlines:airline codes.size,n voos
 * diametro do grafo
 *
 * EXTRA:
 * De quantos países diferentes?
 * Quantos aeroportos, cidades ou países são atingíveis usando um máximo de Y voos?
 *
 *
 */