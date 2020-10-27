/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Control.cpp
 * Purpose: Source file for Control object, containing the constructor, add fns, update fns and populating fns(for populating the vectors with the data from the database)
 */
#include "Control.h"

//Constructor for the control object

Control::Control(Staff *s){
    zeus = new Creator();
    user = s;
    db = new DBManager();
    db->connect();
}

Control::~Control(){

}

//adds a new asset to the database

void Control::add(vector<Asset*> aArr){
    db->addAssets(aArr);
}

//creates a new Job object and adds it to the database
void Control::add(int id, int eid, string en, string t, double q, int cid, string cn, int vid, string vn, double a, vector<CarPart*> d, string tl, string pr, string pa){
    Job* newJob = zeus->create(id, eid, en, t, q, cid, cn, vid, vn, a, d, tl, pr, pa);
    db->addJob(newJob);
}

//creates a new Vehicle Object and adds it to the database
Vehicle* Control::add(int id, string c, string d, string ma, string mo, string y, int i2, string t){
    Vehicle* nv = zeus->create(id, c, d, ma, mo, y, i2, t);
    db->addVehicle(nv, i2);
    return nv;
}

//creates a new client object and adds it to the database
Client* Control::add(int id2, string f, string l, int a, string p1, string p2, string e, string i){
    Client* newClient = zeus->create(id2, f, l, a, p1, p2, e, i);
    db->addClient(newClient);
    return newClient;
}

//creates a new staff object and adds it to the database
void Control::add(int id2, string f, string l, int a, string p1, string p2, string e, string i, double pr, string u, string pw){
    Staff* newStaff = zeus->create(id2, f, l, a, p1, p2, e, i, pr, u, pw);
    db->addStaff(newStaff);
}

//querys the database using the inputted username and password, and upon successful authorization, creates the staff object which will act as the primary user
bool Control::login(QString u, QString p, string &name){
    string first, last, phone1, pos, phone2, email, insta, u_name, password;
    int id, age;
    double pay;
    bool outcome = db->queryLogin(u, p, id, first, last, phone1, age, pos, pay, phone2, email, insta, u_name, password);// querys login to see if the username and password is correct and then populate the staff attributes passed by reference
    if(outcome){
        user = zeus->create(id, first, last, age, phone1, phone2, email, insta, pay, u_name, password);
        name = first + " " + last;// sets the name to be displayed in the top left corner
    }
    return outcome;
}

//to update an already existing entry in the database for a Job object
void Control::update(int id, int eid, string en, string t, double q, int cid, string cn, int vid, string vn, double a, vector<CarPart*> d, string tl, string pr, string pa){
    Job* newJob = zeus->create(id, eid, en, t, q, cid, cn, vid, vn, a, d, tl, pr, pa);//creates an updated instance of the job
    db->addJob(newJob);//adds the updated job to the database by replacing the old version with this new version
}

//to update an already existing entry in the database for a Vehicle object
void Control::update(int id, string c, string d, string ma, string mo, string y, int i2, string t){
    Vehicle* nv = zeus->create(id, c, d, ma, mo, y, i2, t);
    db->addVehicle(nv, i2);
}

//to update an already existing entry in the database for a Client object
void Control::update(int id2, string f, string l, int a, string p1, string p2, string e, string i){
    Client* newClient = zeus->create(id2, f, l, a, p1, p2, e, i);
    db->addClient(newClient);
}

//to update an already existing entry in the database for a Staff object
void Control::update(int id2, string f, string l, int a, string p1, string p2, string e, string i, double pr, string u, string pw){
    Staff* newStaff = zeus->create(id2, f, l, a, p1, p2, e, i, pr, u, pw);
    db->addStaff(newStaff);
}

//to update an already existing entry in the database for a Asset object
void Control::update(int i, string n, double p, string d, int w, string c, double b, double u){
    Asset* newAsset = zeus->create(i, n, p, d, w, c, b, u);
    vector<Asset*> aArr;
    aArr.push_back(newAsset);
    db->addAssets(aArr);
}

//gets the highest id for a specific object stored in the database
int Control::getHighestId(string s1, string s2){
    return db->getHighestId(s1, s2);
}

//gets all the clients in the database
void Control::getClients(vector<Client*>& cArr){
    int numClients = getHighestId("CLIENT", "client_id") - 999;
    zeus->populateClients(cArr, numClients);
    db->getClients(cArr);
}

//gets a list of distinct vehicle makes and colours
void Control::getVehicleAttrs(vector<string> &ma, vector<string> &c){
    db->getVehicleAttrs(ma, c);
}

//clears the vectors that hold all the objects, and then populates them dynamically from the database
void Control::fillTables(vector<Client *> &c, vector<Vehicle *> &v, vector<Asset *> &a, vector<Job *> &j, vector<Staff*> &s){
    c.clear();
    v.clear();
    a.clear();
    j.clear();
    s.clear();
    db->fillTables(c, v, a, j, s);
}

//adds an inventory order to the database
void Control::addOrder(vector<Asset *> aArr){
    db->addAssets(aArr);
}

//gets a list of all the distinct models associated with a specific make of vehicle
void Control::getModels(string make, vector<string> &models){
    db->getModels(make, models);
}

//sends the vectors to the database to return with any instances of the search term
void Control::search(string str, vector<Client*>& c, vector<Vehicle*>& v, vector<Asset*>& a, vector<Job*>& j, vector<Staff*>& s){
    db->search(str, c, v, a, j, s);
}

//gets number of jobs for that specific client
int Control::getNumJobs(int id){
    int res = db->getNumJobs(id);
    return res;
}
