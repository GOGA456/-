#include "trisemus.h"
#include <fstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

void BinaryTrisemus::buildTable() {
    unordered_map<unsigned char, bool> uniqueBytes;
    for (unsigned char c : key) {
        uniqueBytes[c] = true;
    }

    for (int i = 0; i < 256; i++) {
        uniqueBytes[static_cast<unsigned char>(i)] = true;
    }

    vector<unsigned char> bytes;
    for (auto& pair : uniqueBytes) bytes.push_back(pair.first);
    sort(bytes.begin(), bytes.end());
    
    table.resize(rows, vector<unsigned char>(cols));

    for (size_t i = 0; i < bytes.size(); i++) {
        int row = i / cols;
        int col = i % cols;
        table[row][col] = bytes[i];
        charMap[bytes[i]] = {row, col};
    }
}

BinaryTrisemus::BinaryTrisemus(const string& k) : key(k) {
    if (key.empty()) throw invalid_argument("Ключ не может быть пустым");
    buildTable();
}

void BinaryTrisemus::encryptData(const vector<unsigned char>& data, 
                               const string& outputFile) {
    vector<unsigned char> result(data.size());
    
    for (size_t i = 0; i < data.size(); i++) {
        unsigned char c = data[i];
        if (charMap.count(c)) {
            auto pos = charMap[c];
            int newRow = (pos.first + 1) % rows;
            result[i] = table[newRow][pos.second];
        } else {
            result[i] = c;
        }
    }

    ofstream out(outputFile, ios::binary);
    if (!out) throw runtime_error("Не удалось создать файл: " + outputFile);
    out.write(reinterpret_cast<const char*>(result.data()), result.size());
}

void BinaryTrisemus::decryptData(const vector<unsigned char>& data,
                               const string& outputFile) {
    vector<unsigned char> result(data.size());
    
    for (size_t i = 0; i < data.size(); i++) {
        unsigned char c = data[i];
        if (charMap.count(c)) {
            auto pos = charMap[c];
            int newRow = (pos.first - 1 + rows) % rows;
            result[i] = table[newRow][pos.second];
        } else {
            result[i] = c;
        }
    }

    ofstream out(outputFile, ios::binary);
    if (!out) throw runtime_error("Не удалось создать файл: " + outputFile);
    out.write(reinterpret_cast<const char*>(result.data()), result.size());
}
