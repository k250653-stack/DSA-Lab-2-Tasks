#include <iostream>
using namespace std;

const int CLASSES = 3;
const char* CLASS_NAMES[CLASSES] = {"First Class", "Business Class", "Economy Class"};

int main() {
    int seatsPerRow[CLASSES] = {2, 4, 6};

    int** cabin = new int*[CLASSES];
    for (int i = 0; i < CLASSES; i++) {
        cabin[i] = new int[seatsPerRow[i]];
        for (int j = 0; j < seatsPerRow[i]; j++) {
            cabin[i][j] = 0;
        }
    }

    while (true) {
        int row, seat;
        cout << "Enter class (0 = First, 1 = Business, 2 = Economy, -1 = exit): ";
        if (!(cin >> row)) break;
        if (row == -1) break;

        if (row < 0 || row >= CLASSES) {
            cout << "Error: Invalid class selection!" << endl;
            continue;
        }

        cout << "Enter seat number: ";
        if (!(cin >> seat)) break;

        if (seat < 0 || seat >= seatsPerRow[row]) {
            cout << "Error: " << CLASS_NAMES[row] << " has only " << seatsPerRow[row] << " seat slots!" << endl;
            continue;
        }

        if (cabin[row][seat] == 1) {
            cout << "Seat already reserved." << endl;
        } else {
            cabin[row][seat] = 1;
            cout << "Reserved: " << CLASS_NAMES[row] << ", seat " << seat << endl;
        }
    }

    cout << "\nFinal cabin layout (X = reserved, O = free):" << endl;
    for (int i = 0; i < CLASSES; i++) {
        cout << CLASS_NAMES[i] << ": ";
        for (int j = 0; j < seatsPerRow[i]; j++) {
            cout << (cabin[i][j] ? 'X' : 'O') << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < CLASSES; i++) {
        delete[] cabin[i];
    }
    delete[] cabin;
    return 0;
}
