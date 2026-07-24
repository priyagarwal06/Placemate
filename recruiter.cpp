#include "recruiter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include "colors.h"
#include "utils.h"
#include"common.h"
using namespace std;
Recruiter::Recruiter() {
    company = "";
    name = "";
    email = "";
    contact = "";
}

Recruiter::~Recruiter() {
    cout << "\nRecruiter object destroyed.\n";
}




void Recruiter::recruiterMenu() {
    int choice;
    do {
        cout << CYAN;
printCenter("----- Recruiter Menu -----");
cout << RESET;

cout << WHITE;
printCenter("1. Register");
printCenter("2. Login");
printCenter("3. Back");
cout << RESET;
         cout <<WHITE<< "Enter choice: "<<RESET;
         cin >> choice;
        switch(choice){
            case 1: registerRecruiter(); break;
            case 2: if(loginRecruiter()) recruiterDashboard(); break;
            case 3: break;
            default: cout<<"Invalid choice!\n";
        }
    } while(choice != 3);
}

void Recruiter::registerRecruiter() {
    cin.ignore();
   cout << BLUE;
printCenter("===== Recruiter Registration =====");
cout << RESET;


    cout << "Company Name: "; getline(cin, company);
    cout << "Recruiter Name: "; getline(cin, name);

    bool validEmail = false;
    do {
        cout << WHITE<<"Official Email(must contain @): "<<RESET;
         cin >> email;
        if(email.find('@')==string::npos){ cout<<"Invalid email!\n"; continue; }

        ifstream f("recruiters.txt"); string line, storedEmail; bool exists=false;
        while(getline(f,line)){
            stringstream ss(line); string dummy;
            getline(ss,dummy,','); getline(ss,dummy,','); getline(ss,storedEmail,',');
            if(storedEmail==email){ exists=true; break; }
        }
        f.close();
        if(exists){ cout<<"Email already registered!\n"; continue; }
        validEmail=true;
    } while(!validEmail);

    // --- Password ---

       cout<<WHITE<<"Passwords(must contain at least 1 uppercase, 6-8 characters and 1 digit):"<<RESET;
       password=getValidatedPassword();
    
    bool validContact=false;
    do {
        cout << WHITE<<"Contact Number (10 digits): "<<RESET; 
        cin >> contact;
        if(contact.length()!=10){ cout<<"Must be 10 digits!\n"; continue; }
        validContact=true;
    } while(!validContact);

    ofstream out("recruiters.txt", ios::app);
    out << company << "," << name << "," << email << "," << password << "," << contact << endl;
    out.close();
    cout <<GREEN<<"Registration Successful!\n"<<RESET;
}

bool Recruiter::loginRecruiter() {
    ifstream f("recruiters.txt"); string line, storedEmail, storedPass;
    cout << BLUE;
printCenter("===== Recruiter Login =====");
cout << RESET;

    cout <<WHITE<< "Email(must contain @): "<<RESET; cin >> email;
     cout <<WHITE<<"Password(must contain atleast 1 uppercase, 6-8 characters and 1 digit):"<<RESET;
     password=getPassword();

    while(getline(f,line)){
        stringstream ss(line);
        getline(ss,company,','); getline(ss,name,','); getline(ss,storedEmail,','); getline(ss,storedPass,','); getline(ss,contact,',');
        if(storedEmail==email && storedPass==password){ cout<<GREEN<<"Login Successful!\n"<<RESET; f.close(); return true; }
    }
    cout<<RED<<"Invalid Credentials!\n"<<RESET;
     f.close();
     return false;
}

void Recruiter::recruiterDashboard(){
    int choice;
    do{
        cout << YELLOW;
printCenter("===== Recruiter Dashboard =====");
cout << RESET;

        cout<<WHITE<<"1. Post New Job\n2. View My Jobs\n3. View Applications\n4. Update Application Status\n5. Delete Job\n6. Logout\nChoice: "<<RESET; cin>>choice;
        switch(choice){
            case 1: postJob(); break;
            case 2: viewMyJobs(); break;
            case 3: viewApplications(); break;
            case 4: updateApplicationStatus(); break;
            case 5: deleteJob(); break;
        }
    }while(choice!=6);
}

void Recruiter::postJob(){
    cin.ignore();
    string role, branch; float cgpa, salary;
    cout<<WHITE<<"\nJob Role: "<<RESET;
     getline(cin,role);
    cout<<WHITE<<"Required Branch (ALL or CSE|IT|ECE etc): "<<RESET; getline(cin,branch);
    cout<<WHITE<<"Minimum CGPA: "<<RESET; cin>>cgpa;
    cout<<WHITE<<"Salary (LPA): "<<RESET; cin>>salary;

    ofstream f("jobs.txt",ios::app);
    f<<company<<","<<role<<","<<branch<<","<<cgpa<<","<<salary<<",Approved\n";
    f.close();
    cout<<GREEN<<"Job Posted Successfully!\n"<<RESET;
}

