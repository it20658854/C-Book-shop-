#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "book_manager.h"  

namespace OrderManager {

// Order structure
struct Order {
    std::string schoolName;
    std::string orderDate;
    std::vector<std::string> bookIsbns;
};

// Function to calculate total price for an order
double calculateTotalPrice(const Order& order);

// Function to generate quotation with discount
std::string generateQuotation(const Order& order, double discount);

// Function to read orders from orders.txt
std::vector<Order> readOrders();

// Function to display orders
void displayOrders(const std::vector<Order>& orders);

// Function to get order details from user and generate quotation
void generateQuotationForOrder();

std::vector<BookManager::Book> readBooks();


BookManager::Book searchBook(const std::vector<BookManager::Book>& books, const std::string& isbn);
} // namespace OrderManager

#endif // ORDER_MANAGER_H
