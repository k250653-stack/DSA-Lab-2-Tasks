#include <iostream>
#include <string>
using namespace std;

int main() {
    int count;
    cout << "Enter number of passengers expected: ";
    cin >> count;

    if (count <= 0) {
        cout << "Invalid passenger count." << endl;
        return 1;
    }
    cin.ignore();

    string* passengers = new string[count];

    for (int i = 0; i < count; i++) {
        cout << "Enter name of passenger " << (i + 1) << ": ";
        getline(cin, passengers[i]);
    }

    cout << "\nBoarding sequence (last checked-in boards first):" << endl;
    for (int i = count - 1, order = 1; i >= 0; i--, order++) {
        cout << order << ". " << passengers[i] << endl;
    }

    delete[] passengers;
    passengers = nullptr;
    return 0;
}
