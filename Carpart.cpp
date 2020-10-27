/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: CarPart.cpp
 * Purpose: Source file for CarPart objects, containing the constructor and all the necessary getters and setters
 */
#include "Carpart.h"

CarPart::CarPart(int i, string n, bool b, double d): Thing(i){
    name = n;
    used = b;
    damage = d;
    setWeights(n);
}

CarPart::~CarPart(){

}

string CarPart::getName(){
    return name;
}

bool CarPart::getUsed(){
    return used;
}

int CarPart::getDamage(){
    return damage;
}

double CarPart::getWeight(){
    return weight;
}

void CarPart::setName(string n){
    name = n;
}

void CarPart::setUsed(bool u){
    used = u;
}

void CarPart::setDamage(int d){
    damage = d;
}

void CarPart::setWeights(string n){
    if(n == "Rear Bumper"){
        weight = .14;
    }else if(n == "Rear Driver Side Door"){
        weight = .05;
    }else if(n == "Driver Side Door"){
        weight = .05;
    }else if(n == "Front Bumper"){
        weight = .15;
    }else if(n == "Front Left Fender"){
        weight = .03;
    }else if(n == "Front Right Fender"){
        weight = .03;
    }else if(n == "Hood"){
        weight = .09;
    }else if(n == "Left Rocker"){
        weight = .02;
    }else if(n == "Passenger Door"){
        weight = .05;
    }else if(n == "Rear Left Fender"){
        weight = .07;
    }else if(n == "Rear Right Fender"){
        weight = .07;
    }else if(n == "Right Rocker"){
        weight = .02;
    }else if(n == "Roof"){
        weight = .08;
    }else if(n == "Rear Passenger Door"){
        weight = .05;
    }else if(n == "Trunk"){
        weight = .1;
    }
}
