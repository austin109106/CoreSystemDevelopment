#include "WaitingList.h"

WaitingList::WaitingList() {
}

void WaitingList::displayWL() const {
    if (waitinglist.empty()) {
        cout<<"The waitlist is currently empty.\n\n";
    } else {
        for (auto it = waitinglist.begin(); it!=waitinglist.end(); ++it) {
            queue<Entry> temp = it->second;
            while (!temp.empty()) {
                Entry e = temp.front();
                cout<<"Student ID: "<<e.studentID<<"\nStudent Name: "<<e.name<<"\nResource ID: "<<e.resourceID<<endl<<endl;
                temp.pop();
            }
        }
    }
}

void WaitingList::addtoWL(int SID, string n, int RID, int date) {
    Entry e = {SID, n, RID};
    waitinglist[make_pair(RID, date)].push(e);
}

WaitingList::Entry WaitingList::removefromWL(int resourceID, int date) {
    pair<int,int> key = make_pair(resourceID, date);
    queue<Entry>& q = waitinglist[key];
    Entry e = q.front();
    q.pop();
    if (q.empty()) {
        waitinglist.erase(key);
    }
    
    return e;
}

bool WaitingList::isEmpty(int resourceID, int date) {
    auto it = waitinglist.find(make_pair(resourceID, date));
    return it == waitinglist.end() || it->second.empty();
}
