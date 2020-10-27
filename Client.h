/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Client.h
 * Purpose: Header file for Client objects
 */
#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <vector>

#include "Person.h"
#include "Job.h"
#include "Vehicle.h"
#include "Thing.h"

class Client : public Person{
    public:
        Client(int, string, string, int, string, string, string, string);
        vector<Vehicle*> getVehicles();
        void setId(int);
        void setFirst(string);
        void setLast(string);
        void setPhone1(string);
        void setAge(int);
        void setPhone2(string);
        void setEmail(string);
        void setInsta(string);
        void addVehicle(Vehicle*);
    private:
        vector<Vehicle*> vehicleArr;

};

#endif // CLIENT_H
