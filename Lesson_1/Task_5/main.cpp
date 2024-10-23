#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

void drawTriangle1(int row) {
    for (int element = 1; element <= row; element++) {
        for (int numEl = 1; numEl <= element; numEl++) {
            cout << "*";
        }
        cout << endl;
    }
}

void drawTriangle2(int row) {
    for (int element = 1; element <= row; element++) {
        for (int numEl = 1; numEl <= row - element; numEl ++) {
            cout << " ";
        }
        for (int numEl = 1; numEl <= element; numEl++) {
            cout << "*";
        }
        cout << endl;
    }
}

int main() {
    int row = 5;

    while (true) {

        drawTriangle1(row);
        this_thread::sleep_for(chrono::seconds(1));
        system("cls");

        drawTriangle2(row);
        this_thread::sleep_for(chrono::seconds(1));
        system("cls");
    }

    return 0;
}
