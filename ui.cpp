/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: UI.cpp
 * Purpose: Source file for the UI object, containing the constructor and all the necessary getters and setters
 */

#include "UI.h"
#include "ui_ui.h"
#include <iostream>
#include <fstream>
#include <QDateTime>
#include <string>

using namespace std;


UI::UI(QWidget *parent) : QMainWindow(parent), ui(new Ui::UI) {
    ui->setupUi(this);
    Staff* newStaff = new Staff(0, "", "", 0, "", "", "", "", 0.1, "", "");
    controller = new Control(newStaff);
    initUI();
    cChoice = -1;
}

UI::~UI()
{
    delete ui;
}

//initializes various aspects of UI as well as populates the vectors with all data from the database
void UI::initUI(){
    startTimer(1000);
    ui->logoBtn->setIcon(QIcon("C:/Users/habsr/Documents/L6WBusinessManager/fronklogoBlack.png"));
    this->setWindowTitle("Lot 6 Wraps Business Manager");
    this->setWindowIcon(QIcon("C:/Users/habsr/Documents/L6WBusinessManager/l6Logo.jpg"));
    userName = "";
    ui->errorLbl->setVisible(false);
    ui->pageStack->setCurrentIndex(0);
    ui->passField->setEchoMode(QLineEdit::Password);
    controller->getClients(cArr);
    focus = 0;
    fillTables();
}

//populates choose client drop down menu with all customers already in the database
void UI::populateClientDropDown(){
    QString str = "Add New Customer...";
    ui->customerBox->addItem(str);
    for(int i = 0; i < (int)cArr.size(); i++){
       QString str = QString::fromStdString(cArr.at(i)->getFirst()) + " " + QString::fromStdString(cArr.at(i)->getLast());
       ui->customerBox->addItem(str);
    }
}

//populates the choose vehicle drop down with all the vehicles for whichever client is selected
void UI::populateVehicleDropDown(){
    if(cArr.size() > 0){
        vector<Vehicle*> vehicleArr = cArr.at(cChoice)->getVehicles();
        QString str = "Add New Vehicle...";
        ui->vehicleBox->addItem(str);
        for(int i = 0; i < (int)vehicleArr.size(); i++){
            QString str = QString::fromStdString(vehicleArr.at(i)->getYear()) + " " + QString::fromStdString(vehicleArr.at(i)->getMake()) + " " + QString::fromStdString(vehicleArr.at(i)->getModel());
            ui->vehicleBox->addItem(str);
        }
    }
    ui->vehicleBox->setCurrentIndex(-1);
    populateVehicleChoices();
}

//populates the employee drop down with all the employees in the database
void UI::populateEmployeeDropDown(){
    ui->empTxt->clear();
    if(sArr.size() > 0){
        for(int i = 0; i < (int)sArr.size(); i++){
            QString str = QString::number(sArr.at(i)->getId()) + " " + QString::fromStdString(sArr.at(i)->getFirst()) + " " + QString::fromStdString(sArr.at(i)->getLast());
            ui->empTxt->addItem(str);
        }
    }
    ui->empTxt->setCurrentIndex(-1);
}

//populates the vehicle drop down with all the the makes and colour of vehicles already in the database
void UI::populateVehicleChoices(){
    makes.clear();
    colors.clear();
    controller->getVehicleAttrs(makes, colors);
    ui->makeTxt->clear();
    ui->makeTxt_2->clear();
    ui->modelTxt->clear();
    ui->modelTxt_2->clear();
    ui->origColorTxt->clear();
    ui->origColorTxt_2->clear();
    for(int i = 0; i < (int)makes.size(); i++){
        ui->makeTxt->addItem(QString::fromStdString(makes.at(i)));
        ui->makeTxt_2->addItem(QString::fromStdString(makes.at(i)));
    }
    for(int i = 0; i < (int)colors.size(); i++){
        ui->origColorTxt->addItem(QString::fromStdString(colors.at(i)));
        ui->origColorTxt_2->addItem(QString::fromStdString(colors.at(i)));
    }
    ui->makeTxt->setCurrentIndex(-1);
    ui->makeTxt_2->setCurrentIndex(-1);
    ui->modelTxt->setCurrentIndex(-1);
    ui->modelTxt_2->setCurrentIndex(-1);
    ui->origColorTxt->setCurrentIndex(-1);
    ui->origColorTxt_2->setCurrentIndex(-1);

}

void UI::on_quitBtn_triggered()
{
    qApp->exit();
}

//event handler for when the search button is pressed, polls the database and display the info in a list
void UI::on_searchBtn_clicked()
{
    searchCArr.clear();
    searchVArr.clear();
    searchAArr.clear();
    searchJArr.clear();
    searchSArr.clear();
    QString searchVal = ui->searchTxt->toPlainText();
    ui->searchTxt->clear();
    string searchStr = searchVal.toStdString();
    controller->search(searchStr, searchCArr, searchVArr, searchAArr, searchJArr, searchSArr);
    ui->pageStack->setCurrentIndex(11);
    ui->queryLbl->setText(QString::fromStdString("Search For: " + searchStr));
    ui->resList->clear();
    for(int i = 0; i < (int)searchCArr.size(); i++){
        string tempStr = to_string(searchCArr.at(i)->getId()) + ": " + searchCArr.at(i)->getFirst() + " " + searchCArr.at(i)->getLast() + ", " + to_string(searchCArr.at(i)->getAge());
        QString temp = QString::fromStdString("Client: " + tempStr + "\n");
        ui->resList->addItem(temp);
    }
    for(int i = 0; i < (int)searchVArr.size(); i++){
        string tempStr = to_string(searchVArr.at(i)->getId()) + ": " + searchVArr.at(i)->getYear() + " " + searchVArr.at(i)->getMake() + " " + searchVArr.at(i)->getModel();
        QString temp = QString::fromStdString("Vehicle: " + tempStr + "\n");
        ui->resList->addItem(temp);
    }
    for(int i = 0; i < (int)searchAArr.size(); i++){
        string tempStr = to_string(searchAArr.at(i)->getId()) + ": " + searchAArr.at(i)->getColour() + " " + searchAArr.at(i)->getObjectName();
        QString temp;
        if(searchAArr.at(i)->getWrap()){
            temp = QString::fromStdString("Wrap: " + tempStr + "\n");
        }else{
            temp = QString::fromStdString("Tool: " + tempStr + "\n");
        }
        ui->resList->addItem(temp);
    }
    for(int i = 0; i < (int)searchJArr.size(); i++){
        string tempStr = to_string(searchJArr.at(i)->getId()) + ": " + searchJArr.at(i)->getType() + " for " + searchJArr.at(i)->getVName();
        QString temp = QString::fromStdString("Job: " + tempStr + "\n");
        ui->resList->addItem(temp);
    }

}

//event handler for updating the clock
void UI::timerEvent(QTimerEvent *event){
    QString currTime = QTime::currentTime().toString("hh:mm:ss");
    QString currDate = QDate::currentDate().toString();
    QString newStr = QString::fromStdString(userName + "\n") + currTime + QString::fromStdString("\n") + currDate;
    ui->dateLbl->setText(newStr);
}

//event handler for when the user attempts login, verifies the username and password , and then sets up the UI accordingly
void UI::on_loginBtn_clicked()
{
    QString inputName = ui->nameField->text();
    QString inputPass = ui->passField->text();
    string name = "";
    if(controller->login(inputName, inputPass, name)){//login successful
        ui->pageStack->setCurrentIndex(1);
        ui->addBtn->setEnabled(true);
        ui->printBtn->setEnabled(true);
        ui->viewBtn->setEnabled(true);
        ui->searchBtn->setEnabled(true);
        ui->logoBtn->setEnabled(true);
        userName = name;
    }else{
        ui->errorLbl->setVisible(true);
        ui->nameField->setText("");
        ui->passField->setText("");
    }

}

//event handler for when the user clicks the add button, prepares the UI for the prossess of adding a new job
void UI::on_addBtn_clicked(){
    ui->pageStack->setCurrentIndex(2);
    ui->nextBtn1->setEnabled(true);
    ui->customerBox->clear();
    ui->rdBtn1->setAutoExclusive(false);
    ui->rdBtn1->setChecked(false);
    ui->rdBtn2->setAutoExclusive(false);
    ui->rdBtn2->setChecked(false);
    populateClientDropDown();
}

//event handler for when the logo is clicked, which brings the user back to the home page
void UI::on_logoBtn_clicked(){
    ui->pageStack->setCurrentIndex(1);
}

//event handler for the button that is clicked once the user decides if they are adding a new job or an inventory order
void UI::on_pushButton_clicked(){
    if(ui->rdBtn1->isChecked()){//new Job
        ui->rdBtn1->setChecked(false);
        ui->pageStack->setCurrentIndex(3);
        ui->customerBox->setCurrentIndex(-1);
        ui->newCustomerForm->setVisible(false);
    }else if(ui->rdBtn2->isChecked()){//new inventory order
        ui->rdBtn2->setChecked(false);
        ui->pageStack->setCurrentIndex(6);
        ui->addAssetTbl->setColumnWidth(0, 25);
        ui->addAssetTbl->setColumnWidth(1, 400);
        ui->addAssetTbl->setColumnWidth(2, 125);
        ui->addAssetTbl->setColumnWidth(3, 125);
        ui->addAssetTbl->setColumnWidth(4, 200);
        ui->addAssetTbl->setColumnWidth(5, 200);
        ui->addAssetTbl->setColumnWidth(6, 200);
        ui->addAssetTbl->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->addAssetTbl->setRowCount(1);
        order.clear();
    }
}

