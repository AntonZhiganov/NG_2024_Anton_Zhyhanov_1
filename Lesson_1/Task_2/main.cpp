#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    float num_1;
    float num_2;
    char action;
    float powResult;
    cout << "Enter the first number" << endl;
    cin >> num_1;
    cout << "Select action, write below +, -, /, *, or pow (write 'P')" << endl;
    cin >> action;
    cout << "Enter the second number" << endl;
    cin >> num_2;
    cout << "Result: ";
    switch (action){
    case '+':
        cout << num_1 + num_2 << endl;
        break;
    case '-':
        cout << num_1 - num_2 << endl;
        break;
    case '/':
        if (num_2 != 0) {
            cout << num_1 / num_2 << endl;
        }
        else {
            cout << "Error: Division by zero!" << endl;
        }
        break;
    case '*':
        cout << num_1 * num_2 << endl;
        break;
    case 'P':
        powResult = pow(num_1, num_2);
        cout << powResult << endl;
        break;
    default:
        cout << "Invalid operation!" << endl;
    }

    return 0;
}
