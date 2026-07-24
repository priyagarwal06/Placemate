#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using namespace std;

class Student {
private:
     string name, email, branch, phone, skills;
     float cgpa;
    string password;

public:
    Student();
    ~Student();
    friend void showStudent(Student s);

    void registerStudent();
    bool loginStudent();
    void studentDashboard();
    void viewProfile();
    void updateProfile();
    void viewEligibleJobs();
    void applyForJob();
    void viewAppliedJobs();
    void studentMenu();
};

#endif