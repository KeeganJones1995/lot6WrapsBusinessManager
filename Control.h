/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Control.h
 * Purpose: Header file for the main Control object that is used a middle man between the UI and the database
 */
#ifndef CONTROL_H
#define CONTROL_H

#include "Staff.h"
#include "Creator.h"
#include "DBManager.h"
#include "Vehicle.h"
#include "Client.h"

class Control{

    public:

        Control(Staff*);
        ~Control();
        void add(int, int, string, string, double, int, string, int, string, double, vector<CarPart*>, string, string, string);//add a new job
        Vehicle* add(int, string, string, string, string, string, int, string);//add a new vehicle
        Client* add(int, string, string, int, string, string, string, string);//add a new client
        void add(int, string, string, int, string, string, string, string, double, string, string);//add a new staff member
        void add(vector<Asset*>); // add a new inventroy order
        void update(int, int, string, string, double, int, string, int, string, double, vector<CarPart*>, string, string, string);//update new job
        void update(int, string, string, string, string, string, int, string);//update vehicle
        void update(int, string, string, int, string, string, string, string);//update client
        void update(int, string, string, int, string, string, string, string, double, string, string);//update staff member
        void update(int, string, double, string, int, string, double, double);//update assets
        void addOrder(vector<Asset*>);

        bool login(QString, QString, string&);// handles functionality related to logging in
        int getHighestId(string, string);// return the highest id for a specific object stored in the database
        void getClients(vector<Client*>&);
        void getVehicleAttrs(vector<string>&, vector<string>&);
        void fillTables(vector<Client*>&, vector<Vehicle*>&, vector<Asset*>&, vector<Job*>&, vector<Staff*>&);
        void getModels(string, vector<string>&);
        int getAllTools();
        void search(string, vector<Client*>&, vector<Vehicle*>&, vector<Asset*>&, vector<Job*>&, vector<Staff*>&);
        int getNumJobs(int);
    private:

        Staff* user;
        Creator* zeus;
        DBManager* db;

};

#endif // CONTROL_H
