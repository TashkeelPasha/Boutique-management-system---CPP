#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;
const int MAX_ITEMS = 100;

enum UserType { MANAGER, EMPLOYEE, CUSTOMER };
enum class OrderStatus { PENDING, PROCESSING, SHIPPED, DELIVERED };


class UserData {
public:
    string username;
    string password;
    string firstName;
    string lastName;
    UserType userType;
};


class BoutiqueManager {
    
public:

    void processOrders() {
        cout << "Processing orders...\n" << endl;
    }
};


class Entity {
protected:
    int id;

public:
    Entity(int id) : id(id) {}

    int getId() const { return id; }

    virtual void displayDetails() const = 0;

    friend void displayEntityDetails(const Entity& entity);
};


void displayEntityDetails(const Entity& entity) {
    cout << "ID: " << entity.id << endl;
}

class Customer : public Entity {
private:
    string name;
    string contactInfo;

public:
    Customer(int id, string name, string contactInfo) : Entity(id), name(name), contactInfo(contactInfo) {}


    string getName() const { return name; }
    string getContactInfo() const { return contactInfo; }


    void setName(const string &newName) { name = newName; }
    void setContactInfo(const string &newContactInfo) { contactInfo = newContactInfo; }


    void saveToFile(const string &filename) const {
        ofstream outFile(filename, ios::app);
        if (outFile.is_open()) {
            outFile << id << "," << name << "," << contactInfo << endl;
            cout << "============Customer data saved to file successfully. ==========\n" << endl;
        } else {
            throw runtime_error("Unable to open file.  :(  ");
        }
        outFile.close();
    }

    static Customer loadFromFile(const string &filename) {
        ifstream inFile(filename);
        int id;
        string name, contactInfo;
        if (inFile.is_open() && inFile.good()) {
            inFile >> id;
            inFile.ignore();
            getline(inFile, name, ',');
            getline(inFile, contactInfo);
            inFile.close();
            cout << "==========Customer data loaded from file successfully. ==========\n" << endl;
            return Customer(id, name, contactInfo);
        } else {
            throw runtime_error("Unable to open or read from file.\n");
        }
    }


    void displayDetails() const override {
        cout << "==========Customer ==========";
        displayEntityDetails(*this);
        cout << "Name: " << name << endl;
        cout << "Contact Info: " << contactInfo << endl;
    }
};
int display();

struct Employee {
    int id;
    string name;
    string role;
};


void addEmployee(Employee employee) {
    ofstream outFile("employees.txt", ios::app);
    if (outFile.is_open()) {
        outFile << employee.id << " " << employee.name << " " << employee.role << endl;
        cout << "Employee added successfully..... :)" << endl;
        outFile.close();
    } else {
        cerr << "Unable to open file.........:(\n" << endl;
    }
}
void removeEmployee(int id) {
    ifstream inFile("employees.txt");
    if (!inFile) {
        cerr << "Unable to open file......:(\n" << endl;
        return;
    }

    ofstream outFile("temp.txt");
    if (!outFile) {
        cerr << "Unable to open file........:(\n" << endl;
        inFile.close();
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        istringstream iss(line);
        int empId;
        string name, role;
        if (iss >> empId >> name >> role) {
            if (empId == id) {
                found = true;
                cout << "Employee with ID " << id << " removed successfully." << endl;
            } else {
                outFile << line << endl;
            }
        }
    }

    if (!found) {
        cerr << "Employee with ID " << id << " not found.........:(\n" << endl;
    }

    inFile.close();
    outFile.close();

    
    if (remove("employees.txt") != 0) {
        cerr << "Error deleting original file.........:(\n" << endl;
        return;
    }
    if (rename("temp.txt", "employees.txt") != 0) {
        cerr << "Error renaming temp file.........:(\n" << endl;
    }
}


