/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Asset.cpp
 * Purpose: Source file for Asset objects, containing the constructor and all the necessary getters and setters
 */

#include "Asset.h"


Asset::Asset(int i, string n, double p, string d, int w, string c, double b, double u) : Thing(i){
    objectName = n;
    price = p;
    date = d;
    wrap = w;
    colour = c;
    bought = b;
    used = u;
}

int Asset::getId(){
    return Thing::getId();
}

string Asset::getObjectName(){
   return objectName;
}

double Asset::getPrice(){
    return price;
}

string Asset::getDate(){
    return date;
}

int Asset::getWrap(){
    return wrap;
}

string Asset::getColour(){
    return colour;
}

double Asset::getBought(){
    return bought;
}

double Asset::getUsed(){
    return used;
}

void Asset::setWrap(int w){
    wrap = w;
}

void Asset::setId(int i){
    Thing::setId(i);
}

void Asset::setObjectName(string o){
    objectName = o;
}

void Asset::setPrice(double p){
    price = p;
}

void Asset::setDate(string d){
    date = d;
}

void Asset::setBought(double b){
    bought = b;
}

void Asset::setUsed(double u){
    used = u;
}
