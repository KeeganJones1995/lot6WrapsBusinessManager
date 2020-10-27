/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: CarPart.cpp
 * Purpose: Source file for Vehicle objects, containing the constructor and all the necessary getters and setters
 */
#include "Vehicle.h"

Vehicle::Vehicle(int i, string c, string d, string ma, string mo, string y, int i2, string t): Thing(i){
    origColor = c;
    numDoors = d;
    make = ma;
    model = mo;
    year = y;
    ownerId = i2;
    type = t;
}

Vehicle::~Vehicle(){}

string Vehicle::getColor(){
    return origColor;
}

string Vehicle::getNumDoors(){
    return numDoors;
}

string Vehicle::getMake(){
    return make;
}

string Vehicle::getModel(){
    return model;
}

string Vehicle::getYear(){
    return year;
}

int Vehicle::getId(){
    return Thing::getId();
}

int Vehicle::getOwnerId(){
    return ownerId;
}

string Vehicle::getType(){
    return type;
}

void Vehicle::setType(string t){
    type = t;
}

void Vehicle::setColor(string c){
    origColor = c;
}

void Vehicle::setNumDoors(string d){
    numDoors = d;
}

void Vehicle::setMake(string ma){
    make = ma;
}

void Vehicle::setModel(string mo){
    model = mo;
}

void Vehicle::setYear(string y){
    year = y;
}

void Vehicle::setId(int i){
    Thing::setId(i);
}

void Vehicle::setOwnerId(int i){
    ownerId = i;
}
