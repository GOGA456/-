#ifndef BACON_H
#define BACON_H

#include <vector>
#include <string>

std::vector<unsigned char> BaconEncrypt(const std::vector<unsigned char>& secretData, 
                                      const std::vector<unsigned char>& decoyData);

std::vector<unsigned char> BaconDecrypt(const std::vector<unsigned char>& encryptedData);

#endif
