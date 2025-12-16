#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <set>
#include <windows.h>
using namespace std;

// structs for cart, products, users
struct Accounts {
    int id;
    string username;
    string password;
};

struct Product {
    int id;
    string name;
    double price;
    int quantity;
    string category;
    string brand;
};

struct CartItem {
    int id;
    string name;
    int quantity;
    double price;
};

// global variables
CartItem item[20];
int cartItemsCount = 0;
string adminUsername = "abc";
string adminPassword = "123";

// common functions
void loginPanel();
void displayProducts();
void filterPanel(string s);
void filter1(string s, string filterBy);
void filter2(int min, int max, string filterBy);
string toLowerStr(string s);
void searchProduct();
void logout();

// user functions
void loginAsUser();
void createAccount();
int createUserId();
bool checkPasswordAuth(string password);
bool savingUserAccount(string username, string password);
void userPanel();
void userAccManagePanel();
void userInventoryPanel();
void changePassword();
void changeUsername();
void cart();
void addToCart();
void viewCart();
void printBill();
string getCurrentDateTime();
void saveSale(double gstRate);
void updateProductsFile();

// admin functions
void loginAsAdmin();
void adminPanel();
void salesReportPanel();
void adminAccManagePanel();
void adminInventoryPanel();
void addProduct();
int createProductId();
void displayAccounts();
void updateProduct();
void deleteAccount();
void deleteProduct();
void lowStock();
void accountSearch();
void dailySalesReport();
void monthlySalesReport();
void totalRevenueReport();

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    srand(time(0));
    setColor(1);
    cout << "\n============================ Welcome to NextGen Supermarket ============================\n" << endl;
    setColor(7);
    // navigating to login panel
    loginPanel();
    return 0;
}

void logout() {
    //making cart empty
    for(int i = 0; i < 20; i++) {
        item[i] = {};
    }
    cartItemsCount = 0;

    setColor(4);
    cout << "\n-------------------" << endl;
    cout << "Logout!" << endl;
    cout << "-------------------\n" << endl;
    setColor(7);
    loginPanel();
}

void loginPanel() {
    cout << "1. Login as User" << endl;
    cout << "2. Login as Admin" << endl;
    cout << "3. Create an Account" << endl;
    cout << "4. Close App" << endl;
    int choice;
    //taking user choice
    while(true) {
        cout << "Enter (1-4): ";
        cin >> choice;
        if(choice >= 1 && choice <= 4) {
            break;
        } else {
            setColor(4);
            cout << "Wrong Choice! Try Again" << endl;
            setColor(7);
        }
    }
    
    //navigating based on choice
    if(choice == 1) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        loginAsUser();
    } else if(choice == 2) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        loginAsAdmin();
    } else if(choice == 3) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        createAccount();
    } else if(choice == 4) {
        setColor(2);
        cout << string(100, '=')<< endl;
        cout << "Thanks for visiting our store!" << endl;
        setColor(4);
        cout << "App Closed!" << endl;
        cout << string(100, '=') << "\n" << endl;
        setColor(7);

        exit(0);
    }
}

void createAccount() {
// taking credential for new account
    string username, password;
    Accounts account;
    setColor(3);
    cout << "Note: Password should include atleast one uppercase, lowercase, number, special character and min 8 characters long" << endl;
    setColor(7);
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    //opening file in read mode
    ifstream file("users.txt");
    if (!file) {
        setColor(4);
        cout << "File not found!" << endl;
        setColor(7);
        return;
    }

    // checking existing username
    bool found = false;
    while(file >> account.id >> account.username >> account.password) {
        if(account.username == username) {
            found = true; 
            break;
        } 
    }

    file.close();

    if(found) {
        setColor(4);
        cout << "\n-------------------" << endl;
        cout << "Username already exists! Try different" << endl;
        cout << "-------------------\n" << endl;
        setColor(7);
        createAccount();
    }

    // checking validation
    if(checkPasswordAuth(password) && username != "") {
        // storing user account
        if (savingUserAccount(username, password)) {
            setColor(2);
            cout << "\n-------------------" << endl;
            cout << "Account Created Successfully!" << endl;
            cout << "-------------------\n" << endl;
            setColor(7);
            loginPanel();
        } else {
            setColor(4);
            cout << "\n-------------------" << endl;
            cout << "Error Creating Account! Try Again Later" << endl;
            cout << "-------------------\n" << endl;
            setColor(7);
            loginPanel();
        }
    }else {
        setColor(4);
        cout << "\n-------------------" << endl;
        cout << "Invalid credentials! Try Again" << endl;
        cout << "-------------------\n" << endl;
        setColor(7);
        createAccount();
    }
}

bool checkPasswordAuth(string password) {
    bool upper = false, lower = false, digit = false, special = false;
    for(int i = 0; i < password.length(); i++){
        if(isupper(password[i])){
            upper = true;
        }else if(islower(password[i])){
            lower = true;
        }else if(ispunct(password[i])){
            special = true;
        }else if(isdigit(password[i])){
            digit = true;
        }
    }

    if(upper && lower && digit && special && password.length() >= 8) {
        return true;
    } else {
        return false;
    }
}

void loginAsUser() {
    // taking credentials
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    Accounts account;
    //opening file in read mode
    ifstream file("users.txt");
    if (!file) {
        setColor(4);
        cout << "File not found!" << endl;
        setColor(7);
        return;
    }
    
    // validating account existence
    bool found = false;
    while(file >> account.id >> account.username >> account.password) {
        if(account.username == username && account.password == password) {
            found = true; 
            break;
        } 
    }

    file.close();

    if(found) {
        setColor(2);
        cout << "\n-------------------" << endl;
        cout << "Login Successfully!" << endl;
        cout << "-------------------\n" << endl;
        setColor(7);
        // moving to user-panel 
        userPanel();
    } else {
        setColor(4);
        cout << "\n-------------------" << endl;
        cout << "Wrong Credentials! Try Again" << endl;
        cout << "-------------------\n" << endl;
        setColor(7);
        // moving to user-panel 
        loginPanel();
    }
}