void viewEmployees() {
    ifstream inFile("employees.txt");
    if (inFile.is_open()) {
        cout << "ID\tName\tRole" << endl;
        cout << "---------------------------------" << endl;
        int id;
        string name, role;
        while (inFile >> id >> name >> role) {
            cout << id << "\t" << name << "\t" << role << endl;
        }
        inFile.close();
    } else {
        cerr << "Unable to open file." << endl;
    }
}
    void updateEmployee(int id, const string& newName, const string& newRole) {
    ifstream inFile("employees.txt");
    if (!inFile) {
        cerr << "Unable to open file." << endl;
        return;
    }

    ofstream outFile("temp.txt");
    if (!outFile) {
        cerr << "Unable to open file.........:(\n" << endl;
        inFile.close();
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        istringstream iss(line);
        int empId;
        string name, role;
        if (iss >> empId >> name >> role) {
            if (empId == id) {
                found = true;
                outFile << id << " " << newName << " " << newRole << endl;
                cout << "Employee details updated successfully.........:)\n" << endl;
            } else {
                outFile << line << endl;
            }
        }
    }

    if (!found) {
        cerr << "Employee with ID " << id << " not found." << endl;
    }

    inFile.close();
    outFile.close();


    if (remove("employees.txt") != 0) {
        cerr << "Error deleting original file.........:(\n" << endl;
        return;
    }
    if (rename("temp.txt", "employees.txt") != 0) {
        cerr << "Error renaming temp file.........:(\n" << endl;
    }
}


