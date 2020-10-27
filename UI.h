/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: UI.h
 * Purpose: Header file for UI object, which handles all of the user IO and event handlers
 */

#ifndef UI_H
#define UI_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "Control.h"
#include "DBManager.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class UI; }
QT_END_NAMESPACE

class UI : public QMainWindow
{
    Q_OBJECT

public:
    UI(QWidget *parent = nullptr);
    ~UI();

private slots:

    void on_quitBtn_triggered();
    void on_searchBtn_clicked();
    void on_loginBtn_clicked();
    void on_addBtn_clicked();
    void on_logoBtn_clicked();
    void on_pushButton_clicked();
    void on_nextBtn1_clicked();
    void on_nextBtn2_clicked();
    void on_vehicleBtn_clicked();
    void on_addVehicleBtn_clicked();
    void on_makeTxt_currentIndexChanged(int index);
    void on_modelTxt_currentIndexChanged(int index);
    void on_origColorTxt_currentIndexChanged(int index);
    void on_viewBtn_clicked();
    void on_jobTbl_cellDoubleClicked(int row, int column);
    void on_clientTbl_cellDoubleClicked(int row, int column);
    void on_vehicleTbl_cellDoubleClicked(int row, int column);
    void on_assetTbl_cellDoubleClicked(int row, int column);
    void on_dataBaseTabs_currentChanged(int index);
    void on_updateClientBtn_clicked();
    void on_backBtn_clicked();
    void on_addVehicleBtn_2_clicked();
    void on_addItemBtn_clicked();
    void on_assetChoiceBtn_clicked();
    void on_submitToolBtn_clicked();
    void on_submitWrapBtn_clicked();
    void on_submitOrderBtn_clicked();
    void on_updateToolBtn_clicked();
    void on_updateWrapBtn_clicked();
    void on_otherRdBtn_clicked();
    void on_fullRdBtn_clicked();
    void on_hoodRdBtn_clicked();
    void on_chromeRdBtn_clicked();
    void on_decalRdBtn_clicked();
    void on_partialRdBtn_clicked();
    void on_confirmPcsBtn_clicked();
    void on_addAssetJobBtn_clicked();
    void on_submitJobBtn_clicked();
    void on_confirmBtn_clicked();
    void on_addPartBtn_clicked();
    void on_addToolBtn_clicked();
    void on_confirmUpdateBtn_clicked();
    void on_resList_itemDoubleClicked(QListWidgetItem *item);
    void on_backBtn2_clicked();
    void on_jobTbl_2_cellDoubleClicked(int row, int column);
    void on_vehicleTbl_2_cellDoubleClicked(int row, int column);
    void on_printBtn_clicked();
    void on_jobTbl_3_cellDoubleClicked(int row, int column);

private:

    Ui::UI *ui;
    void initUI();
    string userName;
    Control* controller;
    void populateClientDropDown();
    void populateVehicleDropDown();
    void populateEmployeeDropDown();
    void populateVehicleChoices();
    int focus;
    vector<Client*> cArr;
    vector<Asset*> aArr;
    vector<Vehicle*> vArr;
    vector<Job*> jArr;
    vector<Staff*> sArr;
    vector<Client*> searchCArr;
    vector<Asset*> searchAArr;
    vector<Vehicle*> searchVArr;
    vector<Job*> searchJArr;
    vector<Staff*> searchSArr;
    int cChoice;
    int vChoice;
    int aChoice;
    int jChoice;
    int sChoice;
    vector<string> makes;
    vector<string> models;
    vector<string> colors;
    vector<Asset*> order;
    vector<int> toolArr;
    void updateAsset();
    vector<int> getTools(string);
    void setChkBoxes(bool);
    vector<CarPart*> details;
    void getChecked();
    string type;
    double quote();
    double getPercentage();
    void setRdBtns(bool);
    int getNumParts();
    bool partOf(Asset*);
    void fillEditJobBoxes();
    Asset* getAsset(QString);
    void setupClientPage();
    void setupJobPage();
    void setupVehiclePage();
    void setupAssetPage();
    void fillTables();
protected:

    void timerEvent(QTimerEvent *event);

};
#endif // UI_H
