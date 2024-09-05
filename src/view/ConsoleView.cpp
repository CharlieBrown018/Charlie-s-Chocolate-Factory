// ConsoleView.cpp
#include "ConsoleView.h"
#include "../util/ExceptionHandler.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

ConsoleView::ConsoleView()
{
#ifdef _WIN32
    // Enable ANSI escape codes on Windows
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    colorSupported = SetConsoleMode(hOut, dwMode);
#else
    colorSupported = true;
#endif
}

void ConsoleView::displayWelcome() const
{
    clearScreen();
    displayLogo();
    displayLine('=', 60);
    std::cout << centerText("Welcome to Charlie's Chocolate Factory", 60) << std::endl;
    displayLine('=', 60);
    std::cout << std::endl;
}

void ConsoleView::displayMenu(const std::vector<Item> &items) const
{
    setColor(COLOR_CYAN);
    std::cout << centerText("Our Delightful Selection", 70) << std::endl;
    resetColor();
    displayLine('=', 70);
    setColor(COLOR_YELLOW);
    std::cout << std::left << std::setw(10) << "Code"
              << std::setw(40) << "Description"
              << std::right << std::setw(20) << "Price (PHP)" << std::endl;
    resetColor();
    displayLine('-', 70);

    for (const auto &item : items)
    {
        std::cout << std::left << std::setw(10) << item.getCode()
                  << std::setw(40) << item.getName()
                  << std::right << std::setw(20) << std::fixed << std::setprecision(2) << item.getPrice() << std::endl;
    }
    displayLine('=', 70);
    std::cout << std::endl;
}

void ConsoleView::displayTotal(double total) const
{
    setColor(COLOR_GREEN);
    std::cout << "Total amount due: PHP " << std::fixed << std::setprecision(2) << total << std::endl;
    resetColor();
}

int ConsoleView::getItemCode() const
{
    int code;
    std::cout << "Enter item code (0 to finish): ";
    std::cin >> code;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InputException("Invalid input. Please enter a number.");
    }
    return code;
}

int ConsoleView::getQuantity() const
{
    int quantity;
    std::cout << "Enter quantity: ";
    std::cin >> quantity;
    if (std::cin.fail() || quantity <= 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InputException("Invalid quantity. Please enter a positive number.");
    }
    return quantity;
}

double ConsoleView::getCashAmount() const
{
    double cash;
    std::cout << "Cash to pay: PHP ";
    std::cin >> cash;
    if (std::cin.fail() || cash < 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InputException("Invalid cash amount. Please enter a non-negative number.");
    }
    return cash;
}

void ConsoleView::displayChange(double change) const
{
    setColor(COLOR_GREEN);
    std::cout << "Change: PHP " << std::fixed << std::setprecision(2) << change << std::endl;
    std::cout << "(" << numberToWords(static_cast<int>(change)) << " pesos and "
              << decimalToWords(static_cast<int>(std::round((change - static_cast<int>(change)) * 100)))
              << " centavos)" << std::endl;
    resetColor();
}

void ConsoleView::displayError(const std::string &message) const
{
    setColor(COLOR_RED);
    std::cerr << "Error: " << message << std::endl;
    resetColor();
}

void ConsoleView::displayReceipt(const std::vector<std::pair<Item, int>> &items, double total, double cash, double change) const
{
    clearScreen();
    setColor(COLOR_CYAN);
    std::cout << centerText("Charlie's Chocolate Factory", 60) << std::endl;
    std::cout << centerText("Receipt", 60) << std::endl;
    resetColor();
    displayLine('=', 60);

    for (const auto &[item, quantity] : items)
    {
        std::cout << std::left << std::setw(30) << item.getName()
                  << std::right << std::setw(5) << quantity
                  << " x PHP " << std::setw(8) << std::fixed << std::setprecision(2) << item.getPrice()
                  << " = PHP " << std::setw(8) << quantity * item.getPrice() << std::endl;
    }
    displayLine('-', 60);
    std::cout << std::right << std::setw(45) << "Subtotal: PHP " << std::setw(8) << total << std::endl;
    std::cout << std::right << std::setw(45) << "Cash: PHP " << std::setw(8) << cash << std::endl;
    std::cout << std::right << std::setw(45) << "Change: PHP " << std::setw(8) << change << std::endl;
    displayLine('=', 60);
    std::cout << std::endl
              << centerText("Thank you for your purchase!", 60) << std::endl;
    std::cout << centerText("Please come again!", 60) << std::endl
              << std::endl;
}

void ConsoleView::displayChangeBreakdown(double change) const
{
    int changeInCents = static_cast<int>(std::round(change * 100));
    int denominations[] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 25, 10, 5, 1};
    std::string denominationNames[] = {"100", "50", "20", "10", "5", "2", "1", "0.50", "0.25", "0.10", "0.05", "0.01"};

    setColor(COLOR_YELLOW);
    std::cout << centerText("Change Breakdown", 40) << std::endl;
    resetColor();
    displayLine('-', 40);

    for (int i = 0; i < 12; ++i)
    {
        int count = changeInCents / denominations[i];
        if (count > 0)
        {
            std::cout << std::setw(10) << std::left << denominationNames[i]
                      << std::setw(5) << std::right << count
                      << " x PHP " << std::setw(8) << std::fixed << std::setprecision(2)
                      << (denominations[i] / 100.0) << std::endl;
            changeInCents %= denominations[i];
        }
    }
    displayLine('-', 40);
    std::cout << std::endl;
}

