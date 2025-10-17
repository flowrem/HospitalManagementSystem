#include <iostream>
#include <string>
using namespace std;

class Node{
    public:
        int data;
        Node* next;
        Node* prev;

        Node(int value){
            data = value;
            next = nullptr;
            prev = nullptr;
        }

};

class HospitalManagement {
    Node* head;
    Node* tail;

    public:
        HospitalManagement() {
            head = nullptr;
            tail = nullptr;
        }
        struct Doctor{
            string name;
            int id = 0;
        };
        
        Doctor doctors[10];
        int doctorCount = 0;

        void manageDoctors(){
           int n = 0;
           int choice;
           cout<<"Manage Doctors"<<endl;
           
           cout<<"1. Add Doctors"<<endl;
           cout<<"2. Remove Doctors"<<endl;

           cout<<"Enter your choice: ";
           cin>>choice;
           switch(choice){
              case 1:
                cout << "Enter number of doctors to add: ";
                cin>>n;
                    if(n > 10){
                        cout<<"You can only add up to 10 Doctors.";
                        n = 10;
                    }
                    for(int i = 0;i<n;i++){
                        cout<<"Enter name for doctor "<<  i + 1 << ": ";
                        cin>> doctors[doctorCount].name;
                        cout<<"Enter ID for doctor "<<  i + 1 << ": ";
                        cin>> doctors[doctorCount].id;
                        doctorCount++;
                    }

                    cout<<"Doctors added successfully."<<endl;
                    cout<<"Current Doctors List: "<<endl;

                    for(int i = 0;i<doctorCount;i++){
                        cout<<"Doctor "<< i + 1 << ":"<< endl << "Name: " << doctors[i].name << ", ID: " << doctors[i].id << endl;
                    }
                    break;

               case 2:
                    // Future implementation for removing doctors
                    cout<<"Feature to remove doctors is under development."<<endl;
                    break;
                }
        }
        void admitPatients(){
            
        }
        void undoLastAdmission(){

        }
        void viewDoctors(){
            cout<<"Current Doctors List: "<<endl;

            if(doctorCount == 0){
                cout<<"No doctors available."<<endl;
                return;
            }

            for(int i = 0;i<doctorCount;i++){
                cout<<"Doctor "<< i + 1 << endl << "Name: " << doctors[i].name << ", ID: " << doctors[i].id << endl;
            }
        }
        void displayChoices(){
            cout << "1. Manage Doctors" << endl;
            cout << "2. Admit Patients" << endl;
            cout << "3. Undo Last Admission" << endl;
            cout << "4. View Doctors" << endl;
            cout << "5. Exit" << endl;
        }
};

int main(){
    HospitalManagement hm;
    int choice;
    bool stop = false;

    while(!stop){

        cout<<"Welcome to Hospital Management System"<<endl;
        hm.displayChoices();

        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                hm.manageDoctors();
                break;
            case 2:
                hm.admitPatients();
                break;
            case 3:
                hm.undoLastAdmission();
                break;
            case 4:
                hm.viewDoctors();
                break;
            case 5:
                stop = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    }


    return 0;
}
