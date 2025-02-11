//This work was done by the young developer Rayen Abid grp A
//AI was used as a tool to solve some issues not to do all the work

#include <iostream>
#include <string>
using namespace std;


// the question 1 structures
struct event {
    int ID;                
    string responsible;   
    float budget;
    int guests;            
    string eventDate;      
};

struct room {
    int code;           
    float price;     
    int seats;             
    int numevents;       
    event history[300];    
};
//question 3 procedure
void Enter_Room_Info(room& r) {
    cout << "Enter room code, price, and seats: ";
    cin >> r.code ;
    cin>> r.price; 
    cin>> r.seats;
    r.numevents = 0;
    for (int i = 0; i < 300; i++) {
        r.history[i].ID = 0; 
    }
}

//question 4 procedure
room* Fill_Room_Collection(int n) {
    room* roomCollection = new room[n];
    for (int i = 0; i < n; ++i) {
        cout<<endl;
        cout << "Entering details for room " << i + 1 << ":\n";
        Enter_Room_Info(roomCollection[i]);
    }
    return roomCollection;
}

//question 5 function
int Search_Room(room* roomCollection, int n, int x) {
    for (int i = 0; i < n; i++) {
        if (roomCollection[i].code == x) {
            return i + 1; 
        }
    }
    return 0;
}

//question 6 procedure
void List_Rooms(room* s, int n) {
    if (n == 0) {
        cout << "No rooms to display.\n" ;
        return;
    }
    cout << "List of Rooms:";
    for (int i = 0; i < n; ++i) {
        cout << i + 1 << " Details:" << endl;
        cout << "room code : "<< s[i].code << endl;
        cout << "room price : "<<s[i].price << endl;
        cout << "room seats : "<<s[i].seats << endl;
        cout << "Number of Events: " << s[i].numevents << endl;
    }
}

//question 7 function :
event Enter_Event() {
    event newEvent;
    cout << "Enter event ID, responsible, budget, guests, and date: ";
    cin >> newEvent.ID >> newEvent.responsible >> newEvent.budget >> newEvent.guests >> newEvent.eventDate;
    return newEvent;
}

//A function to return if the room is available at the event date or not
bool available(room s, event e) {
    for (int i = 0; i < s.numevents; i++) {
        if (s.history[i].eventDate == e.eventDate) {
            return false;
        }
    }
    return true;
}

//question 8 procedure :
void Reserve_Room(room* s, int n,event e) {
    bool test = false;
    for (int i = 0; i < n; ++i) {
        if (s[i].price <= e.budget && s[i].seats >= e.guests && available(s[i], e) && s[i].numevents < 300) {
            s[i].history[s[i].numevents] = e;
            s[i].numevents++;
            test = true;
            cout << "Room with code " << s[i].code << " has been successfully reserved for the event!\n";
            break;
        }
    }
    if (!test) {
        cout << "There is no room for this event." << endl;
    }
}

//question 9 function :
int Count_Room_Reservations(room r ,int month) {
    int count = 0;
    for (int i = 0; i < r.numevents; ++i) {
        string ch = r.history[i].eventDate.substr(3, 5);
        int n = std::stoi(ch);
        if (n == month) {
            count++;
        }
    }
    return count;
}

//question 10 function :
room* Most_Reserved_Room(room* s, int n, int month) {
    room* mostReservedRoom = nullptr;
    int maxReservations = 0;
    for (int i = 0; i < n; ++i) {
        int currentReservations = Count_Room_Reservations(s[i], month);
        if (currentReservations > maxReservations) {
            maxReservations = currentReservations;
            mostReservedRoom = &s[i];
        }
    }
    return mostReservedRoom;
}

//question 11 procedure
void Replace_Room(room* rooms, int& n, int c1, int c2) {
    room* R1 = nullptr;
    room* R2 = nullptr;
    if (Search_Room(rooms,n,c1) == 0 || Search_Room(rooms,n,c2) == 0) {
        cout << "Room not found." << endl;
        return;
    }else{
        R1 = &rooms[Search_Room(rooms,n,c1)-1];
        R2 = &rooms[Search_Room(rooms,n,c2)-1];
    }
    if (R2->numevents + R1->numevents > 300) {
        cout << "Error" << endl;
        return;
    }
    for (int i = 0; i < R1->numevents; ++i) {
        for (int j = 0; j < R2->numevents; ++j) {
            if (R1->history[i].eventDate == R2->history[j].eventDate) {
                cout << "Duplicate event date"<< endl;
                return;
            }
        }
    }
    for (int i = 0; i < R1->numevents; i++) {
        R2->history[R2->numevents] = R1->history[i];
        R2->numevents++;
    }
    for (int i = 0; i < n; i++) {
        if (rooms[i].code == c1) {
            for (int j = i; j < n - 1; j++) {
                rooms[j] = rooms[j + 1];
            }
            n--;
            break;
        }
    }
}

//the main program (question 12)
int main() {
    int n;
    cout << "Enter the number of rooms: ";
    cin >> n;

    room* roomCollection = new room[n];
    room* s;
    s = Fill_Room_Collection(n);
    event e;
    e = Enter_Event();
    Reserve_Room(s,n,e);

    List_Rooms(s, n);

    int month ;
    cout << "enter the month you search for";
    cin>>month;
    room* mostReserved = Most_Reserved_Room(s, n, month);
    if (mostReserved) {
        cout << "The most reserved room for " << month << " is: " << mostReserved->code << endl;
    } else {
        cout << "No reservations found for the month." << endl;
    }

    delete[] s;
    return 0;
}