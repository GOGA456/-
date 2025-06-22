#include "cipher.h"
#include <iostream>
#include <string>

int main() {
    while(true) {
        std::cout << "1. Бэкон\n2. Нигилист\n3. Трисемус\n4. Выход\nВыберите: ";
        int cipherType;
        std::cin >> cipherType;
        std::cin.ignore();

        if(cipherType == 4) break;

        std::cout << "1. Шифровать\n2. Дешифровать\nВыберите: ";
        int operation;
        std::cin >> operation;
        std::cin.ignore();

        std::cout << "1. Клавиатура\n2. Файл\nВыберите: ";
        int source;
        std::cin >> source;
        std::cin.ignore();

        ProcessCipher(cipherType, operation, source);
    }
    return 0;
}
