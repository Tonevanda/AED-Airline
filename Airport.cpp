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

double Airport::distanceTo(double latitude2, double longitude2) const {
    double latitude1 = this->getLatitude();
    double longitude1 = this->getLongitude();

    double dLat = (latitude2-latitude1)* M_PI / 180.0;
    double dLon = (longitude2-longitude1)* M_PI / 180.0;

    latitude1 = (latitude1) * M_PI / 180.0;
    latitude2 = (latitude2) * M_PI / 180.0;

    double a = pow(sin(dLat/2),2)+ pow(sin(dLon/2),2)* cos(latitude1)* cos(latitude2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

bool Airport::isBetween(double latitude, double longitude, int kilometers) const {
    if(this->distanceTo(latitude,longitude)<kilometers)
        return true;
    return false;
}