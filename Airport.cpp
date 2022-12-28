//
// Created by João Lourenço on 28/12/2022.
//

#include "Airport.h"

Airport::Airport() {
    NULL;
}

Airport::Airport(string code, string name, string city, string country, float latitude, float longitude) {
    this->code=code;
    this->name=name;
    this->city=city;
    this->country=country;
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

float Airport::getLatitude() {
    return latitude;
}

float Airport::getLongitude() {
    return longitude;
}