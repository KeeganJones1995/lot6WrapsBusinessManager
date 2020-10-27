/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: DBManager.cpp
 * Purpose: Source file for DBManager object, containing the constructor, connect function, adding functions, and functions for pulling specific info from the database
 */
#include "DBManager.h"
#include <iostream>
#include <cstddef>

using namespace std;

DBManager::DBManager()
{

}

//connects to the database
void DBManager::connect(){
    QSqlDatabase newDB = QSqlDatabase::addDatabase("QSQLITE");
    newDB.setDatabaseName("../L6WBusinessManager/Database/l6DB.db");

    if(!newDB.open()){
        qWarning() << "Can not open database:/";
    }else{
        qWarning() << "Database has been opened:)";
    }


}

void DBManager::addVehicle(Vehicle* v, int cId){
    QSqlQuery query;

    query.prepare("INSERT OR REPLACE INTO VEHICLE(vehicle_id, owner_id, orig_color, num_doors, make, model, year_made, v_type)"
                    "VALUES(:vehicle_id, :owner_id, :orig_color, :num_doors, :make, :model, :year_made, :v_type)");

    query.bindValue(":vehicle_id", v->getId());
    query.bindValue(":owner_id", cId);
    query.bindValue(":orig_color", QString::fromStdString(v->getColor()));
    query.bindValue(":num_doors", QString::fromStdString(v->getNumDoors()));
    query.bindValue(":make", QString::fromStdString(v->getMake()));
    query.bindValue(":model", QString::fromStdString(v->getModel()));
    query.bindValue(":year_made", QString::fromStdString(v->getYear()));
    query.bindValue(":v_type", QString::fromStdString(v->getType()));

    if(!query.exec()){
        qWarning() << "Query failed yo.";
    }

}

void DBManager::addClient(Client* c){
    QSqlQuery query;

    query.prepare("INSERT OR REPLACE INTO CLIENT(client_id, first_name, last_name, phone1, age, phone2, email, insta)"
                    "VALUES(:client_id, :first, :last, :phone1, :age, :phone2, :email, :insta)");

    query.bindValue(":client_id", c->getId());
    query.bindValue(":first", QString::fromStdString(c->getFirst()));
    query.bindValue(":last", QString::fromStdString(c->getLast()));
    query.bindValue(":phone1", QString::fromStdString(c->getPhone1()));
    query.bindValue(":age", c->getAge());
    query.bindValue(":phone2", QString::fromStdString(c->getPhone2()));
    query.bindValue(":email", QString::fromStdString(c->getEmail()));
    query.bindValue(":insta", QString::fromStdString(c->getInsta()));

    query.exec();

    if(!query.exec()){
        qWarning() << "Query failed yo.";
    }


}

void DBManager::addJob(Job* j){
    string newStr = "";
    vector<CarPart*> detStr = j->getDetails();
    string u = "0";

     //converts the vector of details into a string form that can be stored in the database
    for(int i = 0; i < (int)detStr.size(); i++){
        if(detStr.at(i)->getUsed()){
            u = "1";
        }else{
            u = "0";
        }
        newStr += detStr.at(i)->getName() + "-" + u + "-" + to_string(detStr.at(i)->getDamage()) + ",";
    }

    QSqlQuery query;

    query.prepare("INSERT OR REPLACE INTO JOB(job_id, emp_id, emp_name, job_type, quote, client_id, client_name, final_cost, vehicle_id, vehicle_name, details, tools_used, progress, paid)"
                  "values(:job_id, :emp_id, :emp_name, :job_type, :quote, :client_id, :client_name, :final_cost, :vehicle_id, :vehicle_name, :details, :tools_used, :progress, :paid)");

    query.bindValue(":job_id", j->getId());
    query.bindValue(":emp_id", j->getEmpId());
    query.bindValue(":emp_name", QString::fromStdString(j->getEmpName()));
    query.bindValue(":job_type", QString::fromStdString(j->getType()));
    query.bindValue(":quote", j->getQuote());
    query.bindValue(":client_id", j->getClientId());
    query.bindValue(":client_name", QString::fromStdString(j->getClientName()));
    query.bindValue(":final_cost", QString::number(j->getActualCost()));
    query.bindValue(":vehicle_id", j->getVId());
    query.bindValue(":vehicle_name", QString::fromStdString(j->getVName()));
    query.bindValue(":details", QString::fromStdString(newStr));
    query.bindValue(":tools_used", QString::fromStdString(j->getTools()));
    query.bindValue(":progress", QString::fromStdString(j->getProgress()));
    query.bindValue(":paid", QString::fromStdString(j->getPaid()));

    query.exec();

    if(!query.exec()){
        qWarning() << "add job query failed yo.";
    }

}

