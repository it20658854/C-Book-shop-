#include <iostream>
#include "book_manager.h"
#include "order_manager.h"
#include "user_manager.h"

using namespace std;
using namespace UserManager;

// Function to display the login screen
void displayLoginScreen() {
    cout << "\n** User Login **" << endl;
}

// Function to get user input for login
User getLoginInput() {
    User user;
    cout << "Enter username: ";
    cin >> user.username;
    cout << "Enter password: ";
    cin >> user.password;
    return user;
}

// Function to handle login
bool handleLogin() {
    displayLoginScreen();
    User user = getLoginInput();

    if (checkCredentials(user.username, user.password)) {
        cout << "Login successful!" << endl;
        return true;
    } else {
        cout << "Invalid username or password. Please try again." << endl;
        return false;
    }
}

// Function to display the main menu
void displayMainMenu() {
    cout << "\n** Nethra Book Shop Management System **" << endl;
    cout << "1. Manage Books" << endl;
    cout << "2. Manage Orders" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to get user input for menu choices
int getMainMenuChoice() {
    int choice;
    cin >> choice;
    return choice;
}

int main() {
    // Perform login
    bool loggedIn = false;
    do {
        loggedIn = handleLogin();
    } while (!loggedIn);

    // Main menu
    while (true) {
        displayMainMenu();
        int mainMenuChoice = getMainMenuChoice();

        switch (mainMenuChoice) {
            case 1: {  // Manage Books
                int bookMenuChoice;
                do {
                    cout << "\n** Book Management Menu **" << endl;
                    cout << "1. View All Books" << endl;
                    cout << "2. Add a New Book" << endl;
                    cout << "3. Search for a Book" << endl;
                    cout << "4. Return to Main Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> bookMenuChoice;

                    switch (bookMenuChoice) {
                        case 1:
                            BookManager::displayBooks(BookManager::readBooks());
                            break;
                        case 2: {
                            // Get book details from user and add to file
                            BookManager::Book newBook;
                            cout << "Enter ISBN: ";
                            cin >> newBook.isbn;
                            cout << "Enter Title: ";
                            cin.ignore(); // Ignore newline character from previous input
                            getline(cin, newBook.title);
                            cout << "Enter Author: ";
                            getline(cin, newBook.author);
                            cout << "Enter Price: ";
                            cin >> newBook.price;
                            cout << "Enter Quantity: ";
                            cin >> newBook.quantity;

                            BookManager::addBook(newBook);
                            break;
                        }
                        case 3: {
                            // Get ISBN from user and search for book
                            string searchIsbn;
                            cout << "Enter ISBN to search: ";
                            cin >> searchIsbn;

                            BookManager::Book foundBook = BookManager::searchBook(BookManager::readBooks(), searchIsbn);
                            if (!foundBook.isbn.empty()) {
                                cout << "Book found:" << endl;
                                cout << "ISBN\t\tTitle\t\tAuthor\t\tPrice\tQuantity" << endl;
                                cout << foundBook.isbn << "\t" << foundBook.title << "\t"
                                     << foundBook.author << "\t" << foundBook.price << "\t"
                                     << foundBook.quantity << endl;
                            } else {
                                cout << "Book with ISBN " << searchIsbn << " not found." << endl;
                            }
                            break;
                        }
                        case 4:
                            cout << "Returning to Main Menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                } while (bookMenuChoice != 4);
                break;
            }
            case 2: {  // Manage Orders
                int orderMenuChoice;
                do {
                    cout << "\n** Order Management Menu **" << endl;
                    cout << "1. View All Orders" << endl;
                    cout << "2. Generate Quotation" << endl;
                    cout << "3. Return to Main Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> orderMenuChoice;

                    switch (orderMenuChoice) {
                        case 1:
                            OrderManager::displayOrders(OrderManager::readOrders());
                            break;
                        case 2:
                            OrderManager::generateQuotationForOrder();
                            break;
                        case 3:
                            cout << "Returning to Main Menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                } while (orderMenuChoice != 3);
                break;
            }
            case 3:  // Exit
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}