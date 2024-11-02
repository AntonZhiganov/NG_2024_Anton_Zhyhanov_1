#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

int main() {
    int row = 5;

    while (true) {
        for (int element = 1; element <= row; element++) {
            for (int numEl = 1; numEl <= element; numEl++) {
                cout << "*";
            }
            cout << endl;
        }
        this_thread::sleep_for(chrono::seconds(1));
        system("cls");

        for (int element = 1; element <= row; element++) {
            for (int numEl = 1; numEl <= row - element; numEl++) {
                cout << " ";
            }
            for (int numEl = 1; numEl <= element; numEl++) {
                cout << "*";
            }
            cout << endl;
        }
        this_thread::sleep_for(chrono::seconds(1));
        system("cls");
    }

    return 0;
}
