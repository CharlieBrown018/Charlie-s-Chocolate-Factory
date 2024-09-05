// ShopController.cpp
#include "ShopController.h"
#include "../util/ExceptionHandler.h"
#include "../util/FileHandler.h"
#include <stdexcept>

ShopController::ShopController(Inventory &inventory, ConsoleView &view)
    : inventory(inventory), view(view) {}

void ShopController::run()
{
    view.displayWelcome();
    do
    {
        view.displayMenu(inventory.getAllItems());
        processTransaction();
        processPayment();
    } while (view.askForAnotherTransaction());
    view.displayFarewell();
}

void ShopController::processTransaction()
{
    currentTransaction.clear();
    while (true)
    {
        try
        {
            int code = view.getItemCode();
            if (code == 0)
                break;

            const Item *item = inventory.getItem(code);
            if (!item)
            {
                view.displayError("Invalid item code. Please try again.");
                continue;
            }

            int quantity = view.getQuantity();
            currentTransaction.addItem(*item, quantity);
        }
        catch (const InputException &e)
        {
            view.displayError(e.what());
        }
    }
}

void ShopController::processPayment()
{
    double total = currentTransaction.getTotalAmount();
    view.displayTotal(total);

    while (true)
    {
        try
        {
            double cash = view.getCashAmount();
            if (cash < total)
            {
                view.displayError("Insufficient cash. Please enter an amount greater than or equal to the total.");
                continue;
            }
            double change = cash - total;
            view.displayChange(change);
            view.displayDetailedChangeBreakdown(change);
            generateReceipt(cash, change);
            break;
        }
        catch (const InputException &e)
        {
            view.displayError(e.what());
        }
    }
}

void ShopController::generateReceipt(double cashReceived, double change)
{
    view.displayReceipt(currentTransaction.getItems(), currentTransaction.getTotalAmount(), cashReceived, change);

    std::string filename = view.getOutputFilename();
    try
    {
        FileHandler::writeReceipt(filename, currentTransaction.getItems(), currentTransaction.getTotalAmount(), cashReceived, change);
        view.displayFileWriteSuccess(filename);
    }
    catch (const FileException &e)
    {
        view.displayError(e.what());
    }
}