void DBManager::addStaff(Staff* s){
    cout << s->getId() << endl;
}

//querys the database to see if the username and password are correct and then returns the corresponding staff member
bool DBManager::queryLogin(QString u, QString p, int &id, string &first, string &last, string &phone1, int &age, string &pos, double &pay, string &phone2, string &email, string &insta, string &u_name, string &password){
    QSqlQuery query;

    query.prepare("SELECT * FROM STAFF WHERE u_name = :staff_u_name");
    query.bindValue(":staff_u_name", u);

    if(!query.exec()){
        qWarning() << "Query failed yo.";
    }

    if(!query.next()){
        qWarning() << "No staff member with that name";
        return false;
    }else{
        if(query.value(11).toString() == p){
            id = query.value(0).toString().toInt();
            first = query.value(1).toString().toStdString();
            last = query.value(2).toString().toStdString();
            phone1 = query.value(3).toString().toStdString();
            age = query.value(4).toString().toInt();
            pos = query.value(0).toString().toStdString();
            pay = query.value(0).toString().toDouble();
            phone2 = query.value(0).toString().toStdString();
            email = query.value(0).toString().toStdString();
            insta = query.value(0).toString().toStdString();
            u_name = query.value(0).toString().toStdString();
            password = query.value(0).toString().toStdString();
            return true;
        }else{
            qWarning() << "Incorrect Password";
            return false;
        }
    }
}

//returne the highest id within a specific table
int DBManager::getHighestId(string s1, string s2){
    QSqlQuery query;

    QString str = "SELECT MAX(" + QString::fromStdString(s2) + ") FROM " + QString::fromStdString(s1);

    if(!query.exec(str)){
        qWarning() << "Query failed yo.";
    }

    if(!query.next()){
        qWarning() << "No entries in this database so far";
        return 999;
    }else{
        return query.value(0).toInt();
    }
}

//returns a vector of all the clients
void DBManager::getClients(vector<Client*> &c){
    vector<Vehicle*> vArr;
    int i = 0;
    QSqlQuery query;
    QString str = "SELECT * FROM CLIENT";
    string first, last, phone1, phone2, email, insta;
    int id, age;


    if(!query.exec(str)){
        qWarning() << "Query failed yo.";
    }

    while(query.next()){
        id = query.value(0).toInt();
        first = query.value(1).toString().toStdString();
        last = query.value(2).toString().toStdString();
        phone1 = query.value(3).toString().toStdString();
        age = query.value(4).toInt();
        phone2 = query.value(5).toString().toStdString();
        email = query.value(6).toString().toStdString();
        insta = query.value(7).toString().toStdString();
        vArr.clear();
        getVehicles(vArr, id);
        for(int j = 0; j < (int)vArr.size(); j++){
            c.at(i)->addVehicle(vArr.at(j));
        }
        c.at(i)->setId(id);
        c.at(i)->setFirst(first);
        c.at(i)->setLast(last);
        c.at(i)->setPhone1(phone1);
        c.at(i)->setPhone2(phone2);
        c.at(i)->setAge(age);
        c.at(i)->setEmail(email);
        c.at(i)->setInsta(insta);
        i++;
    }
}

//returns all the vehicles for a specific client
void DBManager::getVehicles(vector<Vehicle*> &v, int id){
    QSqlQuery query;
    int oId = 0, ownerId;
    string color, doors, make, model, year, type;


    QString str = "SELECT * FROM VEHICLE WHERE owner_id = " + QString::number(id);

    if(!query.exec(str)){
        qWarning() << "Query failed yo.";
    }

    while(query.next()){
        id = query.value(0).toInt();
        oId = id;
        ownerId = query.value(1).toInt();
        color = query.value(2).toString().toStdString();
        doors = query.value(3).toString().toStdString();
        make = query.value(4).toString().toStdString();
        model = query.value(5).toString().toStdString();
        year = query.value(6).toString().toStdString();
        type = query.value(7).toString().toStdString();
        Vehicle* nv = new Vehicle(id, color, doors, make, model, year, ownerId, type);
        v.push_back(nv);
    }
}

