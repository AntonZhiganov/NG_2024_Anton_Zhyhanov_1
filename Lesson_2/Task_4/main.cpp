#include <iostream>
#include <map>
using namespace std;

int main()
{
    string userText;
    cout << "Enter text: ";
    getline(cin, userText);

    map<char, int> symbolCount;
    for (char simbol : userText)
    {
        symbolCount[simbol]++;
    }

    cout << "Character counts:\n";
    for (const auto& pair : symbolCount)
    {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