//event handler for the "Next" button that the user will click after they choose which client the job is for
void UI::on_nextBtn1_clicked(){
    if(ui->customerBox->currentIndex() == 0){//new client
        ui->newCustomerForm->setVisible(true);
        ui->nextBtn1->setEnabled(false);
        populateVehicleChoices();
    }else if(ui->customerBox->currentIndex() == -1){

    }else{//existing client
        cChoice = ui->customerBox->currentIndex() - 1;
        ui->pageStack->setCurrentIndex(4);
        int nJobs = controller->getNumJobs(cArr.at(cChoice)->getId());
        ui->customerLbl_2->setText(QString::fromStdString("Customer: " + cArr.at(cChoice)->getFirst() + " " + cArr.at(cChoice)->getLast()+ "\nNumber of Jobs: " + to_string(nJobs)));
        ui->newVehicleForm->setVisible(false);
        ui->vehicleBox->clear();
        populateVehicleDropDown();
    }
    ui->vehicleBtn->setEnabled(true);
}

//event handler for the "Next" button that the user will click after they choose which client the job is for
void UI::on_nextBtn2_clicked()
{
    //Add customer
    string firstName = ui->firstTxt->text().toStdString();
    if((int)firstName[0] > 97 ){
        firstName[0] -= 32;
    }
    string lastName = ui->lastTxt->text().toStdString();
    if((int)lastName[0] > 97 ){
        lastName[0] -= 32;
    }
    QString age = ui->ageTxt->text();
    int ageInt = age.toInt();
    string phone1 = ui->phoneTxt1->text().toStdString();
    string phone2 = ui->phoneTxt2->text().toStdString();
    string email = ui->emailTxt->text().toStdString();
    string insta = ui->instaTxt->text().toStdString();
    string blank = "";
    int id = 0;

    if(firstName != blank && lastName != blank && phone1 != blank){
        ui->pageStack->setCurrentIndex(4);
        ui->newVehicleForm->setVisible(false);
        ui->customerLbl_2->setText(QString::fromStdString("Customer: " + firstName + " " + lastName + "\nNumber of Jobs: 0"));
        id = controller->getHighestId("CLIENT", "client_id");
        if(id == 0){
            id = 1000;
        }else{
            id++;
        }
        cArr.push_back(controller->add(id, firstName, lastName, ageInt, phone1, phone2, email, insta));
        cChoice = id - 1000;
    }
    ui->vehicleBtn->setEnabled(true);
}

//the "Next" button that will be clicked once the user decides which vehicle the job will be for
void UI::on_vehicleBtn_clicked(){
    if(ui->vehicleBox->currentIndex() == 0){//if adding a new vehicle is selected
        ui->newVehicleForm->setVisible(true);
        ui->vehicleBtn->setEnabled(false);
    }else if(ui->customerBox->currentIndex() == -1){

    }else{//choosing an existing vehicle in the database
        cChoice = ui->customerBox->currentIndex() - 1;
        Vehicle* newV = cArr.at(cChoice)->getVehicles().at(ui->vehicleBox->currentIndex() - 1);
        for(int i = 0; i < (int)vArr.size(); i++){
            if(vArr.at(i)->getId() == newV->getId()){
                vChoice = i;
            }
        }
        ui->pageStack->setCurrentIndex(5);
        int nJobs = controller->getNumJobs(cArr.at(cChoice)->getId());
        ui->customerLbl_3->setText(QString::fromStdString("Customer: " + cArr.at(cChoice)->getFirst() + " " + cArr.at(cChoice)->getLast()+ "\nNumber of Jobs: " + to_string(nJobs)));
        ui->vehicleLbl->setText(QString::fromStdString("Vehicle: " + vArr.at(vChoice)->getYear() + " " + vArr.at(vChoice)->getMake() + " "  + vArr.at(vChoice)->getModel() + "\nColour: "  + vArr.at(vChoice)->getColor() + "\nNumber of Doors: " +  vArr.at(vChoice)->getNumDoors() ));
        ui->otherTxt->setVisible(false);
        ui->rustTbl->setRowCount(0);
        ui->detailsWidget->setEnabled(true);
        setChkBoxes(false);
        setRdBtns(false);
    }
}

//event handler for the add new vehicle button
void UI::on_addVehicleBtn_clicked(){
    //Add vehicle
    int id = controller->getHighestId("VEHICLE", "vehicle_id") + 1;
    string color = ui->origColorTxt->currentText().toStdString();
    string nDoors = ui->numDoorsTxt->currentText().toStdString();
    string make = ui->makeTxt->currentText().toStdString();
    string model = ui->modelTxt->currentText().toStdString();
    string year = ui->yearTxt->text().toStdString();
    string type = ui->typeBox->currentText().toStdString();
    string blank = "";


    if(id != 0 && color != blank && make != blank && model != blank && year != blank){
        ui->pageStack->setCurrentIndex(5);
        id = controller->getHighestId("VEHICLE", "vehicle_id");
        if(id == 0){
            id = 1000;
        }else{
            id++;
        }
        Vehicle* nv = controller->add(id, color, nDoors, make, model, year, cArr.at(cChoice)->getId(), type);
        cArr.at(cChoice)->addVehicle(nv);
        controller->fillTables(cArr, vArr, aArr, jArr, sArr);
        vChoice = vArr.size() - 1;
        int nJobs = controller->getNumJobs(cArr.at(cChoice)->getId());
        ui->customerLbl_3->setText(QString::fromStdString("Customer: " + cArr.at(cChoice)->getFirst() + " " + cArr.at(cChoice)->getLast() + "\nAge: " + to_string(cArr.at(cChoice)->getAge()) + "\nNumber of Jobs: " + to_string(nJobs)));
        ui->vehicleLbl->setText(QString::fromStdString("Vehicle: " + vArr.at(vChoice)->getYear() + " " + vArr.at(vChoice)->getMake() + " "  + vArr.at(vChoice)->getModel() + "\nColour: "  + vArr.at(vChoice)->getColor() ));
        ui->otherTxt->setVisible(false);
        ui->rustTbl->setRowCount(0);

        ui->detailsWidget->setEnabled(true);
        setChkBoxes(false);
        setRdBtns(false);
    }


}

//event handler for when the combo box containing all the different makes changes the current item selected
void UI::on_makeTxt_currentIndexChanged(int index){
    if(index == 0 || index == -1){
        ui->makeTxt->setEditable(true);
    }else{
        ui->makeTxt->setEditable(false);
        controller->getModels(ui->makeTxt->currentText().toStdString(), models);
        for(int i = 0; i < (int)models.size(); i++){
            ui->modelTxt->addItem(QString::fromStdString(models.at(i)));
            ui->modelTxt_2->addItem(QString::fromStdString(models.at(i)));
        }
    }
}

//event handler for when the combo box containing all the different models changes the current item selected
void UI::on_modelTxt_currentIndexChanged(int index){
    if(index == 0){
        ui->modelTxt->setEditable(true);
    }else{
        ui->modelTxt->setEditable(false);
    }
}

//event handler for when the combo box containing all the different colours changes the current item selected
void UI::on_origColorTxt_currentIndexChanged(int index){
    if(index == 0){
        ui->origColorTxt->setEditable(true);
    }else{
        ui->origColorTxt->setEditable(false);
    }
}

//event handler for when the "View" button is clicked, which sets up the vectors with most current info from the database and displays it on screen
void UI::on_viewBtn_clicked(){
    fillTables();
    ui->pageStack->setCurrentIndex(7);
}

