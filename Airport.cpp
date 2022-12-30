//
// Created by João Lourenço on 28/12/2022.
//

#include "Airport.h"

#include <utility>

Airport::Airport() {
    NULL;
}

Airport::Airport(string code, string name, string city, string country, double latitude, double longitude) {
    this->code=std::move(code);
    this->name=std::move(name);
    this->city=std::move(city);
    this->country=std::move(country);
    this->latitude=latitude;
    this->longitude=longitude;
}

string Airport::getCode() {
    return code;
}

string Airport::getName() {
    return name;
}

string Airport::getCity() {
    return city;
}

string Airport::getCountry() {
    return country;
}

double Airport::getLatitude() const {
    return latitude;
}

double Airport::getLongitude() const {
    return longitude;
}
