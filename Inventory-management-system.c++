#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Item {
private:
    string itemId;
    string itemName;
    int itemQuantity;
    float itemPrice;
    string itemCategory;

public:
    Item() : itemId(""), itemName(""), itemQuantity(0), itemPrice(0.0), itemCategory("") {}
    Item(string id, string name, int quantity, float price, string category) 
        : itemId(id), itemName(name), itemQuantity(quantity), itemPrice(price), itemCategory(category) {}

    string getId() const { return itemId; }
    string getName() const { return itemName; }
    int getQuantity() const { return itemQuantity; }
    float getPrice() const { return itemPrice; }
    string getCategory() const { return itemCategory; }

    void setQuantity(int newQuantity) { itemQuantity = newQuantity; }
    void setPrice(float newPrice) { itemPrice = newPrice; }

    void display() const {
        cout << itemId << "\t" << itemName << "\t" << itemQuantity << "\t\t" << itemPrice << "\t" << itemCategory << endl;
    }
};

class Inventory {
private:
    static const int maxItems = 100;
    Item items[maxItems];  
    int itemCount;
    string categories[3] = {"FRUITS", "VEGETABLES", "DAIRY"};

public:
    Inventory() : itemCount(0) {}

    string toUpperCase(const string &str) {
        string result = str;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                result[i] = str[i] - ('a' - 'A');
            }
        }
        return result;
    }

    void displayCategories() {
        cout << "Available Categories:\n";
        for (const auto &category : categories) {
            cout << "- " << category << endl;
        }
    }

    bool findCategory(const string &category) {
        string upperCategory = toUpperCase(category);
        for (int i = 0; i < 3; ++i) {
            if (categories[i] == upperCategory) {
                return true;
            }
        }
        return false;
    }

    Item* findItemByID(const string &id) {
        for (int i = 0; i < itemCount; ++i) {
            if (items[i].getId() == toUpperCase(id)) {
                return &items[i];
            }
        }
        return nullptr;
    }

    void addItem() {
        if (itemCount >= maxItems) {
            cout << "Inventory is full!" << endl;
            return;
        }

        string itemId, itemName, itemCategory;
        int itemQuantity;
        float itemPrice;

        displayCategories();
        cout << "Enter Category: ";
        cin >> itemCategory;
        itemCategory = toUpperCase(itemCategory);

        if (!findCategory(itemCategory)) {
            cout << "Category " << itemCategory << " does not exist!" << endl;
            return;
        }

        cout << "Enter ID: ";
        cin >> itemId;
        itemId = toUpperCase(itemId);
        cout << "Enter Name: ";
        cin >> itemName;

        while (true) {
            cout << "Enter Quantity: ";
            cin >> itemQuantity;
            if (cin.fail()) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "Invalid input. Please enter a number." << endl;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                break;
            }
        }

        while (true) {
            cout << "Enter Price: ";
            cin >> itemPrice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number." << endl;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        items[itemCount] = Item(itemId, itemName, itemQuantity, itemPrice, itemCategory);
        itemCount++;
        cout << "Item added successfully!" << endl;

        cout << "Press Enter to go back to the main menu..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cin.get();  
    }

    void updateItem() {
        string itemId;
        cout << "Enter ID: ";
        cin >> itemId;
        itemId = toUpperCase(itemId);

        Item* item = findItemByID(itemId);
        if (!item) {
            cout << "Item not found!" << endl;
            return;
        }

        int choice;
        cout << "What would you like to update?\n1. Quantity\n2. Price\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            int newQuantity;
            while (true) {
                cout << "Enter new Quantity: ";
                cin >> newQuantity;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number." << endl;
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    item->setQuantity(newQuantity);
                    cout << "Quantity of Item " << item->getName() << " is updated to " << newQuantity << endl;
                    break;
                }
            }
        } else if (choice == 2) {
            float newPrice;
            while (true) {
                cout << "Enter new Price: ";
                cin >> newPrice;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number." << endl;
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    item->setPrice(newPrice);
                    cout << "Price of Item " << item->getName() << " is updated to " << newPrice << endl;
                    break;
                }
            }
        } else {
            cout << "Invalid choice!" << endl;
        }

        cout << "Press Enter to go back to the main menu..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cin.get();  
    }

    void removeItem() {
        string itemId;
        cout << "Enter ID: ";
        cin >> itemId;
        itemId = toUpperCase(itemId);

        for (int i = 0; i < itemCount; ++i) {
            if (items[i].getId() == itemId) {
                cout << "Item " << items[i].getName() << " has been removed from the inventory" << endl;
                for (int j = i; j < itemCount - 1; ++j) {
                    items[j] = items[j + 1];
                }
                itemCount--;
                break;
            }
        }

        cout << "Press Enter to go back to the main menu..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cin.get();  
    }

    void displayItemsByCategory() {
        displayCategories();
        string itemCategory;
        cout << "Enter Category: ";
        cin >> itemCategory;
        itemCategory = toUpperCase(itemCategory);

        if (!findCategory(itemCategory)) {
            cout << "Category " << itemCategory << " does not exist!" << endl;
            return;
        }

        cout << "ID\tName\tQuantity\tPrice" << endl;  
        for (int i = 0; i < itemCount; ++i) {
            if (items[i].getCategory() == itemCategory) {
                cout << items[i].getId() << "\t" 
                     << items[i].getName() << "\t" 
                     << items[i].getQuantity() << "\t" 
                     << items[i].getPrice() << endl;
            }
        }

        cout << "Press Enter to go back to the main menu..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cin.get();  
    }

    void displayAllItems() {
        cout << "ID\tName\tQuantity\tPrice\tCategory" << endl;
        for (int i = 0; i < itemCount; ++i) {
            items[i].display();
        }

        cout << "Press Enter to go back to the main menu..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cin.get();  
    }

    void searchItem() {
        string itemId;
        cout << "Enter ID: ";
        cin >> itemId;
        itemId = toUpperCase(itemId);

        Item* item = findItemByID(itemId);
        if (item) {
            cout << "ID: " << item->getId() << ", Name: " << item->getName()
                 << ", Quantity: " << item->getQuantity() << ", Price: " << item->getPrice()
                 << ", Category: " << item->getCategory() << endl;
        } else {
            cout << "Item not found!" << endl;
        }

        cout << "Press Enter to go back to the main menu..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cin.get();  
    }
};

int main() {
    Inventory inventory;
    int choice;

    do {
        cout << "Inventory Management System\n";
        cout << "1. Add Item\n";
        cout << "2. Update Item\n";
        cout << "3. Remove Item\n";
        cout << "4. Display Items by Category\n";
        cout << "5. Display All Items\n";
        cout << "6. Search Item by ID\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                inventory.addItem();
                break;
            case 2:
                inventory.updateItem();
                break;
            case 3:
                inventory.removeItem();
                break;
            case 4:
                inventory.displayItemsByCategory();
                break;
            case 5:
                inventory.displayAllItems();
                break;
            case 6:
                inventory.searchItem();
                break;
            case 0:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
