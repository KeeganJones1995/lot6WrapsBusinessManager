/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Creator.cpp
 * Purpose: Source file for Creator object, containing the constructor and the overloaded function create which creates the Job, Vehicle, Client, Staff, and Asset functions
 */
#include "Creator.h"

Creator::Creator(){

}

Creator::~Creator(){

}

Job* Creator::create(int id, int eid, string en, string t, double q, int cid, string cn, int vid, string vn, double a, vector<CarPart*> d, string tl, string pr, string pa){
    Job* newJob = new Job(id, eid, en, t, q, cid, cn, vid, vn, a, d, tl, pr, pa);
    return newJob;
}

Vehicle* Creator::create(int id, string c, string d, string ma, string mo, string y, int i2, string t){
    Vehicle* newVehicle = new Vehicle(id, c, d, ma, mo, y, i2, t);
    return newVehicle;
}

Client* Creator::create(int id2, string f, string l, int a, string p1, string p2, string e, string i){
    Client* newClient = new Client(id2, f, l, a, p1, p2, e, i);
    return newClient;
}

Staff* Creator::create(int id2, string f, string l, int a, string p1, string p2, string e, string i, double pr, string u, string pw){
    Staff* newStaff = new Staff(id2, f, l, a, p1, p2, e, i, pr, u ,pw);
    return newStaff;
}

Asset* Creator::create(int i, string n, double p, string d, int w, string c, double b, double u){
    Asset* newAsset = new Asset(i, n, p, d, w, c, b, u);
    return newAsset;
}

//creates an array of empty clients that will be populated later with data from the database
void Creator::populateClients(vector<Client*> &c, int n){
    for(int i = 0; i < n; i++){
        Client* newClient = new Client( 0, "", "", 0, "", "", "", "");
        c.push_back(newClient);
    }
}