//gets all the info from the database and sets up and displays the information in the appropriate tables
void UI::fillTables(){
    ui->clientTbl->setRowCount(0);
    ui->vehicleTbl->setRowCount(0);
    ui->vehicleTbl_2->setRowCount(0);
    ui->assetTbl->setRowCount(0);
    ui->jobTbl->setRowCount(0);
    ui->jobTbl_2->setRowCount(0);
    ui->clientTbl->setColumnWidth(0, 25);
    ui->clientTbl->setColumnWidth(1, 200);
    ui->clientTbl->setColumnWidth(2, 200);
    ui->clientTbl->setColumnWidth(3, 75);
    ui->clientTbl->setColumnWidth(4, 200);
    ui->clientTbl->setColumnWidth(5, 200);
    ui->clientTbl->setColumnWidth(6, 300);
    ui->vehicleTbl->setColumnWidth(0, 25);
    ui->vehicleTbl->setColumnWidth(1, 250);
    ui->vehicleTbl->setColumnWidth(2, 250);
    ui->vehicleTbl->setColumnWidth(3, 150);
    ui->vehicleTbl->setColumnWidth(4, 200);
    ui->vehicleTbl->setColumnWidth(5, 350);
    ui->vehicleTbl->setColumnWidth(6, 150);
    ui->vehicleTbl_2->setColumnWidth(0, 25);
    ui->vehicleTbl_2->setColumnWidth(1, 250);
    ui->vehicleTbl_2->setColumnWidth(2, 250);
    ui->vehicleTbl_2->setColumnWidth(3, 150);
    ui->vehicleTbl_2->setColumnWidth(4, 200);
    ui->vehicleTbl_2->setColumnWidth(5, 350);
    ui->vehicleTbl_2->setColumnWidth(6, 150);
    ui->assetTbl->setColumnWidth(0, 25);
    ui->assetTbl->setColumnWidth(1, 400);
    ui->assetTbl->setColumnWidth(2, 125);
    ui->assetTbl->setColumnWidth(3, 125);
    ui->assetTbl->setColumnWidth(4, 200);
    ui->assetTbl->setColumnWidth(5, 200);
    ui->assetTbl->setColumnWidth(6, 200);
    ui->jobTbl->setColumnWidth(0, 25);
    ui->jobTbl->setColumnWidth(1, 175);
    ui->jobTbl->setColumnWidth(2, 200);
    ui->jobTbl->setColumnWidth(3, 125);
    ui->jobTbl->setColumnWidth(4, 75);
    ui->jobTbl->setColumnWidth(5, 150);
    ui->jobTbl->setColumnWidth(6, 75);
    ui->jobTbl->setColumnWidth(7, 200);
    ui->jobTbl->setColumnWidth(8, 100);
    ui->jobTbl->setColumnWidth(9, 150);
    ui->jobTbl->setColumnWidth(10, 125);
    ui->jobTbl_2->setColumnWidth(0, 25);
    ui->jobTbl_2->setColumnWidth(1, 175);
    ui->jobTbl_2->setColumnWidth(2, 200);
    ui->jobTbl_2->setColumnWidth(3, 75);
    ui->jobTbl_2->setColumnWidth(4, 75);
    ui->jobTbl_2->setColumnWidth(5, 150);
    ui->jobTbl_2->setColumnWidth(6, 75);
    ui->jobTbl_2->setColumnWidth(7, 200);
    ui->jobTbl_2->setColumnWidth(8, 100);
    ui->jobTbl_2->setColumnWidth(9, 75);
    ui->jobTbl_3->setColumnWidth(0, 25);
    ui->jobTbl_3->setColumnWidth(1, 175);
    ui->jobTbl_3->setColumnWidth(2, 200);
    ui->jobTbl_3->setColumnWidth(3, 125);
    ui->jobTbl_3->setColumnWidth(4, 75);
    ui->jobTbl_3->setColumnWidth(5, 150);
    ui->jobTbl_3->setColumnWidth(6, 75);
    ui->jobTbl_3->setColumnWidth(7, 200);
    ui->jobTbl_3->setColumnWidth(8, 100);
    ui->jobTbl_3->setColumnWidth(9, 150);
    ui->jobTbl_3->setColumnWidth(10, 125);
    ui->jobTbl_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->jobTbl_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->jobTbl->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->assetTbl->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->vehicleTbl->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->clientTbl->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->dataBaseTabs->setCurrentIndex(focus);

    controller->fillTables(cArr, vArr, aArr, jArr, sArr);//fills the vectors with the data from the database
    for(int i = 0; i < (int)cArr.size(); i++){
        ui->clientTbl->insertRow(i);

        QString id = QString::number(cArr.at(i)->getId());
        ui->clientTbl->setItem(i, 0, new QTableWidgetItem(id));

        QString first = QString::fromStdString(cArr.at(i)->getFirst());
        ui->clientTbl->setItem(i, 1, new QTableWidgetItem(first));

        QString last = QString::fromStdString(cArr.at(i)->getLast());
        ui->clientTbl->setItem(i, 2, new QTableWidgetItem(last));

        QString phone1 = QString::fromStdString(cArr.at(i)->getPhone1());
        ui->clientTbl->setItem(i, 4, new QTableWidgetItem(phone1));

        QString phone2 = QString::fromStdString(cArr.at(i)->getPhone2());
        ui->clientTbl->setItem(i, 5, new QTableWidgetItem(phone2));

        QString age = QString::number(cArr.at(i)->getAge());
        ui->clientTbl->setItem(i, 3, new QTableWidgetItem(age));

        QString email = QString::fromStdString(cArr.at(i)->getEmail());
        ui->clientTbl->setItem(i, 6, new QTableWidgetItem(email));

        QString insta = QString::fromStdString(cArr.at(i)->getInsta());
        ui->clientTbl->setItem(i, 7, new QTableWidgetItem(insta));
    }
    for(int i = 0; i < (int)vArr.size(); i++){
        ui->vehicleTbl->insertRow(i);

        QString id = QString::number(vArr.at(i)->getId());
        ui->vehicleTbl->setItem(i, 0, new QTableWidgetItem(id));

        QString oid = QString::number(vArr.at(i)->getOwnerId());
        ui->vehicleTbl->setItem(i, 6, new QTableWidgetItem(oid));

        QString ownerName;
        for(int j = 0; j < (int)cArr.size(); j++){
            if(cArr.at(j)->getId() == vArr.at(i)->getOwnerId()){
                ownerName = QString::fromStdString(cArr.at(j)->getFirst() + " " + cArr.at(j)->getLast());
            }
        }
        ui->vehicleTbl->setItem(i, 7, new QTableWidgetItem(ownerName));

        QString make = QString::fromStdString(vArr.at(i)->getMake());
        ui->vehicleTbl->setItem(i, 1, new QTableWidgetItem(make));

        QString model = QString::fromStdString(vArr.at(i)->getModel());
        ui->vehicleTbl->setItem(i, 2, new QTableWidgetItem(model));

        QString year = QString::fromStdString(vArr.at(i)->getYear());
        ui->vehicleTbl->setItem(i, 3, new QTableWidgetItem(year));

        QString color = QString::fromStdString(vArr.at(i)->getColor());
        ui->vehicleTbl->setItem(i, 4, new QTableWidgetItem(color));

        QString doors = QString::fromStdString(vArr.at(i)->getNumDoors());
        ui->vehicleTbl->setItem(i, 5, new QTableWidgetItem(doors));
    }

    for(int i = 0; i < (int)jArr.size(); i++){
        ui->jobTbl->insertRow(i);

        QString id = QString::number(jArr.at(i)->getId());
        ui->jobTbl->setItem(i, 0, new QTableWidgetItem(id));

        QString empId = QString::number(jArr.at(i)->getEmpId());
        ui->jobTbl->setItem(i, 1, new QTableWidgetItem(empId));

        QString empName = QString::fromStdString(jArr.at(i)->getEmpName());
        ui->jobTbl->setItem(i, 2, new QTableWidgetItem(empName));

        QString type = QString::fromStdString(jArr.at(i)->getType());
        ui->jobTbl->setItem(i, 3, new QTableWidgetItem(type));

        QString quote = QString::number(jArr.at(i)->getQuote());
        ui->jobTbl->setItem(i, 8, new QTableWidgetItem(quote));

        QString clientId = QString::number(jArr.at(i)->getClientId());
        ui->jobTbl->setItem(i, 4, new QTableWidgetItem(clientId));

        QString clientName = QString::fromStdString(jArr.at(i)->getClientName());
        ui->jobTbl->setItem(i, 5, new QTableWidgetItem(clientName));

        QString vId = QString::number(jArr.at(i)->getVId());
        ui->jobTbl->setItem(i, 6, new QTableWidgetItem(vId));

        QString vName = QString::fromStdString(jArr.at(i)->getVName());
        ui->jobTbl->setItem(i, 7, new QTableWidgetItem(vName));

        QString cost = QString::number(jArr.at(i)->getActualCost());
        ui->jobTbl->setItem(i, 9, new QTableWidgetItem(cost));

        QString tools = QString::fromStdString(jArr.at(i)->getTools());
        ui->jobTbl->setItem(i, 10, new QTableWidgetItem(tools));

        QString progress = QString::fromStdString(jArr.at(i)->getProgress());
        ui->jobTbl->setItem(i, 11, new QTableWidgetItem(progress));

        QString paid = QString::fromStdString(jArr.at(i)->getPaid());
        ui->jobTbl->setItem(i, 12, new QTableWidgetItem(paid));
    }
    ui->addAssetJobBox->clear();
    for(int i = 0; i < (int)aArr.size(); i++){
        ui->assetTbl->insertRow(i);

        QString id = QString::number(aArr.at(i)->getId());
        ui->assetTbl->setItem(i, 0, new QTableWidgetItem(id));

        QString name = QString::fromStdString(aArr.at(i)->getObjectName());
        ui->assetTbl->setItem(i, 1, new QTableWidgetItem(name));

        QString colour = QString::fromStdString(aArr.at(i)->getColour());
        ui->assetTbl->setItem(i, 2, new QTableWidgetItem(colour));

        ui->addAssetJobBox->addItem(name + " " + colour);

        QString price = QString::number(aArr.at(i)->getPrice());
        ui->assetTbl->setItem(i, 3, new QTableWidgetItem(price));

        QString date = QString::fromStdString(aArr.at(i)->getDate());
        ui->assetTbl->setItem(i, 4, new QTableWidgetItem(date));

        QString amntB = QString::number(aArr.at(i)->getBought());
        ui->assetTbl->setItem(i, 5, new QTableWidgetItem(amntB));

        QString amntU = QString::number(aArr.at(i)->getUsed());
        ui->assetTbl->setItem(i, 6, new QTableWidgetItem(amntU));

        QString amntL = QString::number(amntB.toDouble() - amntU.toDouble());
        ui->assetTbl->setItem(i, 7, new QTableWidgetItem(amntL));
    }
    populateEmployeeDropDown();
    ui->addAssetJobTbl->setColumnWidth(0, 25);
    ui->addAssetJobTbl->setColumnWidth(1, 150);
    ui->addAssetJobBox->setCurrentIndex(-1);
}

//event handler for when the Job table is double clicked, which switches the view to the edit job page allowing the user to edit the specific job
void UI::on_jobTbl_cellDoubleClicked(int row, int column){
    for(int i = 0; i < (int)jArr.size(); i++){
        if(ui->jobTbl->item(row, 0)->text().toInt() == jArr.at(i)->getId()){
            jChoice = i;
        }
    }
    setupJobPage();
}

//takes the string of all the tools/wraps id numbers used for a specific job and converts it back to vector of just the id number for each tool/wrap
vector<int> UI::getTools(string str){
    int lastComma = 0;
    vector<int> tools;
    for(int i = 0; i < (int)str.length(); i++){
        if(str[i] == 44){
            string newStr = str.substr(lastComma, i - lastComma);
            lastComma = i + 1;
            int newInt = stoi(newStr);
            tools.push_back(newInt);
        }
    }
    if(str.length() != 0 && (int)str.length() > lastComma){
        string newStr = str.substr(lastComma + 1);
        int newInt = stoi(newStr);
        tools.push_back(newInt);
    }
    return tools;
}

//event handler for when the Client table is double clicked, which switches the view to the edit client page allowing the user to edit the specific client
void UI::on_clientTbl_cellDoubleClicked(int row, int column){
    for(int i = 0; i < (int)cArr.size(); i++){
        if(ui->clientTbl->item(row, 0)->text().toInt() == cArr.at(i)->getId()){
            cChoice = i;
        }
    }
    setupClientPage();
}

