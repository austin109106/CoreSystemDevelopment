//waitlist class for specfic function when choice==2,choice==3,choice==4,and choice==5
#ifndef WAITING_LIST
#define WAITING_LIST

#include <queue>
#include <map>
#include <string>
#include <iostream>

using namespace std;

class WaitingList{
    public:
        WaitingList();
        
        struct Entry {
            int studentID;
            string name;
            int resourceID;
        };
        
        void displayWL() const;
        
        void addtoWL(int SID, string n, int RID, int date);
        
        Entry removefromWL(int resourceID, int date);
        
        bool isEmpty(int resourceID, int date);
        
    private:
        //map and queue for waiting list
        map<pair<int, int>, queue<Entry>> waitinglist;
        
    
};
#endif