void ConsoleView::displayLine(char symbol, int length) const
{
    std::cout << std::string(length, symbol) << std::endl;
}

std::string ConsoleView::numberToWords(int number) const
{
    static const char *const ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
                                       "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    static const char *const tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    if (number == 0)
        return "zero";

    if (number < 20)
        return ones[number];

    if (number < 100)
    {
        std::string result = tens[number / 10];
        if (number % 10)
        {
            result += " " + std::string(ones[number % 10]);
        }
        return result;
    }

    if (number < 1000)
    {
        std::string result = std::string(ones[number / 100]) + " hundred";
        if (number % 100)
        {
            result += " " + numberToWords(number % 100);
        }
        return result;
    }

    std::string result = numberToWords(number / 1000) + " thousand";
    if (number % 1000)
    {
        result += " " + numberToWords(number % 1000);
    }
    return result;
}

std::string ConsoleView::decimalToWords(int decimal) const
{
    if (decimal == 0)
        return "zero";
    return numberToWords(decimal);
}

void ConsoleView::setColor(int color) const
{
    if (colorSupported)
    {
        std::cout << "\033[" << color << "m";
    }
}

void ConsoleView::resetColor() const
{
    if (colorSupported)
    {
        std::cout << "\033[0m";
    }
}

std::string ConsoleView::centerText(const std::string &text, int width) const
{
    int padding = width - text.length();
    if (padding <= 0)
        return text;
    int leftPadding = padding / 2;
    int rightPadding = padding - leftPadding;
    return std::string(leftPadding, ' ') + text + std::string(rightPadding, ' ');
}

void ConsoleView::clearScreen() const
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void ConsoleView::displayLogo() const
{
    setColor(COLOR_YELLOW);
    std::cout << R"(
   _____ _                _ _      _     
  / ____| |              | (_)    ( )    
 | |    | |__   __ _ _ __| |_  ___|/ ___ 
 | |    | '_ \ / _` | '__| | |/ _ \ / __|
 | |____| | | | (_| | |  | | |  __/ \__ \
  \_____|_| |_|\__,_|_|  |_|_|\___| |___/
                                         
     Chocolate Factory
)" << std::endl;
    resetColor();
}

void ConsoleView::displayDetailedChangeBreakdown(double change) const
{
    std::vector<ChangeDenomination> breakdown = calculateChangeBreakdown(change);

    setColor(COLOR_CYAN);
    std::cout << "\n ================ CHANGE BREAKDOWN =================" << std::endl;
    resetColor();

    for (const auto &denom : breakdown)
    {
        std::cout << std::setw(16) << std::right << denom.value << " "
                  << std::setw(10) << denom.count
                  << std::setw(10) << std::fixed << std::setprecision(2)
                  << (denom.value * denom.count) << std::endl;
    }
    std::cout << std::endl;
}

std::vector<ConsoleView::ChangeDenomination> ConsoleView::calculateChangeBreakdown(double change) const
{
    std::vector<double> denominations = {1000, 500, 200, 100, 50, 20, 10, 5, 1, 0.25, 0.10, 0.05};
    std::vector<ChangeDenomination> breakdown;

    int changeInCents = static_cast<int>(std::round(change * 100));

    for (double denom : denominations)
    {
        int denomInCents = static_cast<int>(std::round(denom * 100));
        int count = changeInCents / denomInCents;
        if (count > 0)
        {
            breakdown.push_back({denom, count});
            changeInCents %= denomInCents;
        }
    }

    return breakdown;
}

std::string ConsoleView::getOutputFilename() const
{
    std::string filename;
    std::cout << "  Please enter the name of the file you wish to print to: ";
    std::cin >> filename;
    return filename;
}

void ConsoleView::displayFileWriteSuccess(const std::string &filename) const
{
    setColor(COLOR_GREEN);
    std::cout << std::endl
              << "  Print to " << filename << " was successful." << std::endl
              << std::endl;
    resetColor();
}

void ConsoleView::displayFarewell() const
{
    setColor(COLOR_YELLOW);
    std::cout << " ============== Thank you for purchase! ============" << std::endl;
    std::cout << " ======== Come back to the Factory again :D ========" << std::endl;
    std::cout << " ================== Have a great day! ==============" << std::endl;
    resetColor();
}

bool ConsoleView::askForAnotherTransaction() const
{
    char response;
    std::cout << "  Do you want to have another transaction? (y/n): ";
    std::cin >> response;
    std::cout << std::endl;
    return (response == 'y' || response == 'Y');
}