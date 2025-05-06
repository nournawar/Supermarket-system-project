
#include <iostream>
#include <string>
#include <conio.h> 
#include <cctype> 
#include <fstream>
#include <cstdlib> 

using namespace std;

const int maxcustomers = 500;
const int productsize = 5;
const int max_order_products = 30;
const int categorysize = 6;

struct customer_info
{
    int ID;
    string Password;
    string Name;
    string phonenumber;
    string address;
} customers[maxcustomers];

struct productsDetails
{
    string name, code, productionDate, expiryDate;
    float price;
    int quantity;
};

struct categories
{
    string name;
    productsDetails product[productsize];
}category[categorysize];

struct order
{
    string productname[max_order_products];
    int productquantity[max_order_products];
    float productprice[max_order_products];
    int count = 0;
} myorder;


void waitForEnter();
void login(int& customersCounter);
void sign_up(int& customersCounter);
void MainMenu(int& customersCounter);
void AddProductToOrder();
void customerMenu(int& customersCounter, categories category[]);
void viewProductsMenu(categories category[]);
void productDetails(categories category[]);
double calctotalprice();
void editCustomerInfo(int& customersCounter);
void view_cart();
void edit_order();
void logout(int& customersCounter);
void readFromFile(int& customersCounter);
void writeToFile(int customersCounter);
void loadFromFile(categories category[], int& categoryCount, int& productCount);
void saveToFile(categories category[], int& categoryCount, int& productCount);


int main()
{
    int customersCounter = 0;
    int categoryCount = 0;
    int productCount = 0;
    readFromFile(customersCounter);
    loadFromFile(category, categoryCount, productCount);
    MainMenu(customersCounter);
    saveToFile(category, categoryCount, productCount);
    writeToFile(customersCounter);
    return 0;
}


void sign_up(int& customersCounter)
{
    customer_info customer;
    string name, phone, password;
    bool isvalid = true;

    do
    {
        cout << "Enter Your Name: \n"; //letters only 
        cin.ignore();
        getline(cin, name);
        for (char c : name)
        {
            if (!(isalpha(c) || c == ' '))
            {
                isvalid = false;
                cout << "Invalid name! Only letters are allowed.\n";
                break;
            }
        }
    } while (!isvalid);

    customer.Name = name;

    do
    {
        isvalid = true;
        cout << "Enter Your Password (4 digits): ";
        cin >> password;
        if (password.length() != 4)
        {
            cout << "password must be exactly 4 characters.\n";
            isvalid = false;
        }
    } while (!isvalid);
    customer.Password = password;

    do
    {
        isvalid = true;
        cout << "Enter Your Phone Number (11 digits): ";
        cin >> phone;

        if (phone.length() != 11)
        {
            cout << "Phone number must be exactly 11 digits.\n";
            isvalid = false;
        }
        else {
            for (char c : phone) {
                if (!isdigit(c)) {
                    cout << "Phone number must contain digits only.\n";
                    isvalid = false;
                    break;
                }
            }
        }
    } while (!isvalid);

    customer.phonenumber = phone;
    string address;
    cout << "Enter Your Address: ";
    cin.ignore();
    getline(cin, address);
    customer.address = address;

    if (customersCounter < maxcustomers)
    {
        customer.ID = customersCounter + 2;
        cout << "Registration successful! Welcome, " << customer.Name << endl;
        cout << "Your ID is: " << customer.ID << endl;

        customers[customersCounter] = customer;
        customersCounter++;
        system("pause");
        system("cls");
        cout << "Please log in to open system\n";
        MainMenu(customersCounter);
    }
    else
    {
        cout << "Cannot register. Customer list is full.\n";
    }
}

