#include "cipher.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    while(true) {
        cout << "1. Бэкон\n2. Нигилист\n3. Трисемус\n4. Выход\nВыберите: ";
        int cipherType;
        cin >> cipherType;
        cin.ignore();

        if(cipherType == 4) break;

        cout << "1. Шифровать\n2. Дешифровать\nВыберите: ";
        int operation;
        cin >> operation;
        cin.ignore();

        cout << "1. Клавиатура\n2. Файл\nВыберите: ";
        int source;
        cin >> source;
        cin.ignore();

        ProcessCipher(cipherType, operation, source);
    }
    return 0;
}
