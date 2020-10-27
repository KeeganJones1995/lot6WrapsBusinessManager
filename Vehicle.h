/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Vehicle.h
 * Purpose: Header file for Vehicle objects
 */
#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "Thing.h"

using namespace std;

class Vehicle: public Thing{
    public:
        Vehicle(int, string, string, string, string, string, int, string);
        ~Vehicle();
        string getColor();
        string getNumDoors();
        string getMake();
        string getModel();
        string getYear();
        int getId();
        int getOwnerId();
        string getType();
        void setType(string);
        void setColor(string);
        void setNumDoors(string);
        void setMake(string);
        void setModel(string);
        void setYear(string);
        void setId(int);
        void setOwnerId(int);
    private:
        string origColor;
        string numDoors;
        string make;
        string model;
        string year;
        int ownerId;
        string type;
    };

#endif // VEHICLE_H
