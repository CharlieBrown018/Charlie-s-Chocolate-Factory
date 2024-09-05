// FileHandler.h
#pragma once
#include <string>
#include <vector>
#include "../model/Item.h"

// FileHandler class manages all file operations
class FileHandler {
public:
    // Read inventory from a file
    static std::vector<Item> readInventory(const std::string& filename);
    
    // Write inventory to a file
    static void writeInventory(const std::string& filename, const std::vector<Item>& items);
    
    // Write transaction receipt to a file
    static void writeReceipt(const std::string& filename, const std::vector<std::pair<Item, int>>& items, double total, double cash, double change);
    
    // Ensure a file exists, create if it doesn't
    static void ensureFileExists(const std::string& filename);
};