//event handler for when the Vehicle table is double clicked, which switches the view to the edit vehicle page allowing the user to edit the specific Vehicle
void UI::on_vehicleTbl_cellDoubleClicked(int row, int column){
    for(int i = 0; i < (int)vArr.size(); i++){
        if(ui->vehicleTbl->item(row, 0)->text().toInt() == vArr.at(i)->getId()){
            vChoice = i;
        }
    }
    setupVehiclePage();
}

//event handler for when the Asset table is double clicked, which switches the view to the edit asset page allowing the user to edit the specific asset
void UI::on_assetTbl_cellDoubleClicked(int row, int column){
    for(int i = 0; i < (int)aArr.size(); i++){
        if(ui->assetTbl->item(row, 0)->text().toInt() == aArr.at(i)->getId()){
            aChoice = i;
            ui->pageStack->setCurrentIndex(8);
        }
    }
    setupAssetPage();
}

//event handler for when the user switches from one table to the next, holds which ever table was viewed last so that when that page is called upon again that table will come up first
void UI::on_dataBaseTabs_currentChanged(int index){
    focus = index;
}

//event handler for when the update client page has been filled out and then the updated information will be sent to the database
void UI::on_updateClientBtn_clicked(){
    //Update customer
    string firstName = ui->firstTxt_2->text().toStdString();
    if((int)firstName[0] > 97 ){
        firstName[0] -= 32;
    }
    string lastName = ui->lastTxt_2->text().toStdString();
    if((int)lastName[0] > 97 ){
        lastName[0] -= 32;
    }
    QString age = ui->ageTxt_2->text();
    int ageInt = age.toInt();
    string phone1 = ui->phoneTxt1_2->text().toStdString();
    string phone2 = ui->phoneTxt2_2->text().toStdString();
    string email = ui->emailTxt_2->text().toStdString();
    string insta = ui->instaTxt_2->text().toStdString();
    string blank = "";
    int id = cArr.at(cChoice)->getId();

    if(firstName != blank && lastName != blank && phone1 != blank){
        controller->update(id, firstName, lastName, ageInt, phone1, phone2, email, insta);
        fillTables();
        on_viewBtn_clicked();
    }

}

//event handler for when the back button is clicked
//TODO: make it so when the back button is clicked the focus goes back to whatever page was viewed last not neccesarily just the view database page
void UI::on_backBtn_clicked(){
    on_viewBtn_clicked();
}

//event handler for when the update Vehicle page has been filled out and then the updated information will be sent to the database
void UI::on_addVehicleBtn_2_clicked(){
    //update Vehicle
    populateVehicleChoices();
    int id = vArr.at(vChoice)->getId();
    string color = ui->origColorTxt_2->currentText().toStdString();
    string nDoors = ui->numDoorsTxt_2->currentText().toStdString();
    string make = ui->makeTxt_2->currentText().toStdString();
    string model = ui->modelTxt_2->currentText().toStdString();
    string year = ui->yearTxt_2->text().toStdString();
    string type = ui->typeBox_2->currentText().toStdString();
    string blank = "";


    if(id != 0 && color != blank && make != blank && model != blank && year != blank){
        controller->update(id, color, nDoors, make, model, year, cArr.at(cChoice)->getId(), type);
        fillTables();
        on_viewBtn_clicked();
    }

}

//event handler for when the user chooses to add a new asset to the inventory order
void UI::on_addItemBtn_clicked(){
    string blank = "";
    ui->pageStack->setCurrentIndex(9);
    ui->assetStack->setCurrentIndex(0);
}

//event handler for when the user chooses whether the new asset will be a Tool or a Wrap
void UI::on_assetChoiceBtn_clicked(){
    if(ui->assetChoiceBox->currentText() == "Tool"){
        aChoice = 0;
        ui->assetStack->setCurrentIndex(1);
    }else if(ui->assetChoiceBox->currentText() == "Wrap"){
        aChoice = 1;
        ui->assetStack->setCurrentIndex(2);
    }
}

//event handler for when the user adds the tool to the inventory order, and updates the UI accordingly
void UI::on_submitToolBtn_clicked(){
    ui->pageStack->setCurrentIndex(6);
    ui->assetTbl->setColumnWidth(0, 25);
    ui->assetTbl->setColumnWidth(1, 400);
    ui->assetTbl->setColumnWidth(2, 125);
    ui->assetTbl->setColumnWidth(3, 125);
    ui->assetTbl->setColumnWidth(4, 200);
    ui->assetTbl->setColumnWidth(5, 200);
    ui->assetTbl->setColumnWidth(6, 200);
    int tblSize = ui->addAssetTbl->rowCount();
    int aId = controller->getHighestId("ASSET", "obj_id") + tblSize;
    string name = ui->nameTxt_2->text().toStdString();
    double price = ui->priceTxt_2->text().toDouble();
    string date = ui->dateTxt_2->text().toStdString();
    if(name != "" && date != ""){
        order.push_back(new Asset(aId, name, price, date, 0, "", 1, 0));
        QString qId = QString::number(aId);
        QString qName = ui->nameTxt_2->text();
        QString qPrice = ui->priceTxt_2->text();
        QString qDate = ui->dateTxt_2->text();
        ui->addAssetTbl->setItem(tblSize - 1, 0, new QTableWidgetItem(qId));
        ui->addAssetTbl->setItem(tblSize - 1, 1, new QTableWidgetItem(qName));
        ui->addAssetTbl->setItem(tblSize - 1, 3, new QTableWidgetItem(qPrice));
        ui->addAssetTbl->setItem(tblSize - 1, 4, new QTableWidgetItem(qDate));
        ui->addAssetTbl->setRowCount(tblSize + 1);
        int yPos = 129 + (38 * tblSize);
        ui->addItemBtn->setGeometry(1630, yPos, 93, 38);
        ui->assetChoiceBox->setCurrentIndex(-1);
        ui->nameTxt_2->setText("");
        ui->priceTxt_2->setText("");
        ui->dateTxt_2->setText("");
    }
}

//event handler for when the user adds the wrap to the inventory order, and updates the UI accordingly
void UI::on_submitWrapBtn_clicked(){
    ui->pageStack->setCurrentIndex(6);
    ui->assetTbl->setColumnWidth(0, 25);
    ui->assetTbl->setColumnWidth(1, 400);
    ui->assetTbl->setColumnWidth(2, 125);
    ui->assetTbl->setColumnWidth(3, 125);
    ui->assetTbl->setColumnWidth(4, 200);
    ui->assetTbl->setColumnWidth(5, 200);
    ui->assetTbl->setColumnWidth(6, 200);
    int tblSize = ui->addAssetTbl->rowCount();
    int aId = controller->getHighestId("ASSET", "obj_id") + tblSize;
    string name = ui->nameTxt_3->text().toStdString();
    double price = ui->priceTxt_3->text().toDouble();
    string date = ui->dateTxt_3->text().toStdString();
    if(name != "" && date != ""){

        QString qId = QString::number(aId);
        QString qName = ui->nameTxt_3->text();
        QString qPrice = ui->priceTxt_3->text();
        QString qDate = ui->dateTxt_3->text();
        QString qAmnt = ui->amntTxt_3->text();
        QString qColour = ui->colourTxt_3->text();
        order.push_back(new Asset(aId, name, price, date, 1, qColour.toStdString(), qAmnt.toDouble(), 0));
        ui->addAssetTbl->setItem(tblSize - 1, 0, new QTableWidgetItem(qId));
        ui->addAssetTbl->setItem(tblSize - 1, 1, new QTableWidgetItem(qName));
        ui->addAssetTbl->setItem(tblSize - 1, 2, new QTableWidgetItem(qColour));
        ui->addAssetTbl->setItem(tblSize - 1, 3, new QTableWidgetItem(qPrice));
        ui->addAssetTbl->setItem(tblSize - 1, 4, new QTableWidgetItem(qDate));
        ui->addAssetTbl->setItem(tblSize - 1, 5, new QTableWidgetItem(qAmnt));
        ui->addAssetTbl->setItem(tblSize - 1, 6, new QTableWidgetItem("0"));
        ui->addAssetTbl->setItem(tblSize - 1, 7, new QTableWidgetItem(qAmnt));
        ui->addAssetTbl->setRowCount(tblSize + 1);
        int yPos = 129 + (36 * tblSize);
        ui->addItemBtn->setGeometry(1630, yPos, 93, 31);
        ui->assetChoiceBox->setCurrentIndex(-1);
        ui->nameTxt_3->setText("");
        ui->priceTxt_3->setText("");
        ui->dateTxt_3->setText("");
    }
}

//event handler for when the user adds the whole order into the system, this sends function sends the order to the database to be stored
void UI::on_submitOrderBtn_clicked(){
    ui->pageStack->setCurrentIndex(1);
    controller->addOrder(order);
}

void UI::on_updateToolBtn_clicked(){
    updateAsset();
}

void UI::on_updateWrapBtn_clicked(){
    updateAsset();
}

//event handler for when the user chooses to update a particular asset
void UI::updateAsset(){
    string blank = "", name = "", colour = "", date = "";
    int wrap = aArr.at(aChoice)->getWrap(), id = aArr.at(aChoice)->getId();
    double price = 0, amnt = 0, used = 0;
    if(wrap == 0){
        name = ui->nameTxt_4->text().toStdString();
        date = ui->dateTxt_4->text().toStdString();
        price = ui->priceTxt_4->text().toDouble();
    }else{
        name = ui->nameTxt_5->text().toStdString();
        date = ui->dateTxt_5->text().toStdString();
        price = ui->priceTxt_5->text().toDouble();
        colour = ui->colourTxt_4->text().toDouble();
        amnt = ui->amntTxt_4->text().toDouble();
    }

    if(name != blank && date != blank){
        controller->update(id, name, price, date, wrap, colour, amnt, 0);
        fillTables();
        on_viewBtn_clicked();
    }

}

