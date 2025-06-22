#ifndef TRISEMUS_H
#define TRISEMUS_H

#include <vector>
#include <string>
#include <unordered_map>
#include <utility>

class BinaryTrisemus {
private:
    std::string key;
    std::vector<std::vector<unsigned char>> table;
    std::unordered_map<unsigned char, std::pair<int, int>> charMap;
    int rows = 16;
    int cols = 16;

    void buildTable();

public:
    explicit BinaryTrisemus(const std::string& k);
    
    void encryptData(const std::vector<unsigned char>& data, 
                   const std::string& outputFile);
    
    void decryptData(const std::vector<unsigned char>& data,
                   const std::string& outputFile);
};

#endif // TRISEMUS_H
