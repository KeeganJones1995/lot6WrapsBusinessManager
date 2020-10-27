/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Thing.h
 * Purpose: Header file for Thing objects, which is inherited by every real-world object that is stored in the database within the program(Staff, Client, Asset, Job, Person, Vehicle)
 */
#ifndef THING_H
#define THING_H


class Thing{
    public:
        Thing(int);
        ~Thing();
        int getId();
        void setId(int);
    private:
        int id;
};

#endif // THING_H
