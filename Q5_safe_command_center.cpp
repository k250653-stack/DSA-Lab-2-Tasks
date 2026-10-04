#include <iostream>
using namespace std;

class SafeCommandCenter {
private:
    int* commands;
    int capacity;

public:
    SafeCommandCenter() : capacity(5) {
        commands = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            commands[i] = 0;
        }
    }

    SafeCommandCenter(const SafeCommandCenter&) = delete;
    SafeCommandCenter& operator=(const SafeCommandCenter&) = delete;

    ~SafeCommandCenter() {
        delete[] commands;
    }

    bool safeWrite(int index, int value) {
        if (index < 0 || index >= capacity) {
            cout << "CRITICAL ERROR: Index " << index << " is outside buffer [0-" << (capacity - 1) << "]." << endl;
            cout << "Rover Emergency Braking Triggered!" << endl;
            return false;
        }
        if (value < 0 || value > 100) {
            cout << "CRITICAL ERROR: Speed " << value << " is outside allowed range [0-100]." << endl;
            cout << "Rover Emergency Braking Triggered!" << endl;
            return false;
        }
        commands[index] = value;
        cout << "Command accepted: slot " << index << " = " << value << endl;
        return true;
    }

    void display() const {
        cout << "Planned command sequence: ";
        for (int i = 0; i < capacity; i++) {
            cout << commands[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    SafeCommandCenter center;
    int total;

    cout << "How many commands will be transmitted? ";
    cin >> total;

    for (int i = 0; i < total; i++) {
        int index, speed;
        cout << "Enter index and speed: ";
        cin >> index >> speed;
        center.safeWrite(index, speed);
    }

    center.display();
    return 0;
}
