/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Staff.h
 * Purpose: Header file for staff objects
 */
#ifndef STAFF_H
#define STAFF_H

#include "Person.h"

using namespace std;

#include <iostream>
#include <vector>
#include "Thing.h"

class Staff : public Person{
    public:
        Staff(int, string, string, int, string, string, string, string, double, string, string);
        ~Staff();
        string getPosition();
        double getPayRate();
        //vector<Job> getJobs();
    private:
        string position;
        double payRate;
        string userName;
        string password;
        //vector<Job> jobsWorked;
};

#endif // STAFF_H