bool savingUserAccount(string username, string password) {
    Accounts account;
    //opening file in append mode
    ofstream file("users.txt", ios::app);

    if (!file) {
        cout << "File not found!" << endl;
        return false;
    }
    
    account.id = createUserId();
    account.username = username;
    account.password = password;

    // writing account to file
    file << account.id << " " << account.username << " " << account.password << "\n";
    file.close();
    return true;
}

int createUserId() {
    int num = rand() % 500 + 1;
    Accounts account;
    ifstream file("users.txt");

    if (!file) {
        cout << "File not found!" << endl;
        return num;
    }

    // checking existing ids
    bool found = false;
    while(file >> account.id >> account.username >> account.password) {
        if(num == account.id) {
            found = true;
            break;
        }
    }

    file.close();

    if(found) {
        return createUserId();
    } else {
        return num; 
    }
}

void userPanel() {
    int choice;
    setColor(1);
    cout << string(100, '=') << "\n" << endl;
    setColor(7);
    cout << "1. Move To Inventory" << endl;
    cout << "2. Account Management" << endl;
    cout << "3. Logout" << endl;

    while(true) {
        cout << "Enter choice(1-3): ";
        cin >> choice;
        if(choice >= 1 && choice <= 3) {
            break;
        } else {
            setColor(4);
            cout << "Wrong Choice! Try Again" << endl;
            setColor(7);
        }
    }

    if (choice == 1){
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating to user inventory panel
        userInventoryPanel();
    }
    else if (choice == 2){
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating to user account management panel
        userAccManagePanel();
    }
    else if (choice == 3){
        logout();
    }
}

void displayProducts() {
    Product product;
    //opening file in read mode
    ifstream file("products.txt");

    if (!file) {
        setColor(4);
        cout << "File not found!" << endl;
        setColor(7);
        return;
    }

    //table header
    cout << left; 
    setColor(1);
    cout << setw(15) << "Id"
         << setw(20) << "Name"
         << setw(15) << "Price(Rs)"
         << setw(15) << "Brand"
         << setw(20) << "Category"
         << setw(15) << "Quantity"
         << endl;

    cout << string(100, '-') << endl;
    setColor(7);

    int counter = 0;

    //table body
    while(file >> product.id >> product.name >> product.price >> product.brand >> product.category >> product.quantity) {
        cout << setw(15) << product.id 
            << setw(20) << product.name
            << setw(15) << product.price
            << setw(15) << product.brand
            << setw(20) << product.category
            << setw(15) << product.quantity
            << endl;
        counter++;
    }

    if(counter == 0) {
        setColor(4);
        cout << "No product available in inventory!" << endl;
        setColor(7);
    }
    file.close();
    setColor(2);
    cout << "\nTotal Products = " << counter << endl;
    setColor(7);
}

void changePassword() {
    //opening users file and creating temp file
    ifstream infile("users.txt");
    ofstream outfile("temp.txt");

    if(!infile || !outfile) {
        cout << "File error!\n";
        return;
    }

    Accounts account;
    string username, oldPass, newPass;
    bool userFound = false;
    bool passwordChanged = false;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter old password: ";
    cin >> oldPass;

    while(infile >> account.id >> account.username >> account.password) {
        if(account.username == username) {
            userFound = true;

            if(account.password == oldPass) {
                while(true) {
                    cout << "Enter new password: ";
                    cin >> newPass;
                    if(checkPasswordAuth(newPass)) {
                        break;
                    } else {
                        setColor(4);
                        cout << "Invalid password! Try Again" << endl;
                        setColor(7);
                    }
                }
                //writing updated account to temp file
                outfile << account.id << " "
                        << account.username << " "
                        << newPass << endl;

                passwordChanged = true;
            } else {
                outfile << account.id << " "
                        << account.username << " "
                        << account.password << endl;
            }
        }
        else {
            outfile << account.id << " "
                    << account.username << " "
                    << account.password << endl;
        }
    }

    infile.close();
    outfile.close();

    //validating and updating files
    if(!userFound) {
        setColor(4);
        cout << "Username not found!\n";
        setColor(7);
        remove("temp.txt");
    }
    else if(!passwordChanged) {
        setColor(4);
        cout << "Old password is incorrect!\n";
        setColor(7);
        remove("temp.txt");
    }
    else {
        remove("users.txt");
        rename("temp.txt", "users.txt");

        setColor(2);
        cout << "-----------------------------\n";
        cout << "Password changed successfully!\n";
        cout << "-----------------------------\n";
        setColor(7);
    }

    setColor(1);
    cout << string(100, '=') << "\n" << endl;
    setColor(7);
    //naviagating back to account management panel
    userAccManagePanel();
}

