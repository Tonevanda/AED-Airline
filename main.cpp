#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "graph.h"
#include "Airport.h"

queue<Airport> getAirports(string file){
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
    fout.close();
    return airports;
}


void menu(Graph& airportGraph) {
    bool canRun = true;
    set<string> permittedAirlines;
    while (canRun) {
        int input;
        cout << "Do you wish to specify airlines?\n"
                "1:Yes\n"
                "2:No\n"
                "0:End Program\n";
        while (!(cin >> input)) {
            cout << "Invalid input!\n\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Do you wish to specify airlines?\n"
                    "1:Yes\n"
                    "2:No\n"
                    "0:End Program\n";
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        bool canRun1 = true;
        switch (input) {
            case 0:
                canRun1 = false;
                canRun = false;
                break;
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
                    permittedAirlines.insert(inputAirline);
                    inputing = false;
                }
                break;
            }
            case 2:{
                string code;
                Airline airline;
                for(auto const & [code,airline]:airportGraph.getAirlineCodes()){
                    permittedAirlines.insert(code);
                }
                canRun = false;
                break;
            }
            default:{
                cout << "Invalid input!\n\n";
                canRun1 = false;
            }
        }
        while (canRun1) {
            int input;
            cout << "Choose a starting point.\n"
                    "0: Change Specified Airlines\n"
                    "1: Airport\n"
                    "2: City\n"
                    "3: Coordinates\n"
                    "9: End Program\n";
            while (!(cin >> input)) {
                cout << "Invalid input!\n\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Choose a starting point.\n"
                        "0: Change Specified Airlines\n"
                        "1: Airport\n"
                        "2: City\n"
                        "3: Coordinates\n"
                        "9: End Program\n";
            }
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            switch (input) {
                case 0:
                    canRun1 = false;
                    canRun = true;
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
                                "0: Go back\n"
                                "1: Shortest path to another airport\n"
                                "2: Check information\n"
                                "9: End Program\n";

                        while (!(cin >> input)) {
                            cout << "Invalid input!\n\n";
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cout << "Choose a course of action.\n"
                                    "0: Go back\n"
                                    "1: Shortest path to another airport\n"
                                    "2: Check information\n"
                                    "9: End Program\n";
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
                                airportGraph.getShortestFilteredPath(start, end, permittedAirlines);
                                break;
                            case 2:
                                airportGraph.getAvailableFlights(start);
                                airportGraph.getDestinations(start);
                                break;
                            case 9:
                                canRun = false;
                                canRun1 = false;
                                canRun2 = false;
                                break;
                            default:
                                cout << "Invalid input!\n\n";
                        }
                    }
                    break;
                }
                case 2:{
                    string city;
                    cout << "Input City Name:\n";
                    while (!(cin >> city)) {
                        cout << "Invalid input!\n\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "Input City Name:\n";
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    string destination;
                    cout << "Input destination airport:\n";
                    while (!(cin >> destination)) {
                        cout << "Invalid input!\n\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "Input destination airport:\n";
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout<<endl;
                    list<int> start;
                    for (auto it: airportGraph.getCityAirports()[city]) {
                        start.push_back(airportGraph.getAirports()[it.getCode()]);
                    }
                    airportGraph.getShortestFilteredPathFromList(start,destination,permittedAirlines);
                    break;
                }
                case 3:{
                    double Latitude;
                    cout << "Input Latitude:\n";
                    while (!(cin >> Latitude)) {
                        cout << "Invalid input!\n\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "Input Latitude:\n";
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    double Longitude;
                    cout << "Input Longitude:\n";
                    while (!(cin >> Longitude)) {
                        cout << "Invalid input!\n\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "Input Longitude:\n";
                    }
                    int range;
                    cout << "Input range in km:\n";
                    while (!(cin >> range)) {
                        cout << "Invalid input!\n\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "Input range:\n";
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout<<endl;
                    string destination;
                    cout << "Input destination airport:\n";
                    while (!(cin >> destination)) {
                        cout << "Invalid input!\n\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "Input destination airport:\n";
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout<<endl;
                    airportGraph.getShortestFilteredPathFromList(airportGraph.getCloseAirports(Latitude,Longitude,range),destination,permittedAirlines);
                    airportGraph.clearData();
                    break;
                }
                case 9:{
                    canRun1 = false;
                    canRun = false;
                    break;
                }
                default:{
                    cout << "Invalid input!\n\n";
                }
            }
        }
    }
}


int main() {
    queue<Airport> airports = getAirports("dataset/testAirports.csv");
    int sizeGraph = airports.size();
    Graph airportGraph = Graph(sizeGraph);
    airportGraph.addAirports(airports);
    airportGraph.getAirlines("dataset/airlines.csv");
    airportGraph.getFlights("dataset/testFlights.csv");
    airportGraph.addCityAirports();
    //menu(airportGraph);
    airportGraph.calculateDiameter();
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
    //set<string> permittedAirlines2;
    //permittedAirlines2.insert("TOK");
    //airportGraph.articulationPoints(permittedAirlines2);

    //airportGraph.getShortestFilteredPathFromList("Paris","JFK",permittedAirlines);

    cout << "Got here";
    return 0;
}


/* verificar estatistica
 * adiciona opções de menu for unused functions
 * numero minimo de airlines num path
 *
 *
 *
 * EXTRA:
 * print path diferente?????
 *
 *
 */