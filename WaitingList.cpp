#include "WaitingList.h"

WaitingList::WaitingList() {
}

void WaitingList::displayWL() const {
    for (auto it = waitinglist.begin(); it!=waitinglist.end(); ++it) {
        queue<Entry> temp = it->second;
        while (!temp.empty()) {
            Entry e = temp.front();
            cout<<"Student ID: "<<e.studentID<<"\nStudent Name: "<<e.name<<"\nResource ID: "<<e.resourceID<<endl<<endl;
            temp.pop();
        }
    }
}

void WaitingList::addtoWL(int SID, string n, int RID) {
    Entry e = {SID, n, RID};
    waitinglist[RID].push(e);
}

WaitingList::Entry WaitingList::removefromWL(int resourceID) {
    queue<Entry>& q = waitinglist[resourceID];
    Entry e = q.front();
    q.pop();
    
    return e;
}

bool WaitingList::isEmpty(int resourceID) {
    auto it = waitinglist.find(resourceID);
    if (it ==waitinglist.end()) {
        return true;
    } else {
        return false;
    }
}
