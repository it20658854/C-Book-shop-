
#include "book_manager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>  // for search functionality

using namespace std;
namespace BookManager {


// Function to read books from books.txt
std::vector<Book> readBooks() {
    std::vector<Book> books;
    std::ifstream file("data/books.txt");

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            // Parse the line into book attributes
            Book book;
            int pos = 0;
            std::string attribute;
            for (int i = 0; i < 5; i++) {
                pos = line.find(',', pos + 1);
                attribute = line.substr(0, pos);
                switch (i) {
                    case 0: book.isbn = attribute; break;
                    case 1: book.title = attribute; break;
                    case 2: book.author = attribute; break;
                    case 3: book.price = stod(attribute); break;
                    case 4: book.quantity = stoi(attribute); break;
                }
                line = line.substr(pos + 1);
            }
            books.push_back(book);
        }
        file.close();
    } else {
       std:: cout << "Error opening books.txt" << endl;
    }

    return books;
}

// Function to add a new book
void addBook(const Book& book) {
    std::ofstream file("data/books.txt", std::ios::app);  // Append to the file
    if (file.is_open()) {
        file << book.isbn << "," << book.title << "," << book.author << ","
             << book.price << "," << book.quantity << std::endl;
        file.close();
        std::cout << "Book added successfully!" << std::endl;
    } else {
        std::cout << "Error adding book to file" << std::endl;
    }
}

// Function to display all books
void displayBooks(const std::vector<Book>& books) {
    if (books.empty()) {
        std::cout << "No books found." << std::endl;
    } else {
        std::cout << "ISBN\t\tTitle\t\tAuthor\t\tPrice\tQuantity" << std::endl;
        for (const Book& book : books) {
            std::cout << book.isbn << "\t" << book.title << "\t" << book.author
                 << "\t" << book.price << "\t" << book.quantity << std::endl;
        }
    }
}

// Function to search for a book by ISBN
 Book searchBook(const std::vector<Book>& books, const std::string& isbn) {
    auto it = std::find_if(books.begin(), books.end(),
                           [&isbn](const Book& book) { return book.isbn == isbn; });
    if (it != books.end()) {
        return *it;  // Return the found book
    } else {
        return Book{};  // Return an empty Book if not found
    }
}

// Function to get book details from user and add to file
void addNewBook() {
    Book newBook;

    std::cout << "Enter ISBN: ";
    std::cin >> newBook.isbn;
    std::cout << "Enter Title: ";
    std::cin.ignore(); // Ignore newline character from previous input
    std::getline(cin, newBook.title);
    std::cout << "Enter Author: ";
    std::getline(cin, newBook.author);
    std::cout << "Enter Price: ";
    std::cin >> newBook.price;
    std::cout << "Enter Quantity: ";
    std::cin >> newBook.quantity;

    addBook(newBook);  // Call the existing addBook function
}

// Function to search for a book by ISBN
void searchBookByISBN() {
    std::string isbn;
    std::cout << "Enter ISBN to search: ";
    std::cin >> isbn;

    Book foundBook = searchBook(readBooks(), isbn);

    if (!foundBook.isbn.empty()) {
        cout << "Book found:\n";
        cout << "ISBN\t\tTitle\t\tAuthor\t\tPrice\tQuantity\n";
        cout << foundBook.isbn << "\t" << foundBook.title << "\t" << foundBook.author
             << "\t" << foundBook.price << "\t" << foundBook.quantity << std::endl;
    } else {
        std::cout << "Book with ISBN " << isbn << " not found." << std::endl;
    }
}

int main() {
    while (true) {
        // Your existing main code

        int bookChoice;
        do {
            cout << "\n** Book Management Menu **" << endl;
            cout << "1. View All Books" << endl;
            cout << "2. Add a New Book" << endl;
            cout << "3. Search for a Book" << endl;
            cout << "4. Return to Main Menu" << endl;
            cout << "Enter your choice: ";
            cin >> bookChoice;

            switch (bookChoice) {
                case 1:
                    displayBooks(readBooks());
                    break;
                case 2:
                    addNewBook();
                    break;
                case 3:
                    searchBookByISBN();
                    break;
                case 4:
                    cout << "Returning to Main Menu..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (bookChoice != 4);
    }

    return 0;
}
}