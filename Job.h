/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Job.h
 * Purpose: Header file for Job objects, used to represent each individual job held in the system
 */
#ifndef JOB_H
#define JOB_H

#include <iostream>
#include <vector>

#include "Vehicle.h"
#include "Asset.h"
#include "Thing.h"
#include "Staff.h"
#include "Carpart.h"


class Job: public Thing{
    public:
        Job(int, int, string, string, double, int, string, int, string, double, vector<CarPart*>, string, string, string);
        ~Job();
        int getJobId();
        int getEmpId();
        string getEmpName();
        string getType();
        double getQuote();
        int getClientId();
        string getClientName();
        int getVId();
        string getVName();
        double getActualCost();
        vector<CarPart*> getDetails();
        string getTools();
        string getProgress();
        string getPaid();

        void setJobId(int);
        void setEmpId(int);
        void setEmpName(string);
        void setType(string);
        void setQuote(double);
        void setClientId(int);
        void setClientName(string);
        void setVId(int);
        void setVName(string);
        void setActualCost(double);
        void setDetails(vector<CarPart*>);
        void setTools(string);
        void setProgress(string);
        void setPaid(string);
    private:
        int empId;
        string empName;
        string type;
        double quote;
        int clientId;
        string clientName;
        int vId;
        string vName;
        double actualCost;
        vector<CarPart*> details;
        string tools;
        string progress;
        string paid;
};

#endif // JOB_H