void Recruiter::viewMyJobs(){
    ifstream f("jobs.txt"); string line, comp, role, branch, status; float cgpa, salary;
    cout << BLUE;
printCenter("===== My Posted Jobs =====");
cout << RESET;

    while(getline(f,line)){
        stringstream ss(line);
        getline(ss,comp,','); getline(ss,role,','); getline(ss,branch,','); ss>>cgpa; ss.ignore(); ss>>salary; ss.ignore(); getline(ss,status,',');
        if(comp==company){ cout<<"Role: "<<role<<" | Branch: "<<branch<<" | CGPA: "<<cgpa<<" | Salary: "<<salary<<" LPA | Status: "<<status<<"\n"; }
    }
    f.close();
}

void Recruiter::viewApplications(){
    ifstream f("applications.txt"); string line, stuEmail, comp, role, status; bool found=false;
    cout << BLUE;
printCenter("===== Applications =====");
cout << RESET;

    while(getline(f,line)){
        stringstream ss(line);
        getline(ss,stuEmail,','); getline(ss,comp,','); getline(ss,role,','); getline(ss,status,',');
        if(comp==company){ cout<<"Student: "<<stuEmail<<" | Role: "<<role<<" | Status: "<<status<<"\n"; found=true; }
    }
    if(!found) cout<<RED<<"No students have applied yet.\n"<<RESET;
    f.close();
}
void Recruiter::updateApplicationStatus(){

    vector<string> myJobs;
    ifstream f("jobs.txt");
    string line;

    // gets jobs posted by recruiter
    while(getline(f,line)){
        if(line.find(company)!=string::npos){

            stringstream ss(line);
            string comp, role;

            getline(ss,comp,',');
            getline(ss,role,',');

            myJobs.push_back(role);
        }
    }
    f.close();

    if(myJobs.empty()){
        cout<<"No Jobs Found.\n";
        return;
    }

    cout<<BLUE<<"\nSelect Job:\n"<<RESET;
    for(int i=0;i<myJobs.size();i++)
        cout<<i+1<<". "<<myJobs[i]<<endl;

    int choice;
    cin>>choice;

    string selRole = myJobs[choice-1];

    // ================= GET APPLICANTS =================

    vector<pair<string,string>> applicants;

    ifstream appFile("applications.txt");

    while(getline(appFile,line)){

        string email, comp, role, status;
        stringstream ss(line);

        getline(ss,email,',');
        getline(ss,comp,',');
        getline(ss,role,',');
        getline(ss,status,',');

        if(comp == company && role == selRole){

            ifstream stuFile("students.txt");
            string stuLine;

            while(getline(stuFile,stuLine)){

                string stuName, stuEmail;
                stringstream st(stuLine);

                getline(st,stuName,',');
                getline(st,stuEmail,',');

                if(stuEmail == email){
                    applicants.push_back({stuName,email});
                    break;
                }
            }

            stuFile.close();
        }
    }

    appFile.close();

    if(applicants.empty()){
        cout<<RED<<"No applications for this job.\n"<<RESET;
        return;
    }

    // ================= SHOW APPLICANTS =================

    cout<<WHITE<<"\nApplicants for "<<selRole<<":\n"<<RESET;

    for(int i=0;i<applicants.size();i++){
        cout<<i+1<<". "<<applicants[i].first<<" - "<<applicants[i].second<<endl;
    }

    int stuChoice;
    cout<<"Select Student: ";
    cin>>stuChoice;

    string stuEmail = applicants[stuChoice-1].second;

    cout<<"New Status (Selected/Rejected): ";
    string newStatus;
    cin>>newStatus;

    // ================= UPDATE STATUS =================

    ifstream in("applications.txt");
    ofstream temp("temp.txt");

    bool found=false;

    while(getline(in,line)){

        string email, comp, role, status;
        stringstream ss(line);

        getline(ss,email,',');
        getline(ss,comp,',');
        getline(ss,role,',');
        getline(ss,status,',');

        if(email==stuEmail && comp==company && role==selRole){

            temp<<email<<","<<comp<<","<<role<<","<<newStatus<<"\n";
            found=true;
        }
        else{
            temp<<line<<"\n";
        }
    }

    in.close();
    temp.close();

    remove("applications.txt");
    rename("temp.txt","applications.txt");

    if(found)
        cout<<GREEN<<"Status Updated Successfully!\n"<<RESET;
    else
        cout<<RED<<"Application not found!\n"<<RESET;
}

void Recruiter::deleteJob(){
    cin.ignore();
    cout<<WHITE<<"Enter Role to Delete: "<<RESET; string role; getline(cin,role);
    ifstream f("jobs.txt"); ofstream temp("temp.txt"); string line, compFile, roleFile;
    while(getline(f,line)){
        stringstream ss(line); getline(ss,compFile,','); getline(ss,roleFile,',');
        if(compFile==company && roleFile==role) continue;
        temp<<line<<"\n";
    }
    f.close(); temp.close(); remove("jobs.txt"); rename("temp.txt","jobs.txt");
    cout<<GREEN<<"Job Deleted Successfully!\n"<<RESET;
}
void showRecruiter(Recruiter r) {
    cout << "\n===== RECRUITER INFO =====\n";
    cout << "Company : " << r.company << endl;
    cout << "Name    : " << r.name << endl;
    cout << "Email   : " << r.email << endl;
}