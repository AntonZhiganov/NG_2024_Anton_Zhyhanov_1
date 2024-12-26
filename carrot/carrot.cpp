#include <iostream>
#include <string>

using namespace std;

string caesarDecrypt(const string& text, int shift) {
    string result = "";
    for (char simbol : text) {
        if (isupper(simbol)) {
            result += char(int(simbol - shift - 'A' + 26) % 26 + 'A');
        } else if (islower(simbol)) {
            result += char(int(simbol - shift - 'a' + 26) % 26 + 'a');
        } else {
            result += simbol;
        }
    }
    return result;
}

int main() {
    string cipherText = "Spwwz, declyrpc. Dppxd wtvp jzf yze ufde l dnctae vtootp, dz zfc lrpynj slgp dzxp uzm qzc jzf. Tq jzf hlye ez lnnpae esp “uzm” zqqpc - ufde afds ez jzfc cpaz esp nzop, esle sld opncjaepo estd xpddlrp, lyo ylxp te nlccze.naa. Hp lcp hltetyr...";

    cout << "Iterating through possible shifts for decryption: \n";
    for (int shift = 1; shift <= 25; ++shift) {
        cout << "Shift " << shift << ": " << caesarDecrypt(cipherText, shift) << "\n\n";
    }

    return 0;
}

//Option 11 is correct.