//event handler for when the user selects the "other" Job type, sets all the checkboxes to false
void UI::on_otherRdBtn_clicked(){
    ui->otherTxt->setVisible(true);
    ui->partsWidget->setEnabled(false);
    setChkBoxes(false);
    type = "Other";
}

//event handler for when the user selects the "full" Job type, sets all the checkboxes to true
void UI::on_fullRdBtn_clicked(){
    ui->otherTxt->setVisible(false);
    ui->partsWidget->setEnabled(false);
    setChkBoxes(true);
    type = "Full";
    if(vArr.at(vChoice)->getNumDoors() == "2"){
        ui->bdDoorChkBox->setEnabled(false);
        ui->rpDoorChkBox->setEnabled(false);
    }
}

//sets all the check boxes to whichever boolean option gets passed into it
void UI::setChkBoxes(bool b){
    ui->bbChkBox->setChecked(b);
    ui->bdDoorChkBox->setChecked(b);
    ui->dDoorChkBox->setChecked(b);
    ui->fBChkBox->setChecked(b);
    ui->fLFChkBox->setChecked(b);
    ui->fRFChkBox->setChecked(b);
    ui->hoodChkBox->setChecked(b);
    ui->lRockerChkBox->setChecked(b);
    ui->pDoorChkBox->setChecked(b);
    ui->rLFChkBox->setChecked(b);
    ui->rRFChkBox->setChecked(b);
    ui->rRockerChkBox->setChecked(b);
    ui->roofChkBox->setChecked(b);
    ui->rpDoorChkBox->setChecked(b);
    ui->trunkChkBox->setChecked(b);
}

//event handler for when the user selects the "hood" Job type, sets all but the hood checkboxes to false
void UI::on_hoodRdBtn_clicked(){
    ui->otherTxt->setVisible(false);
    setChkBoxes(false);
    ui->hoodChkBox->setChecked(true);
    ui->partsWidget->setEnabled(false);
    type = "Hood";
}

//event handler for when the user selects the "Chrome Delete" Job type, sets all the checkboxes to false
void UI::on_chromeRdBtn_clicked(){
    ui->otherTxt->setVisible(false);
    setChkBoxes(false);
    ui->partsWidget->setEnabled(true);
    type = "Chrome Delete";
}

//event handler for when the user selects the "decal" Job type, sets all the checkboxes to false
void UI::on_decalRdBtn_clicked(){
    ui->otherTxt->setVisible(false);
    setChkBoxes(false);
    ui->partsWidget->setEnabled(false);
    type = "Decal";
}

//event handler for when the user selects the "partial" Job type, allows the checkboxes to be set manually
void UI::on_partialRdBtn_clicked(){
    ui->otherTxt->setVisible(false);
    setChkBoxes(false);
    ui->partsWidget->setEnabled(true);
    type = "Partial";
}

//event handler for when the user confirms the pieces which will be wrapped in the current job
void UI::on_confirmPcsBtn_clicked(){
    if(ui->empTxt->currentIndex() != -1 && (ui->hoodRdBtn->isChecked() || ui->fullRdBtn->isChecked() || ui->decalRdBtn->isChecked() || ui->otherRdBtn->isChecked() || ui->partialRdBtn->isChecked() || ui->chromeRdBtn->isChecked())){
        sChoice = ui->empTxt->currentIndex();
        ui->detailsWidget->setEnabled(false);
        ui->partsWidget->setEnabled(false);
        getChecked();
        if(ui->hoodRdBtn->isChecked()){
            type = "Hood";
        }else if(ui->fullRdBtn->isChecked()){
            type = "Full";
        }else if(ui->partialRdBtn->isChecked()){
            type = "Partial";
        }else if(ui->decalRdBtn->isChecked()){
            type = "Decal";
        }else if(ui->otherRdBtn->isChecked()){
            type = "Other: " + ui->otherTxt->toPlainText().toStdString();
        }else if(ui->chromeRdBtn->isChecked()){
            type = "Chrome Delete";
        }
        ui->rustWidget->setEnabled(true);
        ui->toolWidget->setEnabled(true);
        int j = 0;
        if(type == "Full" || type == "Partial" || type == "Chrome Delete" || type == "Hood"){
            for(int i = 0; i < (int)details.size(); i++){
                if(details.at(i)->getUsed()){
                    ui->rustTbl->insertRow(j);
                    ui->rustTbl->setItem(j, 0, new QTableWidgetItem(QString::fromStdString(details.at(i)->getName())));
                    ui->rustTbl->setItem(j, 1, new QTableWidgetItem(QString::fromStdString("0")));
                    j++;
                }
            }
        }

    }
}

//figures out which pieces of the car to be added to the specific job by checking each of the check boxes
void UI::getChecked(){
    details.push_back(new CarPart(0, "Rear Bumper", ui->bbChkBox->isChecked(), 0));
    details.push_back(new CarPart(0, "Rear Driver Side Door", ui->bdDoorChkBox->isChecked(), 0));
    details.push_back(new CarPart(0, "Driver Side Door", ui->dDoorChkBox->isChecked(), 0));
    details.push_back(new CarPart(0, "Front Bumper", ui->fBChkBox->isChecked(), 0));
    details.push_back(new CarPart(0, "Front Left Fender", ui->fLFChkBox->isChecked(), 0));
    details.push_back(new CarPart(0, "Front Right Fender", ui->fRFChkBox->isChecked(), 0));
    details.push_back(new CarPart(0, "Hood", ui->hoodChkBox->isChecked(), 0));
    details.push_back(new CarPart(0, "Left Rocker", ui->lRockerChkBox->isChecked(), 0));
    details.push_back(new CarPart(0, "Passenger Door", ui->pDoorChkBox->isChecked(), 0));
    details.push_back(new CarPart(0, "Rear Left Fender", ui->rLFChkBox->isChecked(), 0));
    details.push_back(new CarPart(0, "Rear Right Fender", ui->rRFChkBox->isChecked(), 0));
    details.push_back(new CarPart(0, "Right Rocker", ui->rRockerChkBox->isChecked(), 0));
    details.push_back(new CarPart(0, "Roof", ui->roofChkBox->isChecked(), 0));
    details.push_back(new CarPart(0, "Rear Passenger Door", ui->rpDoorChkBox->isChecked(), 0));
    details.push_back(new CarPart(0, "Trunk", ui->trunkChkBox->isChecked(), 0));
}

//adds a new asset to the job
void UI::on_addAssetJobBtn_clicked(){
    aChoice = ui->addAssetJobBox->currentIndex();
    if(aChoice != -1){
        int i = (int)ui->addAssetJobTbl->rowCount();

        ui->addAssetJobTbl->insertRow(i);

        QString id = QString::number(aArr.at(aChoice)->getId());
        ui->addAssetJobTbl->setItem(i, 0, new QTableWidgetItem(id));

        QString name = QString::fromStdString(aArr.at(aChoice)->getObjectName());
        ui->addAssetJobTbl->setItem(i, 1, new QTableWidgetItem(name));

        QString colour = QString::fromStdString(aArr.at(aChoice)->getColour());
        ui->addAssetJobTbl->setItem(i, 2, new QTableWidgetItem(colour));
    }
    ui->addAssetJobBox->setCurrentIndex(-1);
}

//collects all the information and displays it on a confirmation page before submitting the job
void UI::on_submitJobBtn_clicked(){
    int j = 0;
    if(type != "Decal"){
        for(int i = 0; i < (int)details.size(); i++){
            if(details.at(i)->getUsed()){
                details.at(i)->setName(ui->rustTbl->item(j, 0)->text().toStdString());
                details.at(i)->setDamage(ui->rustTbl->item(j, 1)->text().toDouble());
                details.at(i)->setUsed("1");
                j++;
            }
        }
    }

    string toolsUsed = "";
    for(int i = 0; i < (int)ui->addAssetJobTbl->rowCount(); i++){
         toolsUsed += ui->addAssetJobTbl->item(i, 0)->text().toStdString() + ",";
    }
    int jobId = controller->getHighestId("JOB", "job_id") + 1;
    if(jobId == 1){
        jobId = 1000;
    }
    string empIdStr = ui->empTxt->currentText().toStdString().substr(0,4);
    int empId = stoi(empIdStr);
    string empName =ui->empTxt->currentText().toStdString().substr(5);
    int cId = cArr.at(cChoice)->getId(), vId = vArr.at(vChoice)->getId();
    string strTemp = "", cName = cArr.at(cChoice)->getFirst() + " " + cArr.at(cChoice)->getLast(), vName = vArr.at(vChoice)->getYear() + " " +  vArr.at(vChoice)->getMake() + " " +  vArr.at(vChoice)->getModel();
    double q = quote();
    ui->pageStack->setCurrentIndex(10);
    string progress = "Not Started";
    if(type != "Decal" || type != "Other" ){
        for(int i = 0; i < (int)details.size(); i++){
            if(details.at(i)->getUsed()){
                strTemp += "\t\tPart: " + details.at(i)->getName() + " Prexisting Damage: " + to_string(details.at(i)->getDamage()) + ".\n";
            }
        }
    }

    string cStr = "Job ID: " + to_string(jobId) + "\n"
            + "Primary Employee ID: " + to_string(empId) + "\n"
            + "Primary Employee Name: " + empName + "\n"
            + "Customer ID: " + to_string(cId) + "\n"
            + "Customer Name: " + cName + "\n"
            + "Vehicle ID: " + to_string(vId) + "\n"
            + "Vehicle Name: " + vName + "\n"
            + "Vehicle Type: " + type + "\n"
            + "Quote: " + to_string(q) + "\n"
            + "Parts Used and Pre-Existing Damage: \n"
            + strTemp +
            + "Tools Used: " + toolsUsed
            + "Progress: " + progress;
    ui->confirmLbl->setText(QString::fromStdString(cStr));
}

