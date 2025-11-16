#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// ---------------- Product Class ----------------
class Product {
public:
    int id;
    string name;
    double price;

    Product(int id, string name, double price) {
        this->id = id;
        this->name = name;
        this->price = price;
    }
};

// ---------------- CartItem Class ----------------
class CartItem {
public:
    Product product;
    int quantity;

    CartItem(Product p, int qty) : product(p), quantity(qty) {}

    double getItemTotal() {
        return product.price * quantity;
    }
};

// ---------------- Supermarket Class ----------------
class Supermarket {
private:
    vector<Product> products;
    vector<CartItem> cart;

public:
    Supermarket() {
        // Preloaded Products (Admin side)
        products.push_back(Product(1, "Milk", 40));
        products.push_back(Product(2, "Bread", 30));
        products.push_back(Product(3, "Eggs (Dozen)", 60));
        products.push_back(Product(4, "Rice (1kg)", 55));
        products.push_back(Product(5, "Oil (1L)", 130));
    }

    // Display all products
    void showProducts() {
        cout << "\nAvailable Products:\n";
        cout << "--------------------------------------\n";
        cout << left << setw(5) << "ID"
             << setw(18) << "Product"
             << "Price\n";
        cout << "--------------------------------------\n";

        for (auto &p : products) {
            cout << left << setw(5) << p.id
                 << setw(18) << p.name
                 << "₹" << p.price << endl;
        }
    }

    // Add to Cart
    void addToCart() {
        int id, qty;
        cout << "\nEnter Product ID to Add: ";
        cin >> id;

        // Find product
        for (auto &p : products) {
            if (p.id == id) {
                cout << "Enter quantity: ";
                cin >> qty;
                cart.push_back(CartItem(p, qty));
                cout << "Item added to cart!\n";
                return;
            }
        }
        cout << "❌ Invalid Product ID!\n";
    }

    // Generate Bill
    void generateBill(string customerName) {
        if (cart.empty()) {
            cout << "\nCart is empty! Add items first.\n";
            return;
        }

        double total = 0;
        cout << "\n=============== Supermarket Bill ===============\n";
        cout << "Customer: " << customerName << "\n\n";
        cout << left << setw(18) << "Product"
             << setw(10) << "Qty"
             << "Total\n";
        cout << "-----------------------------------------------\n";

        for (auto &item : cart) {
            double itemTotal = item.getItemTotal();
            total += itemTotal;
            cout << left << setw(18) << item.product.name
                 << setw(10) << item.quantity
                 << "₹" << itemTotal << endl;
        }

        // Discount Logic
        double discount = 0;
        if (total > 500) discount = total * 0.10;        // 10% discount
        else if (total > 200) discount = total * 0.05;   // 5% discount

        double finalAmount = total - discount;

        cout << "\n-----------------------------------------------\n";
        cout << "Subtotal: ₹" << total << endl;
        cout << "Discount: ₹" << discount << endl;
        cout << "Final Payable Amount: ₹" << finalAmount << endl;
        cout << "=============== Thank You! Visit Again ===============\n";
    }
};

// ---------------- Main Function ----------------
int main() {
    Supermarket market;
    string name;
    int choice;

    cout << "Enter Customer Name: ";
    getline(cin, name);

    do {
        cout << "\n========== Supermarket Menu ==========\n";
        cout << "1. Show Products\n";
        cout << "2. Add to Cart\n";
        cout << "3. Generate Bill\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            market.showProducts();
            break;
        case 2:
            market.addToCart();
            break;
        case 3:
            market.generateBill(name);
            break;
        case 4:
            cout << "Exiting... Thank you!\n";
            break;
        default:
            cout << "❌ Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
