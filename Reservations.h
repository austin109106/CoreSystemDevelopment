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
        string name; //name of customer 

    // |res number |student number |name |resource number |date |
    public:
        //constructors
        Reservations(); //constructor (o(1))
        Reservations(int rNumber, int SID, string name, int recNumber, int d, int m, int y);//loaded constructor (O(1))

        //setters
        void setReservationNumber(int rNumber);//sets Reservation number (O(1))
        void setStudentID(int SID);//sets Student ID (O(1))
        void setName(string name);//sets Name (O(1))
        void setResourceNumber(int rNum);//set resource number (O(1))
        void setDate(int d, int m, int y);//sets the date (O(1))

        //getters
        int getReservationNumber() const;//Returns Reservations (O(1))
        int getStudentID() const;//returns StudentID
        string getName() const;//returns Name
        int getResourceNumber() const;//returns resource number
        int getDay() const;//returns day on reservations
        int getMonth() const;//returns month on reservation
        int getYear() const;//returns year on reservation
        string getDate() const; //returns date as 09/15/2026


        //operator overloads
        bool operator==(const Reservations& other) const;//overloads the == operand

        bool operator>(const Reservations& other) const;//overloads the > operand
        bool operator<(const Reservations& other) const;//overloads the < operand, when comparing Reservations it will compare by their Reservation number

        friend ostream& operator<<(ostream& out, const Reservations& r);//how to print a Reservation
        friend istream& operator>>(istream& in, Reservations& r);//how to read a Reservation

        //print
        void display() const; //obsoliet cant be printed normally now

};


#endif //RESERVATIONS_H