//calculates an approximate quote for each job, this function is reliant on the clients information for how he normally quotes jobs
double UI::quote(){
    double final = 0, base = 0;
    Vehicle* newV = vArr.at(vChoice);
    if(newV->getType() == "Truck"){
        base = 2300;
    }else if(newV->getType() == "Van/SUV"){
        base = 2500;
    }else if(newV->getType() == "Car"){
        if(newV->getNumDoors() == "2"){
            base = 2000;
        }else if(newV->getNumDoors() == "4"){
            base = 2200;
        }
    }
    if(type == "Hood"){
        final = 0.09 * base;
    }else if(type == "Full"){
        final = base;
    }else if(type == "Decal"){
        final = 0;
    }else if(type == "Partial"){
        final = getPercentage() * base;
    }else if(type == "Chrome Delete"){
        final = 180;
    }
    return final;
}

//calculates the percentage of the total cost that is appropriate depending on which pieces of the car are to wrapped
double UI::getPercentage(){

    double sum = 0;
    for(int i = 0; i < (int)details.size(); i++){
        if(details.at(i)->getUsed()){
            sum += details.at(i)->getWeight();
        }
    }
    return sum;
}

//sets the radio buttons to whichever boolean value is passed into this function
void UI::setRdBtns(bool b){
    ui->otherRdBtn->setChecked(b);
    ui->fullRdBtn->setChecked(b);
    ui->hoodRdBtn->setChecked(b);
    ui->chromeRdBtn->setChecked(b);
    ui->decalRdBtn->setChecked(b);
    ui->partialRdBtn->setChecked(b);
}

//once the user has reviewed thte confirmation page and is finally ready to add the new job to the system, the confirm button is selected and the job is added to the database
void UI::on_confirmBtn_clicked(){
    string toolsUsed = "";
    for(int i = 0; i < (int)ui->addAssetJobTbl->rowCount(); i++){
         toolsUsed += ui->addAssetJobTbl->item(i, 0)->text().toStdString() + ",";
    }
    int jobId = controller->getHighestId("JOB", "job_id") + 1;
    if(jobId == 1){
        jobId = 1000;
    }
    string empIdStr = ui->empTxt->currentText().toStdString().substr(0,4);
    int empId = stoi(empIdStr);
    string empName =ui->empTxt->currentText().toStdString().substr(5);
    int cId = cArr.at(cChoice)->getId(), vId = vArr.at(vChoice)->getId();
    string strTemp = "", cName = cArr.at(cChoice)->getFirst() + " " + cArr.at(cChoice)->getLast(), vName = vArr.at(vChoice)->getYear() + " " +  vArr.at(vChoice)->getMake() + " " +  vArr.at(vChoice)->getModel();
    double q = quote();
    controller->add(jobId, empId, empName, type, q, cId, cName, vId, vName, 0, details, toolsUsed, "Not Started", "Not Paid");
    ui->pageStack->setCurrentIndex(1);
    setRdBtns(false);
    ui->addAssetJobTbl->setRowCount(0);
}

//for when a new part is added in the update job page, checks what parts are not currently being wrapped and displays them in drop down
void UI::on_addPartBtn_clicked(){
    int partsUsed = getNumParts();
    if(ui->newPartBox->currentIndex() >= 0 && partsUsed != 15){
        int numRows = ui->carPartsTbl->rowCount();
        ui->carPartsTbl->insertRow(numRows);

        QString part = ui->newPartBox->currentText();
        QTableWidgetItem *newItem = new QTableWidgetItem(part);
        newItem->setFlags(newItem->flags() & ~Qt::ItemIsEditable);
        ui->carPartsTbl->setItem(numRows, 0, newItem);

        QString damage = QString::fromStdString("0");
        ui->carPartsTbl->setItem(numRows, 1, new QTableWidgetItem(damage));
    }
    for(int i = 0; i < (int)details.size(); i++){
        if(details.at(i)->getName() == ui->newPartBox->currentText().toStdString()){
            details.at(i)->setUsed(true);
        }
    }
    ui->newPartBox->setCurrentIndex(-1);
    fillEditJobBoxes();
}

//returns the total number of parts currently selected to be wrapped in a given job
int UI::getNumParts(){
    details = jArr.at(jChoice)->getDetails();
    int total = 0;
    for(int i = 0; i < (int)details.size(); i++){
        if(details.at(i)->getUsed()){
            total++;
        }
    }
    return total;
}

//checks if a specific tool is being used for a specific job
bool UI::partOf(Asset* a){
    for(int i = 0; i < (int)toolArr.size(); i++){
        if(a->getId() == toolArr.at(i)){
            return true;
        }
    }
    return false;
}

//populates the new part and new asset dropdown of the update job page
void UI::fillEditJobBoxes(){
    ui->newPartBox->clear();
    ui->newToolBox->clear();
    int numParts = getNumParts();
    if(numParts < 15){
        for(int i = 0; i < 15; i++){
            if(!details.at(i)->getUsed()){
                ui->newPartBox->addItem(QString::fromStdString(details.at(i)->getName()));
            }
        }
    }
    ui->newPartBox->setCurrentIndex(-1);
    if(toolArr.size() < aArr.size()){
        for(int i = 0; i < (int)aArr.size(); i++){
            if(!partOf(aArr.at(i))){
                ui->newToolBox->addItem(QString::fromStdString(to_string(aArr.at(i)->getId()) + " " + aArr.at(i)->getObjectName() + " - " + aArr.at(i)->getColour()));
            }
        }
    }
    ui->newToolBox->setCurrentIndex(-1);
}

//adds a new tool to the job within the update job page
void UI::on_addToolBtn_clicked(){
    if(ui->newToolBox->currentIndex() >= 0 && toolArr.size() < aArr.size()){
        int numRows = ui->toolsTbl->rowCount();
        ui->toolsTbl->insertRow(numRows);

        Asset* newA = getAsset(ui->newToolBox->currentText());

        QString id = QString::number(newA->getId());
        QTableWidgetItem *newItem = new QTableWidgetItem(id);
        newItem->setFlags(newItem->flags() & ~Qt::ItemIsEditable);
        ui->toolsTbl->setItem(numRows, 0, newItem);

        QString name = QString::fromStdString(newA->getObjectName());
        QTableWidgetItem *newItem2 = new QTableWidgetItem(name);
        newItem->setFlags(newItem2->flags() & ~Qt::ItemIsEditable);
        ui->toolsTbl->setItem(numRows, 1, newItem2);

        QString amnt = QString::number(newA->getUsed());
        QTableWidgetItem *newItem3 = new QTableWidgetItem(amnt);
        ui->toolsTbl->setItem(numRows, 2, newItem3);

        toolArr.push_back(newA->getId());
        ui->newToolBox->setCurrentIndex(-1);
        fillEditJobBoxes();
    }

}

//returns an asset object based on the id
Asset* UI::getAsset(QString qStr){
    string str = qStr.toStdString();
    int id = stoi(str.substr(0, 4));
    for(int i = 0; i < (int)aArr.size(); i++){
        if(id == aArr.at(i)->getId()){
            return aArr.at(i);
        }
    }
    return NULL;
}

//this used to submit the updated version of the job by taking all the info from the update job page
void UI::on_confirmUpdateBtn_clicked(){
    string toolsUsed = "";
    for(int i = 0; i < (int)ui->toolsTbl->rowCount(); i++){
         toolsUsed += ui->toolsTbl->item(i, 0)->text().toStdString() + ",";
    }
    int jobId = ui->updateJobTbl->item(0, 0)->text().toInt();
    string empIdStr = ui->updateJobTbl->item(0, 1)->text().toStdString();
    int empId = stoi(empIdStr);
    string empName = ui->updateJobTbl->item(0, 2)->text().toStdString();
    type = ui->updateJobTbl->item(0, 3)->text().toStdString();
    int cId = ui->updateJobTbl->item(0, 4)->text().toInt(), vId = ui->updateJobTbl->item(0, 6)->text().toInt();
    string strTemp = "", cName = ui->updateJobTbl->item(0, 5)->text().toStdString(), vName = ui->updateJobTbl->item(0, 7)->text().toStdString();
    for(int i = 0; i < (int)vArr.size(); i++){
        if(vArr.at(i)->getId() == vId){
            vChoice = i;
        }
    }
    double q = quote();
    double a = ui->updateJobTbl->item(0, 9)->text().toDouble();
    string part;
    string progress = ui->progressBox->currentText().toStdString(), paid = ui->paidBox->currentText().toStdString();
    for(int i = 0; i < (int)ui->carPartsTbl->rowCount(); i++){
        part = ui->carPartsTbl->item(i, 0)->text().toStdString();
        for(int j = 0; j < (int)details.size(); j++){
            if(part == details.at(j)->getName()){
                details.at(j)->setDamage(ui->carPartsTbl->item(i,1)->text().toInt());
            }
        }
    }
    controller->update(jobId, empId, empName, type, q, cId, cName, vId, vName, a, details, toolsUsed, progress, paid);
    ui->pageStack->setCurrentIndex(1);
}

//this function is what is called when a user selects one of the options from the list returned from a search
void UI::on_resList_itemDoubleClicked(QListWidgetItem *item){
    string tempItem = item->text().toStdString();
    size_t f = tempItem.find_first_of(":");
    string resType;
    if(f != std::string::npos){
        resType = tempItem.substr(0, f);
    }
    size_t f2 = tempItem.find(":", f+1);
    int objId;
    if(f2 != std::string::npos){
        objId = stoi(tempItem.substr(f+2, 4));
    }
    if(resType == "Client"){
        for(int i = 0; i < (int)cArr.size(); i++){
            if(objId == cArr.at(i)->getId()){
                cChoice = i;
            }
        }
        setupClientPage();
    }else if(resType == "Job"){
        for(int i = 0; i < (int)jArr.size(); i++){
            if(objId == jArr.at(i)->getId()){
                jChoice = i;
            }
        }
        setupJobPage();
    }else if(resType == "Vehicle"){
        for(int i = 0; i < (int)vArr.size(); i++){
            if(objId == vArr.at(i)->getId()){
                vChoice = i;
            }
        }
        setupVehiclePage();
    }else if(resType == "Wrap" || resType == "Tool"){
        for(int i = 0; i < (int)aArr.size(); i++){
            if(objId == aArr.at(i)->getId()){
                aChoice = i;
            }
        }
        setupAssetPage();
    }
}

