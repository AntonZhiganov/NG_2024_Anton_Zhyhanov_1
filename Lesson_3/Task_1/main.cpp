#include <iostream>

using namespace std;

void printSpaces(int count) {
    if (count <= 0)
    {
        return;
    }
    cout << " ";
    printSpaces(count - 1);
}

void printStars(int count) {
    if (count <= 0)
    {
        return;
    }
    cout << "*";
    printStars(count - 1);
}

void printPyramid(int row, int num) {
    if (row > num)
    {
        return;
    }
    printSpaces(num - row);
    printStars(2 * row - 1);
    cout << endl;
    printPyramid(row + 1, num);
}

void printBottom(int num) {
    printSpaces(num - 1);
    cout << "*" << endl;
}

int main() {
    int num;
    cout << "Enter number" << endl;
    cin >> num;

    printPyramid(1, num);
    printBottom(num);

    return 0;
}
