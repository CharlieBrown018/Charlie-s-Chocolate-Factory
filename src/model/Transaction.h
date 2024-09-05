// Transaction.h
#pragma once
#include <vector>
#include "Item.h"

// Transaction class represents a single purchase transaction
class Transaction {
public:
    // Add an item to the transaction
    void addItem(const Item& item, int quantity);
    
    // Get the total amount of the transaction
    double getTotalAmount() const;
    
    // Clear all items from the transaction
    void clear();
    
    // Get all items in the transaction
    const std::vector<std::pair<Item, int>>& getItems() const;

private:
    std::vector<std::pair<Item, int>> items;  // Collection of items and their quantities
};
