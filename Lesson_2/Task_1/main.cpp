#include <iostream>

using namespace std;

int main()
{
    int num [5];
    int elem = 0;
    while (elem < 5)
    {
        cout << "Enter number" << endl;
        cin >> num[elem];
        elem ++;
    }

    for (int number = 0; number < 5; number++)
    {
        if (number < 4)
        {
            cout << num[number] << ", ";
        }
        else
        {
            cout << num[number] << endl;
        }

    }

    return 0;
}
