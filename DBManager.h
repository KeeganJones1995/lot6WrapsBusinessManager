/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: DBManager.h
 * Purpose: Header file for DBManager object that handles accessing the database
 */
#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QtCore>
#include <QtGui>
#include <vector>

#include "Vehicle.h"
#include "Client.h"
#include "Job.h"
#include "Staff.h"
#include "Asset.h"
#include "Carpart.h"

class DBManager{

    public:

        DBManager();
        void addVehicle(Vehicle*, int);
        void addClient(Client*);
        void addJob(Job*);
        void addStaff(Staff*);
        void connect();
        bool queryLogin(QString, QString, int&, string&, string&, string&, int&, string&, double&, string&, string&, string&, string&, string&);
        int getHighestId(string, string);
        void getClients(vector<Client*>&);
        void getVehicles(vector<Vehicle*>&, int);
        void getVehicleAttrs(vector<string>&, vector<string>&);
        void fillTables(vector<Client*>&, vector<Vehicle*>&, vector<Asset*>&, vector<Job*>&, vector<Staff*>&);
        void addAssets(vector<Asset*>);
        void getModels(string, vector<string>&);
        void search(string, vector<Client*>&, vector<Vehicle*>&, vector<Asset*>&, vector<Job*>&, vector<Staff*>&);
        int getNumJobs(int);
};

#endif // DBMANAGER_H
