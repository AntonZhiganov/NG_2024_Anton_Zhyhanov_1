#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> values(5);

    for (int elem = 0; elem < 5; elem++) {
        cout << "Enter " << (elem + 1) << " value: ";
        cin >> values[elem];
    }

    int maxHeight = 0;
    for (int value : values) {
        if (value > maxHeight) {
            maxHeight = value;
        }
    }

    for (int row = 0; row < maxHeight; row++) {
        for (int elem = 0; elem < 5; elem++) {
            if (values[elem] > row) {
                cout << "* ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }

    return 0;
}
