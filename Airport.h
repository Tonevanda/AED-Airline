//
// Created by João Lourenço on 28/12/2022.
//

#ifndef PROJETO_AED_2_AIRPORT_H
#define PROJETO_AED_2_AIRPORT_H

#include <string>
#include <cmath>

using namespace std;

class Airport {
private:
    string code;
    string name;
    string city;
    string country;
    double latitude;
    double longitude;
public:
    Airport();
    Airport(string code, string name, string city, string country, double latitude, double longitude);
    string getCode();
    string getName();
    string getCity();
    string getCountry();
    double getLatitude() const;
    double getLongitude() const;
    double distanceTo(double latitude, double longitude) const;
    bool isBetween(double latitude, double longitude, int kilometers) const;
};


#endif //PROJETO_AED_2_AIRPORT_H
