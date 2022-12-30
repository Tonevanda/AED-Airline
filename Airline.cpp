//
// Created by João Lourenço on 28/12/2022.
//

#include "Airline.h"

#include <utility>
Airline::Airline(){
    NULL;
}

Airline::Airline(string code, string name, string callsign, string country) {
    this->code=std::move(code);
    this->name=std::move(name);
    this->callSign=std::move(callsign);
    this->country=std::move(country);
}

string Airline::getCode() {
    return code;
}

string Airline::getName() {
    return name;
}

string Airline::getCallSign() {
    return callSign;
}

string Airline::getCountry() {
    return country;
}