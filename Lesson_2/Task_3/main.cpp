#include <iostream>
using namespace std;

int main() {
    int num[20] = {0};
    int elem = 0;
    int value;

    while (elem < 20) {
        cout << "Enter number: ";
        cin >> value;
        if (value > 0) {
            num[elem] = value;
            elem++;
        } else {
            break;
        }
    }

    int maxStars = 0;
    for (int max = 0; max < elem; max++) {
        if (num[max] > maxStars) {
            maxStars = num[max];
        }
    }

    for (int star = 0; star < elem; star++) {
        int spaces = (maxStars - num[star]) / 2;

        for (int distance = 0; distance < spaces; distance++) {
            cout << " ";
        }

        for (int distance = 0; distance < num[star]; distance++) {
            cout << "*";
        }

        cout << endl;
    }

    return 0;
}

