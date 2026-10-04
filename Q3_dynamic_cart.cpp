#include <iostream>
#include <string>
using namespace std;

void addItem(string*& cart, int& size, int& capacity, const string& item) {
    if (size == capacity) {
        int newCapacity = capacity * 2;
        string* temp = new string[newCapacity];
        for (int i = 0; i < size; i++) {
            temp[i] = cart[i];
        }
        delete[] cart;
        cart = temp;
        cout << "[RESIZE] Capacity increased from " << capacity << " to " << newCapacity << endl;
        capacity = newCapacity;
    }
    cart[size++] = item;
}

void displayCart(const string* cart, int size, int capacity) {
    cout << "Cart (" << size << "/" << capacity << "): ";
    for (int i = 0; i < size; i++) {
        cout << cart[i];
        if (i < size - 1) cout << ", ";
    }
    cout << endl;
}

int main() {
    int capacity = 3;
    int size = 0;
    string* cart = new string[capacity];

    string items[7] = {"Laptop", "Mouse", "Keyboard", "Monitor", "Webcam", "Headset", "Charger"};

    for (int i = 0; i < 7; i++) {
        cout << "Adding item " << (i + 1) << ": " << items[i] << endl;
        addItem(cart, size, capacity, items[i]);
    }

    displayCart(cart, size, capacity);

    delete[] cart;
    cart = nullptr;
    return 0;
}
