#include "admin.h"
#include <fstream>
#include <sstream>
#include "colors.h"
#include "utils.h"
#include <conio.h>

Admin::Admin()
{
    username = "admin@placement.com";
    password = "Admin12";
}

string getHiddenPassword() {
    string password;
    char ch;

    while(true){
        ch = _getch(); 

        if(ch == 13){ 
            cout << endl;
            break;
        }
        else if(ch == 8){ 
            if(!password.empty()){
                password.pop_back();
                cout << "\b \b"; 
            }
        }
        else{
            password.push_back(ch);
            cout << "*"; 
        }
    }
    return password;
}
bool Admin::login()
{
    string u, p;

    cout << BLUE << "Enter Admin email(must contain @):" << RESET;
    cin >> u;

    // ---------------- Hidden Password Input ----------------
    bool validPass = false;
    do {
        cout << BLUE << "Enter Admin Password (must contain at least 1 uppercase ,6-8 character and 1 digit): " << RESET;
        p = getHiddenPassword(); 

        bool hasUpper = false, hasDigit = false;
        for(char c : p){
            if(isupper(c)) hasUpper = true;
            if(isdigit(c)) hasDigit = true;
        }

        if(p.length() < 6){
            cout << RED << "Password must be at least 6-8characters!\n" << RESET;
        }
        else if(!hasUpper || !hasDigit){
            cout << RED << "Password must contain at least 1 uppercase and 1 digit!\n" << RESET;
        }
        else{
            validPass = true; 
        }
    } while(!validPass);

   
   

    // ---------------- Validate Username & Password ----------------
    if(u == username && p == password){
        cout << GREEN << "Login Successful!\n" << RESET;
        return true;
    }
    else{
        cout << RED << "Invalid Admin Credentials!\n" << RESET;
        return false;
    }
}

void Admin::menu()
{
    int choice;

    do
    {
       cout << CYAN;
printCenter("----- ADMIN MENU -----");
cout << RESET;

cout << WHITE;
printCenter("1. View Students");
printCenter("2. View Recruiters");
printCenter("3. View Jobs");
printCenter("4. View Applications");
printCenter("5. Delete Student");
printCenter("6. Delete Recruiter");
printCenter("7. Logout");
cout << RESET;


        cout <<"Enter choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: viewStudents(); break;
            case 2: viewRecruiters(); break;
            case 3: viewJobs(); break;
            case 4: viewApplications(); break;
            case 5: deleteStudent(); break;
            case 6: deleteRecruiter(); break;
            
        }

    } while(choice!=7);
}

void Admin::viewStudents()
{
    ifstream file("students.txt");
    string line;

cout << BLUE;
printCenter("--- STUDENTS ---");
cout << RESET;

    while(getline(file,line))
        cout<<line<<endl;

    file.close();
}

void Admin::viewRecruiters()
{
    ifstream file("recruiters.txt");
    string line;

    cout<<BLUE;
    printCenter("--- RECRUITERS ---");
    cout << RESET;

    while(getline(file,line))
        cout<<line<<endl;

    file.close();
}

void Admin::viewJobs()
{
    ifstream file("jobs.txt");
    string line;

    cout<<BLUE;
    printCenter("--- JOBS ---");
    cout << RESET;

    while(getline(file,line))
        cout<<line<<endl;

    file.close();
}

void Admin::viewApplications()
{
    ifstream file("applications.txt");
    string line;

    cout<<BLUE;
    printCenter("--- APPLICATIONS ---");
    cout << RESET;

    while(getline(file,line))
        cout<<line<<endl;

    file.close();
}

void Admin::deleteStudent()
{
    cout <<BLUE<< "Enter Student Email to Delete: "<<RESET;
    string email;
    cin >> email;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while(getline(file,line))
    {
        if(line.find(email) != string::npos)
        {
            found = true;   
            continue;       
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    if(found)
    {
        remove("students.txt");
        rename("temp.txt","students.txt");
        cout <<GREEN <<"Student Deleted Successfully!\n" << RESET;
    }
    else
    {
        remove("temp.txt");
        cout << RED << "Student Not Found!\n" << RESET;
    }
}

void Admin::deleteRecruiter()
{
    cout <<BLUE<< "Enter Recruiter Email to Delete: "<<RESET;
    string email;
    cin >> email;

    ifstream file("recruiters.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while(getline(file,line))
    {
        if(line.find(email) != string::npos)
        {
            found = true;
            continue;
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    if(found)
    {
        remove("recruiters.txt");
        rename("temp.txt","recruiters.txt");
        cout <<GREEN<< "Recruiter Deleted Successfully!\n" << RESET;
    }
    else
    {
        remove("temp.txt");
        cout << RED << "Recruiter Not Found!\n" << RESET;
    }
}

