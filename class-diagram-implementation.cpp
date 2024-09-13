#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <ctime>

using namespace std;

class Product {
private:
    string productId;
    string name;
    double price;
    int stock;

public:
    Product(string id, string n, double p, int s)
        : productId(id), name(n), price(p), stock(s) {}

    string getProductId() const { return productId; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    bool updateStock(int quantity) {
        if (stock >= quantity) {
            stock -= quantity;
            return true;
        } else {
            cout << "Insufficient stock." << endl;
            return false;
        }
    }

    void displayProduct() const {
        cout << setw(10) << productId
             << setw(25) << name
             << setw(10) << fixed << setprecision(2) << price
             << setw(10) << stock << endl;
    }
};

class Order {
private:
    int orderId;
    string orderDate;
    double totalAmount;
    string status;
    vector<Product> products;       // Vector to store products in the order
    vector<int> quantities;         // Vector to store corresponding quantities

public:
    Order(int id, const string& date, double amount, const string& stat)
        : orderId(id), orderDate(date), totalAmount(amount), status(stat) {}

    void addProductToOrder(const Product& product, int quantity) {
        products.push_back(product);
        quantities.push_back(quantity);
    }

    void displayOrder() const {
        cout << "Order ID: " << orderId << endl;
        cout << "Order Date: " << orderDate << endl;
        cout << "Status: " << status << endl;
        cout << "Products in this order:\n";
        cout << setw(10) << "Product ID"
             << setw(25) << "Name"
             << setw(10) << "Price"
             << setw(10) << "Quantity" << endl;

        for (size_t i = 0; i < products.size(); ++i) {
            cout << setw(10) << products[i].getProductId()
                 << setw(25) << products[i].getName()
                 << setw(10) << fixed << setprecision(2) << products[i].getPrice()
                 << setw(10) << quantities[i] << endl;
        }

        cout << "Total Amount: " << fixed << setprecision(2) << totalAmount << endl;
    }

    int getOrderId() const { return orderId; }
};

class ShoppingCart {
private:
    struct ShoppingCartItem {
        Product product;
        int quantity;

        ShoppingCartItem(Product p, int q) : product(p), quantity(q) {}
    };

    vector<ShoppingCartItem> items;
    vector<Order> orders;
    static int orderCounter;

public:
    ShoppingCart() {}

    void addProduct(Product product, int quantity) {
        bool found = false;
        for (auto &item : items) {
            if (item.product.getProductId() == product.getProductId()) {
                if (product.updateStock(quantity)) {
                    item.quantity += quantity;
                }
                found = true;
                break;
            }
        }
        if (!found && product.updateStock(quantity)) {
            items.push_back(ShoppingCartItem(product, quantity));
        }
    }

    void viewCart() {
        if (items.empty()) {
            cout << "Shopping Cart is empty." << endl;
            return;
        }

        cout << setw(10) << "Product ID"
             << setw(25) << "Name"
             << setw(10) << "Price"
             << setw(10) << "Quantity" << endl;

        for (auto &item : items) {
            cout << setw(10) << item.product.getProductId()
                 << setw(25) << item.product.getName()
                 << setw(10) << fixed << setprecision(2) << item.product.getPrice()
                 << setw(10) << item.quantity << endl;
        }

        char checkoutChoice;
        cout << "Do you want to check out all the products? (Y/N): ";
        while (true) {
            cin >> checkoutChoice;
            if (checkoutChoice == 'Y' || checkoutChoice == 'y' || checkoutChoice == 'N' || checkoutChoice == 'n') {
                break;
            } else {
                cout << "Invalid choice. Please enter Y or N: ";
            }
        }

        if (checkoutChoice == 'Y' || checkoutChoice == 'y') {
            int id = ++orderCounter;
            time_t now = time(0);
            tm *ltm = localtime(&now);
            string currentDate = to_string(ltm->tm_mday) + "/" +
                                 to_string(ltm->tm_mon + 1) + "/" +
                                 to_string(ltm->tm_year + 1900);

            double totalAmount = calculateCartTotal();
            string status = "Completed";

            Order newOrder(id, currentDate, totalAmount, status);

            // Add products to the order
            for (auto &item : items) {
                newOrder.addProductToOrder(item.product, item.quantity);
            }

            orders.push_back(newOrder);
            clearCart();
        }
    }

    double calculateCartTotal() {
        double total = 0;
        for (auto &item : items) {
            total += item.product.getPrice() * item.quantity;
        }
        return total;
    }

    void viewOrder(int orderId) {
        for (const auto &order : orders) {
            if (order.getOrderId() == orderId) {
                order.displayOrder();
                break;
            }
        }
    }

    void viewAllOrders() {
        if (orders.empty()) {
            cout << "No orders have been placed." << endl;
            return;
        }

        for (const auto &order : orders) {
            order.displayOrder();
            cout << "-------------------------------------------------" << endl;
        }
    }

    void clearCart() {
        items.clear();
    }
};

int ShoppingCart::orderCounter = 0;

string getValidatedString() {
    string value;
    while (true) {
        cin >> value;
        if (!value.empty()) {
            return value;
        } else {
            cout << "Invalid input. Please enter a valid product ID: ";
        }
    }
}

int getValidatedInteger() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid quantity: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int main() {
    cout << "\nWelcome To MERS Clothing Line Shopping System!\n";

    vector<Product> products = {
        Product("XL001", "White T-Shirt S", 199, 20),
        Product("XL002", "White T-Shirt M", 199, 50),
        Product("XL003", "White T-Shirt L", 199, 40),
        Product("XL004", "White T-Shirt XL", 199, 15),
        Product("HL001", "Black Hoodie M", 499, 30),
        Product("HL002", "Black Hoodie L", 499, 20),
        Product("HL003", "Black Hoodie XL", 499, 60),
        Product("CP001", "White Premium Cap", 299, 50),
        Product("CP002", "Black Premium Cap", 299, 60),
        Product("CP003", "Red Premium Cap", 299, 20)
    };

    ShoppingCart cart;
    int choice;

    do {
        cout << "Menu:\n";
        cout << "1. View Products\n";
        cout << "2. View Shopping Cart\n";
        cout << "3. View All Orders\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        choice = getValidatedInteger();

        switch (choice) {
            case 1: {
                system("cls");
                cout << "Available Products:\n";
                cout << setw(10) << "Product ID"
                     << setw(25) << "Name"
                     << setw(10) << "Price"
                     << setw(10) << "Stock" << endl;
                for (auto &product : products) {
                    product.displayProduct();
                }

                char addMore;
                do {
                    string productId;
                    int quantity;
                    cout << "Enter the Product ID to add to cart: ";
                    productId = getValidatedString();
                    cout << "Enter the quantity: ";
                    quantity = getValidatedInteger();

                    bool found = false;
                    for (auto &product : products) {
                        if (product.getProductId() == productId) {
                            cart.addProduct(product, quantity);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "Invalid Product ID!" << endl;
                    }

                    cout << "Do you want to add another product? (Y/N): ";
                    while (true) {
                        cin >> addMore;
                        if (addMore == 'Y' || addMore == 'y' || addMore == 'N' || addMore == 'n') {
                            break;
                        } else {
                            cout << "Invalid choice. Please enter Y or N: ";
                        }
                    }
                } while (addMore == 'Y' || addMore == 'y');
                break;
            }
            case 2:
                system("cls");
                cart.viewCart();
                break;
            case 3:
                system("cls");
                cart.viewAllOrders();
                break;
            case 4:
                cout << "Bye!\nThank you!" << endl;
                break;
            default:
                system("cls");
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
