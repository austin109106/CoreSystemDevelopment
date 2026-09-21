#pragma once
#ifndef RESERVATIONSLIST_H
#define RESERVATIONSLIST_H

#include "Reservations.h"

#include <vector>

class ReservationsList {
private:
    struct Node {
        Reservations data;
        Node* next;

        Node (const Reservations& r) : data(r), next(nullptr) {}
    };//node for navigating the list

    Node* head;
    Node* tail;
    int count;

public:
    ReservationsList();//defualt constructor
    ~ReservationsList();    //dynamic value needs to be deleted

    ReservationsList(const ReservationsList&) = delete; // ensures no doubleing
    ReservationsList& operator=(const ReservationsList&) = delete;
    
    const Reservations* searchbyRes(int resNumber) const; //nullptr if not found

    vector<Reservations> searchbySID(int SID) const; //searches the list by StudentID

    int countForResource(int resNumber) const;

    bool cancel(int resNumber); //false if not found and cancel
    
    void add(const Reservations& r); //add a reservation to the list

    bool loadFromFile(const string& filename);//loads the reservations from a file
    
    void display() const;//displays the reservations list
    
    void printEarliest() const;//prints the earliest (wow who woulda thought)
    
    int size() const;// returns the size of the list
    
    void clear();//clear the list and deletes the dynamic values

};

#endif //RESERVATIONSLIST
