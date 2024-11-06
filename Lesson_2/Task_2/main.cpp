#include <iostream>
using namespace std;

int main() {
    int values[5];

    for (int elem = 0; elem < 5; elem++) {
        cout << "Enter " << (elem + 1) << " value: ";
        cin >> values[elem];
    }

    int maxHeight = 0;
    for (int i = 0; i < 5; i++) {
        if (values[i] > maxHeight) {
            maxHeight = values[i];
        }
    }

    for (int row = 0; row < maxHeight; row++) {
        for (int i = 0; i < 5; i++) {
            if (values[i] > row) {
                cout << "* ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }

    return 0;
}