void login(int& customersCounter)
{
    string name;
    int  id;
    string password;
    string final_pass;
    int index_cust = -1, trials = 0;
    bool password_correct = false;
    bool name_correct = false;

    cout << "Enter Name: \n";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Password (4 digits): ";

    for (int i = 0;i < 4;i++)
    {
        password = _getch();
        final_pass += password;
        cout << "*";
    }
    while (trials < 3 && !password_correct)
    {
        name_correct = false;
        for (int i = 0;i < maxcustomers;i++)
        {
            if (name == customers[i].Name)
            {
                index_cust = i;
                name_correct = true;
                break;
            }

        }
        if (name_correct == true)
        {
            if (customers[index_cust].Password == final_pass)
            {
                password_correct = true;
            }
            else
            {
                cout << '\n';
                cout << "Wrong password please try again\n";
                trials++;
                cout << "Enter PassWord : ";
                final_pass.erase();
                for (int i = 0;i < 4;i++)
                {
                    password = _getch();
                    final_pass += password;
                    cout << "*";

                }
            }
        }
        else
        {
            cout << " Name is wrong please try again\n";
            trials++;
            cout << "Enter Name: ";
            name.erase();
            getline(cin, name);
        }
    }

    if (password_correct == true)
    {
        cout << "\nCorrect password and Name\n";
        system("cls");
        customerMenu(customersCounter, category);
    }
    else if (password_correct == false)
    {
        cout << "\nYou may have forgotten your password!\n";
        cout << "You can login with your ID \n";
        cout << " Enter id :" << endl;
        cin >> id;
        if (id == customers[index_cust].ID)
        {
            cout << "login successfully and please change your password \n";
            editCustomerInfo(customersCounter);
            customerMenu(customersCounter, category);
        }
        else
        {
            cout << "Your account not found please sign up at first \n";
            sign_up(customersCounter);
        }
    }

}
void MainMenu(int& customersCounter)
{


    cout << string(70, ' ') << "WELCOME TO SHOPPINGO" << string(45, ' ') << endl; //______________
    cout << string(156, '_') << endl;
    cout << string(70, ' ') << "Press 1 to Sign Up " << string(45, ' ') << '\n';
    cout << string(70, ' ') << "Press 2 to Log in " << string(45, ' ') << '\n';
    int choice;
    while (true)
    {
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number only.\n";
            continue;

        }
        break;
    }

    switch (choice)
    {
    case 1:
        sign_up(customersCounter);
        break;
    case 2:
        login(customersCounter);
        break;
    default:
        do
        {
            cout << endl;
            cout << "Invalid choice. Please try again.\n";
            cout << string(70, ' ') << "Press 1 to Sign Up " << string(45, ' ') << '\n';
            cout << string(70, ' ') << "Press 2 to Log in " << string(45, ' ') << '\n';
            cin >> choice;

            if (choice == 1)
                sign_up(customersCounter);
            else if (choice == 2)
                login(customersCounter);


        } while (choice > 2 || choice < 1);
        break;
    }

}

void customerMenu(int& customersCounter, categories category[])
{

    int choice;

    do {


        cout << endl;
        cout << string(70, ' ') << "CUSTOMER MENU" << string(70, ' ') << endl;
        cout << string(156, '_') << endl;
        cout << string(70, ' ') << "1. View Available Products" << string(70, ' ') << endl;
        cout << string(70, ' ') << "2. Product Details " << string(70, ' ') << endl;
        cout << string(70, ' ') << "3. Add Product to Cart" << string(70, ' ') << endl;
        cout << string(70, ' ') << "4. Edit Your Order" << string(70, ' ') << endl;
        cout << string(70, ' ') << "5. View Cart" << string(70, ' ') << endl;
        cout << string(70, ' ') << "6. Calculate Total Price" << string(70, ' ') << endl;
        cout << string(70, ' ') << "7. Edit info" << string(70, ' ') << endl;
        cout << string(70, ' ') << "8. Log Out" << string(70, ' ') << endl;
        cout << string(70, ' ') << "9. Exit" << string(70, ' ') << endl;
        cout << string(156, '_') << endl;

        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number only.\n";
            continue;

        }
        switch (choice)
        {
        case 1:
            viewProductsMenu(category);
            waitForEnter();
            system("cls");
            break;
        case 2:
            productDetails(category);


            break;
        case 3:
            AddProductToOrder();

            break;
        case 4:
            edit_order();
            //waitForEnter();
            break;
        case 5:
            view_cart();
            waitForEnter();
            break;
        case 6:
            cout << "Total Price is " << calctotalprice() << "$ \n";
            waitForEnter();
            break;
        case 7:
            editCustomerInfo(customersCounter);
            // waitForEnter();
            break;
        case 8:
            logout(customersCounter);
            break;
        case 9:
            break;

        default: cout << "Invalid choice. Try again.\n";
            break;
        }
    } while (choice != 9);

}

void viewProductsMenu(categories category[])
{
    for (int i = 0; i < categorysize; i++)
    {
        cout << string(70, ' ') << " Category: " << category[i].name << string(70, ' ') << endl;

        for (int j = 0; j < productsize; j++)
        {
            cout << string(70, ' ')
                << "  Name: " << category[i].product[j].name
                << "  Price: " << category[i].product[j].price << '$' << string(70, ' ') << endl;
        }
    }
    cout << string(156, '_') << endl;
}

