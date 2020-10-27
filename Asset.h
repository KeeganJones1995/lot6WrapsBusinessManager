/*Lot 6 Wrap's Business Manager
 * Made for: Zachary Fronchack
 * Made By: Keegan Jones
 * File: Asset.h
 * Purpose: Header file for Asset objects
 */
#ifndef ASSET_H
#define ASSET_H

#include <string>
#include "Thing.h"

using std::string;

class Asset: public Thing{
    public:
        Asset(int, string, double, string, int, string, double, double);
        int getId();
        string getObjectName();
        double getPrice();
        string getDate();
        int getWrap();
        string getColour();
        double getUsed();
        double getBought();
        void setWrap(int);
        void setId(int);
        void setObjectName(string);
        void setPrice(double);
        void setDate(string);
        void setUsed(double);
        void setBought(double);
    private:
        string objectName;
        double price;
        string date;
        int wrap;//1 for if its a wrap, 0 if its a tool
        string colour;
        double used;
        double bought;
};

#endif // ASSET_H
