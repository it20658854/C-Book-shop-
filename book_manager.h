#ifndef BOOK_MANAGER_H
#define BOOK_MANAGER_H

#include <string>
#include <vector>

namespace BookManager {
    // Book structure
    struct Book {
        std::string isbn;
        std::string title;
        std::string author;
        double price;
        int quantity;
    };

    // Function declarations
    void addBook(const Book& book);
    void displayBooks(const std::vector<Book>& books);
    Book searchBook(const std::vector<Book>& books, const std::string& isbn); 
    void addNewBook();
    void searchBookByISBN();
    std::vector<Book> readBooks();

    
}

#endif // BOOK_MANAGER_H
