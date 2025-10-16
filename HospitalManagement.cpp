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

        }
};

int main(){

    return 0;
}
