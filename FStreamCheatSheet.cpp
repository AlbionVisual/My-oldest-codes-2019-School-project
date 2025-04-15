#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main() {
//Reafing
    //Объявление
    ifstream file;
    //Присваивание файла
    file.open("way");
    //Тест на удачное открытие файла
    if (!file) {
        cout << "Файл не открыт\n\n"; 
        return -1;
    }
    //Другой способ теста
    //Объявление и присваивание файла
    ifstream file2 ("way");
    //Сам тест
    if (!file2.is_open()) {
        cout << "Файл не открыт!\n\n" << endl;
        return -1;
    }
    //Извлечение информации из файла
    double d;
    int i;
    string s;
    file >> d >> i >> s;
    //Извлечение информации и вывод её в консоль сразу
    for(file2 >> s; !file2.eof(); file2 >> s) cout << s << endl;
    //Построчное извлечение
    //string s;
    getline(file,s);
    //Переставление курсора чтения файла
    //В конец файла
    file.seekg(0,ios_base::end);
    //На 10 символ с конца
    file.seekg(10,ios_base::end);
    //На 31 символ
    file.seekg(30,ios_base::beg);
    //Пропуск 3 символа
    file.seekg(3,ios_base::cur);
    file.seekg(3);
    //Номер символа с начала
    cout << "Считано байт: " << file.tellg();
    //Размер файла или позиция последнего символа
    file.seekg(0,ios_base::end);
    cout << "Размер файла (в байтах): " << file.tellg();
    //Закрыть файл
    file.close();
    file2.close();
//Writing
    //Объявление
    ofstream file3;
    //Присваивание файла
    file3.open("way");
    //Объявление с присваиванием сразу
    ofstream file4 ("way");
    //Запись информации
    file3 << "info: " << 123;
    //Закрыть файл
    file3.close();
    file4.close();

    return 0;
}