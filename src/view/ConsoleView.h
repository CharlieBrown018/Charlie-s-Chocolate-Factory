// ConsoleView.h
#pragma once
#include <vector>
#include <string>
#include "../model/Item.h"

class ConsoleView {
public:
    ConsoleView();
    void displayWelcome() const;
    void displayMenu(const std::vector<Item>& items) const;
    void displayTotal(double total) const;
    int getItemCode() const;
    int getQuantity() const;
    double getCashAmount() const;
    void displayChange(double change) const;
    void displayError(const std::string& message) const;
    bool askForAnotherTransaction() const;
    void displayReceipt(const std::vector<std::pair<Item, int>>& items, double total, double cash, double change) const;
    void displayDetailedChangeBreakdown(double change) const;
    void displayChangeBreakdown(double change) const;
    std::string getOutputFilename() const;
    void displayFileWriteSuccess(const std::string& filename) const;
    void displayFarewell() const;

private:
    struct ChangeDenomination {
        double value;
        int count;
    };

    void displayLine(char symbol = '-', int length = 50) const;
    std::string numberToWords(int number) const;
    std::string decimalToWords(int decimal) const;
    void setColor(int color) const;
    void resetColor() const;
    std::string centerText(const std::string& text, int width) const;
    void clearScreen() const;
    void displayLogo() const;
    std::vector<ChangeDenomination> calculateChangeBreakdown(double change) const;

    // ANSI color codes
    static const int COLOR_RED = 31;
    static const int COLOR_GREEN = 32;
    static const int COLOR_YELLOW = 33;
    static const int COLOR_BLUE = 34;
    static const int COLOR_MAGENTA = 35;
    static const int COLOR_CYAN = 36;
    static const int COLOR_WHITE = 37;

    bool colorSupported;
};