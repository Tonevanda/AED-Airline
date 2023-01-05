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
    /**
     * Default Airline constructor. Creates a NULL Airline object.
     */
    Airline();
    /**
     * Airline constructor. Creates an Airline object with the code, name, callSign and country provided.
     * @param code
     * @param name
     * @param callSign
     * @param country
     */
    Airline(string code, string name, string callSign, string country);
    /**
     * Getter for the private code field.
     * Time-complexity -> O(1)
     * @return String with the Airline code.
     */
    string getCode()const;
    /**
     * Getter for the private name field.
     * Time-complexity -> O(1)
     * @return String with the Airline name.
     */
    string getName()const;
    /**
     * Getter for the private callSign field.
     * Time-complexity -> O(1)
     * @return String with Airline callSign.
     */
    string getCallSign()const;
    /**
     * Getter for the private country field.
     * Time-complexity -> O(1)
     * @return String with Airline country.
     */
    string getCountry()const;
};


#endif //PROJETO_AED_2_AIRLINE_H
