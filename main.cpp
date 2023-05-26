#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;


int main() {
    connection c("user = kmigel password = qwerty hostaddr=127.0.0.1 port=5432 dbname = loginform");
    if(!c.is_open()) {
        cout << "Can't open database\n";
        return 1;
    }
    string input, username, password, sql;
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

                sql = "SELECT password FROM users WHERE username = '" + username + "';";
                work W(c);
                result R = W.exec(sql);
                
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
                    sql = "SELECT username FROM users WHERE username = '" + username + "';";
                    work W(c);
                    result R = W.exec(sql);
                    if(R.size() == 0) {
                        sql = "INSERT INTO users(username, password) VALUES('" + username + "', '" + password + "');";
                        W.exec(sql);
                        W.commit();

                        cout << "Successfully registered, now you can log in\n";
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

    c.disconnect();
    return 0;
}