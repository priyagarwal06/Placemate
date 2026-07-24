#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

// ---------- Masked Password Input ----------
inline string getPassword() {
    string password = "";
    char ch;

    while((ch = getch()) != '\r') { 
        if(ch == 8) {               
            if(!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << "*";
        }
    }
    cout << endl;
    return password;
}

// ---------- Password Validation ----------
inline string getValidatedPassword() {
    string password;
    do {
        password = getPassword();
        bool hasUpper = false, hasDigit = false;

        for(char c : password) {
            if(isupper(c)) hasUpper = true;
            if(isdigit(c)) hasDigit = true;
        }

        if(password.length() < 6 || password.length() > 8 || !hasUpper || !hasDigit) {
            cout << "Password must be 6-8 characters long, with at least 1 uppercase letter and 1 digit.\n";
        } else {
            break; 
        }
    } while(true);

    return password;
}

#endif