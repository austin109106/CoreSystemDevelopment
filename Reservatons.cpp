#include "Reservations.h"
#include <sstream>
#include<iomanip>

Reservations::Reservations(){
    resNumber = 0;
    studentID = 0;
    name = " ";
    resourceNumber = 0;
    day = 1;
    month = 1;
    year = 2026;
};

Reservations::Reservations(int rNumber, int SID, string name, int resourceNum, int d, int m, int y){
    resNumber = rNumber;
    studentID = SID;
    this->name = name;
    resourceNumber = resourceNum;
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
int Reservations::getReservationNumber() const { return resNumber; }
int Reservations::getStudentID() const { return studentID; }
string Reservations::getName() const { return name;}
int Reservations::getResourceNumber() const { return resourceNumber; }
int Reservations::getDay() const { return day; }
int Reservations::getMonth() const { return month; }
int Reservations::getYear() const { return year; }

string Reservations::getDate(){
    ostringstream oss;
    oss << setfill('0') << setw(2) << month << '/' << setw(2) << day << '/' << year;
    return oss.str();
} //returns 09/15/2026


bool Reservations::operator==(const Reservations& other) const {
    return this->resNumber == other.resNumber;
}
        
bool Reservations::operator>(const Reservations& other) const{
    return this->resNumber > other.resNumber;
}

bool Reservations::operator<(const Reservations& other) const{
    return this->resNumber < other.resNumber;
}

ostream& operator<<(ostream& out, const Reservations& r){
    out << r.resNumber << "|" << r.studentID << "|" << r.name << "|R" << r.resourceNumber << "|" << setfill('0') << setw(2) << r.month << "/" << setw(2) << r.day << "/" << r.year << setfill(' ');
//setw(2)/setfill('0') is for single digit days of the month, I.E "09/21/2001" instead of "9/21/2001"
    return out;
}

istream& operator>>(istream& in, Reservations r){
    string res;
    if(!getline(in, line)){
        return in;
    }
    if(line.empty()){
        in.setstate(ios::failbit);
        return in;
    }//error handling

    stringstream ss(line);
    string rStr, sidStr, resStr, dateStr;

    getline(ss, rStr, '|');
    getline(ss, sidStr, '|');
    getline(ss, r.name, '|');
    getline(ss, resStr, '|');
    getline(ss, dateStr);
    //disects reservation

    r.resNumber = stoi(rStr); //stoi = string to int
    r.studentID = stoi (sidStr);
    r.resourceNumber = stoi(resStr.substr(1));//grebs resNumber without the R
    
    stringstream ds(dateStr);
    string monthStr, dayStr, yearStr;
    getline(ds, monthStr, '/');
    getline(ds, dayStr, '/');
    getline(ds, yearStr);

    r.month = stoi(monthStr);
    r.day = stoi(dayStr);
    r.year = stoi(yearStr);

    return in;
}


void Reservations::display() const {
    cout << "|" << resNumber << "|" << studentID << "|" << name << "|R" << resourceNumber << "|" << getDate() << "|";
}

