#include "Resource.h"
#include "Reservations.h"
#include "ReservationsList.h"
#include "WaitingList.h"

#include <stack>
#include <queue>
#include <cstdlib>

using namespace std;

//Puts date together as a code
int date(int d, int m, int y) {
    return (y*10000)+(m*100)+d;
}

//Checks if ResourceNum matches with Date
bool isReserved(const ReservationsList& r1, int resourceNum, int d, int m, int y) {
    vector<Reservations> all = r1.getAll();
    for (size_t i = 0; i < all.size(); i++) {
        if (all[i].getResourceNumber() == resourceNum && all[i].getDay() == d&& all[i].getMonth() == m && all[i].getYear() == y) {
            return true;
        }
    }
    return false;
}

void printMostPopular(const ReservationsList& reservations, const ResourceManager& manager) { // gets the most popular resource use
    const vector<Resource>& all = manager.getAllResources();

    int bestIndex = -1;
    int bestCount = 0;

    for (size_t i = 0; i < all.size(); ++i) {
        int c = reservations.countForResource(all[i].getResourceNumber());
        if (c > bestCount) {
            bestCount = c;
            bestIndex = i;
        }
    }

    if (bestIndex == -1) {
        cout << "No reservations yet." << endl;
    } else {
        cout << "Most popular Resource: " << all[bestIndex].getName()
             << " (" << all[bestIndex].getId() << ") with "
             << bestCount << " reservations." << endl;
    }
}

//QUICKSORT FUNCTIONS
bool comesBefore(const Resource& a, const Resource& b, int fieldChoice) {
    if (fieldChoice==1) {
        return a.getName()<b.getName();
    } else if (fieldChoice==2) {
        return a.getType()<b.getType();
    } else if (fieldChoice==3) {
        return a.isAvailable()<b.isAvailable();
    } else if (fieldChoice==4) {
        return a.getResourceNumber()<b.getResourceNumber();
    } else {
        cout<<"Not a valid number.\n";
        return false;
    }
}

int partition(vector<Resource>& v, int low, int high, int fieldChoice) {
    Resource pivot = v[high];
    int i = low-1;
    for (int j=low; j<high; j++) {
        if (comesBefore(v[j], pivot, fieldChoice)) {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i+1], v[high]);
    return i + 1;
}

void quickSort(vector<Resource>& v, int low, int high, int fieldChoice) {
    if (low>=high) {
        return;
    } else {
        int pivotIndex = partition(v, low, high, fieldChoice);
        quickSort(v, low, pivotIndex-1, fieldChoice);
        quickSort(v, pivotIndex+1, high, fieldChoice);
    }
}

