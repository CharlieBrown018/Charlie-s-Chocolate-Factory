// FileHandler.cpp
#include "FileHandler.h"
#include "ExceptionHandler.h"
#include <fstream>
#include <sstream>
#include <iomanip>

std::vector<Item> FileHandler::readInventory(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw FileException("Unable to open inventory file: " + filename);
    }

    std::vector<Item> items;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int code;
        std::string name;
        double price;
        if (iss >> code >> std::ws && std::getline(iss >> std::ws, name, ':') && iss >> price) {
            items.emplace_back(code, name, price);
        }
    }
    return items;
}

void FileHandler::writeInventory(const std::string& filename, const std::vector<Item>& items) {
    std::ofstream file(filename);
    if (!file) {
        throw FileException("Unable to open inventory file for writing: " + filename);
    }

    for (const auto& item : items) {
        file << item.getCode() << " " << item.getName() << " : " << std::fixed << std::setprecision(2) << item.getPrice() << std::endl;
    }
}

void FileHandler::writeReceipt(const std::string& filename, const std::vector<std::pair<Item, int>>& items, double total, double cash, double change) {
    std::ofstream file(filename);
    if (!file) {
        throw FileException("Unable to open receipt file for writing: " + filename);
    }

    file << "================ RECEIPT ================\n";
    for (const auto& [item, quantity] : items) {
        file << std::setw(20) << std::left << item.getName()
             << std::setw(5) << std::right << quantity
             << " x Php " << std::fixed << std::setprecision(2) << item.getPrice()
             << " = Php " << quantity * item.getPrice() << std::endl;
    }
    file << "----------------------------------------\n";
    file << "Total:                 Php " << std::fixed << std::setprecision(2) << total << std::endl;
    file << "Cash:                  Php " << cash << std::endl;
    file << "Change:                Php " << change << std::endl;
    file << "========================================\n";
}

void FileHandler::ensureFileExists(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::ofstream newFile(filename);
        if (!newFile) {
            throw FileException("Unable to create file: " + filename);
        }
    }
}