void productDetails(categories category[])
{
    char ans;
    string targetProduct;
    do {



        cout << "Please enter the name of the product that you need its details : " << endl;
        cin >> targetProduct;


        bool valid = false;
        do {
            for (int j = 0; j < categorysize; j++) {
                for (int i = 0; i < productsize; i++) {
                    if (targetProduct == category[j].product[i].name) {
                        cout << string(70, ' ') << "Category: " << category[j].name << string(70, ' ') << endl
                            << string(70, ' ') << "Product name: " << category[j].product[i].name << string(70, ' ') << endl
                            << string(70, ' ') << "Product code: " << category[j].product[i].code << string(70, ' ') << endl
                            << string(70, ' ') << "Production date: " << category[j].product[i].productionDate << string(70, ' ') << endl
                            << string(70, ' ') << "Expiry date: " << category[j].product[i].expiryDate << string(70, ' ') << endl
                            << string(70, ' ') << "Price: " << category[j].product[i].price << string(70, ' ') << endl
                            << string(70, ' ') << "Available quantity: " << category[j].product[i].quantity << string(70, ' ') << endl;
                        valid = true;
                        break;
                    }

                }
            }
            if (!valid)
            {
                cout << "Please enter product name correctly" << endl;

                cin >> targetProduct;
            }


        } while (!valid);

        cout << "Would you like to continue?(y/n)";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    // system("cls");
}

void AddProductToOrder()
{
    int quantity;
    string name;
    viewProductsMenu(category);

    char selection;
    do
    {
        bool found = false;
        cout << "Enter Product Name: ";
        cin >> name;

        cout << "Enter Quantity: ";
        cin >> quantity;

        if (quantity <= 0)
        {
            cout << "Quantity is invalid\n";
            continue;
        }

        for (int i = 0; i < categorysize; i++)
        {
            for (int j = 0; j < productsize; j++)
            {
                if (category[i].product[j].name == name)
                {
                    found = true;

                    if (quantity > category[i].product[j].quantity)
                    {
                        cout << "Sorry, we only have " << category[i].product[j].quantity << " in stock.\n";
                        break;
                    }


                    bool alreadyInCart = false;
                    for (int f = 0; f < myorder.count; f++)
                    {
                        if (myorder.productname[f] == name)
                        {
                            myorder.productquantity[f] += quantity;
                            alreadyInCart = true;
                            break;
                        }
                    }

                    if (!alreadyInCart)
                    {
                        if (myorder.count < max_order_products)
                        {
                            myorder.productname[myorder.count] = name;
                            myorder.productquantity[myorder.count] = quantity;
                            myorder.productprice[myorder.count] = category[i].product[j].price;
                            myorder.count++;
                        }
                        else
                        {
                            cout << "Order is full\n";
                        }
                    }

                    category[i].product[j].quantity -= quantity;
                    cout << "Item is added\n";

                    break;
                }
            }

            if (found) break;
        }

        if (!found)
        {
            cout << "Invalid product name\n";
        }

        cout << "Do you want to add another product? (Y/N): ";
        cin >> selection;
    } while (selection == 'Y' || selection == 'y');
}

double calctotalprice()
{
    double total = 0;
    double itemtotal = 0;

    for (int i = 0; i < myorder.count; i++)
    {
        string name = myorder.productname[i];
        int quantity = myorder.productquantity[i];
        float price = myorder.productprice[i];
        for (int j = 0; j < categorysize; j++)
        {
            for (int m = 0;m < productsize;m++)
            {
                if (category[j].product[m].name == name)
                {
                    itemtotal = price * quantity;
                    cout << quantity << " " << name << " x " << price << " $ " << " = " << itemtotal << '$' << endl;
                    total += itemtotal;


                }
            }
        }
    }

    return total;
}

void view_cart()
{
    if (myorder.count == 0)
    {
        cout << "Your cart is empty!\n";
    }
    else
    {

        cout << string(70, ' ') << "Your cart!" << string(70, ' ') << endl;
        int x = 1;
        cout << "Name" << "\t Selected quantity \n";
        for (int i = 0; i < myorder.count; i++)
        {
            cout << x << "-" << myorder.productname[i] << " " << '\t' << myorder.productquantity[i] << endl;
            x++;
        }
    }
    cout << "Total price is " << calctotalprice() << '$' << endl;
}

void edit_order()
{
    int sequence;
    while (true)
    {
        if (myorder.count <= 0)
        {
            cout << "Your cart is empty! Please select items into your cart first.";
            break;
        }
        else
        {

            view_cart();
            cout << "Select item number in the list: ";
            cin >> sequence;

            if (sequence < 1 || sequence > myorder.count) {
                cout << "Invalid item number.\n";
                continue;
            }

            int choice;
            cout << "Press 1 to Edit Quantity\n\n";
            cout << "Press 2 to Delete this product from your cart\n\n";
            cin >> choice;

            string name = myorder.productname[sequence - 1];
            int old_quantity = myorder.productquantity[sequence - 1];

            switch (choice)
            {
            case 1:
            {
                int new_quantity;
                cout << "Enter new number of items: ";
                cin >> new_quantity;

                if (new_quantity < 0) {
                    cout << "Invalid quantity.\n";
                    break;
                }

                for (int i = 0; i < categorysize; i++) {
                    for (int j = 0; j < productsize; j++) {
                        if (category[i].product[j].name == name) {
                            int availableStock = category[i].product[j].quantity + old_quantity;

                            if (new_quantity > availableStock) {
                                cout << "Not enough stock available.\n\n";
                                break;
                            }

                            category[i].product[j].quantity = availableStock - new_quantity;
                            myorder.productquantity[sequence - 1] = new_quantity;
                            cout << "Quantity updated.\n\n";
                            break;
                        }
                    }
                }
                break;
            }

            case 2:

                for (int i = 0; i < categorysize; i++) {
                    for (int j = 0; j < productsize; j++) {
                        if (category[i].product[j].name == name) {
                            category[i].product[j].quantity += old_quantity;
                        }
                    }
                }


                for (int i = sequence - 1; i < myorder.count - 1; i++) {
                    myorder.productname[i] = myorder.productname[i + 1];
                    myorder.productquantity[i] = myorder.productquantity[i + 1];
                    myorder.productprice[i] = myorder.productprice[i + 1];
                }
                myorder.count--;
                cout << "Item removed.\n";
                break;

            default:
                cout << "Invalid option.\n";
            }
        }
        char again;
        cout << "Do you want to edit anything else? (Y/N): ";
        cin >> again;
        if (again != 'Y' && again != 'y')
            break;
    }
}
void editCustomerInfo(int& customersCounter)
{
    char selection = 'y';

    while (selection == 'y')
    {
        string phone, password;
        bool isvalid = true;
        int choice, id;
        cout << "Enter Your ID: ";
        cin >> id;
        if (id > customersCounter + 1 || id < 1)
        {
            cout << "Invalid ID. Please try again\n";
            continue;
        }
        do
        {
            cout << "\n--- Edit Menu ---\n";
            cout << "1. Edit Password\n";
            cout << "2. Edit Phone Number\n";
            cout << "3. Edit Address\n";
            cout << "4. Exit\n";
            cout << "Enter Your Choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                do
                {
                    isvalid = true;
                    cout << "Enter New Password (4 characters): ";
                    cin >> password;
                    if (password.length() != 4)
                    {
                        cout << "Password must be exactly 4 characters.\n";
                        isvalid = false;
                    }
                } while (!isvalid);
                customers[id - 1].Password = password;

                cout << "Password edited successfully!";
                break;
            case 2:
                do
                {
                    isvalid = true;
                    cout << "Enter New Phone Number (11 digits): ";
                    cin >> phone;

                    if (phone.length() != 11)
                    {
                        cout << "Phone number must be exactly 11 digits.\n";
                        isvalid = false;
                    }
                    else {
                        for (char c : phone) {
                            if (!isdigit(c)) {
                                cout << "Phone number must contain digits only.\n";
                                isvalid = false;
                                break;
                            }
                        }
                    }
                } while (!isvalid);
                customers[id - 1].phonenumber = phone;
                cout << "Phone Number edited successfully!";
                break;
            case 3:
                cout << "Enter New Address: ";
                cin >> customers[id - 1].address;
                cout << "Address edited successfully!" << endl;
                break;
            case 4:
                cout << "Exiting Edit Menu\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
            cout << "\nDo you want to edit something else? (y/n): ";
            cin >> selection;

            if (selection != 'y')
                break;
        } while (choice != 4);
        customerMenu(customersCounter, category);
    }
}
void logout(int& customersCounter)
{
    int num;
    cout << " press 1. sign up" << endl;
    cout << " press 2. log in" << endl;
    cin >> num;
    switch (num)
    {
    case 1:
        sign_up(customersCounter);
        break;
    case 2:
        login(customersCounter);
        break;
    default:
    {
        do
        {
            cout << "\n wrong choice\n";
            cout << " 1. sign up" << endl;
            cout << " 2. log in" << endl;
            cin >> num;
            switch (num)
            {
            case 1:
                sign_up(customersCounter);
                break;
            case 2:
                login(customersCounter);
                break;
            default:
                break;

            }
        } while (num != 2 || num != 1);
    }
    }
}

void readFromFile(int& customersCounter)
{
    ifstream infile("D:\\Project1\\Projectfinal\\x64\\Debug\\categories&products.txt");
    if (!infile)
    {
        cout << "Failed to open file: customers info.txt" << endl;
        return;
    }
    int totalRecords;
    infile >> totalRecords;
    infile.ignore();
    for (int i = 0; i < totalRecords; i++)
    {
        string name, password, phone, address;
        int id;

        getline(infile, name);
        infile >> id;
        infile.ignore();
        getline(infile, password);
        getline(infile, phone);
        getline(infile, address);

        customers[i].Name = name;
        customers[i].ID = id;
        customers[i].Password = password;
        customers[i].phonenumber = phone;
        customers[i].address = address;
    }
    customersCounter = totalRecords - 1;
    infile.close();
}

void writeToFile(int customersCounter)
{
    ofstream outfile("D:\\Project1\\Projectfinal\\x64\\Debug\\categories&products.txt");
    if (!outfile)
    {
        cout << "Failed to open file for writing: customers info.txt" << endl;
        return;
    }

    outfile << customersCounter + 1 << endl;
    for (int i = 0; i <= customersCounter; i++)
    {
        outfile << customers[i].Name << endl;
        outfile << customers[i].ID << endl;
        outfile << customers[i].Password << endl;
        outfile << customers[i].phonenumber << endl;
        outfile << customers[i].address << endl;
    }
    outfile.close();
}

void loadFromFile(categories category[], int& categoryCount, int& productCount)
{
    ifstream inFile("D:\\Project1\\Projectfinal\\x64\\Debug\\categories&products.txt");
    if (!inFile)
    {
        cout << "Failed to open file: products.txt" << endl;
        return;
    }
    int categorycount, productcount;
    inFile >> categorycount;
    inFile >> productcount;
    categoryCount = categorycount;
    productCount = productcount;
    inFile.ignore();
    for (int i = 0; i < categorycount; i++)
    {

        string categoryName;

        getline(inFile, categoryName);


        category[i].name = categoryName;



        for (int j = 0; j < productcount; j++)
        {
            string productName, code, prodDate, expDate;
            int quantity;
            float price;


            getline(inFile, productName);
            inFile >> quantity;
            inFile.ignore();
            getline(inFile, code);
            getline(inFile, expDate);
            getline(inFile, prodDate);
            inFile >> price;
            inFile.ignore();

            category[i].product[j].name = productName;
            category[i].product[j].quantity = quantity;

            category[i].product[j].code = code;

            category[i].product[j].productionDate = prodDate;

            category[i].product[j].expiryDate = expDate;

            category[i].product[j].price = price;
        }
    }

    inFile.close();
}

void saveToFile(categories category[], int& categoryCount, int& productCount)
{
    ofstream outFile("D:\\Project1\\Projectfinal\\x64\\Debug\\categories&products.txt");
    if (!outFile)
    {
        cout << "Failed to open file for writing!" << endl;
        return;
    }

    outFile << categoryCount << endl << productCount << endl;

    for (int i = 0; i < categoryCount; i++)
    {
        string categoryName = category[i].name;
        outFile << categoryName << endl;

        for (int j = 0; j < productCount; j++)
        {
            string productName = category[i].product[j].name;
            int quantity = category[i].product[j].quantity;
            string code = category[i].product[j].code;
            string prodDate = category[i].product[j].productionDate;
            string expDate = category[i].product[j].expiryDate;
            float price = category[i].product[j].price;

            outFile << productName << endl;
            outFile << quantity << endl;
            outFile << code << endl;
            outFile << prodDate << endl;
            outFile << expDate << endl;
            outFile << price << endl;
        }
    }

    outFile.close();
}
void waitForEnter() {
    cout << "Press Enter to continue...";
    cin.ignore();  // Clear any leftover input
    cin.get();     // Wait for Enter key
};
