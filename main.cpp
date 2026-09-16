#include "Resource.h";
#include "Reservation.h";
#include <iostream>
#include <queue>
//#include <list>

#include <iostream>
using namespace std;

int main() {
  int choice=9;

  while (choice!=9) {
    //Main User-Interface
    cout<<"===== Campus Resource Reservation System =====\n\n
      1. View Resources\n
      2. Create Reservation\n
      3. Cancel Reservation\n
      4. View Waiting Lists\n
      5. Undo Cancellation\n
      6. Search Reservations\n
      7. Sort Resources\n
      8. Generate Report\n
      9. Exit\n\n
      Enter Choice: ";
      cin>>choice;

    //VIEW RESOURCES
    if (choice==1) {

    }
    
    //CREATE RESERVATION
    else if (choice==2) {

    }
    
    //CANCEL RESERVATION
    else if (choice==3) {

    }
    
    //VIEW WAITING LISTS
    else if (choice==4) {

    }
    
    //UNDO CACELLATION
    else if (choice==5) {

    }

    //SEARCH RESERVATIONS
    else if (choice==6) {

    }

    //SORT RESOURCES
    else if (choice==7) {

    }

    //GENERATE REPORT
    else if (choice==8) {

    }

  }
cout<<"Exited Program.\n";
  return 0;
}
