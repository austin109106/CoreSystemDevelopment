#pragma once
#ifndef RESERVATIONSLIST_H
#define RESERVATIONSLIST_H

#include "Reservations.h"
#include <fstream>

class ReservationsList {
private:
    struct Node {
        Reservations data;
        Node* next;

        Node (int rNum, int sNum, string name, int recNum, int d, int m, int y) : data(rNum, sNum, name, recNum, d, m, y) , next(nullptr);
    };

    Node* head;
    Node* tail;

public:
    ReservationsList();
    ~ReservationsList();    //dynamic value needs to be deleted

    void append(int rNum, int sNum, string name, int recNum, int d, int m, int y); 
    bool loadFromFile(const string& filename);
    void display() const;
    void printEarliest() const;

};

#endif //RESERVATIONSLIST