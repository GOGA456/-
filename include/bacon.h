#ifndef BACON_H
#define BACON_H

#include <vector>
#include <string>
using namespace std;

vector<unsigned char> BaconEncrypt(const vector<unsigned char>& secretData, 
                                      const vector<unsigned char>& decoyData);

vector<unsigned char> BaconDecrypt(const vector<unsigned char>& encryptedData);

#endif
