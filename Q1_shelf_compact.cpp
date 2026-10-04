#include <iostream>
#include <string>
using namespace std;

void displayShelf(const int shelf[], int size, const string& label) {
    cout << label << ": {";
    for (int i = 0; i < size; i++) {
        cout << shelf[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "}" << endl;
}

void compactShelf(int shelf[], int size) {
    int writeIndex = 0;
    for (int readIndex = 0; readIndex < size; readIndex++) {
        if (shelf[readIndex] != 0) {
            shelf[writeIndex++] = shelf[readIndex];
        }
    }
    while (writeIndex < size) {
        shelf[writeIndex++] = 0;
    }
}

int main() {
    const int SIZE = 6;
    int shelf[SIZE] = {102, 0, 305, 0, 401, 908};
    string command;

    displayShelf(shelf, SIZE, "Initial shelf");

    while (true) {
        cout << "Enter command (compact / exit): ";
        if (!(cin >> command)) break;

        if (command == "compact") {
            displayShelf(shelf, SIZE, "Before");
            compactShelf(shelf, SIZE);
            displayShelf(shelf, SIZE, "After ");
        } else if (command == "exit") {
            break;
        } else {
            cout << "Unknown command." << endl;
        }
    }
    return 0;
}