//event handler for when the back button is clicked
//TODO: make it so when the back button is clicked the focus goes back to whatever page was viewed last not neccesarily just the view database page
void UI::on_backBtn2_clicked(){
    ui->pageStack->setCurrentIndex(1);
}

//sets up the edit client page
void UI::setupClientPage(){
    ui->pageStack->setCurrentIndex(8);
    ui->updatePageStack->setCurrentIndex(0);
    ui->idLbl_2->setText(QString::fromStdString("ID: " + to_string(cArr.at(cChoice)->getId())));
    ui->firstTxt_2->setText(QString::fromStdString(cArr.at(cChoice)->getFirst()));
    ui->lastTxt_2->setText(QString::fromStdString(cArr.at(cChoice)->getLast()));
    ui->ageTxt_2->setText(QString::number(cArr.at(cChoice)->getAge()));
    ui->phoneTxt1_2->setText(QString::fromStdString(cArr.at(cChoice)->getPhone1()));
    ui->phoneTxt2_2->setText(QString::fromStdString(cArr.at(cChoice)->getPhone2()));
    ui->emailTxt_2->setText(QString::fromStdString(cArr.at(cChoice)->getEmail()));
    ui->instaTxt_2->setText(QString::fromStdString(cArr.at(cChoice)->getInsta()));
    ui->vehicleTbl_2->setRowCount(0);
    ui->jobTbl_2->setRowCount(0);

    for(int i = 0; i < (int)cArr.at(cChoice)->getVehicles().size(); i++){
        ui->vehicleTbl_2->insertRow(i);

        QString id = QString::number(cArr.at(cChoice)->getVehicles().at(i)->getId());
        ui->vehicleTbl_2->setItem(i, 0, new QTableWidgetItem(id));

        QString oid = QString::number(cArr.at(cChoice)->getVehicles().at(i)->getOwnerId());
        ui->vehicleTbl_2->setItem(i, 6, new QTableWidgetItem(oid));

        QString ownerName = QString::fromStdString(cArr.at(cChoice)->getFirst() + " " + cArr.at(cChoice)->getLast());
        ui->vehicleTbl_2->setItem(i, 7, new QTableWidgetItem(ownerName));

        QString make = QString::fromStdString(cArr.at(cChoice)->getVehicles().at(i)->getMake());
        ui->vehicleTbl_2->setItem(i, 1, new QTableWidgetItem(make));

        QString model = QString::fromStdString(cArr.at(cChoice)->getVehicles().at(i)->getModel());
        ui->vehicleTbl_2->setItem(i, 2, new QTableWidgetItem(model));

        QString year = QString::fromStdString(cArr.at(cChoice)->getVehicles().at(i)->getYear());
        ui->vehicleTbl_2->setItem(i, 3, new QTableWidgetItem(year));

        QString color = QString::fromStdString(cArr.at(cChoice)->getVehicles().at(i)->getColor());
        ui->vehicleTbl_2->setItem(i, 4, new QTableWidgetItem(color));

        QString doors = QString::fromStdString(cArr.at(cChoice)->getVehicles().at(i)->getNumDoors());
        ui->vehicleTbl_2->setItem(i, 5, new QTableWidgetItem(doors));
    }

    int j = 0;
    for(int i = 0; i < (int)jArr.size(); i++){
        if(jArr.at(i)->getClientId() == cArr.at(cChoice)->getId()){
            ui->jobTbl_2->insertRow(j);

            QString id = QString::number(jArr.at(i)->getId());
            ui->jobTbl_2->setItem(j, 0, new QTableWidgetItem(id));

            QString empId = QString::number(jArr.at(i)->getEmpId());
            ui->jobTbl_2->setItem(j, 1, new QTableWidgetItem(empId));

            QString empName = QString::fromStdString(jArr.at(i)->getEmpName());
            ui->jobTbl_2->setItem(j, 2, new QTableWidgetItem(empName));

            QString type = QString::fromStdString(jArr.at(i)->getType());
            ui->jobTbl_2->setItem(j, 3, new QTableWidgetItem(type));

            QString quote = QString::number(jArr.at(i)->getQuote());
            ui->jobTbl_2->setItem(j, 8, new QTableWidgetItem(quote));

            QString clientId = QString::number(jArr.at(i)->getClientId());
            ui->jobTbl_2->setItem(j, 4, new QTableWidgetItem(clientId));

            QString clientName = QString::fromStdString(jArr.at(i)->getClientName());
            ui->jobTbl_2->setItem(j, 5, new QTableWidgetItem(clientName));

            QString vId = QString::number(jArr.at(i)->getVId());
            ui->jobTbl_2->setItem(j, 6, new QTableWidgetItem(vId));

            QString vName = QString::fromStdString(jArr.at(i)->getVName());
            ui->jobTbl_2->setItem(j, 7, new QTableWidgetItem(vName));

            vector<CarPart*> detailsTemp = jArr.at(i)->getDetails();
            string strTemp;
            if(jArr.at(i)->getType() != "Decal" || jArr.at(j)->getType() != "Other" ){
                for(int k = 0; k < (int)detailsTemp.size(); k++){
                    strTemp += "Part: " + detailsTemp.at(k)->getName() + " Prexisting Damage: " + to_string(detailsTemp.at(k)->getDamage()) + ".\n";
                }
            }
            QString details = QString::fromStdString(strTemp);
            ui->jobTbl_2->setItem(j, 10, new QTableWidgetItem(details));

            QString cost = QString::number(jArr.at(i)->getActualCost());
            ui->jobTbl_2->setItem(j, 9, new QTableWidgetItem(cost));

            QString tools = QString::fromStdString(jArr.at(i)->getTools());
            ui->jobTbl_2->setItem(j, 11, new QTableWidgetItem(tools));
            j++;
        }
    }
}

//sets up the edit Jpb page
void UI::setupJobPage(){
    details = jArr.at(jChoice)->getDetails();
    ui->pageStack->setCurrentIndex(8);
    ui->updatePageStack->setCurrentIndex(3);
    ui->idLbl_2->setText(QString::fromStdString("ID: " + to_string(jArr.at(jChoice)->getId())));
    ui->updateJobTbl->setColumnWidth(0, 60);
    ui->updateJobTbl->setColumnWidth(1, 210);
    ui->updateJobTbl->setColumnWidth(2, 235);
    ui->updateJobTbl->setColumnWidth(3, 185);
    ui->updateJobTbl->setColumnWidth(4, 110);
    ui->updateJobTbl->setColumnWidth(5, 145);
    ui->updateJobTbl->setColumnWidth(6, 110);
    ui->updateJobTbl->setColumnWidth(7, 235);
    ui->updateJobTbl->setColumnWidth(8, 85);
    ui->updateJobTbl->setColumnWidth(9, 95);
    ui->toolsTbl->setColumnWidth(0, 250);
    ui->toolsTbl->setColumnWidth(1, 300);
    ui->toolsTbl->setColumnWidth(2, 300);
    ui->carPartsTbl->setColumnWidth(0, 250);
    ui->carPartsTbl->setColumnWidth(1, 300);
    ui->carPartsTbl->setColumnWidth(2, 300);

    QString id = QString::number(jArr.at(jChoice)->getId());
    QTableWidgetItem *newItem = new QTableWidgetItem(id);
    newItem->setFlags(newItem->flags() & ~Qt::ItemIsEditable);
    ui->updateJobTbl->setItem(0, 0, newItem);

    QString empId = QString::number(jArr.at(jChoice)->getEmpId());
    ui->updateJobTbl->setItem(0, 1, new QTableWidgetItem(empId));

    QString empName = QString::fromStdString(jArr.at(jChoice)->getEmpName());
    ui->updateJobTbl->setItem(0, 2, new QTableWidgetItem(empName));

    QString type = QString::fromStdString(jArr.at(jChoice)->getType());
    ui->updateJobTbl->setItem(0, 3, new QTableWidgetItem(type));

    QString clientId = QString::number(jArr.at(jChoice)->getClientId());
    ui->updateJobTbl->setItem(0, 4, new QTableWidgetItem(clientId));

    QString clientName = QString::fromStdString(jArr.at(jChoice)->getClientName());
    ui->updateJobTbl->setItem(0, 5, new QTableWidgetItem(clientName));

    QString vId = QString::number(jArr.at(jChoice)->getVId());
    ui->updateJobTbl->setItem(0, 6, new QTableWidgetItem(vId));

    QString vName = QString::fromStdString(jArr.at(jChoice)->getVName());
    ui->updateJobTbl->setItem(0, 7, new QTableWidgetItem(vName));

    QString quote = QString::number(jArr.at(jChoice)->getQuote());
    ui->updateJobTbl->setItem(0, 8, new QTableWidgetItem(quote));

    QString cost = QString::number(jArr.at(jChoice)->getActualCost());
    ui->updateJobTbl->setItem(0, 9, new QTableWidgetItem(cost));

    if(jArr.at(jChoice)->getProgress() == "Not Started"){
        ui->progressBox->setCurrentIndex(0);
    }else if(jArr.at(jChoice)->getProgress() == "In Progress"){
        ui->progressBox->setCurrentIndex(1);
    }else if(jArr.at(jChoice)->getProgress() == "Finished"){
        ui->progressBox->setCurrentIndex(2);
    }

    if(jArr.at(jChoice)->getPaid() == "Not Paid"){
        ui->paidBox->setCurrentIndex(0);
    }else if(jArr.at(jChoice)->getProgress() == "Paid"){
        ui->paidBox->setCurrentIndex(1);
    }

    toolArr = getTools(jArr.at(jChoice)->getTools());

    ui->toolsTbl->setRowCount(0);

    for(int i = 0; i < (int)toolArr.size(); i++){
        ui->toolsTbl->insertRow(i);
        for(int j = 0; j < (int)aArr.size(); j++){
            if(toolArr.at(i) == aArr.at(j)->getId()){
                QString tId = QString::number(aArr.at(j)->getId());
                QTableWidgetItem *newItem = new QTableWidgetItem(tId);
                newItem->setFlags(newItem->flags() & ~Qt::ItemIsEditable);
                ui->toolsTbl->setItem(i, 0, newItem);

                QString tName = QString::fromStdString(aArr.at(j)->getObjectName());
                QTableWidgetItem *newItem2 = new QTableWidgetItem(tName);
                newItem2->setFlags(newItem2->flags() & ~Qt::ItemIsEditable);
                ui->toolsTbl->setItem(i, 1, newItem2);

                QString tUsed = QString::number(aArr.at(j)->getUsed());
                ui->toolsTbl->setItem(i, 2, new QTableWidgetItem(tUsed));
            }
        }
    }
    ui->carPartsTbl->setRowCount(0);
    if(jArr.at(jChoice)->getType() != "Decal" && jArr.at(jChoice)->getType() != "Other"){
        int j = 0;
        for(int i = 0; i < (int)details.size(); i++){
            if(details.at(i)->getUsed()){
                ui->carPartsTbl->insertRow(j);

                QString part = QString::fromStdString(details.at(i)->getName());
                QTableWidgetItem *newItem = new QTableWidgetItem(part);
                newItem->setFlags(newItem->flags() & ~Qt::ItemIsEditable);
                ui->carPartsTbl->setItem(j, 0, newItem);

                QString damage = QString::fromStdString(to_string(details.at(i)->getDamage()));
                ui->carPartsTbl->setItem(j, 1, new QTableWidgetItem(damage));
                j++;
            }
        }
    }

    fillEditJobBoxes();

}

