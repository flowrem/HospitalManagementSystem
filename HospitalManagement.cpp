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
        void manageDoctors(){

        }
        void admitPatients(){
            
        }
        void undoLastAdmission(){

        }
        void displayChoices(){
            cout << "1. Manage Doctors" << endl;
            cout << "2. Admit Patients" << endl;
            cout << "3. Undo Last Admission" << endl;
            cout << "4. Exit" << endl;
        }
};

int main(){
    HospitalManagement hm;
    int choice;
    
    return 0;
}
