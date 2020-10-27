/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Creator.h
 * Purpose: Header file for the Creator object that creates the specific instances of the Job, Client, Vehicle, Staff, and Asset objects
 */
#ifndef CREATOR_H
#define CREATOR_H

#include "Vehicle.h"
#include "Staff.h"
#include "Client.h"
#include "Job.h"


class Creator{
    public:
        Creator();
        ~Creator();
        Job* create(int, int, string, string, double, int, string, int, string, double, vector<CarPart*>, string, string, string);//creates job obj
        Vehicle* create(int, string, string, string, string, string, int, string);//creates vehicle obj
        Client* create(int, string, string, int, string, string, string, string);//creates client obj
        Staff* create(int, string, string, int, string, string, string, string, double, string, string);//creates staff obj
        Asset* create(int, string, double, string, int, string, double, double);//creates asset obj
        void populateClients(vector<Client*>&, int);

};

#endif // CREATION_H
