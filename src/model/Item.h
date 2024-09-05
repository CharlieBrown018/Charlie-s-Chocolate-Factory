// Item.h
#pragma once
#include <string>

// Item class represents a single product in the shop
class Item {
public:
    // Constructor to initialize an item with code, name, and price
    Item(int code, const std::string& name, double price);
    
    // Getter methods
    int getCode() const;
    std::string getName() const;
    double getPrice() const;

private:
    int code;           // Unique identifier for the item
    std::string name;   // Name of the item
    double price;       // Price of the item
};