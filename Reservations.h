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
        int getReservationNumber() const;
        int getStudentID() const;
        string getName() const;
        int getResourceNumber() const;
        int getDay() const;
        int getMonth() const;
        int getYear() const;
        string getDate() const; //returns 09/15/2026


        //operator overloads
        bool operator==(const Reservations& other) const;

        bool operator>(const Reservations& other) const;
        bool operator<(const Reservations& other) const;

        friend ostream& operator<<(ostream& out, const Reservations& r);
        friend istream& operator>>(istream& in, Reservations r);

        //print
        void display() const; //obsoliet

};


#endif //RESERVATIONS_H