void changeUsername() {
    //opening users file and creating temp file
    ifstream infile("users.txt");
    ofstream outfile("temp.txt");

    if(!infile || !outfile) {
        cout << "File error!\n";
        return;
    }

    Accounts account;
    string oldUsername, password, newUsername;
    bool userFound = false;
    bool usernameChanged = false;

    cout << "Enter current username: ";
    cin >> oldUsername;
    cout << "Enter password: ";
    cin >> password;

    while(infile >> account.id >> account.username >> account.password) {
        if(account.username == oldUsername) {
            userFound = true;

            if(account.password == password) {
                cout << "Enter new username: ";
                cin >> newUsername;

                outfile << account.id << " "
                        << newUsername << " "
                        << account.password << endl;

                usernameChanged = true;
            } else {
                //writing existing account to temp file
                outfile << account.id << " "
                        << account.username << " "
                        << account.password << endl;
            }
        }
        else {
            outfile << account.id << " "
                    << account.username << " "
                    << account.password << endl;
        }
    }

    infile.close();
    outfile.close();

    //validating and updating files
    if(!userFound) {
        setColor(4);
        cout << "Username not found!\n";
        setColor(7);
        remove("temp.txt");
    }
    else if(!usernameChanged) {
        setColor(4);
        cout << "Incorrect password!\n";
        setColor(7);
        remove("temp.txt");
    }
    else {
        remove("users.txt");
        rename("temp.txt", "users.txt");

        setColor(2);
        cout << "----------------------------\n";
        cout << "Username changed successfully!\n";
        cout << "----------------------------\n";
        setColor(7);
    }

    setColor(1);
    cout << string(100, '=') << "\n" << endl;
    setColor(7);
    //naviagating back to account management panel
    userAccManagePanel();
}


void userAccManagePanel() {
    int choice;
    cout << "1. Change Password" << endl;
    cout << "2. Change Username" << endl;
    cout << "3. Go Back" << endl;
    cout << "4. Logout" << endl;

    while(true) {
        cout << "Enter choice(1-4): ";
        cin >> choice;
        if(choice >= 1 && choice <= 4) {
            break;
        } else {
            setColor(4);
            cout << "Wrong Choice! Try Again" << endl;
            setColor(7);
        }
    }

    if(choice == 1) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        changePassword();
    } else if(choice == 2) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        changeUsername();
    } else if(choice == 3) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating back to user panel
        userPanel();
    } else if(choice == 4) {
        logout();
    }
}

void userInventoryPanel() {
    int choice;
    cout << "1. View All Products" << endl;
    cout << "2. Filter Products" << endl;
    cout << "3. Search Product" << endl;
    cout << "4. View Cart" << endl;
    cout << "5. Proceed to Billing" << endl;
    cout << "6. Go Back" << endl;
    cout << "7. Logout" << endl;

    while(true) {
        cout << "Enter choice(1-7): ";
        cin >> choice;
        if(choice >= 1 && choice <= 7) {
            break;
        } else {
            setColor(4);
            cout << "Wrong Choice! Try Again" << endl;
            setColor(7);
        }
    }

    if(choice == 1) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //displaying all products
        displayProducts();
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating to cart panel  
        cart();
    } else if(choice == 2) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating to filter panel
        filterPanel("user");
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating to cart panel
        cart();
    } else if(choice == 3) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //searching product
        searchProduct();
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating to cart panel
        cart();
    } else if(choice == 4) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //viewing cart
        viewCart();
    } else if(choice == 5) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //printing bill
        printBill();
    } else if(choice == 6) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating back to user panel
        userPanel();
    } else if(choice == 7) {
        logout();
    }
}

void filterPanel(string s) {
    int choice;
    cout << "1. Filter by Brand" << endl;
    cout << "2. Filter by Category" << endl;
    cout << "3. Filter by Price" << endl;
    cout << "4. Filter by Quantity" << endl;
    cout << "5. Go Back" << endl;
    cout << "6. Logout" << endl;

    while(true) {
        cout << "Enter choice(1-6): ";
        cin >> choice;
        if(choice >= 1 && choice <= 6) {
            break;
        } else {
            setColor(4);
            cout << "Wrong Choice! Try Again" << endl;
            setColor(7);
        }
    }

    if(choice == 1) {
        Product product;
        ifstream file("products.txt");

        setColor(1);
        cout << "\nAvailable Brands Are:" << endl;
        cout << "--------------------\n";
        setColor(7);
        set<string> brands; 

        //collecting unique brands
        while (file >> product.id >> product.name >> product.price >> product.brand >> product.category >> product.quantity) {
            brands.insert(product.brand);
        }
        file.close();

        //displaying brands
        int count = 1;
        for(const string &brand : brands) {
            cout << count << ". " << brand << endl;
            count++;
        }

        string brand;
        cout << "\nEnter brand name: ";
        cin >> brand;

        //filtering by brand
        filter1(brand, "Brand");
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating back to filter panel
        filterPanel(s);

    } else if(choice == 2) {

        Product product;
        ifstream file("products.txt");

        setColor(1);
        cout << "\nAvailable Categories Are:" << endl;
        cout << "-----------------\n";
        setColor(7);
        set<string> categories;

        //collecting unique categories
        while (file >> product.id >> product.name >> product.price >> product.brand >> product.category >> product.quantity) {
            categories.insert(product.category);
        }
        file.close();

        //displaying categories
        int count = 1;
        for (const string &category : categories) {
            cout << count << ". " << category << endl;
            count++;
        } 

        string category;
        cout << "\nEnter category: ";
        cin >> category;
        
        //filtering by category
        filter1(category, "Category");
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        filterPanel(s);

    }else if(choice == 3) {

        int min, max;
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        cout << "Filter from Rs: ";
        cin >> min;
        cout << "Filter to Rs: ";
        cin >> max;

        if(min > max || min < 0 || max < 0) {
            setColor(4);
            cout << "-------------------" << endl;
            cout << "Invalid Range! Try Again" << endl;
            cout << "-------------------\n" << endl;
            setColor(7);
            filterPanel(s);
            return;
        }

        //filtering by price range
        filter2(min, max, "Price");
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        filterPanel(s);

    }else if(choice == 4) {

        int min, max;
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        cout << "Filter from Quantity: ";
        cin >> min;
        cout << "Filter to Quantity: ";
        cin >> max;

        if(min > max || min < 0 || max < 0) {
            setColor(4);
            cout << "-------------------" << endl;
            cout << "Invalid Range! Try Again" << endl;
            cout << "-------------------\n" << endl;
            setColor(7);

            filterPanel(s);
            return;
        }

        filter2(min, max, "Quantity");
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        filterPanel(s);

    }else if(choice == 5) {
        if(s == "user") {
            setColor(1);
            cout << string(100, '=') << "\n" << endl;
            setColor(7);
            //navigating back to user inventory panel
            userInventoryPanel();
        } else if(s == "admin") {
            setColor(1);
            cout << string(100, '=') << "\n" << endl;
            setColor(7);
            //navigating back to admin inventory panel
            adminInventoryPanel();
        }
    }else if(choice == 6) {
        logout();
    }
}

