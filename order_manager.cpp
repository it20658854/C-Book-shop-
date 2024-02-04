#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "book_manager.h"  // Include book_manager functions
#include "order_manager.h"

using namespace std;

namespace OrderManager {

// Function to split a string by a delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<BookManager::Book> readBooks() {
    
}

// Function to calculate total price for an order
double calculateTotalPrice(const Order& order) {
    double totalPrice = 0.0;
    for (const string& isbn : order.bookIsbns) {
        BookManager::Book book;
        book = BookManager::searchBook(readBooks(), isbn);  // Specify the namespace
        if (!book.isbn.empty()) {
            totalPrice += book.price;
        } else {
            cout << "Book with ISBN " << isbn << " not found." << endl;
        }
    }
    return totalPrice;
}

// Function to generate quotation with discount
string generateQuotation(const Order& order, double discount) {
    double totalPrice = calculateTotalPrice(order);
    double discountedPrice = totalPrice - (totalPrice * discount);

    string quotation = "Quotation for " + order.schoolName + "\n";
    quotation += "Order Date: " + order.orderDate + "\n\n";
    quotation += "Book ISBN\tTitle\t\tPrice\n";
    for (const string& isbn : order.bookIsbns) {
        BookManager::Book book;
        book = BookManager::searchBook(readBooks(), isbn);  // Specify the namespace
        if (!book.isbn.empty()) {
            quotation += isbn + "\t" + book.title + "\t" + to_string(book.price) + "\n";
        }
    }
    quotation += "\nTotal Price: " + to_string(totalPrice) + "\n";
    quotation += "Discount: " + to_string(discount * 100) + "%\n";
    quotation += "Discounted Price: " + to_string(discountedPrice) + "\n";
    return quotation;
}

// Function to read orders from orders.txt
vector<Order> readOrders() {
    vector<Order> orders;
    ifstream file("data/orders.txt");

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // Parse the line into order attributes
            Order order;
            int pos = 0;
            string attribute;
            for (int i = 0; i < 3; i++) {
                pos = line.find(',', pos + 1);
                attribute = line.substr(0, pos);
                switch (i) {
                    case 0: order.schoolName = attribute; break;
                    case 1: order.orderDate = attribute; break;
                    case 2: order.bookIsbns = split(attribute, ','); break;
                }
                line = line.substr(pos + 1);
            }
            orders.push_back(order);
        }
        file.close();
    } else {
        cout << "Error opening orders.txt" << endl;
    }

    return orders;
}

// Function to display orders
void displayOrders(const vector<Order>& orders) {
    if (orders.empty()) {
        cout << "No orders found." << endl;
    } else {
        cout << "School Name\tOrder Date\tBooks\n";
        for (const Order& order : orders) {
            cout << order.schoolName << "\t" << order.orderDate << "\t";
            for (const string& isbn : order.bookIsbns) {
                cout << isbn << " ";
            }
            cout << endl;
        }
    }
}

// Function to get order details from the user and generate a quotation
void generateQuotationForOrder() {
    Order newOrder;

    cout << "Enter School Name: ";
    cin.ignore(); // Ignore newline character from previous input
    getline(cin, newOrder.schoolName);
    cout << "Enter Order Date (YYYY-MM-DD): ";
    cin >> newOrder.orderDate;

    int numBooks;
    cout << "Enter the number of books in the order: ";
    cin >> numBooks;

    cout << "Enter ISBNs of books (separated by spaces): ";
    for (int i = 0; numBooks > 0; ++i) {
        string isbn;
        cin >> isbn;
        newOrder.bookIsbns.push_back(isbn);
        numBooks--;
    }

    // Display the generated quotation
    double discount;
    cout << "Enter Discount Percentage: ";
    cin >> discount;

    string quotation = generateQuotation(newOrder, discount);
    cout << "Generated Quotation:\n" << quotation << endl;

    // Append the new order to orders.txt
    ofstream file("data/orders.txt", ios::app);
    if (file.is_open()) {
        file << newOrder.schoolName << "," << newOrder.orderDate << ",";
        for (const string& isbn : newOrder.bookIsbns) {
            file << isbn << ",";
        }
        file << endl;
        file.close();
        cout << "Order added successfully!" << endl;
    } else {
        cout << "Error adding order to file" << endl;
    }
}

} // namespace OrderManager
