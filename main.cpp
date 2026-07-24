#include <iostream>
#include "student.h"
#include "recruiter.h"
#include "admin.h"
#include "colors.h"
#include <windows.h>
#include "utils.h"

using namespace std;



int main() {

    Student studentObj;
    Recruiter recruiterObj;
    Admin adminObj;

    int choice;

    do {
         cout<< PINK << BOLD;


printCenter("=================================");
printCenter("           PlaceMate             ");
printCenter("   Smart Placement Portal System");
printCenter("=================================");

cout << RESET;


        cout << WHITE;

printCenter("1. Student");
printCenter("2. Recruiter");
printCenter("3. Admin");
printCenter("4. Exit");

cout << RESET;



        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                studentObj.studentMenu();
                break;

            case 2:
                recruiterObj.recruiterMenu();
                break;

            case 3:
                if(adminObj.login())
                    adminObj.menu();
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 4);

    return 0;
}