void filter1(string s, string filterBy) {
    Product product;

    ifstream file("products.txt");
    if(!file) {
        cout << "Error opening file!";
        return;
    }

    //table header
    cout << left; 
    setColor(1);
    cout << setw(15) << "Id"
        << setw(20) << "Name"
        << setw(15) << "Price(Rs)"
        << setw(15) << "Brand"
        << setw(20) << "Category"
        << setw(15) << "Quantity"
        << endl;

    cout << string(100, '-') << endl;
    setColor(7);

    //table body
    int counter = 0;
    if(filterBy == "Brand") {
        while (file >> product.id >> product.name >> product.price >> product.brand >> product.category >> product.quantity) {
            if(toLowerStr(product.brand) == toLowerStr(s)) {
                counter++;
                cout << setw(15) << product.id 
                    << setw(20) << product.name
                    << setw(15) << product.price
                    << setw(15) << product.brand
                    << setw(20) << product.category
                    << setw(15) << product.quantity
                    << endl;
            }
        }
    } else if(filterBy == "Category") {
        while (file >> product.id >> product.name >> product.price >> product.brand >> product.category >> product.quantity) {
            if(toLowerStr(product.category) == toLowerStr(s)) {
                counter++;
                cout << setw(15) << product.id 
                    << setw(20) << product.name
                    << setw(15) << product.price
                    << setw(15) << product.brand
                    << setw(20) << product.category
                    << setw(15) << product.quantity
                    << endl;
            }
        }
    }
    
    if(counter == 0) {
        setColor(4);
        cout << "No product available in this " << filterBy << "!" << endl;
        setColor(7);
    }

    file.close();
}

void filter2(int min, int max, string filterBy) {
    Product product;

    ifstream file("products.txt");
    if(!file) {
        cout << "Error opening file!";
        return;
    }

    //table header
    cout << left; 
    setColor(1);
    cout << setw(15) << "Id"
        << setw(20) << "Name"
        << setw(15) << "Price(Rs)"
        << setw(15) << "Brand"
        << setw(20) << "Category"
        << setw(15) << "Quantity"
        << endl;

    cout << string(100, '-') << endl;
    setColor(7);

    //table body
    int counter = 0;
    if(filterBy == "Price") {
        while (file >> product.id >> product.name >> product.price >> product.brand >> product.category >> product.quantity) {
            if(product.price >= min && product.price <= max) {
                counter++;
                cout << setw(15) << product.id 
                    << setw(20) << product.name
                    << setw(15) << product.price
                    << setw(15) << product.brand
                    << setw(20) << product.category
                    << setw(15) << product.quantity
                    << endl;
            }
        }
    } else if(filterBy == "Quantity") {
        while (file >> product.id >> product.name >> product.price >> product.brand >> product.category >> product.quantity) {
            if(product.quantity >= min && product.quantity <= max) {
                counter++;
                cout << setw(15) << product.id 
                    << setw(20) << product.name
                    << setw(15) << product.price
                    << setw(15) << product.brand
                    << setw(20) << product.category
                    << setw(15) << product.quantity
                    << endl;
            }
        }
    }

    if(counter == 0) {
        setColor(4);
        cout << "No product available in this Price Range!" << endl;
        setColor(7);
    }

    file.close();
}

string toLowerStr(string s) {
    for(int i = 0; i < s.length(); i++) {
        s[i] = tolower(s[i]);
    } 
    return s;
}

void searchProduct() {
    Product product;
    string name;
    cout << "Enter product name: ";
    cin >> name;

    ifstream file("products.txt");
    if(!file) {
        cout << "Error opening file!";
        return;
    }

    //table header
    cout << left; 
    setColor(1);
    cout << setw(15) << "Id"
        << setw(20) << "Name"
        << setw(15) << "Price(Rs)"
        << setw(15) << "Brand"
        << setw(20) << "Category"
        << setw(15) << "Quantity"
        << endl;

    cout << string(100, '-') << endl;
    setColor(7);

    //table body
    bool found = false;
    while (file >> product.id >> product.name >> product.price >> product.brand >> product.category >> product.quantity) {
        if(toLowerStr(product.name) == toLowerStr(name)) {
            found = true;
            cout << setw(15) << product.id 
                << setw(20) << product.name
                << setw(15) << product.price
                << setw(15) << product.brand
                << setw(20) << product.category
                << setw(15) << product.quantity
                << endl;
        }
    }

    file.close();

    if(!found) {
        setColor(4);
        cout << "Product not found!" << endl;
        setColor(7);
    }
}

void cart() {
    int choice;
    cout << "1. Add to Cart" << endl;
    cout << "2. Go Back" << endl;

    while(true) {
        cout << "Enter choice(1-2): ";
        cin >> choice;
        if(choice >= 1 && choice <= 2) {
            break;
        } else {
            setColor(4);
            cout << "Wrong Choice! Try Again" << endl;
            setColor(7);
        }
    }

    if(choice == 1) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //adding products to cart
        addToCart();
    } else if(choice == 2) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating back to user inventory panel
        userInventoryPanel();
    }
}

