#ifndef NIHILIST_H
#define NIHILIST_H

#include <vector>
#include <string>

class NihilistCipher {
public:
    void encryptData(const std::vector<unsigned char>& data, 
                   const std::string& key, 
                   const std::string& outputFile);
    
    void decryptData(const std::vector<unsigned char>& data,
                   const std::string& key,
                   const std::string& outputFile);
};

#endif // NIHILIST_H
