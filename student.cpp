#include "student.h"
#include"common.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include "colors.h"
#include "utils.h"

using namespace std;
Student::Student(){
    cgpa=0.0;
    name="";
    email="";
    branch="";
    phone="";
    skills="";
}
Student::~Student(){
    cout<<"\nStudent object destroyed.\n";
}



void Student::studentMenu() {
    int choice;
    do {
       cout << CYAN;
printCenter("----- Student Menu -----");
cout << RESET;

cout << WHITE;
printCenter("1. Register");
printCenter("2. Login");
printCenter("3. Back");
cout << RESET;

        cout << "Enter choice: "; cin >> choice;
        switch(choice) {
            case 1: registerStudent(); break;
            case 2: if(loginStudent()) studentDashboard(); break;
            case 3: break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 3);
}

void Student::registerStudent() {
    cin.ignore();
    cout << BLUE;
printCenter("===== Student Registration =====");
cout << RESET;


    cout << WHITE<<"Name: "<<RESET; getline(cin, name);

    bool validEmail = false;
    do {
        cout << WHITE<<"Email(must contain @): "<<RESET; cin >> email;
        if(email.find('@') == string::npos) 
        { cout<<RED<<"Invalid email!\n"<<RESET; continue; }

        ifstream f("students.txt");
        string line, tmp;
        bool exists=false;
        while(getline(f,line)) {
            stringstream ss(line);
            getline(ss,tmp,','); 
            getline(ss,tmp,','); 
            if(tmp==email){ exists=true; break; }
        }
        f.close();
        if(exists){ cout<<YELLOW<<"Email already registered!\n"<<RESET; continue; }
        validEmail=true;
    } while(!validEmail);

    // --- Password ---
    cout<<WHITE<<"Password(must contain at least 1 uppercase, 6-8 characters and 1 digit):"<<RESET;
    password=getValidatedPassword();
    cin.ignore();
    
    cout << WHITE<<"Branch: "<<RESET; cin >> branch;

    cout << WHITE<<"CGPA: "<<RESET; cin >> cgpa;

    bool validPhone=false;
    do {
        cout << WHITE<<"Phone (10 digits): "<<RESET; cin >> phone;
        if(phone.length()!=10){ cout<<RED<<"Phone must be 10 digits!\n"<<RESET; continue; }
        validPhone=true;
    } while(!validPhone);
    cin.ignore();

    cout <<WHITE<< "Skills: "<<RESET; cin >> skills;

    ofstream out("students.txt", ios::app);
    out<<name<<","<<email<<","<<password<<","<<branch<<","<<cgpa<<","<<phone<<","<<skills<<endl;
    out.close();

    cout << GREEN<<"Registration Successful!\n"<<RESET;
}

bool Student::loginStudent() {
    ifstream f("students.txt");
    string line; bool emailFound=false;

    cout << BLUE;
printCenter("===== Student Login =====");
cout << RESET;

     cout<< WHITE << "Email(must contain @): " << RESET;
     cin >> email;

    cout<<WHITE<<"Password(must contain at least 1 uppercase, 6-8 characters and 1 digit):"<<RESET;
    password=getPassword();
    while(getline(f,line)) {
        stringstream ss(line);
        string storedEmail, storedPass;
        getline(ss,name,','); getline(ss,storedEmail,','); getline(ss,storedPass,',');
        getline(ss,branch,','); ss>>cgpa; ss.ignore(); getline(ss,phone,','); getline(ss,skills,',');
        if(storedEmail==email){
            emailFound=true;
            if(storedPass==password){ cout<<GREEN<<"Login Successful!\n"<<RESET; f.close(); return true; }
            else{ cout<<RED<<"Incorrect Password!\n"<<RESET; f.close(); return false; }
        }
    }
    if(!emailFound) cout<<RED<<"Email Not Found!\n"<<RESET;
    f.close(); return false;
}

void Student::studentDashboard() {
    int choice;
    do{
        cout << YELLOW;
printCenter("===== Student Dashboard =====");
cout << RESET;
        cout<<WHITE<<"1. View Profile\n2. Update Profile\n3. View Eligible Jobs\n4. Apply For Job\n5. View Applied Jobs\n6. Logout\nChoice: "<<RESET;
        cin>>choice;
        switch(choice){
            case 1: viewProfile(); break;
            case 2: updateProfile(); break;
            case 3: viewEligibleJobs(); break;
            case 4: applyForJob(); break;
            case 5: viewAppliedJobs(); break;

        }
    }while(choice!=6);
}

void Student::viewProfile(){
    cout<<BLUE;
    printCenter("===== MY PROFILE =====");
    cout << RESET;

    showStudent(*this);   

    cout<<" Branch : "<<branch<<endl;
    cout<<" CGPA   : "<<cgpa<<endl;
    cout<<" Phone  : "<<phone<<endl;
    cout<<" Skills : "<<skills<<endl;
}
void Student::updateProfile(){
    int choice;
    do{
        cout << BLUE;
        printCenter("===== Update Profile =====");
        cout << RESET;
        cout << WHITE << "\n1. Update Mobile No\n2. Update Skills\n3. Update CGPA\n4. Back\nChoice: " << RESET; cin >> choice;
        if(choice==1){ cout << WHITE << "New Mobile: " << RESET; cin >> phone; }
        else if(choice==2){ cout << WHITE << "New Skills: " << RESET; cin >> skills; }
        else if(choice==3){ cout << WHITE << "New CGPA: " << RESET; cin >> cgpa; }
    }while(choice!=4);
    cout<<GREEN<<"Profile Updated Successfully!\n"<<RESET;
}


void Student::viewEligibleJobs(){
    ifstream file("jobs.txt");
    string line; int count=1;
    vector<string> eligible;
    cout << BLUE;
    printCenter("===== Eligible Jobs =====");
    cout << RESET;
    while(getline(file,line)){
        stringstream ss(line); string company, role, jobBranch, status; float minCGPA, salary;
        getline(ss,company,','); getline(ss,role,','); getline(ss,jobBranch,',');
        ss>>minCGPA; ss.ignore(); ss>>salary; ss.ignore(); getline(ss,status,',');
        if(status!="Approved") continue;
        if(cgpa<minCGPA) continue;
        bool branchMatch=false;
        if(jobBranch=="ALL") branchMatch=true;
        else{
            stringstream bs(jobBranch); string jb;
            while(getline(bs,jb,'|')){ if(jb==branch){branchMatch=true; break;} }
        }
        if(!branchMatch) continue;
        cout<<count++<<WHITE<<". Company: "<<company<<" | Role: "<<role<<" | Min CGPA: "<<minCGPA<<" | Salary: "<<salary<<" LPA\n"<<RESET;
        eligible.push_back(company+","+role);
    }
    if(eligible.empty()) cout<<RED<<"No Eligible Jobs.\n"<<RESET;
    file.close();
}
void Student::applyForJob() {

    vector<string> eligibleJobs;
    ifstream file("jobs.txt");
    string line;

    while (getline(file, line)) {

        stringstream ss(line);
        string company, role, jobBranch, status;
        float minCGPA, salary;

        getline(ss, company, ',');
        getline(ss, role, ',');
        getline(ss, jobBranch, ',');
        ss >> minCGPA; ss.ignore();
        ss >> salary; ss.ignore();
        getline(ss, status, ',');

        if (status == "Approved" && cgpa >= minCGPA &&
            (jobBranch == "ALL" || jobBranch.find(branch) != string::npos)) {
            eligibleJobs.push_back(company + "," + role);
        }
    }
    file.close();

    if (eligibleJobs.empty()) {
        cout <<RED<<"No Eligible Jobs.\n"<<RESET;
        return;
    }

    cout << BLUE;
printCenter("===== Eligible Jobs =====");
cout << RESET;

    for (int i = 0; i < eligibleJobs.size(); i++) {
        stringstream ss(eligibleJobs[i]);
        string comp, role;
        getline(ss, comp, ',');
        getline(ss, role, ',');
        cout << i+1 << WHITE<<". Company: " << comp << " | Role: " << role <<RESET<< endl;
    }

    int choice;
    cout <<WHITE<<"Enter Job Number to Apply: "<<RESET;
    cin >> choice;

    if (choice < 1 || choice > eligibleJobs.size()) {
        cout <<RED<<"Invalid Choice!\n"<<RESET;
        return;
    }

    string selectedJob = eligibleJobs[choice - 1];

    ifstream check("applications.txt");
    while (getline(check, line)) {
        if (line.find(email + "," + selectedJob) != string::npos) {
            cout <<RED<<"Already Applied!\n"<<RESET;
            check.close();
            return;
        }
    }
    check.close();

    ofstream out("applications.txt", ios::app);
    out << email << "," << selectedJob << ",Pending\n";
    out.close();

    cout <<GREEN<<"Applied Successfully! Status: Pending\n"<<RESET;
}


void Student::viewAppliedJobs() {

    ifstream file("applications.txt");
    string line;
    int count = 1; 

    cout << BLUE;
printCenter("===== My Job Applications =====");
cout << RESET;


    bool found = false;
    while (getline(file, line)) {

        stringstream ss(line);
        string stuEmail, company, role, status;

        getline(ss, stuEmail, ',');
        getline(ss, company, ',');
        getline(ss, role, ',');
        getline(ss, status, ',');

        if (stuEmail == email) { 
            cout << count << ". Company: " << company
                 << " | Role: " << role
                 << " | Status: " << status << endl;
            count++;
            found = true;
        }
    }

    if (!found)
        cout <<RED<<"No Applications Yet.\n"<<RESET;

    file.close();
}
void showStudent(Student s) {
    cout << "\n          ===== STUDENT BASIC INFO =====\n";
    cout << "          Name  : " << s.name << endl;
    cout << "          Email : " << s.email << endl;
}