#include <iostream>
#include <string>
#include <regex>

using namespace std;

int countWords(const string& str) {
    regex wordRegex(R"(\b[a-zA-Z0-9]+\b)");
    auto wordsBegin = sregex_iterator(str.begin(), str.end(), wordRegex);
    auto wordsEnd = sregex_iterator();
    return distance(wordsBegin, wordsEnd);
}

int main() {

    string text;
    cout << "Enter line: " << endl;
    getline(cin, text);
    cout << "You line: " << text << endl;
    cout << "Number of words: " << countWords(text) << endl;
    return 0;
}
