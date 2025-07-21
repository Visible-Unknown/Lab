#include <iostream>
#include <string>
using namespace std;

string caesarDecrypt(string cipher, int shift) {
    string result = "";
    for (char c : cipher) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            result += (c - base - shift + 26) % 26 + base;
        } else {
            result += c;
        }
    }
    return result;
}

int main() {
    string cipher = "odroboewscdrolocdcwkbdmyxdbkmdzvkdpybwyeddrobo";

    cout << "Caesar Cipher Brute Force Results:\n";
    for (int shift = 1; shift < 26; shift++) {
        cout << "Shift " << shift << ": " << caesarDecrypt(cipher, shift) << endl;
    }

    return 0;
}
