#include "ReservationsList.h"
#include <fstream>

ReservationsList::ReservationsList() : head(nullptr), tail(nullptr), count(0) {}

ReservationsList::~ReservationsList(){
    clear();
}//dynamic value needs to be deleted

//Seach by Resouce Number
const Reservations* ReservationsList::searchbyRes(int resNumber) const {
    for(Node* cur = head; cur != nullptr; cur = cur->next){
        if(cur->data.getReservationNumber() == resNumber){
            return &cur->data;
        }
    }
    return nullptr;
} //nullptr if not found

//Search by Student ID
vector<Reservations> ReservationsList::searchbySID(int SID) const {
    vector<Reservations> r;
    for(Node* cur = head; cur != nullptr; cur = cur->next){
        if(cur->data.getStudentID() == SID){
            r.push_back(cur->data);
        }
    }
    return r;
}

int ReservationsList::countForResource(int resourceNum) const {
    int total = 0;
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data.getResourceNumber() == resourceNum) {
            total++;
        }
    }
    return total;
}


bool ReservationsList::cancel(int resNumber){
    Node* prev = nullptr;
    Node* cur = head;

    while(cur != nullptr){
        if(cur->data.getReservationNumber() == resNumber){
            if(prev == nullptr){ //kills the head
                head = cur->next;
            } else prev->next = cur->next;

            if(cur == tail){ //kills tail
                tail = prev;
            }
            delete cur;
            count--;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
} //false if not found

void ReservationsList::add(const Reservations& r) {
    Node* n = new Node(r);
    if (head == nullptr) {
        head = tail = n;
    } else {
        tail-> next = n;
        tail = n;
    }
    count++;
}

bool ReservationsList::loadFromFile(const string& filename){
    ifstream in(filename);
    if (!in){
        return false;
    }

    Reservations r;
    while (in >> r){
        add(r);
    }
    return true;
}

void ReservationsList::display() const{
    for(Node* cur = head; cur != nullptr; cur = cur->next){
        cout << cur->data  << endl; 
    }
}

void ReservationsList::printEarliest() const {
    if(head == nullptr){
        cout << "List is empty." << endl;
        return;
    }

    Node* earliest = head;
    for(Node* cur = head->next; cur != nullptr; cur = cur->next){
        const Reservations& a = cur->data;
        const Reservations& b = earliest->data;

        bool earlier = (a.getYear() < b.getYear()) ||(a.getYear() == b.getYear() && a.getMonth() < b.getMonth()) ||(a.getYear() == b.getYear() && a.getMonth() == b.getMonth() && a.getDay() < b.getDay());
        //finds earliest node

        if(earlier) { earliest = cur; }
    }

    cout << earliest->data << endl;
}

int ReservationsList::size() const{
    return count;
}

void ReservationsList::clear(){
    while (head != nullptr) {
        Node* next = head->next;
        delete head;
        head = next;
    }
    tail = nullptr;
    count = 0;
}