//returns 2 vectors containing distinct lists of all the makes and colours already in the database
void DBManager::getVehicleAttrs(vector<string> &makes, vector<string> &colors){
    QSqlQuery makeQuery, colorQuery;
    QString makeStr, colorStr;

    makeStr = "SELECT DISTINCT make FROM VEHICLE";
    colorStr = "SELECT DISTINCT orig_color FROM VEHICLE";

    if(!makeQuery.exec(makeStr)){
        qWarning() << "makeQuery failed yo.";
    }
    if(!colorQuery.exec(colorStr)){
        qWarning() << "colorQuery failed yo.";
    }

    while(makeQuery.next()){
        makes.push_back(makeQuery.value(0).toString().toStdString());
    }
    while(colorQuery.next()){
        colors.push_back(colorQuery.value(0).toString().toStdString());
    }

}

//populates the respective vectors with all the data in the database
void DBManager::fillTables(vector<Client *> &c, vector<Vehicle *> &v, vector<Asset *> &a, vector<Job *> &j, vector<Staff*> &s){
    QSqlQuery cQuery, aQuery, vQuery, jQuery, sQuery;

    if(!cQuery.exec("SELECT * FROM CLIENT")){
        qWarning() << "cQuery failed yo.";
    }
    if(!vQuery.exec("SELECT * FROM VEHICLE")){
        qWarning() << "vQuery failed yo.";
    }
    if(!aQuery.exec("SELECT * FROM ASSET")){
        qWarning() << "aQuery failed yo.";
    }
    if(!jQuery.exec("SELECT * FROM JOB")){
        qWarning() << "jQuery failed yo.";
    }
    if(!sQuery.exec("SELECT * FROM STAFF")){
        qWarning() << "sQuery failed yo.";
    }

    while(cQuery.next()){
        Client* newC = new Client(cQuery.value(0).toString().toInt(), cQuery.value(1).toString().toStdString(), cQuery.value(2).toString().toStdString(), cQuery.value(4).toString().toInt(),
                                  cQuery.value(3).toString().toStdString(), cQuery.value(5).toString().toStdString(), cQuery.value(6).toString().toStdString(), cQuery.value(7).toString().toStdString());
        c.push_back(newC);
    }
    while(vQuery.next()){
        Vehicle* newV = new Vehicle(vQuery.value(0).toString().toInt(), vQuery.value(2).toString().toStdString(), vQuery.value(3).toString().toStdString(), vQuery.value(4).toString().toStdString(),
                                  vQuery.value(5).toString().toStdString(), vQuery.value(6).toString().toStdString(), vQuery.value(1).toString().toInt(), vQuery.value(7).toString().toStdString());
        v.push_back(newV);
        for(int i = 0; i < (int)c.size(); i++){
            if(c.at(i)->getId() == vQuery.value(1).toInt()){
                c.at(i)->addVehicle(newV);
            }
        }
    }
    while(aQuery.next()){
        Asset* newA = new Asset(aQuery.value(0).toString().toInt(), aQuery.value(1).toString().toStdString(), aQuery.value(3).toString().toDouble(), aQuery.value(4).toString().toStdString(),
                                aQuery.value(7).toString().toInt(), aQuery.value(2).toString().toStdString(), aQuery.value(5).toString().toDouble(), aQuery.value(6).toString().toDouble());
        a.push_back(newA);
    }
    while(jQuery.next()){
        vector<CarPart*> details;
        string str = jQuery.value(10).toString().toStdString(), n = "";
        int lastComma = 0, u = 0;
        double d = 0;
        for(int i = 0; i < (int)str.length(); i++){//seperates and parses the string of carparts and populates the details vactor
            if((int)str[i] == 44){
                string newStr = str.substr(lastComma, i - lastComma);
                lastComma = i + 1;
                size_t f = newStr.find_first_of("-");
                if(f != std::string::npos){
                    n = newStr.substr(0, f);
                    u = stoi(newStr.substr(f + 1, 1));
                    d = stoi(newStr.substr(f + 3));
                }
                CarPart* newP = new CarPart(0, n, u, d);
                details.push_back(newP);
            }
        }

        Job* newJ = new Job(jQuery.value(0).toString().toInt(), jQuery.value(1).toString().toInt(), jQuery.value(2).toString().toStdString(), jQuery.value(3).toString().toStdString(),
                                  jQuery.value(4).toString().toDouble(), jQuery.value(5).toString().toInt(), jQuery.value(6).toString().toStdString(),
                                  jQuery.value(8).toString().toInt(),  jQuery.value(9).toString().toStdString(), jQuery.value(7).toString().toDouble(), details, jQuery.value(11).toString().toStdString(), jQuery.value(12).toString().toStdString(), jQuery.value(13).toString().toStdString());
        j.push_back(newJ);
    }
    while(sQuery.next()){
        Staff* newS = new Staff(sQuery.value(0).toString().toInt(), sQuery.value(1).toString().toStdString(), sQuery.value(2).toString().toStdString(), sQuery.value(4).toString().toInt(),
                                  sQuery.value(3).toString().toStdString(), sQuery.value(7).toString().toStdString(), sQuery.value(8).toString().toStdString(),
                                  sQuery.value(9).toString().toStdString(),  sQuery.value(6).toString().toDouble(), sQuery.value(10).toString().toStdString(), sQuery.value(11).toString().toStdString());
        s.push_back(newS);
    }
}

