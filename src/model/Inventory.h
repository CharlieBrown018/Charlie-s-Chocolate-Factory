// Inventory.h
#pragma once
#include <vector>
#include <memory>
#include "Item.h"

// Inventory class manages the collection of items in the shop
class Inventory {
public:
    // Load inventory from a file
    void loadFromFile(const std::string& filename);
    
    // Save inventory to a file
    void saveToFile(const std::string& filename) const;
    
    // Add a new item to the inventory
    void addItem(const Item& item);
    
    // Get an item by its code
    const Item* getItem(int code) const;
    
    // Get all items in the inventory
    std::vector<Item> getAllItems() const;

private:
    std::vector<std::unique_ptr<Item>> items;  // Collection of items using smart pointers
};