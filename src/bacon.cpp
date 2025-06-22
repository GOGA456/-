#include "bacon.h"
#include <bitset>
#include <algorithm>

using namespace std;

vector<unsigned char> ExtendDecoy(const vector<unsigned char>& decoy, size_t requiredSize) {
    vector<unsigned char> extended;
    while (extended.size() < requiredSize) {
        size_t toCopy = min(decoy.size(), requiredSize - extended.size());
        extended.insert(extended.end(), decoy.begin(), decoy.begin() + toCopy);
    }
    return extended;
}

vector<unsigned char> BaconEncrypt(const vector<unsigned char>& secretData, 
                                 const vector<unsigned char>& decoyData) {
    vector<unsigned char> result;
    size_t requiredSize = secretData.size() * 8;
    auto extendedDecoy = ExtendDecoy(decoyData, requiredSize);
    
    size_t decoyPos = 0;
    for (unsigned char byte : secretData) {
        bitset<8> bits(byte);
        for (int i = 7; i >= 0; --i) {
            unsigned char decoyByte = extendedDecoy[decoyPos++];
            result.push_back(bits[i] ? (decoyByte | 0x80) : (decoyByte & 0x7F));
        }
    }
    return result;
}

vector<unsigned char> BaconDecrypt(const vector<unsigned char>& encryptedData) {
    vector<unsigned char> result;
    bitset<8> currentByte;
    int bitPos = 7;
    
    for (unsigned char byte : encryptedData) {
        currentByte[bitPos--] = (byte >> 7) & 1;
        if (bitPos < 0) {
            result.push_back(static_cast<unsigned char>(currentByte.to_ulong()));
            currentByte.reset();
            bitPos = 7;
        }
    }
    return result;
}