//sets up the edit vehicle page
void UI::setupVehiclePage(){
    ui->updatePageStack->setCurrentIndex(1);
    ui->pageStack->setCurrentIndex(8);
    string ownerName;
    for(int j = 0; j < (int)cArr.size(); j++){
        if(cArr.at(j)->getId() == vArr.at(vChoice)->getOwnerId()){
            ownerName = cArr.at(j)->getFirst() + " " + cArr.at(j)->getLast();
            cChoice = j;
        }
    }
    ui->idLbl_2->setText(QString::fromStdString("ID: " + to_string(vArr.at(vChoice)->getId()) + " Client Id: " + to_string(vArr.at(vChoice)->getOwnerId()) + " Client Name: " + ownerName));
    ui->makeTxt_2->setCurrentIndex(0);
    ui->makeTxt_2->setCurrentText(QString::fromStdString(vArr.at(vChoice)->getMake()));
    ui->modelTxt_2->setCurrentIndex(0);
    ui->modelTxt_2->setCurrentText(QString::fromStdString(vArr.at(vChoice)->getModel()));
    ui->origColorTxt_2->setCurrentIndex(0);
    ui->origColorTxt_2->setCurrentText(QString::fromStdString(vArr.at(vChoice)->getColor()));
    ui->numDoorsTxt_2->setCurrentIndex(0);
    ui->numDoorsTxt_2->setCurrentText(QString::fromStdString(vArr.at(vChoice)->getNumDoors()));
    ui->yearTxt_2->setText(QString::fromStdString(vArr.at(vChoice)->getYear()));
}

//sets up the edit asset page
void UI::setupAssetPage(){
    ui->pageStack->setCurrentIndex(8);
    ui->updatePageStack->setCurrentIndex(2);
    if(aArr.at(aChoice)->getWrap() == 0){
        ui->assetStack_2->setCurrentIndex(1);
        ui->nameTxt_4->setText(QString::fromStdString(aArr.at(aChoice)->getObjectName()));
        ui->dateTxt_4->setText(QString::fromStdString(aArr.at(aChoice)->getDate()));
        ui->priceTxt_4->setText(QString::number(aArr.at(aChoice)->getPrice()));
    }else{
        ui->assetStack_2->setCurrentIndex(2);
        ui->nameTxt_5->setText(QString::fromStdString(aArr.at(aChoice)->getObjectName()));
        ui->dateTxt_5->setText(QString::fromStdString(aArr.at(aChoice)->getDate()));
        ui->priceTxt_5->setText(QString::number(aArr.at(aChoice)->getPrice()));
        ui->amntTxt_4->setText(QString::number(aArr.at(aChoice)->getBought()));
        ui->colourTxt_4->setText(QString::fromStdString(aArr.at(aChoice)->getColour()));
    }

}

//when a job within the edit client page is selected
void UI::on_jobTbl_2_cellDoubleClicked(int row, int column){
    for(int i = 0; i < (int)jArr.size(); i++){
        if(ui->jobTbl_2->item(row, 0)->text().toInt() == jArr.at(i)->getId()){
            jChoice = i;
        }
    }
    setupJobPage();
}

//when a vehicle within the edit client page is selected
void UI::on_vehicleTbl_2_cellDoubleClicked(int row, int column){
    for(int i = 0; i < (int)vArr.size(); i++){
        if(ui->vehicleTbl_2->item(row, 0)->text().toInt() == vArr.at(i)->getId()){
            vChoice = i;
        }
    }
    setupVehiclePage();
}

//when the print receipt button is selected and all the jobs which the user has already been paid for are displayed
void UI::on_printBtn_clicked(){
    ui->pageStack->setCurrentIndex(12);
    int numPaid = 0;
    ui->jobTbl_3->setRowCount(0);
    for(int i = 0; i < (int)jArr.size(); i++){
        if(jArr.at(i)->getPaid() == "Paid"){
            numPaid++;
            ui->jobTbl_3->insertRow(i);

            QString id = QString::number(jArr.at(i)->getId());
            ui->jobTbl_3->setItem(i, 0, new QTableWidgetItem(id));

            QString empId = QString::number(jArr.at(i)->getEmpId());
            ui->jobTbl_3->setItem(i, 1, new QTableWidgetItem(empId));

            QString empName = QString::fromStdString(jArr.at(i)->getEmpName());
            ui->jobTbl_3->setItem(i, 2, new QTableWidgetItem(empName));

            QString type = QString::fromStdString(jArr.at(i)->getType());
            ui->jobTbl_3->setItem(i, 3, new QTableWidgetItem(type));

            QString quote = QString::number(jArr.at(i)->getQuote());
            ui->jobTbl_3->setItem(i, 8, new QTableWidgetItem(quote));

            QString clientId = QString::number(jArr.at(i)->getClientId());
            ui->jobTbl_3->setItem(i, 4, new QTableWidgetItem(clientId));

            QString clientName = QString::fromStdString(jArr.at(i)->getClientName());
            ui->jobTbl_3->setItem(i, 5, new QTableWidgetItem(clientName));

            QString vId = QString::number(jArr.at(i)->getVId());
            ui->jobTbl_3->setItem(i, 6, new QTableWidgetItem(vId));

            QString vName = QString::fromStdString(jArr.at(i)->getVName());
            ui->jobTbl_3->setItem(i, 7, new QTableWidgetItem(vName));

            QString cost = QString::number(jArr.at(i)->getActualCost());
            ui->jobTbl_3->setItem(i, 9, new QTableWidgetItem(cost));

            QString tools = QString::fromStdString(jArr.at(i)->getTools());
            ui->jobTbl_3->setItem(i, 10, new QTableWidgetItem(tools));

            QString progress = QString::fromStdString(jArr.at(i)->getProgress());
            ui->jobTbl_3->setItem(i, 11, new QTableWidgetItem(progress));

            QString paid = QString::fromStdString(jArr.at(i)->getPaid());
            ui->jobTbl_3->setItem(i, 12, new QTableWidgetItem(paid));
        }
    }
}

//when a job is selected to have a recipt printed for it, it creates a recipt and saves it in the file directory to be printed
//TODO: this is a temporary function, a new library is to be learned so that a nice clean PDF receipt will be saved instead
void UI::on_jobTbl_3_cellDoubleClicked(int row, int column){
    ui->pageStack->setCurrentIndex(13);
    for(int i = 0; i < (int)jArr.size(); i++){
        if(jArr.at(i)->getId() == ui->jobTbl_3->item(row, 0)->text().toInt()){
            jChoice = i;
        }
    }
    toolArr = getTools(jArr.at(jChoice)->getTools());
    string wrapUsed = "";
    for(int i = 0; i < (int)toolArr.size(); i++){
        for(int j = 0; j < (int)aArr.size(); j++){
            if(toolArr.at(i) == aArr.at(j)->getId() && i == 0){
                wrapUsed += aArr.at(j)->getColour() + " " + aArr.at(j)->getObjectName();
            }else if(toolArr.at(i) == aArr.at(j)->getId()){
                wrapUsed += " and " + aArr.at(j)->getColour() + " " + aArr.at(j)->getObjectName();
            }
        }
    }


    string receipt = "";
    receipt += "\t\t\t\t Lot 6 Wraps\n\t\tAddress: 176 Hilltop Drive, Ayr, Ontario, Canada N0B1E0\n\t\t\tPhone: 519-589-5011\nJob Id No: " + to_string(jArr.at(jChoice)->getId()) + "\n" +
              "Customer Name: " + jArr.at(jChoice)->getClientName() + "\n" +
              "-------------------------------------------------------------\n" +
              jArr.at(jChoice)->getType() + " wrap using " + wrapUsed + "\tCost: " + to_string(jArr.at(jChoice)->getActualCost()) + " \n" +
              "Paid by: E-Transfer";
    ui->reviewTxt->setText(QString::fromStdString(receipt));
    ofstream newFile("Receipt.txt");
    if(newFile.is_open()){
        newFile << receipt;
        newFile.close();
        cout << "can open file" << endl;
    }


}