void manageEmployees() {
    int choice;
    do {
    
        cout << "\n===============Employee Management Menu:==================" << endl;
        cout << "===============1. Add Employee            ================" << endl;
        cout << "===============2. View Employees          ================" << endl;
        cout << "===============3. Update Employee         ================" << endl;
        cout << "===============4. Remove Employee         ================" << endl;
        cout << "===============0. Exit                    ================" << endl;
        cout << "\n\n========Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name, role;
                cout << "Enter employee ID: ";
                cin >> id;
                cout << "Enter employee name: ";
                cin.ignore(); 
                getline(cin, name);
                cout << "Enter employee role: ";
                getline(cin, role);
                Employee newEmployee = {id, name, role};
                addEmployee(newEmployee);
                break;
            }
            case 2:
                viewEmployees();
                
                break;
            case 3: {
                int id;
                string newName, newRole;
                cout << "Enter ID of the employee to update: ";
                cin >> id;
                cout << "Enter new name for the employee: ";
                cin.ignore(); 
                getline(cin, newName);
                cout << "Enter new role for the employee: ";
                getline(cin, newRole);
                updateEmployee(id, newName, newRole);
                break;
            }
            case 4: {
                int id;
                cout << "Enter ID of the employee to remove: ";
                cin >> id;
                removeEmployee(id);
                break;
            }
            case 0:
                cout << "Exiting employee management menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

struct Item {
    int itemId;
    string itemName;
    double itemPrice;
    int quantity;
};


bool addInventory(Item inventory[], int& numItems, const string& itemName, double itemPrice, int quantity) {

    if (numItems >= MAX_ITEMS) {
        cerr << "Inventory is full. Cannot add more items..............:(" << endl;
        return false;
    }


    int itemId = numItems + 1;


    inventory[numItems] = { itemId, itemName, itemPrice, quantity };
    ++numItems;

    cout << "Item added to inventory successfully........:)" << endl;

    return true;
}
void viewInventory(const Item inventory[], int numItems) {
	system("cls");
    cout << "============Inventory: ====================" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "ID\tItem Name\tPrice\tQuantity" << endl;
    cout << "-------------------------------------------" << endl;
    for (int i = 0; i < numItems; ++i) {
        cout << inventory[i].itemId << "\t" << inventory[i].itemName << "\t\tRs." << inventory[i].itemPrice << "\t" << inventory[i].quantity << endl;
    }
    cout << "-------------------------------------------" << endl;
}

bool saveInventory(const Item inventory[], int numItems, const string& filename) {
    ofstream outputFile(filename);
    if (!outputFile) {
        cerr << "Unable to open file." << endl;
        return false;
    }

    for (int i = 0; i < numItems; ++i) {
        outputFile << inventory[i].itemId << " " << inventory[i].itemName << " " << inventory[i].itemPrice << " " << inventory[i].quantity << endl;
    }

    outputFile.close();
    return true;
}
void generateReport(const Item inventory[], int numItems) {
	system("cls");
    cout << "Report:" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "ID\tItem Name\tPrice\tQuantity" << endl;
    cout << "-------------------------------------------" << endl;
    for (int i = 0; i < numItems; ++i) {
        cout << inventory[i].itemId << "\t" << inventory[i].itemName << "\t\tRs." << inventory[i].itemPrice << "\t\t" << inventory[i].quantity << endl;
    }
    cout << "-------------------------------------------" << endl;
}

struct Order {
    int orderId;
    string itemName;
    double itemPrice;
    OrderStatus status;
};


bool updateOrderStatus(Order orders[], int numOrders, int orderId, OrderStatus newStatus) {
    for (int i = 0; i < numOrders; ++i) {
        if (orders[i].orderId == orderId) {
            orders[i].status = newStatus;
            return true;
        }
    }
    return false;
}

bool loadOrders(Order orders[], int& numOrders, const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Unable to open file...............:(" << endl;
        return false;
    }

    numOrders = 0;
    while (inputFile >> orders[numOrders].orderId >> orders[numOrders].itemName >> orders[numOrders].itemPrice >> (int&)orders[numOrders].status) {
        ++numOrders;
    }

    inputFile.close();
    return true;
}

bool saveOrders(const Order orders[], int numOrders, const string& filename) {
    ofstream outputFile(filename);
    if (!outputFile) {
        cerr << "Unable to open file." << endl;
        return false;
    }

    for (int i = 0; i < numOrders; ++i) {
        outputFile << orders[i].orderId << " " << orders[i].itemName << " " << orders[i].itemPrice << " " << static_cast<int>(orders[i].status) << endl;
    }

    outputFile.close();
    return true;
}

UserData loadUser(const string& username);


bool login(const string& username, const string& password) {
    try {
        UserData user = loadUser(username); 
        if (user.password == password) {
            cout << "Login successful......!!!!" << endl;
            return true;
        } else {
            throw runtime_error("Invalid password.");
        }
    } catch (const exception& e) {
        throw runtime_error("Invalid username.");
    }
}




UserData loadUser(const string& username) {
    ifstream inFile("users.txt");
    if (!inFile) {
        throw runtime_error("Unable to open file.");
    }

    string firstName, lastName, storedUsername, password;
    int userTypeInt;

    while (inFile >> firstName >> lastName >> storedUsername >> password >> userTypeInt) {
        if (storedUsername == username) {
            UserType userType = static_cast<UserType>(userTypeInt);
            return {storedUsername, password, firstName, lastName, userType};
        }
    }

    inFile.close();
    throw runtime_error("User not found.");
}



void saveUser(const UserData& user) {
    ofstream outFile("users.txt", ios::app); 
    if (!outFile) {
        throw runtime_error("Unable to open file.");
    }
    outFile << user.firstName << " " << user.lastName << " "
            << user.username << " " << user.password << " " << user.userType << endl;
    outFile.close();
}

void customerMenu() {
    cout << "\n============= Customer Menu =============" << endl;
    cout << "==============1. Place Order  =============" << endl;
    cout << "==============2. View Orders  =============" << endl;
    cout << "==============0. Logout       =============" << endl;
}

void employeeMenu() {
    cout << "\n============ Employee Menu =============" << endl;
    cout << "=============1. View Orders  =============" << endl;
    cout << "=============2. Update Order Status=======" << endl;
    cout << "=============3. View Inventory============" << endl;
    cout << "=============4. Add Inventory Item========" << endl;
    cout << "=============0. Logout        ============" << endl;
}

void managerMenu() {
    cout << "\n================ Manager Menu ===============" << endl;
    cout << "=============1. View Orders     ===============" << endl;
    cout << "=============2. Generate Reports===============" << endl;
    cout << "=============3. Manage Employees===============" << endl;
    cout << "=============0. Logout          ===============" << endl;
}


void displayCategories() {
    cout << "===============Available Categories:=================" << endl;
    cout << "===============1. Men's Wear       ==================" << endl;
    cout << "===============2. Women's Wear     ==================" << endl;
    cout << "===============3. Kids' Wear       ==================" << endl;
    cout << "===============4. None             ==================" << endl; 
}


void displayItems(int category) {
	system("cls");
    switch (category) {
        case 1:
            cout << "================Men's Wear Options: ==============" << endl;
            cout << "================1. Shalwar Qameez - Rs.5000=======" << endl;
            cout << "================2. Kurta - Rs.4000         =======" << endl;
            cout << "================3. Kurta Pajama - Rs.6000  =======" << endl;
            break;
        case 2:
            cout << "================Women's Wear Options====================:" << endl;
            cout << "================1. Kurti - Rs.3000=======" << endl;
            cout << "================2. Unstitched Fabric - Rs.2000=======" << endl;
            cout << "================3. Stitched Outfit - Rs.5000=======" << endl;
            break;
        case 3:
            cout << "================Kids' Wear Options:====================" << endl;
            cout << "================1. Stitched Collection - Rs.2500=======" << endl;
            cout << "================2. Formals - Rs.3500            =======" << endl;
            cout << "================3. Kurti - Rs.2000              =======" << endl;
            cout << "================4. Trousers - Rs.1500           =======" << endl;
            break;
        case 4:
    			display();
        	break;
        default:
            cout << "Invalid category." << endl;
    }
}


double placeOrder() {
    double totalPrice = 0;


    displayCategories();
    int category;
    cout << "\n\nSelect a category to view items: ";
    cin >> category;
    displayItems(category);


    ofstream outputFile("order.txt", ios::app); 
    if (!outputFile) {
        cerr << "Error opening file." << endl;
        return -1; 
    }

    char continueShopping = 'y';
    while (continueShopping == 'y') {
        int item;
        cout << "\n\nSelect an item: ";
        cin >> item;

        string itemName;
        double itemPrice;


        switch (category) {
            case 1:
                switch (item) {
                    case 1:
                        itemName = "Shalwar Qameez";
                        itemPrice = 5000;
                        break;
                    case 2:
                        itemName = "Kurta";
                        itemPrice = 4000;
                        break;
                    case 3:
                        itemName = "Kurta Pajama";
                        itemPrice = 6000;
                        break;
                    default:
                        cout << "Invalid item." << endl;
                        continue;
                }
                break;
            case 2:
                switch (item) {
                    case 1:
                        itemName = "Kurti";
                        itemPrice = 3000;
                        break;
                    case 2:
                        itemName = "Unstitched Fabric";
                        itemPrice = 2000;
                        break;
                    case 3:
                        itemName = "Stitched Outfit";
                        itemPrice = 5000;
                        break;
                    default:
                        cout << "Invalid item." << endl;
                        continue;
                }
                break;
            case 3:
                switch (item) {
                    case 1:
                        itemName = "Stitched Collection";
                        itemPrice = 2500;
                        break;
                    case 2:
                        itemName = "Formals";
                        itemPrice = 3500;
                        break;
                    case 3:
                        itemName = "Kurti";
                        itemPrice = 2000;
                        break;
                    case 4:
                        itemName = "Trousers";
                        itemPrice = 1500;
                        break;
                    default:
                        cout << "Invalid item." << endl;
                        continue;
                }
                break;
            default:
                cout << "Invalid category." << endl;
                continue;
        }


        outputFile << itemName << " - Rs." << itemPrice << endl;

        cout << "Added " << itemName << " to your cart." << endl;
        totalPrice += itemPrice;

        cout << "\nDo you want to continue shopping? (y/n): ";
        cin >> continueShopping;
        if (continueShopping != 'y') {
            cout << "Total Price: Rs." << totalPrice << endl;
            return totalPrice;
        }
    }


    outputFile << "\nTotal Price: Rs." << totalPrice << endl;
    outputFile.close(); 


    

    return totalPrice;
}

void viewOrder() {
    ifstream inputFile("order.txt"); 
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return;
    }

    string line;
    cout << "Order Details:" << endl;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }

    inputFile.close(); 
}


