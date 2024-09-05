// Inventory.cpp
#include "Inventory.h"
#include "../util/FileHandler.h"
#include "../util/ExceptionHandler.h"
#include <algorithm>

void Inventory::loadFromFile(const std::string& filename) {
    items.clear();  // Clear existing items before loading
    auto loadedItems = FileHandler::readInventory(filename);
    for (const auto& item : loadedItems) {
        items.push_back(std::make_unique<Item>(item));
    }
}

void Inventory::saveToFile(const std::string& filename) const {
    std::vector<Item> itemsToSave;
    for (const auto& item : items) {
        itemsToSave.push_back(*item);
    }
    FileHandler::writeInventory(filename, itemsToSave);
}

void Inventory::addItem(const Item& item) {
    items.push_back(std::make_unique<Item>(item));
}

const Item* Inventory::getItem(int code) const {
    auto it = std::find_if(items.begin(), items.end(),
                           [code](const auto& item) { return item->getCode() == code; });
    return it != items.end() ? it->get() : nullptr;
}

std::vector<Item> Inventory::getAllItems() const {
    std::vector<Item> allItems;
    for (const auto& item : items) {
        allItems.push_back(*item);
    }
    return allItems;
}