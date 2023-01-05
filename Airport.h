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
    /**
     * Default Airport constructor. Creates a NULL Airport object.
     */
    Airport();
    /**
     * Airport constructor. Creates an Airport object with the code, name, city, country, latitude and longitude provided.
     * @param code
     * @param name
     * @param city
     * @param country
     * @param latitude
     * @param longitude
     */
    Airport(string code, string name, string city, string country, double latitude, double longitude);
    /**
     * Getter for the private code field.
     * Time-complexity -> O(1)
     * @return String with the Airport code
     */
    string getCode();
    /**
     * Getter for the private name field.
     * Time-complexity -> O(1)
     * @return String with the Airport name
     */
    string getName();
    /**
     * Getter for the private city field.
     * Time-complexity -> O(1)
     * @return String with the Airport city
     */
    string getCity();
    /**
     * Getter for the private country field.
     * Time-complexity -> O(1)
     * @return String with the Airport country
     */
    string getCountry();
    /**
     * Getter for the private latitude field.
     * Time-complexity -> O(1)
     * @return Double with the Airport latitude
     */
    double getLatitude() const;
    /**
     * Getter for the private latitude field.
     * Time-complexity -> O(1)
     * @return Double with the Airport longitude
     */
    double getLongitude() const;
    /**
     * Calculates the distance from *this* Airport to the coordinates provided (latitude and longitude) using the Haversine formula
     * Time-complexity -> O(1)
     * @param latitude
     * @param longitude
     * @return Double with the distance from the Airport to the coordinates provided
     */
    double distanceTo(double latitude, double longitude) const;
    /**
     * Checks if the Airport is x kilometers away or less from the coordinates provided
     * Time-complexity -> O(1)
     * @param latitude
     * @param longitude
     * @param kilometers
     * @return True if the airport is x kilometers away or less from the coordinates provided. False otherwise.
     */
    bool isBetween(double latitude, double longitude, int x) const;
};


#endif //PROJETO_AED_2_AIRPORT_H
