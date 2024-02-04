#include "user_manager.h"
#include <iostream>

namespace UserManager {

User validUser = {"admin", "password123"};

bool checkCredentials(const std::string& username, const std::string& password) {
    bool isUsernameCorrect = (username == validUser.username);
    bool isPasswordCorrect = (password == validUser.password);

    // Display login result messages
    displayLoginResult(isUsernameCorrect, isPasswordCorrect);

    return (isUsernameCorrect && isPasswordCorrect);
}

void displayLoginResult(bool isUsernameCorrect, bool isPasswordCorrect) {
    if (!isUsernameCorrect && isPasswordCorrect) {
        std::cout << "Invalid username. Please try again with a correct username." << std::endl;
    } else if (isUsernameCorrect && !isPasswordCorrect) {
        std::cout << "Invalid password. Please try again with a correct password." << std::endl;
    } else if (!isUsernameCorrect && !isPasswordCorrect) {
        std::cout << "Invalid username and password. Please try again with correct credentials." << std::endl;
    }
}

} // namespace UserManager
