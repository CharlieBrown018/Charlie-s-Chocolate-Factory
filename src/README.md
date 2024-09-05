## Project Overview

This Point of Sale (POS) system is designed for Charlie's Chocolate Factory. It allows users to select items from a menu, process transactions, and generate receipts. The system follows the Model-View-Controller (MVC) architectural pattern for better organization and maintainability.

## Key Components

### Model

1. **Item** (`Item.h`, `Item.cpp`)
   - Represents a single product in the shop.
   - Properties: code, name, price.
   - Methods: getCode(), getName(), getPrice().

2. **Inventory** (`Inventory.h`, `Inventory.cpp`)
   - Manages the collection of items in the shop.
   - Methods: 
     - loadFromFile(): Loads inventory from a file.
     - saveToFile(): Saves inventory to a file.
     - addItem(): Adds a new item to the inventory.
     - getItem(): Retrieves an item by its code.
     - getAllItems(): Returns all items in the inventory.

3. **Transaction** (`Transaction.h`, `Transaction.cpp`)
   - Represents a single purchase transaction.
   - Methods:
     - addItem(): Adds an item to the transaction.
     - getTotalAmount(): Calculates the total amount of the transaction.
     - clear(): Removes all items from the transaction.
     - getItems(): Returns all items in the transaction.

### View

**ConsoleView** (`ConsoleView.h`, `ConsoleView.cpp`)
- Handles all user interface operations.
- Key methods:
  - displayWelcome(): Shows welcome message.
  - displayMenu(): Displays the shop's menu.
  - getItemCode(), getQuantity(), getCashAmount(): Get user inputs.
  - displayChange(): Shows change amount in numbers and words.
  - displayReceipt(): Prints the transaction receipt.
  - displayChangeBreakdown(): Shows a breakdown of change by denomination.

### Controller

**ShopController** (`ShopController.h`, `ShopController.cpp`)
- Manages the flow of the application.
- Key methods:
  - run(): Main method to run the application.
  - processTransaction(): Handles a single transaction.
  - processPayment(): Manages the payment process.
  - generateReceipt(): Creates and displays the receipt.

### Utilities

1. **FileHandler** (`FileHandler.h`, `FileHandler.cpp`)
   - Manages all file operations.
   - Methods:
     - readInventory(): Reads inventory from a file.
     - writeInventory(): Writes inventory to a file.
     - writeReceipt(): Writes transaction receipt to a file.
     - ensureFileExists(): Checks if a file exists, creates it if it doesn't.

2. **ExceptionHandler** (`ExceptionHandler.h`)
   - Defines custom exceptions for the application.
   - Exceptions:
     - InputException: For input-related errors.
     - FileException: For file-related errors.

## Main Application Flow

1. The application starts in `main.cpp`.
2. It ensures the inventory file exists and loads the inventory.
3. It creates instances of ConsoleView and ShopController.
4. The main application loop runs in ShopController's run() method.
5. For each transaction:
   - The menu is displayed.
   - The user selects items and quantities.
   - The total is calculated and displayed.
   - The user provides payment.
   - Change is calculated and displayed.
   - A receipt is generated and saved.
6. The process repeats until the user chooses to exit.

## Error Handling

The application uses custom exceptions (InputException and FileException) to handle errors gracefully. These are caught in the main function, which displays appropriate error messages.

## File Operations

- The inventory is loaded from and saved to `data/inventory.txt`.
- Each transaction generates a receipt file named `receipt.txt`.

## Building the Project

The project uses CMake for building. To build the project:

1. Navigate to the project root directory.
2. Create a build directory: `mkdir build && cd build`
3. Run CMake: `cmake ..`
4. Build the project: `make`

## Future Enhancements

Potential areas for future improvement include:
1. Implementing a graphical user interface.
2. Adding user authentication for employees.
3. Implementing inventory management features.
4. Adding a database for persistent storage instead of text files.
5. Implementing a reporting system for sales analytics.