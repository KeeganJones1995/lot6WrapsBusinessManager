/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Person.cpp
 * Purpose: Source file for Person objects, containing the constructor and all the necessary getters and setters
 */
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include "Person.h"

Person::Person(int id2, string fName, string lName, int a, string p1, string p2, string e, string i): Thing(id2){
    first = fName;
    last = lName;
    age = a;
    phone1 = p1;
    phone2 = p2;
    email = e;
    insta = i;
}

string Person::getFirst(){
    return first;
}

string Person::getLast(){
    return last;
}

string Person::getPhone1(){
    return phone1;
}

string Person::getPhone2(){
    return phone2;
}

string Person::getEmail(){
    return email;
}

int Person::getAge(){
    return age;
}

int Person::getId(){
    return Thing::getId();
}

string Person::getInsta(){
    return insta;
}

void Person::setFirst(string f){
    first = f;
}

void Person::setLast(string l){
    last = l;
}

void Person::setPhone1(string p){
    phone1 = p;
}

void Person::setPhone2(string p){
    phone2 = p;
}

void Person::setEmail(string e){
    email = e;
}

void Person::setInsta(string i){
    insta = i;
}

void Person::setAge(int a){
    age = a;
}

void Person::setId(int i){
    Thing::setId(i);
}
