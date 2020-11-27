//1) Design a Call taxi booking application
//-There are n number of taxi’s. For simplicity, assume 4. But it should work for any number of taxi’s.
//-The are 6 points(A,B,C,D,E,F)
//-All the points are in a straight line, and each point is 15kms away from the adjacent points.
//-It takes 60 mins to travel from one point to another
//-Each taxi charges Rs.100 minimum for the first 5 kilometers and Rs.10 for the subsequent kilometers.
//-For simplicity, time can be entered as absolute time. Eg: 9hrs, 15hrs etc.
//-All taxi’s are initially stationed at A.
//-When a customer books a Taxi, a free taxi at that point is allocated
//-If no free taxi is available at that point, a free taxi at the nearest point is allocated.
//-If two taxi’s are free at the same point, one with lower earning is allocated
//-Note that the taxi only charges the customer from the pickup point to the drop point. Not the distance it travels from an adjacent point to pickup the customer.
//-If no taxi is free at that time, booking is rejected

#include <bits/stdc++.h>
#include<windows.h>
using namespace std;

struct Stop{                          // struct node to store main details
    int taxino;
    string driver;
    int earnings;
    char stop;
    Stop* next = NULL;
};
map <char, Stop*> stopmap;            // map to store stoping as key and value as Node with driver name, taxino, earnings, etc
map <char, Stop*>::iterator itr;

class Taxi{                           // to get new taxi details
    public :
    int taxino;
    string driver;

    int getTaxino(){
        cout<<"Enter ur taxi number"<<endl;
        cin>>taxino;
        return taxino;
    }
    string getDriver(){
        cout<<"Enter the driver name"<<endl;
        cin>>driver;
        return driver;
    }
};

class Booking{                                    // to get booking deatails
    public :
    char pickup, drop;
    Booking(){
        cout<<"Enter ur pickup location [A-B-C-D-E-F]"<<endl;
        cin>>pickup;
        cout<<"Enter ur drop location [A-B-C-D-E-F]"<<endl;
        cin>>drop;
    }

};

void UpdateRide(Stop* temp, char location){                                    // update driver current location from pickup to drop
    temp->next = NULL;
    if(stopmap.find(location)==stopmap.end()){
        stopmap.insert(pair<char, Stop*>(location, temp));
    }
    else{
        itr = stopmap.find(location);
        Stop* node = itr->second;
        while(node->next!=NULL){
            node = node->next;
        }
        node->next = temp;
    }
}

char FindNearest(char location){                                              // function to find nearest taxi, incase of no taxi in pickup position
    char left, right;
    left = right = location;
    while(stopmap.find(left)==stopmap.end() && stopmap.find(right)==stopmap.end()){
        left--;
        right++;
    }
    if(stopmap.find(left)!=stopmap.end()) return left;
    else return right;
}

int Money(Stop* temp, char start, char end){                                          // function to claculate cost for ride, and update in driver's earnings
    int km = abs(end-start)*15;
    int money = 100;
    km -= 5;
    km /= 5;
    money += (km*10);
    temp->earnings += money;
    return money;
}

void BookTaxi(){                                                                      //find taxi at pickup position if available, or nearest position
    Booking book;
    if(stopmap.find(book.pickup)!=stopmap.end()){
        itr = stopmap.find(book.pickup);
        Stop* temp = itr->second;
        cout<<"-------------------------------------"<<endl
            <<"Booking Confirmed"<<endl
            <<"Driver : "<<temp->driver<<endl
            <<"Taxi No : "<<temp->taxino<<endl
            <<"Current Location : "<<itr->first<<endl
            <<"Estimated time : 0 Minutes"<<endl
            <<"Cost : Rs."<<Money(temp, book.pickup, book.drop)<<endl
            <<"Ride distance ["<<book.pickup<<" - "<<book.drop<<"] : "<<abs(book.pickup-book.drop)*15<<"km"<<endl
            <<"-------------------------------------"<<endl;
        itr->second = itr->second->next;
        UpdateRide(temp, book.drop);
    }
    else{
        char found = FindNearest(book.pickup);
        itr = stopmap.find(found);
        Stop* temp = itr->second;
        cout<<"-------------------------------------"<<endl
            <<"Booking Confirmed"<<endl
            <<"Driver : "<<temp->driver<<endl
            <<"Taxi No : "<<temp->taxino<<endl
            <<"Current Location : "<<itr->first<<endl
            <<"Estimated time : "<<abs(book.pickup-found)*6<<" Minutes"<<endl
            <<"Cost : Rs."<<Money(temp, book.pickup, book.drop)<<endl
            <<"Ride distance ["<<book.pickup<<" - "<<book.drop<<"] : "<<abs(book.pickup-book.drop)*15<<"km"<<endl
            <<"-------------------------------------"<<endl;
        itr->second = itr->second->next;
        UpdateRide(temp, book.drop);
    }
    if(itr->second==NULL) stopmap.erase(itr);
}

void RegisterTaxi(){                                                                     // resgister new taxi using Taxi class in map
    Taxi obj;
    Stop* temp = new Stop();
    temp->taxino = obj.getTaxino();
    temp->driver = obj.getDriver();
    temp->stop = 'A';
    temp->next =NULL;

    if(stopmap.find(temp->stop)==stopmap.end()){
        stopmap.insert(pair<char, Stop*>(temp->stop, temp));
    }
    else{
        itr = stopmap.find(temp->stop);
        Stop* node = itr->second;
        while(node->next!=NULL){
            node = node->next;
        }
        node->next = temp;
    }
}

void Display(){                                                                        // display all the taxi details with current position and earnings
    for (auto itr=stopmap.begin(); itr!=stopmap.end(); itr++){
        Stop* temp = itr->second;
        while(temp!=NULL){
            cout<<"-------------------------------------"<<endl
                <<"Driver : "<<temp->driver<<endl
                <<"Taxi No : "<<temp->taxino<<endl
                <<"Earnings : Rs."<<temp->earnings<<endl
                <<"Current Location : "<<itr->first<<endl
                <<"-------------------------------------"<<endl;
            temp = temp->next;
        }
    }
}

int main(){
    int choice;
    do{
        cout<<"Welcome to Sparrow Cab"<<endl                                                           //first register a taxi and book taxi
            <<"Select ur choice"<<endl                                                                 //user single wor for name and only numbers for taxi no
            <<"1. Register ur Taxi"<<endl                                                              // enjoy 
            <<"2. Book Taxi"<<endl
            <<"3. Display"<<endl
            <<"0. Exit"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                RegisterTaxi();
                break;

            case 2:
                BookTaxi();
                break;
            
            case 3:
                Display();
                break;

            case 0:
                cout<<"Thankyou for using Sparrow Cab"<<endl;
                break;
        }
    }while(choice!=0);
    return 0;
}