int main() {
  
  ResourceManager rm;
  ReservationsList rl;
  WaitingList wl;
  stack<Reservations> cancelHis;

  rl.loadFromFile("reservations.txt");
  rm.loadFromFile("resources.txt");
  

  
  int choice=0;
  int nextResNumber=321; //for counting incoming reservations

  while (choice!=9) {
    //Main User-Interface
    cout<<"===== Campus Resource Reservation System =====\n\n1. View Resources\n2. Create Reservation\n3. Cancel Reservation\n4. View Waiting Lists\n5. Undo Cancellation\n6. Search Reservations\n7. Sort Resources\n8. Generate Report\n9. Exit\n\nEnter Choice: ";
      cin>>choice;

    //VIEW RESOURCES
    if (choice==1) {
      rm.displayAllResources();
    }
    
    //CREATE RESERVATION
    else if (choice==2) {
      //Reservations(int rNumber, int SID, string name, int recNumber, int d, int m, int y);
      
      string resourceID;
      cout<<"\nEnter Resource ID: (include 'R')";
      cin>>resourceID;
      
      //test if resource number exists
      Resource* res = rm.findById(resourceID);
      if (res == nullptr) {
          cout<<"No resource found with Resource ID "<<resourceID<<endl;
      } else {
        int month,day,year;
        cout<<"Enter Date for Reservation (mm dd yyyy): ";
        cin>>month>>day>>year;

        int studentID;
        cout<<"Enter Student ID: ";
        cin>>studentID;  
        string name;
        cout<<"Enter Name: ";
        cin.ignore(); //to make sure incoming getline() works consistently
        getline(cin, name);

        int rNum = res->getResourceNumber();

        if (isReserved(rl,rNum,day,month,year)) {
            cout<<res->getName()<<" is already reserved on that date. You will be added to the waitlist.\n";
            wl.addtoWL(studentID,name,rNum,date(day,month,year));
        } else {
            Reservations newRes(nextResNumber,studentID,name,rNum,day,month,year);
            rl.add(newRes);
            cout<<"\nReservation created.\n";
            nextResNumber++;
        }
      }
    }
    
    //CANCEL RESERVATION
    else if (choice==3) {
      int reservationID;
      cout<<"\nCurrent Reservations:\n";
      rl.display();
      
      cout<<"\nEnter Reservation ID(should be the first number): ";
      cin>>reservationID;
      
      const Reservations* sRes = rl.searchbyRes(reservationID);
      
      if (sRes==nullptr) {
          cout<<"Reservation Not Found.\n";
      } else {
          int freeResNum = sRes->getResourceNumber();
          int fRNDay = sRes->getDay();
          int fRNMonth = sRes->getMonth();
          int fRNYear = sRes->getYear();
          cancelHis.push(*sRes);
          rl.cancel(reservationID);
          cout<<"Reservation has been cancelled.\n";
          
          int dateNum = date(fRNDay, fRNMonth, fRNYear);
          if (!wl.isEmpty(freeResNum,dateNum)) {
            //   pop them and auto create their reservation
            WaitingList::Entry e = wl.removefromWL(freeResNum, dateNum);
            Reservations WLr = Reservations(nextResNumber, e.studentID, e.name, freeResNum, fRNDay, fRNMonth, fRNYear);
            rl.add(WLr);
            nextResNumber++;
            cout<<"Waitlisted Reservation moved up to cancelled Reservation's date.\n";
        }   
      }   
    }
    
    //VIEW WAITING LISTS
    else if (choice==4) {
        wl.displayWL();
    }
    
    //UNDO CANCELLATION
    else if (choice==5) {
      if (cancelHis.empty()) {
          cout<<"No cancellations to undo.\n";
      } else {
          Reservations restoreRes = cancelHis.top();
          cancelHis.pop();

          int rNum = restoreRes.getResourceNumber();
          int d = restoreRes.getDay();
          int m = restoreRes.getMonth();
          int y = restoreRes.getYear();

          if (!isReserved(rl,rNum,d,m,y)) { 
              rl.add(restoreRes);
              cout<<"Reservation "<<restoreRes<<" has been added back.\n";
          } else {
              //call waiting list add to wl back of queue
              wl.addtoWL(restoreRes.getStudentID(), restoreRes.getName(), rNum, date(d,m,y));
              cout<<"Resource is unavilable at that time. You've been added to the waiting list.\n";
          }
      }
    }

    //SEARCH RESERVATIONS
    else if (choice==6) {
      int x;
      cout<<"How to search? (1 for by Reservation ID, 2 for by Student ID) ";
      cin>>x;
      if (x==1) {
          int s1;
          cout<<"Enter Reservation Number: ";
          cin>>s1;
          const Reservations* result = rl.searchbyRes(s1);
          if (result==nullptr) {
              cout<<"This reservation does not exist.\n";
          } else {
              cout<<"Found! Here it is:\n"<<*result<<endl;
          }
      } else if (x==2) {
          int s2;
          cout<<"Enter Student ID: ";
          cin>>s2;
          vector<Reservations> results = rl.searchbySID(s2);
          if (results.empty()) {
              cout<<"This student's reservations cannot be found.\n";
          } else {
              cout<<"Found! Here it is:\n";
              for (int i = 0; i<results.size(); i++) {
                cout<<results.at(i)<<endl;  
              }
          }
      } else {
          cout<<"Not a valid number.\n";
      }
    }

    //SORT RESOURCES
    else if (choice==7) {
      vector<Resource> toSort = rm.getAllResources();
      cout<<"\nHow do you want to sort:\n1) By Name\n2) By Type\n3) By Availability\n4) By ResourceID\n\nEnter Here: ";
      int y;
      cin>>y;
      
      if (y!=1&&y!=2&&y!=3&&y!=4) {
          cout<<"Not a valid choice.\n";
      } else {
          quickSort(toSort, 0, toSort.size() -1, y);
          for (int i = 0; i < toSort.size(); i++) {
              toSort.at(i).display();
              
          }
      }
    }

    //GENERATE REPORT
    else if (choice==8) {
        /*Most frequently reserved resources
        Current availability
        Number of active reservations
        Waiting list reports*/
        printMostPopular(rl, rm);
        cout << "\nCurrent availability:" << endl;
        rm.displayAvailableResources();
        cout << "Number of active reservations: " << rl.size() << endl;
        cout << "\nWaiting List Report:" << endl;
        wl.displayWL();
    }

  }

cout<<"Exited Program.\n";
  return 0;
}
