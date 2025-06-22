#include "cipher.h"
#include "bacon.h"
#include "nihilist.h"
#include "trisemus.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

extern "C" {

static std::vector<unsigned char> GetDataFromSource(int source, const std::string& prompt) {
    std::cout << prompt;
    
    if (source == KEYBOARD) {
        std::string text;
        std::getline(std::cin, text);
        return std::vector<unsigned char>(text.begin(), text.end());
    } 
    else {
        std::string filename;
        std::getline(std::cin, filename);
        
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (!file) throw std::runtime_error("Не удалось открыть файл: " + filename);
        
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        std::vector<unsigned char> buffer(size);
        file.read(reinterpret_cast<char*>(buffer.data()), size);
        return buffer;
    }
}

static std::string GetOutputFilename() {
    std::cout << "Введите имя выходного файла (по умолчанию 'output.bin'): ";
    std::string filename;
    std::getline(std::cin, filename);
    
    if (filename.empty()) {
        return "output.bin";
    }
    return filename;
}

void ProcessCipher(int cipherType, int operation, int source) {
    try {
        std::string outputFile = GetOutputFilename();
        
        switch (static_cast<CipherType>(cipherType)) {
            case BACON: {
                auto secret = GetDataFromSource(source, "Введите секретные данные: ");
                auto decoy = GetDataFromSource(source, "Введите отвлекающие данные: ");
                
                std::vector<unsigned char> result;
                if (operation == ENCRYPT) {
                    result = BaconEncrypt(secret, decoy);
                } else {
                    result = BaconDecrypt(secret);
                }
                
                std::ofstream out(outputFile, std::ios::binary);
                out.write(reinterpret_cast<char*>(result.data()), result.size());
                break;
            }
            
            case NIHILIST: {
                std::cout << "Введите ключ: ";
                std::string key;
                std::getline(std::cin, key);
                
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
                std::cout << "Введите ключ: ";
                std::string key;
                std::getline(std::cin, key);
                
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
        
        std::cout << "Операция выполнена. Результат сохранен в " << outputFile << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

}// extern "C"
