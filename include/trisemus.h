#ifndef TRISEMUS_H
#define TRISEMUS_H

#include <vector>
#include <string>
#include <unordered_map>
#include <utility>

class BinaryTrisemus {
private:
    string key;
    vector<vector<unsigned char>> table;
    unordered_map<unsigned char, pair<int, int>> charMap;
    int rows = 16;
    int cols = 16;

    void buildTable();

public:
    explicit BinaryTrisemus(const string& k);
    
    void encryptData(const vector<unsigned char>& data, 
                   const string& outputFile);
    
    void decryptData(const vector<unsigned char>& data,
                   const string& outputFile);
};

#endif 
