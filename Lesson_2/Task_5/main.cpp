#include <iostream>
#include <string>

using namespace std;

int countWords(const string& str) {
    int wordCount = 0;
    bool inWord = false;

    for (char simbol : str) {
        if (isalnum(simbol)) {
            if (!inWord) {
                inWord = true;
                wordCount++;
            }
        } else {
            inWord = false;
        }
    }

    return wordCount;
}

int main() {
    string text;
    cout << "Enter line: ";
    getline(cin, text);
    cout << "Your line: " << text << endl;
    cout << "Number of words: " << countWords(text) << endl;
    return 0;
}
