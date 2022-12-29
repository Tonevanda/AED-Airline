//
// Created by João Lourenço on 28/12/2022.
//

#include "Airline.h"
Airline::Airline(){
    NULL;
}

Airline::Airline(string code, string name, string callsign, string country) {
    this->code=code;
    this->name=name;
    this->callsign=callsign;
    this->country=country;
}

string Airline::getCode() {
    return code;
}

string Airline::getName() {
    return name;
}

string Airline::getCallsign() {
    return callsign;
}

string Airline::getCountry() {
    return country;
}