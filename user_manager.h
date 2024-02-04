#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>

namespace UserManager {
    struct User {
        std::string username;
        std::string password;
    };

    // Function to check user credentials
    bool checkCredentials(const std::string& username, const std::string& password);


     void displayLoginResult(bool isUsernameCorrect, bool isPasswordCorrect);

     void registerUser(const std::string& username, const std::string& password);
}

#endif // USER_MANAGER_H
