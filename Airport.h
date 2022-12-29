//
// Created by João Lourenço on 28/12/2022.
//

#ifndef PROJETO_AED_2_AIRPORT_H
#define PROJETO_AED_2_AIRPORT_H

#include <string>


using namespace std;

class Airport {
private:
    string code;
    string name;
    string city;
    string country;
    float latitude;
    float longitude;
public:
    Airport();
    Airport(string code, string name, string city, string country, float latitude, float longitude);
    string getCode();
    string getName();
    string getCity();
    string getCountry();
    float getLatitude() const;
    float getLongitude() const;
};


#endif //PROJETO_AED_2_AIRPORT_H
