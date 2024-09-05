// Transaction.cpp
#include "Transaction.h"

void Transaction::addItem(const Item& item, int quantity) {
    items.emplace_back(item, quantity);
}

double Transaction::getTotalAmount() const {
    double total = 0.0;
    for (const auto& [item, quantity] : items) {
        total += item.getPrice() * quantity;
    }
    return total;
}

void Transaction::clear() {
    items.clear();
}

const std::vector<std::pair<Item, int>>& Transaction::getItems() const {
    return items;
}