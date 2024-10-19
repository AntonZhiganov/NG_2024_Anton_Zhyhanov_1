#include <iostream>

using namespace std;

int main()
{
    float money;
    cout << "How much money do you make?" << endl;
    cin >> money;

    if (money < 1000){
        cout << "You must work more!" << endl;
    }
    if (money > 999){
        if (money < 1000000){
            cout << "Well done!" << endl;
        }
        if(money > 999999){
            cout << "You are a millionaire!" << endl;
        }
    }
    return 0;
}
