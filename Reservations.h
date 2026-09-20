#pragma once
#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include <iostream>
#include <string>

using namespace std;

class Reservations {
    private:
        //variables
        int resNumber, studentID, resourceNumber, day, month, year;
        string name;

    // |res number |student number |name |resource number |date |
    public:
        //constructors
        Reservations();
        Reservations(int rNumber, int SID, string name, int recNumber, int d, int m, int y);

        //setters
        void setReservationNumber(int rNumber);
        void setStudentID(int SID);
        void setName(string name);
        void setResourceNumber(int rNum);
        void setDate(int d, int m, int y);

        //getters
        int getReservationNumber();
        int getStudentID();
        string getName();
        int getResourceNumber();
        string getDate(); //returns 09/15/2026


        //operator overloads
        bool operator==(const Reservations& other) const;

        bool operator>(const Reservations& other) const;
        bool operator<(const Reservations& other) const;

        //print
        void display() const;

};


#endif //RESERVATIONS_H