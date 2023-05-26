#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

int main() {
    string input, username, password;
    bool isLogged = false;
    while(true) {
        if(!isLogged) {
            cout << "Hello, would you like to \n1. Login\n2. Register\n3. Exit\n";
            getline(cin, input);

            if(input == "1") {
                cout << "Username: ";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);
                cout << "Succesfully logged in!\n";
                isLogged = true;
            }
            else if(input == "2") {
                cout << "Enter your new username: ";
                getline(cin, username);
                cout << "Enter your new password: ";
                getline(cin, password);
                string passrepeat;
                cout << "Enter your password again: ";
                getline(cin, passrepeat);
                if(password != passrepeat) {
                    cout << "Passwords don't match, failed to register\n";
                }
                else {
                    cout << "Successfully registered, now you can log in\n";
                }
            }
            else if(input == "3") {
                cout << "Exiting...\n";
                this_thread::sleep_for(1s);
                break;
            }
            else {
                cout << "Unknown command, try again\n";
            }
        }
        else {
            cout << "Hello " << username << "! Do you want to\n1. Log out\n2. Exit\n";
            getline(cin, input);
            if(input == "1") {
                isLogged = false;
                cout << "Succesfully logged out!\n";
            }
            else if(input == "2") {
                cout << "Exiting...\n";
                this_thread::sleep_for(1s);
                break;
            }
            else {
                cout << "Unknown command, try again\n";
            }
        }
        this_thread::sleep_for(1s);
        cout << '\n';
    }
    return 0;
}