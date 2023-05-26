# Login and registration form
This is a console version of a login and registration form. You are able to register and then login into an account. You can also delete the account or logout.
## Features
- As a user
  - Register an account
  - Login into an account
  - Delete your own account
- As a superuser
  - To login into the superuser account use username "admin" and password "admin"
  - Register an ordinary account
  - Login into an account
  - View any account's password
  - Delete any account except the superuser account if you know their username
## Installation
First you need to download PostgreSQL.
```console
foo@bar:~$ sudo apt-get update
foo@bar:~$ sudo apt-get upgrade
foo@bar:~$ sudo apt-get install postgresql-15
```
Then you need to create a superuser (you can follow [this documentation](https://www.postgresql.org/docs/current/app-createuser.html)).
After you have done that, launch PostgreSQL using this command with your username instead of "yourusername".
```console
foo@bar:~$ psql --username=yourusername --dbname=postgres
```
Finally, you need to create a database that will be used in this login form.
```postgres
postgres=# CREATE DATABASE loginform;
postgres=# \c loginform
loginform=# CREATE TABLE users(id SERIAL PRIMARY KEY, username VARCHAR(50) NOT NULL UNIQUE, password VARCHAR(50) NOT NULL);
loginform=# INSERT INTO users(username, password) VALUES('admin', 'admin');
loginform=# exit
```
Now that you have finished setting up PostgreSQL, you can clone the repository and launch the loginForm file.
```console
foo@bar:~$ ./loginForm/loginForm
```
When you first launch the program you will be prompted for your postgres username, password, host address and port. This data will then be stored in userinfo.txt file and will be used for connecting to the loginform database.

## Built with
<ul>
  <li><img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++"></li>
  <li><img src="https://img.shields.io/badge/PostgreSQL-316192?style=for-the-badge&logo=postgresql&logoColor=white" alt="PostgreSQL"></li>
  <li>libpqxx library</li>
</ul>

## License
Copyright © 2023, [Kristina Migel](https://github.com/kmigel).
Released under the [MIT License](https://choosealicense.com/licenses/mit/).
