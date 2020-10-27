/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Client.cpp
 * Purpose: Source file for Client objects, containing the constructor and all the necessary getters and setters
 */
#include "Client.h"


Client::Client(int id2, string fName, string lName, int a, string p1, string p2, string e, string i) :
    Person(id2, fName, lName, a, p1, p2, e, i){}

vector<Vehicle*> Client::getVehicles(){
    return vehicleArr;
}

void Client::addVehicle(Vehicle * v){
    vehicleArr.push_back(v);
}

void Client::setId(int i){
    Person::setId(i);
}

void Client::setFirst(string f){
    Person::setFirst(f);
}

void Client::setLast(string l){
    Person::setLast(l);
}

void Client::setPhone1(string p){
    Person::setPhone1(p);
}

void Client::setAge(int a){
    Person::setAge(a);
}

void Client::setPhone2(string p){
    Person::setPhone2(p);
}

void Client::setEmail(string e){
    Person::setEmail(e);
}

void Client::setInsta(string i){
    Person::setInsta(i);
}


