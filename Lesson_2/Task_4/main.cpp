#include <iostream>

using namespace std;

int main()
{
    string userText;
    int symbol;
    cout << "Enter text" << endl;
    getline(cin, userText);
    symbol = userText.length();
    cout << "You have "  << symbol <<  " characters in the line!" << endl;
    return 0;
}
