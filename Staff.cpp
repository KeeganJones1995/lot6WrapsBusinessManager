/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Staff.cpp
 * Purpose: Source file for Staff objects, containing the constructor and all the necessary getters and setters
 */
#include "Staff.h"

Staff::Staff(int id2, string f, string l, int a, string p1, string p2, string e, string i, double pr, string u, string pw) :
    Person(id2, f, l, a, p1, p2, e, i), payRate(pr), userName(u), password(pw) {}

string Staff::getPosition(){
    return position;
}

double Staff::getPayRate(){
    return payRate;
}
