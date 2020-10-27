/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: CarPart.h
 * Purpose: Header file for CarPart objects, to be contained in a vector within each each Job object
 */
#ifndef CARPART_H
#define CARPART_H

#include <string>
#include "Thing.h"

using namespace std;

class CarPart: public Thing{
    public:
        CarPart(int, string, bool, double);
        ~CarPart();
        string getName();
        bool getUsed();
        int getDamage();
        double getWeight();
        void setName(string);
        void setUsed(bool);
        void setDamage(int);
        void setWeights(string);
    private:
        string name;
        bool used;//whether the specific part is being used in the specific job that it is a part of
        int damage;
        double weight;

};

#endif // CARPART_H
