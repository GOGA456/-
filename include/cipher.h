#ifndef CIPHER_H
#define CIPHER_H

#ifdef __cplusplus
extern "C" {
#endif

enum CipherType { BACON = 1, NIHILIST, TRISEMUS };
enum Operation { ENCRYPT = 1, DECRYPT };
enum Source { KEYBOARD = 1, FILEINPUT };

void ProcessCipher(int cipherType, int operation, int source);

#ifdef __cplusplus
}
#endif

#endif 
