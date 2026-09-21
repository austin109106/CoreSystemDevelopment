#pragma once
#ifndef RESERVATIONSLIST_H
#define RESERVATIONSLIST_H

#include "Reservations.h"

class ReservationsList {
private:
    struct Node {
        Reservations data;
        Node* next;

        Node (const Reservations& r) : data(r), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    ReservationsList();
    ~ReservationsList();    //dynamic value needs to be deleted

    ReservationsList(const ReservationsList&) = delete; // ensures no doubleing
    ReservationsList& operator=(const ReservationsList&) = delete;
    
    
    void add(const Reservations& r); 
    bool loadFromFile(const string& filename);
    void display() const;
    void printEarliest() const;
    int size() const;
    void clear();

};

#endif //RESERVATIONSLIST