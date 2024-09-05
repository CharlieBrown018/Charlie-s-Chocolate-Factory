// main.cpp
#include "model/Inventory.h"
#include "view/ConsoleView.h"
#include "controller/ShopController.h"
#include "util/FileHandler.h"
#include "util/ExceptionHandler.h"
#include <iostream>

int main() {
    try {
        // Ensure the inventory file exists
        FileHandler::ensureFileExists("data/inventory.txt");
        
        // Create and load the inventory
        Inventory inventory;
        inventory.loadFromFile("data/inventory.txt");
        
        // Create the view
        ConsoleView view;
        
        // Create the controller
        ShopController controller(inventory, view);
        
        // Run the main application loop
        controller.run();
    } 
    catch (const InputException& e) {
        std::cerr << "Input error: " << e.what() << std::endl;
        return 1;
    } 
    catch (const FileException& e) {
        std::cerr << "File error: " << e.what() << std::endl;
        return 1;
    } 
    catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}