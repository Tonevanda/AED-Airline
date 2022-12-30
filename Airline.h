//
// Created by João Lourenço on 28/12/2022.
//

#ifndef PROJETO_AED_2_AIRLINE_H
#define PROJETO_AED_2_AIRLINE_H

#include <string>

using namespace std;

class Airline {
private:
    string code;
    string name;
    string callSign;
    string country;
public:
    Airline();
    Airline(string code, string name, string callSign, string country);
    string getCode();
    string getName();
    string getCallSign();
    string getCountry();
};


#endif //PROJETO_AED_2_AIRLINE_H