void viewCart() {
    Product product;
    ifstream file("products.txt");

    if (!file) {
        cout << "File not found!" << endl;
        return;
    }

    //table header
    cout << left; 
    setColor(1);
    cout << setw(15) << "Id"
         << setw(20) << "Name"
         << setw(20) << "Price per Unit(Rs)"
         << setw(20) << "Total Price(Rs)"
         << setw(15) << "Quantity"
         << endl;

    cout << string(110, '-') << endl;
    setColor(7);

    if(cartItemsCount == 0) {
        setColor(4);
        cout << "No item added in cart!" << endl;
        setColor(7);
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating back to user inventory panel
        userInventoryPanel();
        return;
    }

    //table body
    for(int i = 0; i < cartItemsCount; i++) {
        cout << setw(15) << item[i].id
            << setw(20) << item[i].name
            << setw(20) << item[i].price
            << setw(20) << item[i].price * item[i].quantity
            << setw(15) << item[i].quantity
            << endl;
    }
    
    file.close();
    setColor(1);
    cout << string(100, '=') << "\n" << endl;
    setColor(7);
    //navigating back to user inventory panel
    userInventoryPanel();
}

void addToCart() {
    Product product;
    int choice = 1;

    while(choice != 0) {
        ifstream file("products.txt");
        if(!file) {
            cout << "Error opening file!" << endl;
            return;
        }

        int id, quantity;
        cout << "Enter Product ID to add to cart: ";
        cin >> id;
        cout << "Enter Quantity: ";
        cin >> quantity;

        bool found = false;

        //searching product by id
        while(file >> product.id >> product.name >> product.price 
                   >> product.brand >> product.category >> product.quantity) {

            if(product.id == id) {
                found = true;

                if(quantity > product.quantity) {
                    setColor(4);
                    cout << "\n-------------------" << endl;
                    cout << "Insufficient stock! Available: " 
                         << product.quantity << endl;
                    cout << "-------------------\n" << endl;
                    setColor(7);
                } else {
                    item[cartItemsCount].id = id;
                    item[cartItemsCount].name = product.name;
                    item[cartItemsCount].price = product.price;
                    item[cartItemsCount].quantity = quantity;
                    cartItemsCount++;

                    setColor(2);
                    cout << "\n-------------------" << endl;
                    cout << "Product Added to Cart!" << endl;
                    cout << "-------------------\n" << endl;
                    setColor(7);
                }
                break;
            }
        }

        if(!found) {
            setColor(4);
            cout << "\n-------------------" << endl;
            cout << "Product ID does not exist!" << endl;
            cout << "-------------------\n" << endl;
            setColor(7);
        }

        file.close();

        setColor(1);
        cout << "Add more products? (1 = Yes, 0 = No): ";
        setColor(7);
        cin >> choice;
    }

    setColor(1);
    cout << string(100, '=') << "\n" << endl;
    setColor(7);
    //navigating back to user inventory panel
    userInventoryPanel();
}

void loginAsAdmin() {
    string username;
    string password;

    while(true) {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        // validating credentials
        if(username == adminUsername && password == adminPassword) {
            setColor(2);
            cout << "\n-------------------" << endl;
            cout << "Login Successfully!" << endl;
            cout << "-------------------\n" << endl;
            setColor(7);
            adminPanel();
            break;
        } else {
            setColor(4);
            cout << "\n-------------------" << endl;
            cout << "Wrong Credentials! Try Again" << endl;
            cout << "-------------------\n" << endl;
            setColor(7);
        }
    }
}

void adminPanel() {
    int choice;
    cout << "1. Inventory Management" << endl;
    cout << "2. Account Management" << endl;
    cout << "3. Sales Report" << endl;
    cout << "4. Logout" << endl;
    while(true) {
        cout << "Enter choice(1-4): ";
        cin >> choice;
        if(choice >= 1 && choice <= 4) {
            break;
        } else {
            setColor(4);
            cout << "Wrong Choice! Try Again" << endl;
            setColor(7);
        }
    }
    
    if(choice == 1) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating to admin inventory panel
        adminInventoryPanel();
    } else if(choice == 2) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating to admin account management panel
        adminAccManagePanel();
    } else if(choice == 3) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        // navigating to sales report panel
        salesReportPanel();
    } else if(choice == 4) {
        logout();
    }
}

void salesReportPanel() {
    int choice;
    cout << "1. Total Revenue Report" << endl;
    cout << "2. Daily Sales Report" << endl;
    cout << "3. Monthly Sales Report" << endl;
    cout << "4. Go Back" << endl;
    cout << "5. Logout" << endl;

    while(true) {
        cout << "Enter choice(1-5): ";
        cin >> choice;
        if(choice >= 1 && choice <= 5) {
            break;
        } else {
            setColor(4);
            cout << "Wrong Choice! Try Again" << endl;
            setColor(7);
        }
    }
    
    //handling choices
    if(choice == 1) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //printing total revenue report
        totalRevenueReport();
    } else if(choice == 2) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //printing daily sales report
        dailySalesReport();
    } else if(choice == 3) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //printing monthly sales report
        monthlySalesReport();
    } else if(choice == 4) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating back to admin panel
        adminPanel();
    } else if(choice == 5) {
        logout();
    }
}

void addProduct() {
    Product product;
    product.id = createProductId();
    cout << "Enter Name: ";
    cin >>  product.name;
    cout << "Enter Price: ";
    cin >> product.price;
    cout << "Enter Brand: ";
    cin >> product.brand;
    cout << "Enter Category: ";
    cin >> product.category;
    cout << "Enter Quantity: ";
    cin >> product.quantity;

    ofstream file("products.txt", ios::app);
    if (!file) {
        cout << "File not found!" << endl;
        return;
    }
    
    //writing product to file
    file << product.id << " " << product.name << " " << product.price << " " << product.brand << " " << product.category << " " << product.quantity << "\n";
    setColor(2);
    cout << "\n-------------------" << endl;
    cout << "Product Added Successfully!" << endl;
    cout << "-------------------\n" << endl;
    setColor(7);
    file.close();
    //navigating back to admin inventory panel
    adminInventoryPanel();
}

