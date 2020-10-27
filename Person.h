/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Person.h
 * Purpose: Header file for Person objects, whichwill be inherited by the Client and Staff objects
 */
#ifndef PERSON_H
#define PERSON_H

#include <string>
#include "Thing.h"

using std::string;

class Person: public Thing{
    public:
        Person(int, string, string, int, string, string, string, string);
        string getFirst();
        string getLast();
        string getPhone1();
        string getPhone2();
        string getEmail();
        string getInsta();
        int getAge();
        int getId();
        void setFirst(string);
        void setLast(string);
        void setPhone1(string);
        void setPhone2(string);
        void setEmail(string);
        void setInsta(string);
        void setAge(int);
        void setId(int);
    private:
        string first, last, phone1, phone2, email, insta;
        int age;
};


#endif // PERSON_H
