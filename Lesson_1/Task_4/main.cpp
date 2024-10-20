#include <iostream>

using namespace std;

int main()
{
    int num;
    cout << "Enter number" << endl;
    cin >> num;

    for (int counter = 1; counter <= num; counter++) {
        for (int elements = counter; elements < num; elements++) {
            cout << " ";
        }
        for (int space = 1; space <= (2 * counter - 1); space++) {
            cout << "*";
        }
        cout << endl;
    }
    for (int counter = 1; counter < num; counter++) {
        cout << " ";
    }
    cout << "*" << endl;

    return 0;
}

