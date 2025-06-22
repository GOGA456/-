#include "nihilist.h"
#include <fstream>
#include <cstring>

using namespace std;

pair<int, int> GetCharCode(unsigned char ch) {
    return {ch / 16 + 1, ch % 16 + 1};
}

unsigned char CodeToChar(pair<int, int> code) {
    code.first = (code.first - 1) % 16;
    code.second = (code.second - 1) % 16;
    return code.first * 16 + code.second;
}

void NihilistCipher::encryptData(const vector<unsigned char>& data, 
                               const string& key, 
                               const string& outputFile) {
    ofstream out(outputFile, ios::binary);
    size_t keyIndex = 0;
    for (unsigned char ch : data) {
        auto charCode = GetCharCode(ch);
        auto keyCode = GetCharCode(key[keyIndex % key.size()]);
        int num1 = charCode.first + keyCode.first;
        int num2 = charCode.second + keyCode.second;
        out.write(reinterpret_cast<const char*>(&num1), sizeof(num1));
        out.write(reinterpret_cast<const char*>(&num2), sizeof(num2));
        keyIndex++;
    }
}

void NihilistCipher::decryptData(const vector<unsigned char>& data,
                               const string& key,
                               const string& outputFile) {
    ofstream out(outputFile, ios::binary);
    size_t keyIndex = 0;
    for (size_t i = 0; i < data.size(); i += sizeof(int) * 2) {
        int num1, num2;
        memcpy(&num1, &data[i], sizeof(num1));
        memcpy(&num2, &data[i + sizeof(int)], sizeof(num2));
        auto keyCode = GetCharCode(key[keyIndex % key.size()]);
        int code1 = num1 - keyCode.first;
        int code2 = num2 - keyCode.second;
        out << CodeToChar({code1, code2});
        keyIndex++;
    }
}
