#include "Reservations.h"

Reservations::Reservations(){
    resNumber = 0;
    studentID = 0;
    name = " ";
    resourceNumber = 0;
    day = 1;
    month = 1;
    year = 2026;
};

Reservations::Reservations(int rNumber, int SID, string name, int resNumber, int d, int m, int y){
    resNumber = rNumber;
    studentID = SID;
    this->name = name;
    resourceNumber = resNumber;
    day = d;
    month = m;
    year = y;
};

//setters
void Reservations::setReservationNumber(int rNumber){ resNumber = rNumber; }
void Reservations::setStudentID(int SID){ studentID = SID; }
void Reservations::setName(string name){ this->name = name; }
void Reservations::setResourceNumber(int rNum){resourceNumber = rNum;}

void Reservations::setDate(int d, int m, int y){ 
    day = d;
    month = m;
    year = y;
}

//getters
int Reservations::getReservationNumber(){ return resNumber; }
int Reservations::getStudentID(){ return studentID; }
string Reservations::getName(){ return name;}
int Reservations::getResourceNumber(){ return resourceNumber; }

string Reservations::getDate(){
    string date = to_string(day) + '/' + to_string(month) + '/' + to_string(year);
    return date;
} //returns 09/15/2026


bool Reservations::operator==(const Reservations& other) const {
    return this->resNumber == other.resNumber;
}
        
bool Reservations::operator>(const Reservations& other) const{
    return this->resNumber > other.resNumber;
}

bool Reservations::operator>(const Reservations& other) const{
    return this->resNumber < other.resNumber;
}

void Reservations::display() const {
    string d  = this->getDate();
    cout << "|" << resNumber << "|" << studentID << "|" << name << "|R" << resourceNumber << "|" << d << "|";
}

