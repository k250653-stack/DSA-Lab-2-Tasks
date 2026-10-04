#include <iostream>
using namespace std;

const int SUBJECTS = 3;

int** allocateGrid(int rows) {
    int** grid = new int*[rows];
    for (int i = 0; i < rows; i++) {
        grid[i] = new int[SUBJECTS];
    }
    return grid;
}

void releaseGrid(int** grid, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}

void displayGrid(int** grid, int rows) {
    cout << "Student | Sub1 Sub2 Sub3" << endl;
    for (int i = 0; i < rows; i++) {
        cout << "   " << (i + 1) << "    | ";
        for (int j = 0; j < SUBJECTS; j++) {
            cout << grid[i][j] << "    ";
        }
        cout << endl;
    }
}

void addNewStudent(int**& currentGrades, int& currentN) {
    cout << "\n[MEMORY] Old grid address: " << currentGrades << " (" << currentN << " students)" << endl;

    int** newGrades = allocateGrid(currentN + 1);
    cout << "[MEMORY] New grid allocated at: " << newGrades << " (" << (currentN + 1) << " students)" << endl;

    for (int i = 0; i < currentN; i++) {
        for (int j = 0; j < SUBJECTS; j++) {
            newGrades[i][j] = currentGrades[i][j];
        }
    }
    cout << "[VALIDATION] Copied grades of " << currentN << " existing students." << endl;

    cout << "Enter grades for the new transfer student (" << SUBJECTS << " subjects): ";
    for (int j = 0; j < SUBJECTS; j++) {
        cin >> newGrades[currentN][j];
    }

    releaseGrid(currentGrades, currentN);
    cout << "[VALIDATION] Old grid released." << endl;

    currentGrades = newGrades;
    currentN++;
    cout << "[VALIDATION] Main pointer now points to: " << currentGrades << endl;
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    if (n < 0) {
        cout << "Invalid number of students." << endl;
        return 1;
    }

    int** grades = allocateGrid(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter " << SUBJECTS << " grades for student " << (i + 1) << ": ";
        for (int j = 0; j < SUBJECTS; j++) {
            cin >> grades[i][j];
        }
    }

    cout << "\nGrades before enrollment:" << endl;
    displayGrid(grades, n);

    addNewStudent(grades, n);

    cout << "\nGrades after enrollment:" << endl;
    displayGrid(grades, n);

    releaseGrid(grades, n);
    return 0;
}
