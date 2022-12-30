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

string Airline::getCode() const{
    return code;
}

string Airline::getName()const {
    return name;
}

string Airline::getCallSign() const{
    return callSign;
}

string Airline::getCountry()const {
    return country;
}