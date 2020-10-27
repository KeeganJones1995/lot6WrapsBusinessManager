/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: CarPart.cpp
 * Purpose: Source file for Thing objects, containing the constructor and all the necessary getters and setters
 */
#include "Thing.h"

Thing::Thing(int i)
{
    id = i;
}

Thing::~Thing(){

}

int Thing::getId(){
    return id;
}

void Thing::setId(int i){
    id = i;
}
