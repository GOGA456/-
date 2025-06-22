#include "cipher.h"
#include "bacon.h"
#include "nihilist.h"
#include "trisemus.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

extern "C" {

static vector<unsigned char> GetDataFromSource(int source, const string& prompt) {
    cout << prompt;
    
    if (source == KEYBOARD) {
        string text;
        getline(cin, text);
        return vector<unsigned char>(text.begin(), text.end());
    } 
    else {
        string filename;
        getline(cin, filename);
        
        ifstream file(filename, ios::binary | ios::ate);
        if (!file) throw runtime_error("Не удалось открыть файл: " + filename);
        
        streamsize size = file.tellg();
        file.seekg(0, ios::beg);
        
        vector<unsigned char> buffer(size);
        file.read(reinterpret_cast<char*>(buffer.data()), size);
        return buffer;
    }
}

static string GetOutputFilename() {
    cout << "Введите имя выходного файла (по умолчанию 'output.bin'): ";
    string filename;
    getline(cin, filename);
    
    if (filename.empty()) {
        return "output.bin";
    }
    return filename;
}

void ProcessCipher(int cipherType, int operation, int source) {
    try {
        string outputFile = GetOutputFilename();
        
        switch (static_cast<CipherType>(cipherType)) {
            case BACON: {
                auto secret = GetDataFromSource(source, "Введите секретные данные: ");
                auto decoy = GetDataFromSource(source, "Введите отвлекающие данные: ");
                
                vector<unsigned char> result;
                if (operation == ENCRYPT) {
                    result = BaconEncrypt(secret, decoy);
                } else {
                    result = BaconDecrypt(secret);
                }
                
                ofstream out(outputFile, ios::binary);
                out.write(reinterpret_cast<char*>(result.data()), result.size());
                break;
            }
            
            case NIHILIST: {
                cout << "Введите ключ: ";
                string key;
                getline(cin, key);
                
                auto input = GetDataFromSource(source, "Введите данные: ");
                
                NihilistCipher cipher;
                if (operation == ENCRYPT) {
                    cipher.encryptData(input, key, outputFile);
                } else {
                    cipher.decryptData(input, key, outputFile);
                }
                break;
            }
            
            case TRISEMUS: {
                cout << "Введите ключ: ";
                string key;
                getline(cin, key);
                
                auto input = GetDataFromSource(source, "Введите данные: ");
                
                BinaryTrisemus cipher(key);
                if (operation == ENCRYPT) {
                    cipher.encryptData(input, outputFile);
                } else {
                    cipher.decryptData(input, outputFile);
                }
                break;
            }
        }
        
        cout << "Операция выполнена. Результат сохранен в " << outputFile << endl;
        
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

}
