#include <string>
#include <iostream>
using namespace std;

class User
{
private:
    string firstname;
    string surname;
    string username;
    string password;
    bool isAdmin;

public:
    User(){}
    User(string firstname, string surname, string username, string password, bool isAdmin)
        : firstname(firstname), surname(surname), username(username), password(password), isAdmin(isAdmin) {}

    const string& getFirstname() const {
        return firstname;
    }
    const string& getSurname() const {
        return surname;
    }
    const string& getUsername() const {
        return username;
    }
    const string& getPassword() const {
        return password;
    }
    bool getRole() const {
        return isAdmin;
    }

    void toggleRole() {
        isAdmin = !isAdmin;
    }

    void printUser() {
        cout << "Firstname: " << firstname << ", Surname: " << surname << ", Username: " << username << ", Role: " << (isAdmin ? "Admin" : "User") << endl;
    }
    
};
