// ShopController.h
#pragma once
#include "../model/Inventory.h"
#include "../model/Transaction.h"
#include "../view/ConsoleView.h"
#include "../util/FileHandler.h"

class ShopController {
public:
    ShopController(Inventory& inventory, ConsoleView& view);
    void run();

private:
    Inventory& inventory;
    Transaction currentTransaction;
    ConsoleView& view;

    void processTransaction();
    void processPayment();
    void generateReceipt(double cashReceived, double change);
};