//adds an inventory order into the database
void DBManager::addAssets(vector<Asset *> aArr){
    QSqlQuery query;
    for(int i = 0; i < (int)aArr.size(); i++){
        query.prepare("INSERT OR REPLACE INTO ASSET(obj_id, obj_name, colour, price, date_bought, amnt_bought, amnt_used, wrap)"
                        "VALUES(:obj_id, :obj_name, :colour, :price, :date_bought, :amnt_bought, :amnt_used, :wrap)");
        if(aArr.at(i)->getWrap() == 1){
            query.bindValue(":obj_id", aArr.at(i)->getId());
            query.bindValue(":obj_name", QString::fromStdString(aArr.at(i)->getObjectName()));
            query.bindValue(":colour", QString::fromStdString(aArr.at(i)->getColour()));
            query.bindValue(":price", QString::number(aArr.at(i)->getPrice()));
            query.bindValue(":date_bought", QString::fromStdString(aArr.at(i)->getDate()));
            query.bindValue(":amnt_used", QString::number(0));
            query.bindValue(":amnt_bought", QString::number(aArr.at(i)->getBought()));
            query.bindValue(":wrap", QString::number(aArr.at(i)->getWrap()));
        }else{
            query.bindValue(":obj_id", aArr.at(i)->getId());
            query.bindValue(":obj_name", QString::fromStdString(aArr.at(i)->getObjectName()));
            query.bindValue(":price", QString::number(aArr.at(i)->getPrice()));
            query.bindValue(":date_bought", QString::fromStdString(aArr.at(i)->getDate()));
            query.bindValue(":wrap", QString::number(aArr.at(i)->getWrap()));
        }




        query.exec();

        if(!query.exec()){
            qWarning() << "AssetQuery failed yo.";
        }
    }

}

//populates a vector with all the models in the databade for a specific make of car
void DBManager::getModels(string make, vector<string> &models){
    QSqlQuery mQuery;

    mQuery.prepare("SELECT DISTINCT model FROM VEHICLE WHERE make = :make");
    mQuery.bindValue(":make", QString::fromStdString(make));

    if(!mQuery.exec()){
        qWarning() << "mQuery failed yo.";
    }

    while(mQuery.next()){
        models.push_back(mQuery.value(0).toString().toStdString());
    }
}

