#ifndef RECRUITER_H
#define RECRUITER_H
#include <string>
using namespace std;

class Recruiter {
private:
    string name, company, email, contact;
    string password;

public:
    Recruiter();
    ~Recruiter();
    friend void showRecruiter(Recruiter r);

    void registerRecruiter();
    bool loginRecruiter();
    void recruiterDashboard();
    void postJob();
    void viewMyJobs();
    void viewApplications();
    void updateApplicationStatus();
    void deleteJob();
    void recruiterMenu();
};

#endif