void processCustomerActions(BoutiqueManager& boutique) {
    int choice;
    do {
        customerMenu();
        cout << "Enter your choice: ";
        cin >> choice;
		double totalPrice = placeOrder();
        switch (choice) {
            case 1:
           	
                placeOrder();
                cout << "Order placed successfully.................:)" << endl;
                cout << "Total Price: Rs." << totalPrice << endl;
                break;
            case 2:
                viewOrder();
                break;
            case 0:
                cout << "Logging out..." << endl;
                display();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}


void processEmployeeActions(BoutiqueManager& boutique) {
    int choice;
    const int MAX_ORDERS = 100;
    Order orders[MAX_ORDERS];
    const int MAX_ITEMS = 100;
    Item inventory[MAX_ITEMS];
    int numItems = 0;
    int numOrders = 0;
    do {
    	

        employeeMenu();
        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                 viewOrder();
                break;
            case 2:
                 if (!loadOrders(orders, numOrders, "order.txt")) {
        cerr << "Error loading orders." << endl;
        exit(0);
    }


    if (updateOrderStatus(orders, numOrders, 1001, OrderStatus::SHIPPED)) {
        cout << "Order status updated successfully." << endl;
    } else {
        cerr << "Order not found." << endl;
    }


    if (!saveOrders(orders, numOrders, "order.txt")) {
        cerr << "Error saving orders." << endl;
        exit(0);
    }

                break;
            case 3:
                inventory[0] = { 1, "Stiched", 2500.0, 50 };
    			inventory[1] = { 2, "trouser", 3500.0, 30 };
   				inventory[2] = { 3, "Formal", 5000.0, 20 };
   				inventory[3] = { 3, "Qameez", 5000.0, 20 };
    			inventory[4] = { 3, "Kurta", 5000.0, 20 };
    			numItems = 5;


    viewInventory(inventory, numItems);
                break;
            case 4:
                if (addInventory(inventory, numItems, "Shirt", 2500.0, 50)) {
        cout << "\nItem added successfully." << endl;
    } else {
        cerr << "Failed to add item." << endl;
    }


    if (!saveInventory(inventory, numItems, "inventory.txt")) {
        cerr << "Failed to save inventory." << endl;
    }

                break;
            case 0:
                cout << "Logging out..." << endl;
                display();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void processManagerActions(BoutiqueManager& boutique) {
    int choice;
        const int MAX_ITEMS = 100;
    Item inventory[MAX_ITEMS];
    int numItems = 0;
    do {
        managerMenu();
        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewOrder();
                break;
            case 2:
                inventory[0] = { 1, "Stiched", 2500.0, 50 };
    			inventory[1] = { 2, "trouser", 3500.0, 30 };
   				inventory[2] = { 3, "Formal", 5000.0, 20 };
   				inventory[3] = { 3, "Qameez", 5000.0, 20 };
    			inventory[4] = { 3, "Kurta", 5000.0, 20 };
    			numItems = 5;


    generateReport(inventory, numItems);
                break;
            case 3:
                manageEmployees();
                break;
            case 0:
                cout << "Logging out..." << endl;
                display();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}
int display() {
    int choice;
    UserType userType;

    cout << "\n\n\n=========Choose User Type:==========\n";
    cout << "=========1. Manager==========\n";
    cout << "=========2. Employee==========\n";
    cout << "=========3. Customer==========\n";
    cout << "\n\nEnter your choice: ";
    cin >> choice;

    if (choice < 1 || choice > 3) {
        cerr << "Invalid choice!" << endl;
        exit(0);
    }

    switch (choice) {
        case 1:
            userType = MANAGER;
            break;
        case 2:
            userType = EMPLOYEE;
            break;
        case 3:
            userType = CUSTOMER;
            break;
    }

    int loginOrSignUpChoice;
    cout << "==========1. Login   ==========\n";
    cout << "==========2. Sign up ==========\n";
    cout << "==========3. Exit    ==========\n";
    cout << "\n\nEnter your choice: ";
    cin >> loginOrSignUpChoice;

    switch (loginOrSignUpChoice) {
        case 1: {
            string username, password;
            cout << "\nEnter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            try {
                if (login(username, password)) {
                    cout << "\nWelcome, " << username << "..!" << endl;

                    BoutiqueManager boutique;
                    switch (userType) {
                        case CUSTOMER:
                            processCustomerActions(boutique);
                            break;
                        case EMPLOYEE:
                            processEmployeeActions(boutique);
                            break;
                        case MANAGER:
                            processManagerActions(boutique);
                            break;
                    }
                }
            } catch (const exception& e) {
                cerr << "Login failed: " << e.what() << endl;
                return 1;
            }
            break;
        }

        case 2: {
            UserData user;
            cout << "Enter first name: ";
            cin >> user.firstName;
            cout << "Enter last name: ";
            cin >> user.lastName;
            cout << "Enter username: ";
            cin >> user.username;
            if (user.username.length() > 10) {
                cerr << "Username must be up to 10 characters long." << endl;
                return 1;
            }
            cout << "Enter password: ";
            cin >> user.password;
            if (user.password.length() > 10) {
                cerr << "Password must be up to 10 characters long." << endl;
                return 1;
            }
            user.userType = userType;

            try {
                saveUser(user);
                cout << "Registration successful!" << endl;
            } catch (const exception& e) {
                cerr << "Registration failed: " << e.what() << endl;
                return 1;
            }
            break;
        }
        case 3:
            cout << "Goodbye!" << endl;
            break;
        default:
            cerr << "Invalid choice!" << endl;
            return 1;
    }
    return 0;
}

int main() {
    int choice;
    UserType userType;
	system("cls");
    cout << "======================================================" << endl;
    cout << "            Welcome to HPW Boutique!                  " << endl;
    cout << "======================================================" << endl;
    cout << "   We are delighted to have you here. Explore our     " << endl;
    cout << "   exquisite collection and discover the perfect      " << endl;
    cout << "   pieces that suit your unique style.                " << endl;
    cout << "======================================================" << endl;

    display();
    



    return 0;
}
