#include "Job.h"

/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Job.cpp
 * Purpose: Source file for Job objects, containing the constructor and all the necessary getters and setters
 */
Job::Job(int id, int eid, string en, string t, double q, int cid, string cn, int vid, string vn, double a, vector<CarPart*> d, string tl, string pr, string pa): Thing(id){
    empId = eid;
    empName = en;
    type = t;
    quote = q;
    clientId = cid;
    clientName = cn;
    vId = vid;
    vName = vn;
    actualCost = a;
    details = d;
    tools = tl;
    progress = pr;
    paid = pa;
}

Job::~Job(){}

int Job::getJobId(){
    return Thing::getId();
}

int Job::getEmpId(){
    return empId;
}

string Job::getEmpName(){
    return empName;
}

string Job::getType(){
    return type;
}

double Job::getQuote(){
    return quote;
}

int Job::getClientId(){
    return clientId;
}

string Job::getClientName(){
    return clientName;
}

int Job::getVId(){
    return vId;
}

string Job::getVName(){
    return vName;
}

double Job::getActualCost(){
    return actualCost;
}

vector<CarPart*> Job::getDetails(){
    return details;
}

string Job::getTools(){
    return tools;
}

string Job::getProgress(){
    return progress;
}

string Job::getPaid(){
    return paid;
}

void Job::setJobId(int i){
    Thing::setId(i);
}

void Job::setEmpId(int e){
    empId = e;
}

void Job::setEmpName(string n){
    empName = n;
}

void Job::setType(string t){
    type = t;
}

void Job::setQuote(double q){
    quote = q;
}

void Job::setClientId(int i){
    clientId = i;
}

void Job::setClientName(string n){
    clientName = n;
}

void Job::setVId(int i){
    vId = i;
}

void Job::setVName(string n){
    vName = n;
}

void Job::setActualCost(double a){
    actualCost = a;
}

void Job::setDetails(vector<CarPart*> d){
    details = d;
}

void Job::setTools(string d){
    tools = d;
}

void Job::setProgress(string p){
    progress = p;
}

void Job::setPaid(string pa){
    paid = pa;
}
