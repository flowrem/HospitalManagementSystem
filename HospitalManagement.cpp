#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string name;
	int id;
    Node* next;
    Node* prev;

    Node(string patientName, int patientID) {
        name = patientName;
        id = patientID;
        next = nullptr;
        prev = nullptr;
    }
};

class HospitalManagement {
    Node* head;
    Node* tail;
    Node* waitingHead;
    Node* waitingTail;

public:
    HospitalManagement() {
        head = nullptr;
        tail = nullptr;
        waitingHead = nullptr;
        waitingTail = nullptr;
    }

    struct Doctor {
        string name;
        int id = 0;
    };

    Doctor doctors[10];
    int doctorCount = 0;

    void manageDoctors() {
        int n = 0;
        int choice;
        int valueToRemove;

        cout << "Manage Doctors" << endl;
        cout << "1. Add Doctors" << endl;
        cout << "2. Remove Doctors" << endl;
        cout << "3. View Doctors" << endl;
        cout << "4. Back to Main Menu" << endl;

        cout << "Enter your choice: ";
        cin >> choice;
		cout << endl;
		
        switch (choice) {
        case 1:
            cout << "Enter number of doctors to add: ";
            cin >> n;
            if (n > 10) {
                cout << "You can only add up to 10 Doctors." << endl;
                n = 10;
            }
            for (int i = 0; i < n; i++) {
                if (doctorCount >= 10) {
                    cout << "Doctor list is full!" << endl;
                    break;
                }
                cout << "Enter name for doctor " << i + 1 << ": ";
                cin >> doctors[doctorCount].name;
                
                bool idAlreadyExist;
				int newID;
                
                //Checks if ID is taken or not
                do{
				idAlreadyExist = false;
				
				cout << "Enter ID for doctor " << i + 1 << ": ";
                cin >> newID;
                
                for(int j = 0; j < doctorCount; j++){
                	if(doctors[j].id == newID){
                		cout << "This ID is already taken. Please enter a difference ID." << endl;
                		idAlreadyExist = true;
                		break;
						}
					}
				} while(idAlreadyExist);
				
				doctors[doctorCount].id = newID;
				doctorCount++;
				cout << "Doctors added successfully." << endl;
            }

            
			cout << "\n=== Current Doctors List ===" << endl;
            for (int i = 0; i < doctorCount; i++) {
                cout << "Doctor " << i + 1 << ": " 
                     << "Name: " << doctors[i].name 
                     << ", ID: " << doctors[i].id << endl;
            }
            break;

        case 2:
            cout << "Enter ID of doctor to remove: ";
            cin >> valueToRemove;

            if (doctorCount == 0) {
                cout << "No doctors to remove." << endl;
                break;
            }

            {
                bool found = false;
                for (int i = 0; i < doctorCount; i++) {
                    if (doctors[i].id == valueToRemove) {
                        found = true;
                        // Shift doctors down
                        for (int j = i; j < doctorCount - 1; j++) {
                            doctors[j] = doctors[j + 1];
                        }
                        doctorCount--;
                        cout << "Doctor with ID " << valueToRemove << " removed successfully." << endl;
                        break;
                    }
                }
                if (!found) {
                    cout << "Doctor with ID " << valueToRemove << " not found." << endl;
                }
            }
            break;
            
        case 3:
        cout << "Current Doctors List:" << endl;

        	if (doctorCount == 0) {
            cout << "No doctors available." << endl;
            return;
        	}

        	for (int i = 0; i < doctorCount; i++) {
            cout << "Doctor " << i + 1 << ": "
                 << "Name: " << doctors[i].name 
                 << ", ID: " << doctors[i].id << endl;
        	}
    	break;

        case 4:
            cout << "Returning to Main Menu." << endl;
            break;

        default:
            cout << "Invalid choice. Returning to Main Menu." << endl;
            break;
        }
    }

	void managePatient() {
    	int choice;
    	do {
        	cout << "\n=== Manage Patients ===" << endl;
        	cout << "1. Add Patient" << endl;
        	cout << "2. View Patients" << endl;
        	cout << "3. Manage Waiting Queue" << endl;
        	cout << "4. Back to Main Menu" << endl;
        	cout << "Enter your choice: ";
        	cin >> choice;
        	cout << endl;

        	switch (choice) {
        		case 1:
            		addPatient();
            		break;
        		case 2:
            		viewPatientHistory();
            		break;
        		case 3:
            		manageWaitingQueue();
            		break;
        		case 4:
            		cout << "Returning to main menu..." << endl;
            		break;
        	default:
            	cout << "Invalid choice. Try again." << endl;
        	}
    	} while (choice != 4);
	}	
	
	void addPatient(){
		
		string patientName;
		int patientID;
		bool idTaken;
		
		cout << "Enter Patients Name: ";
		cin >> patientName;
		
		do{
			idTaken = false;
			cout << "Enter Patients ID: ";
			cin >> patientID;
			
			//check if id already exist in the list
			Node* current = head;
			while(current != nullptr){
				if(current->id == patientID){
					cout << "The ID is already taken. Please enter a different one. \n";
					idTaken = true;
					break;
				}
				current = current->next;
			}
		} while(idTaken);
		
		Node* newPatient = new Node(patientName, patientID);
		if(head == nullptr){
			head = tail = newPatient; // check if the list is empty, if yes sets head and tail to newPatient
		}
		else{
			tail->next = newPatient;
			newPatient->prev = tail;
			tail = newPatient;
		}
		cout << "\nPatient: " << patientName << " ID: " << patientID << " has been added successfully!" << endl;
	}

	void viewPatientHistory(){
		//checks if the list is empty
		if(head == nullptr){
			cout << "No Patient have been admitted yet.\n";
			return;
		}
		
		int choice;
		bool repeat = true;
		
		while(repeat){
		cout << "\n=== View Patient History ===\n";
		cout << "1. View from first to last (Forward)\n";
    	cout << "2. View from last to first (Backward)\n";
    	cout << "3. Back \n";
		cout << "Enter your choice: ";
		cin >> choice;
		
		
		if(choice == 1){
			cout << "Patient List (Olders -> Newest): \n";
				Node* current = head;
				while(current != nullptr){
					cout<< "Name: " << current->name << " ID: " << current->id << endl;
					current = current->next;
				}
		}		
		else if(choice == 2){
			cout << "Patient List (Newest -> Oldest): \n";
				Node* current =  tail;
				while(current != nullptr){
					cout << "Name: " << current->name << " ID: " << current->id << endl;
					current = current->prev;
					}	
		}
		else if(choice == 3){
			repeat = false;
			cout << "Returning to Manage Patient Menu....\n";
		}
		else {
			cout << "Invalid choice. Please try again \n";
			}
		} 
	}

	void manageWaitingQueue(){
		cout << "Manage Waiting Queue is not yet implemented";
		return;
	}


	void displayChoices() {
        cout << "1. Manage Doctors" << endl;
        cout << "2. Manage Patient" << endl;
        cout << "3. Exit" << endl;
    }
};

int main() {
    HospitalManagement hm;
    int choice;
    bool stop = false;

    while (!stop) {
        cout << "\nWelcome to Hospital Management System" << endl;
        hm.displayChoices();

        cout << "Enter your choice: ";
        cin >> choice;
		cout << endl;
        switch (choice) {
        case 1:
            hm.manageDoctors();
            break;
        case 2:
            hm.managePatient();
            break;
        /*case 3:
            hm.undoLastAdmission();
            break;*/
        case 3:
            stop = true;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    cout << "Exiting system. Goodbye!" << endl;
    return 0;
}