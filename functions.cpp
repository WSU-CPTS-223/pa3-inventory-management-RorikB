#include "functions.h"

void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
    cout << " Use :quit to quit the REPL" << endl;
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}

void evalCommand(string line, avl_map<string, Data>& inventoryMap)
{
    if (line == ":help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        // Extract the inventory ID from the command
        string inventoryId = line.substr(5); // Skip "find " (4 chars + space)
        findInventoryById(inventoryId, inventoryMap);
    }
    // if line starts with listInventory
    else if (line.rfind("listInventory") == 0)
    {
        // Look up the appropriate datastructure to find all inventory belonging to a specific category
        cout << "YET TO IMPLEMENT!" << endl;
    }
}

void bootStrap(avl_map<string, Data>& inventoryMap)
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";
    // TODO: Do all your bootstrap operations here
    // example: reading from CSV and initializing the data structures
    // Don't dump all code into this single function
    // use proper programming practices
    
    // avl_map<string, Data> inventoryMap;
    parseCSVfile(inventoryMap);
}

// Parse the command line arguments and load data from CSV file into appropriate data structures
void parseCSVfile(avl_map<string, Data>& inventoryMap) {
    ifstream file("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data-1.csv");
    if (!file.is_open()) {
        cerr << "Error opening file: marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data-1.csv" << endl;
        return;
    }

    // avl_map<string, Data> inventoryMap; // AVL map to store inventory data

    string line;
    bool inQuotes = false; 

    // Read the header line
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string productId, productName, category;

        // Parse a CSV line into a list of strings that may have quoted commas
        std::vector<string> parsedValues;
        string current; // Current field being parsed
        for (char c : line) {
            if (c == '\r' || c == '\n') continue; // Skip new line characters
            else if (c == '\"') { 
                inQuotes = !inQuotes; // Toggle inQuotes state
                current += c; // Keep the quote character
            } else if (c == ',' && !inQuotes) {
                parsedValues.push_back(current);
                current.clear();
            } else {
                current += c;
            }
        }
        parsedValues.push_back(current); // Add the last value

        // Now assign parsed values to respective variables
        productId = parsedValues[0];
        productName = parsedValues[1];
        category = parsedValues[2];

        // Create Data object
        Data data(productName, category);
        // Insert into AVL map
        inventoryMap.insert(productId, data);
    }
    
    file.close();
}

// listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. 
// If the category doesn't exists, prints 'Invalid Category'.
void listInventoryByCategory(string category) {
    if (category.empty()) {
        cout << "Invalid category provided." << endl;
        return;
    }
}

// find <inventoryid> - Finds if a product exists whose ‘Uniq id’ matches the ‘inventoryid’. If
// it exists, print the details of the product. If not, print 'Inventory/Product not found’.
void findInventoryById(string inventoryId, avl_map<string, Data>& inventoryMap) {
    if (inventoryId.empty()) {
        cout << "Invalid inventory ID provided." << endl;
        return;
    }

    // Attempt to find the inventory in the AVL map
    auto it = inventoryMap.find(inventoryId);
    if (it != nullptr) {
        // Inventory found, print details
        cout << "Inventory found: " << endl;
        // Assuming Data class has appropriate getters
        cout << "Product Name: " << it->getProductName() << ", Category: " << it->getCategory() << endl;
    } else {
        // Inventory not found
        cout << "Inventory/Product not found." << endl;
    }
}