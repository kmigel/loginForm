#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <pqxx/pqxx>
#include <fstream>

using namespace std;
using namespace pqxx;

int main() {
    ifstream userInfo("userinfo.txt");
    bool isFirstTime = !userInfo;
    string postuser, postpass, host, port;
    if(isFirstTime) {
        cout << "You are only asked this so the program can access the database that you have just created. If you haven't created any databases, close the program and follow instructions in README.md.\n";
        this_thread::sleep_for(1s);
        cout << "Write your postgres username: ";
        cin >> postuser;
        cout << "Write your postgres password: ";
        cin >> postpass;
        cout << "Write your host address: ";
        cin >> host;
        cout << "Write your port: ";
        cin >> port;

        ofstream out("userinfo.txt");
        out << postuser << '\n';
        out << postpass << '\n';
        out << host << '\n';
        out << port << '\n';
    }
    else {
        getline(userInfo, postuser);
        getline(userInfo, postpass);
        getline(userInfo, host);
        getline(userInfo, port);
    }

    connection c("user=" + postuser + " password=" + postpass + " hostaddr=" + host + " port=" + port + " dbname = loginform");
    if(!c.is_open()) {
        cout << "Can't open database\n";
        return 1;
    }
    string input, username, password;
    bool isLogged = false;
    while(true) {
        if(!isLogged) {
            cout << "Hello, would you like to \n1. Login\n2. Register\n3. Exit\n";
            cin >> input;

            if(input == "1") {
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                work W(c);
                result R = W.exec("SELECT password FROM users WHERE username = '" + W.esc(username) + "';");
                
                if(R.size() == 0) {
                    cout << "Username does not exist, failed to log in\n";
                }
                else if(R[0][0].as<string>() != password) {
                    cout << "Incorrect password, failed to log in\n";
                }
                else {
                    cout << "Succesfully logged in!\n";
                    isLogged = true;
                }
            }
            else if(input == "2") {
                cout << "Enter your new username: ";
                cin >> username;
                cout << "Enter your new password: ";
                cin >> password;
                string passrepeat;
                cout << "Enter your password again: ";
                cin >> passrepeat;
                if(password != passrepeat) {
                    cout << "Passwords don't match, failed to register\n";
                }
                else {
                    work W(c);
                    result R = W.exec("SELECT username FROM users WHERE username = '" + W.esc(username) + "';");

                    if(R.size() == 0) {
                        W.exec("INSERT INTO users(username, password) VALUES('" + W.esc(username) + "', '" + W.esc(password) + "');");
                        W.commit();

                        cout << "Successfully registered, you can now log in\n";
                    }
                    else {
                        cout << "User already exists, failed to register\n";
                    }
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
            cout << "Hello " << username << "! Do you want to\n1. Log out\n2. Delete account\n3. Exit\n";
            cin >> input;
            if(input == "1") {
                isLogged = false;
                cout << "Logging out...\n";
            }
            else if(input == "2") {
                cout << "Are you sure you want to continue? (y/n)";
                cin >> input;
                if(input == "y") {
                    cout << "Confirm your password: ";
                    cin >> password;    
                    work W(c);
                    result R = W.exec("SELECT password FROM users WHERE username = '" + W.esc(username) + "';");
                    
                    if(R[0][0].as<string>() != password) {
                        cout << "Incorrect password, failed to delete account\n";
                    }
                    else {
                        cout << "Deleting...";
                        W.exec("DELETE FROM users WHERE username = '" + W.esc(username) + "';");
                        W.exec("SELECT setval(pg_get_serial_sequence('users', 'id'), coalesce(max(id), 0) + 1, false) FROM users");
                        W.commit();
                        this_thread::sleep_for(1s);
                        cout << "Account successfully deleted\n";
                        isLogged = false;
                    }
                }
                else if(input == "n") {
                    cout << "Canceled\n";
                }
                else {
                    cout << "Unknown command, try again\n";
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
        this_thread::sleep_for(1s);
        cout << '\n';
    }

    c.disconnect();
    return 0;
}