void displayAccounts() {
    Accounts account;
    ifstream file("users.txt");

    if (!file) {
        cout << "File not found!" << endl;
        return;
    }

    //table header
    cout << left;
    setColor(1);
    cout << setw(20) << "Id"
         << setw(20) << "Usernames"
         << setw(20) << "Passwords" 
         << endl;
    cout << string(60, '-') << endl;
    setColor(7);

    //table body
    int counter = 0;
    while(file >> account.id >> account.username >> account.password) {
        cout << setw(20) << account.id 
            << setw(20) << account.username
            << setw(20) << account.password
            << endl;
        counter++;
    }
    if(counter == 0) {
        setColor(4);
        cout << "No user found!" << endl;
        setColor(7);
    }
    file.close();

    setColor(2);
    cout << "\nTotal Accounts = " << counter << endl;
    setColor(7);
}

void updateProduct() {
    //displaying all products
    displayProducts();

    Product product;
    bool found = false;
    int id;
    cout << "Enter Id of product to update: ";
    cin >> id;

    ifstream infile("products.txt");
    ofstream outfile("temp.txt");

    if (!infile || !outfile) {
        cout << "Error opening file!" << endl;
        return;
    }

    // Read each product
    while (infile >> product.id >> product.name >> product.price 
                  >> product.brand >> product.category >> product.quantity) {
        if (product.id == id) {
            found = true;
            cout << "Enter new Name: ";
            cin >> product.name;
            cout << "Enter new Price: ";
            cin >> product.price;
            cout << "Enter new Brand: ";
            cin >> product.brand;
            cout << "Enter new Category: ";
            cin >> product.category;
            cout << "Enter new Quantity: ";
            cin >> product.quantity;
        }
        // Write the product (updated or not) to the temp file
        outfile << product.id 
                << " " << product.name 
                << " " << product.price 
                << " " << product.brand 
                << " " << product.category 
                << " " << product.quantity << "\n";
    }

    infile.close();
    outfile.close();

    //updating files
    if (!found) {
        setColor(4);
        cout << "\n-------------------" << endl;
        cout << "Product with ID " << id << " not found!" << endl;
        cout << "-------------------\n" << endl;
        setColor(7);
        remove("temp.txt");
    } else {
        remove("products.txt");
        rename("temp.txt", "products.txt");
        setColor(2);
        cout << "\n-------------------" << endl;
        cout << "Product Updated Successfully!" << endl;
        cout << "-------------------\n" << endl;
        setColor(7);
    }
    //navigating back to admin inventory panel
    adminInventoryPanel();
}

void deleteAccount() {
    //displaying all accounts
    displayAccounts();

    Accounts account;
    bool found = false;
    int id;
    cout << "Enter Id of user to remove: ";
    cin >> id;

    ifstream infile("users.txt");
    ofstream outfile("temp.txt");

    if (!infile || !outfile) {
        cout << "Error opening file!" << endl;
        return;
    }

    // Read each account
    while(infile >> account.id >> account.username >> account.password) {
        if(account.id == id) {
            found = true;
            continue;
        }
        outfile << account.id << " " << account.username << " " << account.password << "\n";
    }

    infile.close();
    outfile.close();

    //validating and updating files
    if (!found) {
        setColor(4);
        cout << "\n-------------------" << endl;
        cout << "User with ID " << id << " not found!" << endl;
        cout << "-------------------\n" << endl;
        setColor(7);
        remove("temp.txt");
    } else {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        setColor(2);
        cout << "\n-------------------" << endl;
        cout << "User Removed Successfully!" << endl;
        cout << "-------------------\n" << endl;
        setColor(7);
    }
    //navigating back to admin account management panel
    adminAccManagePanel();
}

void deleteProduct() {
    //displaying all products
    displayProducts();
    Product product;
    bool found = false;
    int id;
    cout << "Enter Id of product to remove: ";
    cin >> id;

    ifstream infile("products.txt");
    ofstream outfile("temp.txt");

    if (!infile || !outfile) {
        cout << "Error opening file!" << endl;
        return;
    }

    // Read each product
    while (infile >> product.id >> product.name >> product.price 
            >> product.brand >> product.category >> product.quantity) {
        if(product.id == id) {
            found = true;
            continue;
        }
        // Write the product (if not deleted) to the temp file
        outfile << product.id << " " << product.name << " " << product.price << " "
                << product.brand << " " << product.category << " " << product.quantity << "\n";
    }

    infile.close();
    outfile.close();

    if (!found) {
        setColor(4);
        cout << "\n-------------------" << endl;
        cout << "Product with ID " << id << " not found!" << endl;
        cout << "-------------------\n" << endl;
        setColor(7);
        remove("temp.txt");
    } else {
        remove("products.txt");
        rename("temp.txt", "products.txt");
        setColor(2);
        cout << "\n-------------------" << endl;
        cout << "Product Removed Successfully!" << endl;
        cout << "-------------------\n" << endl;
        setColor(7);
    }
    //navigating back to admin inventory panel
    adminInventoryPanel();
}

