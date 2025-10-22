#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string name;
	int id;
    Node* next;
    Node* prev;
    int assignedDoctorID;  
 
    Node(string patientName, int patientID) {
        name = patientName;
        id = patientID;
        next = nullptr;
        prev = nullptr;
        assignedDoctorID = -1;  // -1 means no doctor assigned
    }
};

class HospitalManagement {
    Node* head;
    Node* tail;
    Node* waitingHead;
    Node* waitingTail;
    Node* stackTop;  

public:
    HospitalManagement() {
        head = nullptr;
        tail = nullptr;
        waitingHead = nullptr;
        waitingTail = nullptr;
        stackTop = nullptr;  
    }

    struct Doctor {
        string name;
        int id = 0;
    };

    Doctor doctors[10];
    int doctorCount = 0;
    int patientCount = 0;
    bool isDoctorAssigned = false;

    void manageDoctors() {
        int choice;

        cout << "Manage Doctors" << endl;
        cout << "1. Add Doctors" << endl;
        cout << "2. Remove Doctors" << endl;
        cout << "3. View Doctors" << endl;
        cout << "4. Assign Doctor to Patient" << endl;
        cout << "5. Back to Main Menu" << endl;

        cout << "Enter your choice: ";
        cin >> choice;
		cout << endl;
		
        switch (choice) {
        case 1:
            addDoctor();
            break;

        case 2:
            removeDoctor();
            break;
            
        case 3:
            viewDoctors();
    	    break;
        case 4:
            assignDoctorToPatient();
            break;

        default:
            cout << "Invalid choice. Returning to Main Menu." << endl;
            break;
        }
    }
    void addDoctor(){
        int n = 0;
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
    }
    void removeDoctor(){
        int valueToRemove;
        cout << "Enter ID of doctor to remove: ";
            cin >> valueToRemove;

            if (doctorCount == 0) {
                cout << "No doctors to remove." << endl;
                return;
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
                        return;
                    }
                }
                if (!found) {
                    cout << "Doctor with ID " << valueToRemove << " not found." << endl;
                }
            }
    }
    void viewDoctors(){
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
    }
	void managePatient() {
    	int choice;
    	do {
        	cout << "\n=== Manage Patients ===" << endl;
        	cout << "1. Add Patient" << endl;
        	cout << "2. Remove Patient" << endl;
        	cout << "3. View Patient History" << endl;
        	cout << "4. View Patients with Assigned Doctors" << endl;
        	cout << "5. Assign Doctor to Patient" << endl;
            cout << "6. Undo Last Admission"<< endl;
            cout << "7. Back to Main Menu" << endl;
        	cout << "Enter your choice: ";
        	cin >> choice;
        	cout << endl;

        	switch (choice) {
        		case 1:
            		addPatient();
            		break;
        		case 2:
            		removePatient();
            		break;
        		case 3:
            		viewPatientHistory();  
            		break;
                case 4:
                    displayPatientsWithDoctors();
                    break;
                case 5:
                    assignDoctorToPatient();
                    break;
                case 6:
                    undoLastAdmission();
                    break;
                case 7:
                    cout << "Returning to main menu..." << endl;
                    break;
        	    default:
            	    cout << "Invalid choice. Try again." << endl;
        	}
    	} while (choice != 7);
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
                head = tail = newPatient; 
            }
            else{
                tail->next = newPatient;
                newPatient->prev = tail;
                tail = newPatient;
            }
            
            // Push to undo stack
            pushToStack(patientName, patientID);
            
            cout << "\nPatient: " << patientName << " with ID: " << patientID << " has been added successfully!" << endl;
            patientCount++;
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
			cout << "Patient List (Oldest -> Newest): \n";
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

    void displayPatientsWithDoctors() {
        // Temporary queue for patients with assigned doctors
        Node* queueFront = nullptr;
        Node* queueRear = nullptr;
        
        // Traverse patient list and enqueue patients with assigned doctors
        Node* current = head;
        int count = 0;
        
        while(current != nullptr) {
            if(current->assignedDoctorID != -1) {
                // Create copy for queue
                Node* queueNode = new Node(current->name, current->id);
                queueNode->assignedDoctorID = current->assignedDoctorID;
                
                // Enqueue (add to rear)
                if(queueFront == nullptr) {
                    queueFront = queueRear = queueNode;
                } else {
                    queueRear->next = queueNode;
                    queueRear = queueNode;
                }
                count++;
            }
            current = current->next;
        }
        
        // Display queue
        if(queueFront == nullptr) {
            cout << "\nNo patients have assigned doctors yet." << endl;
        } else {
            cout << "\n=== Patients with Assigned Doctors ===" << endl;
            cout << "Total: " << count << " patient(s)\n" << endl;
            
            Node* temp = queueFront;
            int position = 1;
            
            while(temp != nullptr) {
                cout << position << ". Patient: " << temp->name 
                     << " (ID: " << temp->id << ")";
                
                // Find and display doctor name
                for(int i = 0; i < doctorCount; i++) {
                    if(doctors[i].id == temp->assignedDoctorID) {
                        cout << "-> Assigned to Dr. " << doctors[i].name 
                             << " (ID: " << doctors[i].id << ")";
                        break;
                    }
                }
                cout << endl;
                temp = temp->next;
                position++;
            }
        }
        
        // Clean up temporary queue 
        while(queueFront != nullptr) {
            Node* temp = queueFront;
            queueFront = queueFront->next;
            delete temp;
        }
    }

    void assignDoctorToPatient(){
        
       if (doctorCount == 0) {
           cout << "No doctors available to assign." << endl;
           return;
       }
       if(patientCount == 0){
           cout << "No patients available to assign." << endl;
           return;
       }
       
       // Display all patients
       cout << "\n=== Available Patients ===" << endl;
       Node* current = head;
       while(current != nullptr){
           cout << "Patient ID: " << current->id 
                << ", Name: " << current->name;
           
           // Show if doctor is already assigned
           if(current->assignedDoctorID != -1){
               // Find doctor name
               for(int i = 0; i < doctorCount; i++){
                   if(doctors[i].id == current->assignedDoctorID){
                       cout << " (Assigned to Dr. " << doctors[i].name << ")";
                       break;
                   }
               }
           } else {
               cout << " (No doctor assigned)";
           }
           cout << endl;
           current = current->next;
       }
       
       // Get patient ID
       int patientID;
       cout << "\nEnter Patient ID to assign doctor: ";
       cin >> patientID;
       
       // Find patient
       current = head;
       Node* targetPatient = nullptr;
       while(current != nullptr){
           if(current->id == patientID){
               targetPatient = current;
               break;
           }
           current = current->next;
       }
       
       if(targetPatient == nullptr){
           cout << "Patient with ID " << patientID << " not found." << endl;
           return;
       }
       
       // Display all doctors
       cout << "\n=== Available Doctors ===" << endl;
       for(int i = 0; i < doctorCount; i++){
           cout << "Doctor ID: " << doctors[i].id 
                << ", Name: " << doctors[i].name << endl;
       }
       
       // Get doctor ID
       int doctorID;
       cout << "\nEnter Doctor ID to assign: ";
       cin >> doctorID;
       
       // Find doctor
       bool doctorFound = false;
       int doctorIndex = -1;
       for(int i = 0; i < doctorCount; i++){
           if(doctors[i].id == doctorID){
               doctorFound = true;
               doctorIndex = i;
               break;
           }
       }
       
       if(!doctorFound){
           cout << "Doctor with ID " << doctorID << " not found." << endl;
           return;
       }
       
       // Assign doctor to patient
       targetPatient->assignedDoctorID = doctorID;
       
       cout << "\nSuccessfully assigned Dr. " << doctors[doctorIndex].name 
            << " (ID: " << doctorID << ") to Patient " << targetPatient->name 
            << " (ID: " << patientID << ")" << endl;
    }
    
    // Push patient to undo stack
    void pushToStack(string patientName, int patientID) {
        Node* newNode = new Node(patientName, patientID);
        newNode->next = stackTop;  // Link to previous top
        stackTop = newNode;         // Update top
    }
    
    // Pop patient from undo stack
    Node* popFromStack() {
        if (stackTop == nullptr) {
            return nullptr;  
        }
        Node* temp = stackTop;
        stackTop = stackTop->next;  
        return temp;
    }
    
	void displayChoices() {
        cout << "1. Manage Doctors" << endl;
        cout << "2. Manage Patient" << endl;
        cout << "3. Exit" << endl;
    }
    void undoLastAdmission() {
        if (stackTop == nullptr) {
            cout << "No admissions to undo!" << endl;
            return;
        }
        Node* lastAdmitted = popFromStack();
        int patientID = lastAdmitted->id;
        string patientName = lastAdmitted->name;
        
        // Remove from main patient list
        Node* current = head;
        bool found = false;
        
        while (current != nullptr) {
            if (current->id == patientID) {
                found = true;
                // Handle removal from doubly linked list
                if (current == head && current == tail) {
                    head = tail = nullptr;
                } else if (current == head) {
                    head = head->next;
                    head->prev = nullptr;
                } else if (current == tail) {
                    tail = tail->prev;
                    tail->next = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                patientCount--;
                cout << "\nSuccessfully undid admission of Patient: " 
                     << patientName << " with ID: " << patientID << endl;
                break;
            }
            current = current->next;
        }
        
        if (!found) {
            cout << "Patient was already removed manually." << endl;
        }
        
        // Clean up the stack node
        delete lastAdmitted;
        return;
    }

    void removePatient() {
        if (head == nullptr) {
            cout << "No patients to remove." << endl;
            return;
        }

        viewPatientHistory();
        
        int patientID;
        Node* current = head;
        cout << "Enter the Patient ID to remove: ";
        cin >> patientID;

        while (current != nullptr) {
            if (current->id == patientID) {
                // Handle removal from doubly linked list
                if (current == head && current == tail) {
                    head = tail = nullptr;
                } else if (current == head) {
                    head = head->next;
                    head->prev = nullptr;
                } else if (current == tail) {
                    tail = tail->prev;
                    tail->next = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                patientCount--;
                cout << "Patient with ID " << patientID << " removed successfully." << endl;
                return;
            }
            current = current->next;
        }
        cout << "Patient with ID " << patientID << " not found." << endl;
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