//searchs throught the database and returns any entries that contain the given search query
void DBManager::search(string str, vector<Client*>& c, vector<Vehicle*>& v, vector<Asset*>& a, vector<Job*>& j, vector<Staff*>& s){
    QSqlQuery cQuery, aQuery, vQuery, jQuery, sQuery;

    cQuery.prepare("SELECT * FROM CLIENT WHERE first_name like :str COLLATE NOCASE OR last_name LIKE :str COLLATE NOCASE OR phone1 LIKE :str COLLATE NOCASE OR phone2 LIKE :str COLLATE NOCASE OR insta LIKE :str COLLATE NOCASE");
    cQuery.bindValue(":str", QString::fromStdString("%" + str + "%"));

    vQuery.prepare("SELECT * FROM VEHICLE WHERE make LIKE :str COLLATE NOCASE OR model LIKE :str COLLATE NOCASE OR orig_color LIKE :str COLLATE NOCASE OR year_made LIKE :str COLLATE NOCASE OR v_type LIKE :str COLLATE NOCASE");
    vQuery.bindValue(":str", QString::fromStdString("%" + str + "%"));

    aQuery.prepare("SELECT * FROM ASSET WHERE obj_name LIKE :str COLLATE NOCASE OR colour LIKE :str COLLATE NOCASE");
    aQuery.bindValue(":str", QString::fromStdString("%" + str + "%"));

    jQuery.prepare("SELECT * FROM JOB WHERE job_type LIKE :str COLLATE NOCASE OR details LIKE :str COLLATE NOCASE");
    jQuery.bindValue(":str", QString::fromStdString("%" + str + "%"));


    if(!vQuery.exec()){
        qWarning() << "vSearchQuery failed yo.";
    }
    if(!cQuery.exec()){
        qWarning() << "cSearchQuery failed yo.";
    }
    if(!aQuery.exec()){
        qWarning() << "aSearchQuery failed yo.";
    }
    if(!jQuery.exec()){
        qWarning() << "jSearchQuery failed yo.";
    }

    while(cQuery.next()){
        Client* newC = new Client(cQuery.value(0).toString().toInt(), cQuery.value(1).toString().toStdString(), cQuery.value(2).toString().toStdString(), cQuery.value(4).toString().toInt(),
                                  cQuery.value(3).toString().toStdString(), cQuery.value(5).toString().toStdString(), cQuery.value(6).toString().toStdString(), cQuery.value(7).toString().toStdString());
        c.push_back(newC);
    }
    while(vQuery.next()){
        Vehicle* newV = new Vehicle(vQuery.value(0).toString().toInt(), vQuery.value(2).toString().toStdString(), vQuery.value(3).toString().toStdString(), vQuery.value(4).toString().toStdString(),
                                  vQuery.value(5).toString().toStdString(), vQuery.value(6).toString().toStdString(), vQuery.value(1).toString().toInt(), vQuery.value(7).toString().toStdString());
        v.push_back(newV);
        for(int i = 0; i < (int)c.size(); i++){
            if(c.at(i)->getId() == vQuery.value(1).toInt()){
                c.at(i)->addVehicle(newV);
            }
        }
    }
    while(aQuery.next()){
        Asset* newA = new Asset(aQuery.value(0).toString().toInt(), aQuery.value(1).toString().toStdString(), aQuery.value(3).toString().toDouble(), aQuery.value(4).toString().toStdString(),
                                aQuery.value(7).toString().toInt(), aQuery.value(2).toString().toStdString(), aQuery.value(5).toString().toDouble(), aQuery.value(6).toString().toDouble());
        a.push_back(newA);
    }
    while(jQuery.next()){
        vector<CarPart*> details;
        string str = jQuery.value(10).toString().toStdString(), n = "";
        int lastComma = 0, u = 0;
        double d = 0;
        for(int i = 0; i < (int)str.length(); i++){
            if((int)str[i] == 44){
                string newStr = str.substr(lastComma, i - lastComma);
                lastComma = i + 1;
                size_t f = newStr.find_first_of("-");
                if(f != std::string::npos){
                    n = newStr.substr(0, f);
                    u = stoi(newStr.substr(f + 1, 1));
                    d = stoi(newStr.substr(f + 3));
                }
                CarPart* newP = new CarPart(0, n, u, d);
                details.push_back(newP);
            }
        }

        Job* newJ = new Job(jQuery.value(0).toString().toInt(), jQuery.value(1).toString().toInt(), jQuery.value(2).toString().toStdString(), jQuery.value(3).toString().toStdString(),
                                  jQuery.value(4).toString().toDouble(), jQuery.value(5).toString().toInt(), jQuery.value(6).toString().toStdString(),
                                  jQuery.value(8).toString().toInt(),  jQuery.value(9).toString().toStdString(), jQuery.value(7).toString().toDouble(), details, jQuery.value(11).toString().toStdString(), jQuery.value(12).toString().toStdString(), jQuery.value(13).toString().toStdString());
        j.push_back(newJ);
    }
}

//returns the number of jobs a specific client has had done
int DBManager::getNumJobs(int id){
    QSqlQuery jQuery;
    int res = 0;

    jQuery.prepare("SELECT COUNT(*) FROM JOB WHERE client_id = :id");
    jQuery.bindValue(":id", id);

    if(!jQuery.exec()){
        qWarning() << "jSearchQuery failed yo.";
    }

    while(jQuery.next()){
        res = jQuery.value(0).toString().toInt();
    }
    return res;
}