void accountSearch() {
    Accounts account;
    string name;
    cout << "Enter username: ";
    cin >> name;

    ifstream file("users.txt");
    if(!file) {
        cout << "Error opening file!";
        return;
    }

    cout << left;
    //table header
    setColor(1);
    cout << setw(20) << "Id"
         << setw(20) << "Usernames"
         << setw(20) << "Passwords" 
         << endl;
    cout << string(60, '-') << endl;
    setColor(7);

    //table body
    bool found = false;
    while (file >> account.id >> account.username >> account.password) {
        if(account.username == name) {
            found = true;
            cout << setw(20) << account.id 
            << setw(20) << account.username
            << setw(20) << account.password
            << endl;
        }
    }

    file.close();

    if(!found) {
        setColor(4);
        cout << "Account not found!" << endl;
        setColor(7);
    }
    setColor(1);
    cout << string(100, '=') << "\n" << endl;
    setColor(7);
    //navigating back to admin account management panel
    adminAccManagePanel();
}

void lowStock() {
    Product product;
    ifstream file("products.txt");
    if(!file) {
        cout << "Error opening file!";
        return;
    }

    //table header
    cout << left; 
    setColor(1);
    cout << setw(15) << "Id"
        << setw(20) << "Name"
        << setw(15) << "Price(Rs)"
        << setw(15) << "Brand"
        << setw(20) << "Category"
        << setw(15) << "Quantity"
        << endl;

    cout << string(100, '-') << endl;
    setColor(7);

    //table body
    int count = 0;
    while (file >> product.id >> product.name >> product.price >> product.brand >> product.category >> product.quantity) {
        //checking for low stock
        if(product.quantity <= 10) {
            cout << setw(15) << product.id 
                << setw(20) << product.name
                << setw(15) << product.price
                << setw(15) << product.brand
                << setw(20) << product.category
                << setw(15) << product.quantity
                << endl;
        }
    }

    file.close();

    if(count == 0) {
        setColor(2);
        cout << "All products are sufficiently stocked!" << endl;
        setColor(7);
    }

    setColor(1);
    cout << string(100, '=') << "\n" << endl;
    setColor(7);
    //navigating back to admin inventory panel
    adminInventoryPanel();
}

int createProductId() {
    int num = rand() % 500 + 1;
    Product product;
    ifstream file("products.txt");

    if (!file) {
        cout << "File not found!" << endl;
        return num;
    }

    //checking for unique product id
    bool found = false;
    while(file >> product.id >> product.name >> product.price >> product.brand >> product.category >> product.quantity) {
        if(num == product.id) {
            found = true;
            break;
        }
    }

    file.close();

    if(found) {
        return createProductId();
    } else {
        return num; 
    }
}

void adminAccManagePanel() {
    int choice;
    cout << "1. Delete Account" << endl;
    cout << "2. View All Accounts" << endl;
    cout << "3. Search Account" << endl;
    cout << "4. Go Back" << endl;
    cout << "5. Logout" << endl;

    while(true) {
        cout << "Enter choice(1-5): ";
        cin >> choice;
        if(choice >= 1 && choice <= 5) {
            break;
        } else {
            setColor(4);
            cout << "Wrong Choice! Try Again" << endl;
            setColor(7);
        }
    }

    if(choice == 1) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //deleting account
        deleteAccount();
    } else if(choice == 2) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //displaying all accounts
        displayAccounts();
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating back to admin account management panel
        adminAccManagePanel();
    } else if(choice == 3) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //searching account
        accountSearch();
    } else if(choice == 4) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating back to admin panel
        adminPanel();
    } else if(choice == 5) {
        logout();
    }
}

void adminInventoryPanel() {
    int choice;
    cout << "1. Add Product" << endl;
    cout << "2. Update Product" << endl;
    cout << "3. Delete Product" << endl;
    cout << "4. Search Product" << endl;
    cout << "5. View All Products" << endl;
    cout << "6. Low Stock Product" << endl;
    cout << "7. Filter Products" << endl;
    cout << "8. Go Back" << endl;
    cout << "9. Logout" << endl;

    while(true) {
        cout << "Enter choice(1-9): ";
        cin >> choice;
        if(choice >= 1 && choice <= 9) {
            break;
        } else {
            setColor(4);
            cout << "Wrong Choice! Try Again" << endl;
            setColor(7);
        }
    }
    
    if(choice == 1) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //adding new product
        addProduct();
    } else if(choice == 2) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //updating existing product
        updateProduct();
    } else if(choice == 3) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //deleting a product
        deleteProduct();
    } else if(choice == 4) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //searching a product
        searchProduct();
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating back to admin inventory panel
        adminInventoryPanel();
    } else if(choice == 5) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //displaying all products
        displayProducts();
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating back to admin inventory panel
        adminInventoryPanel();
    } else if(choice == 6) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //displaying low stock products
        lowStock();
    } else if(choice == 7) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //filtering products
        filterPanel("admin");
    } else if(choice == 8) {
        setColor(1);
        cout << string(100, '=') << "\n" << endl;
        setColor(7);
        //navigating back to admin panel
        adminPanel();
    } else if(choice == 9) {
        logout();
    }
}

string getCurrentDateTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    //formatting date and time
    char buffer[25];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

void saveSale(double gstRate) {
    ofstream sales("sales.txt", ios::app);
    if(!sales) return;

    string dateTime = getCurrentDateTime();

    for(int i = 0; i < cartItemsCount; i++) {
        //calculating totals
        double total = item[i].quantity * item[i].price;
        double gst = total * gstRate;
        double netTotal = total + gst;

        //writing sale to file
        sales << dateTime << " "
              << item[i].id << " "
              << item[i].name << " "
              << item[i].quantity << " "
              << item[i].price << " "
              << total << " "
              << gst << " "
              << netTotal << endl;
    }
    sales.close();
}

