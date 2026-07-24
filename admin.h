#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
using namespace std;

class Admin
{
private:
    string username;
    string password;

public:
    Admin();

    bool login();

    void menu();

    void viewStudents();
    void viewRecruiters();
    void viewJobs();
    void viewApplications();
    void deleteJob();
    void deleteStudent();
    void deleteRecruiter();  

};

#endif
