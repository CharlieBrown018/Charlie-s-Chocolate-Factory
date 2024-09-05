// Item.cpp
#include "Item.h"

Item::Item(int code, const std::string& name, double price)
    : code(code), name(name), price(price) {}

int Item::getCode() const { return code; }
std::string Item::getName() const { return name; }
double Item::getPrice() const { return price; }