void updateProductsFile() {
    ifstream infile("products.txt");
    ofstream outfile("temp.txt");

    if(!infile || !outfile) {
        cout << "Error opening file!" << endl;
        return;
    }

    Product product;
    //updating product quantities
    while(infile >> product.id >> product.name >> product.price >> product.brand >> product.category >> product.quantity) {
        for(int i = 0; i < cartItemsCount; i++) {
            if(product.id == item[i].id) {
                product.quantity -= item[i].quantity;
            }
        }
        //writing updated product to temp file
        outfile << product.id << " " << product.name << " " << product.price << " " << product.brand << " " << product.category << " " << product.quantity << "\n";
    }

    infile.close();
    outfile.close();

    remove("products.txt");
    rename("temp.txt", "products.txt");
}

void printBill() {
    if(cartItemsCount == 0) {
        setColor(4);
        cout << "No item in cart to generate bill!" << endl;
        setColor(7);
        cout << string(100, '=') << "\n" << endl;
        userInventoryPanel();
        return;
    }

    double subtotal = 0;
    double gstRate = 0.18;
    string dateTime = getCurrentDateTime();

    // Header
    setColor(2);
    cout << "\n================================================== INVOICE ==================================================\n";
    setColor(7);
    cout << "Date & Time: " << dateTime << endl;

    setColor(1);
    // Table Header
    cout << left;
    cout << setw(5) << "ID"
         << setw(20) << "Item"
         << setw(10) << "Qty"
         << setw(12) << "Price"
         << setw(12) << "Amount" << endl;

    cout << string(60, '-') << endl;
    setColor(7);

    // Items
    for(int i = 0; i < cartItemsCount; i++) {
        double amount = item[i].quantity * item[i].price;
        subtotal += amount;
        cout << left;
        cout << setw(5) << item[i].id
             << setw(20) << item[i].name
             << setw(10) << item[i].quantity
             << setw(12) << item[i].price
             << setw(12) << amount << endl;
    }

    cout << string(60, '-') << endl;

    //calculating discount based on subtotal
    double discount = 0;
    if(subtotal > 5000) discount = subtotal * 0.10;
    else if(subtotal > 3000) discount = subtotal * 0.05;

    double afterDiscount = subtotal - discount;
    double gstAmount = afterDiscount * gstRate;
    double netTotal = afterDiscount + gstAmount;

    cout << right << setw(47) << "Subtotal: Rs. " << subtotal << endl;
    cout << setw(47) << "Discount: Rs. " << discount << endl;
    cout << setw(47) << "GST (18%): Rs. " << gstAmount << endl;
    cout << setw(47) << "Net Payable: Rs. " << netTotal << endl;
    cout << string(60, '-') << endl;

    //saving sale and updating products file
    saveSale(gstRate);
    updateProductsFile();

    for(int i = 0; i < 20; i++) {
        item[i] = {};
    }
    cartItemsCount = 0;

    setColor(1);
    cout << string(100, '=') << "\n" << endl;
    setColor(7);
    //navigating back to user inventory panel
    userInventoryPanel();
}

void dailySalesReport() {
    ifstream sales("sales.txt");
    if(!sales) {
        cout << "No sales data found!\n";
        return;
    }

    string date, time, name;
    int id, qty;
    double price, total, gst, net;

    string dates[100];
    double revenue[100];
    int count = 0;

    //reading sales data
    while(sales >> date >> time >> id >> name >> qty >> price >> total >> gst >> net) {
        bool found = false;
        for(int i = 0; i < count; i++) {
            if(dates[i] == date) {
                revenue[i] += net;
                found = true;
                break;
            }
        }

        if(!found) {
            dates[count] = date;
            revenue[count] = net;
            count++;
        }
    }

    sales.close();

    setColor(2);
    cout << "\n======================= DAILY SALES REPORT =======================\n";
    setColor(7);
    for(int i = 0; i < count; i++) {
        cout << dates[i] << "  Total Revenue: Rs. " << revenue[i] << endl;
    }

    setColor(1);
    cout << string(100, '=') << "\n" << endl;
    setColor(7);
    //navigating back to sales report panel
    salesReportPanel();
}

void monthlySalesReport() {
    ifstream sales("sales.txt");
    if(!sales) {
        cout << "No sales data found!\n";
        return;
    }

    string date, time, name;
    int id, qty;
    double price, total, gst, net;

    string months[50];
    double revenue[50];
    int count = 0;

    while(sales >> date >> time >> id >> name >> qty >> price >> total >> gst >> net) {
        string month = date.substr(0, 7);
        bool found = false;
        //aggregating revenue by month
        for(int i = 0; i < count; i++) {
            if(months[i] == month) {
                revenue[i] += net;
                found = true;
                break;
            }
        }

        if(!found) {
            months[count] = month;
            revenue[count] = net;
            count++;
        }
    }

    sales.close();

    setColor(2);
    cout << "\n======================= MONTHLY SALES REPORT =======================\n";
    setColor(7);

    for(int i = 0; i < count; i++) {
        cout << months[i] << "  Total Revenue: Rs. " << revenue[i] << endl;
    }

    setColor(1);
    cout << string(100, '=') << "\n" << endl;
    setColor(7);
    //navigating back to sales report panel
    salesReportPanel();
}


void totalRevenueReport() {
    ifstream sales("sales.txt");
    if(!sales) {
        cout << "No sales data found!\n";
        return;
    }

    string date, time, name;
    int id, qty;
    double price, total, gst, net;

    double grandTotal = 0;

    //calculating grand total revenue
    while(sales >> date >> time >> id >> name >> qty >> price >> total >> gst >> net) {
        grandTotal += net;
    }

    sales.close();

    setColor(2);
    cout << "\n======================= TOTAL REVENUE REPORT =======================\n";
    setColor(7);
    cout << "Overall Revenue: Rs. " << grandTotal << endl;

    setColor(1);
    cout << string(100, '=') << "\n" << endl;
    setColor(7);
    //navigating back to sales report panel
    salesReportPanel();
}