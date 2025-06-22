#ifndef NIHILIST_H
#define NIHILIST_H

#include <vector>
#include <string>
using namespace std;

class NihilistCipher {
public:
    void encryptData(const vector<unsigned char>& data, 
                   const string& key, 
                   const string& outputFile);
    
    void decryptData(const vector<unsigned char>& data,
                   const string& key,
                   const string& outputFile);
};

#endif 
