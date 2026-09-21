//waitlist class for specfic function when choice==2,choice==3,choice==4,and choice==5
#ifndef WAITING_LIST
#define WAITING_LIST

#include <queue>
#include <map>
#include <string>

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
        
        void addtoWL(int SID, string n, int RID);
        
        Entry removefromWL(int resourceID);
        
        bool isEmpty(int resourceID);
        
    private:
        //queue for waiting list
        map<int, queue<Entry>> waitinglist;
        
    
};
#endif
