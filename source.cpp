#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <windows.h>

using namespace std;

void open_fstream(const char* filename) {
    ifstream input(filename);
    if (!input) {// если файл не откроется, то ошибка
        cout << "Ошибка открытия файла" << endl;

    }
    char ch;
    int Count = 0;
    while (input >> noskipws >> ch) {//цикл, чтобы узнать, кол-во элементов в массиве
        Count++;
    }
    cout << "Count = " << Count << endl;
    input.close();
    char* mass = new char[Count + 1];
    ifstream file(filename);

    for (int i = 0; i < Count; i++) {
        file >> noskipws >> mass[i];         //запись строк из файла в массив
        mass[Count] = '\0';
    }
    input.close();
    cout << mass << endl;
    int j = 0;
    int k = 0;
    int l = 0;
    int g = 0;
    char fname[]{ "fstream.txt" };
    remove(fname);
    ofstream oFile(fname);
    ofstream out;          // поток для записи
    out.open(fname); // окрываем файл для записи
    if (out.is_open()) {//если открылось без ошибок
        char* masst = new char[100];
        for (int i = 0; i < Count; i++) {//перебор большого массива
            if (mass[i] == ' ' || mass[i] == '?' || mass[i] == '!' || mass[i] == ':' || mass[i] == ';' || mass[i] == '.' || mass[i] == ',' || mass[i] == '\n' || mass[i] == '1' || mass[i] == '2' || mass[i] == '3' || mass[i] == '4' || mass[i] == '5' || mass[i] == '6' || mass[i] == '7' || mass[i] == '8' || mass[i] == '9' || mass[i] == '0' || mass[i] == '(' || mass[i] == ')'||mass[i]=='-'||mass[i]=='"') {
                masst[j] = '\0';
                if (j <= 4 && j != 0) {
                    for (int n = 0;n < Count;n++) {//перебор строки из файла
                        int h = 0;
                        while (masst[h] == mass[n]) {//сравнение элементов двух массивов
                            k++;h++;n++;
                        }
                        if (k >= j) { //если счетчик набрал кол-во элементов из слова, то поиск удачный
                            k = 0;
                            g = h;
                            if (mass[n] == ' ' || mass[n + 1] == '\n' || mass[n + 1] == ',' || mass[n + 1] == '.' || mass[n + 1] == '"') {
                                if (mass[n - h - 1] == '-' || mass[n - h - 1] == ' ' || mass[n - h - 1] == '.' || mass[n - h - 1] == ',' || mass[n - h - 1] == '!' || mass[n + 1] == '"') {
                                    l++;
                                    for (int u = 0;u < j; u++) {
                                        mass[n - g] = ' ';
                                        g = g - 1;
                                    }
                                }
                            }
                            g = 0;
                        }
                        if (masst[h] != mass[n]) {//если элементы массивов не равны, то обнуление счетчика
                            n = n - h;
                            h = 0;k = 0;
                        }
                    }
                    if (l != 0) {
                        out << "Количество слова: " << masst << " равно=" << l << endl;
                        cout << "Количество слова: " << masst << " равно=" << l << endl;
                        l = 0;
                    }
                }
                masst[j] = ' ';
                j = 0;
            }
            else {
                masst[j] = mass[i];
                j++;
            }
        }
        delete[] masst;
    }
    input.close();
    delete[] mass;
}

void open_cstdio(const char* filename) {
    FILE* ptrFile = fopen(filename, "r");
    if (!ptrFile) {    // если файл не открыт, то выводит ошибку
        cout << "Ошибка открытия файла" << endl;
    }
    char ch;
    int Count = 0;
    while ((ch = getc(ptrFile)) != EOF) { //Подсчет кол-ва элементов в файле для создания массива
        Count++;
    }
    cout << "Count = " << Count << endl;
    fseek(ptrFile, 0, SEEK_SET);//сдвиг каретки
    char* mass = new char[Count + 1];
    for (int i = 0; i < Count; i++) {
        char c = fgetc(ptrFile);
        mass[i] = c;//Запись в массив файла
        mass[Count] = '\0';
    }
    fclose(ptrFile);
    cout << mass << endl;
    int j = 0;
    int k = 0;
    int l = 0;
    int g = 0;
    char fname[]{ "cstdio.txt" };
    FILE* cstdio = fopen(fname, "w");
    FILE* fdopen(0);
    char* masst = new char[100];
    for (int i = 0; i < Count; i++) {//перебор массива файла 
        if (i == 0 || mass[i] == ' ' || mass[i] == '?' || mass[i] == '!' || mass[i] == ':' || mass[i] == ';' || mass[i] == '.' || mass[i] == ',' || mass[i] == '\n' || mass[i] == '1' || mass[i] == '2' || mass[i] == '3' || mass[i] == '4' || mass[i] == '5' || mass[i] == '6' || mass[i] == '7' || mass[i] == '8' || mass[i] == '9' || mass[i] == '0' || mass[i] == '(' || mass[i] == ')' || mass[i] == '-' || mass[i] == '"') {//когда находит один из элементов
            masst[j] = '\0';// терминальный ноль для искомого массива
            if (j <= 4 && j != 0) {
                for (int n = 0;n < Count;n++) {//перебор строки из файла
                    int h = 0;
                    while (masst[h] == mass[n]) {//сравнение элементов двух массивов
                        k++;h++;n++;
                    }
                    if (k >= j) { //если счетчик набрал кол-во элементов из слова, то поиск удачный
                        k = 0;
                        g = h;
                        if (mass[n] == ' ' || mass[n + 1] == '\n' || mass[n + 1] == ',' || mass[n + 1] == '.' || mass[n + 1] == '"') {
                            if (mass[n - h - 1] == '-' || mass[n - h - 1] == ' ' || mass[n - h - 1] == '.' || mass[n - h - 1] == ',' || mass[n - h - 1] == '!' || mass[n + 1] == '"') {
                                l++;
                                for (int u = 0;u < j; u++) {
                                    mass[n - g] = ' ';
                                    g = g - 1;
                                }
                            }
                        }
                        g = 0;
                    }
                    if (masst[h] != mass[n]) {//если элементы массивов не равны, то обнуление счетчика
                        n = n - h;
                        h = 0;k = 0;
                    }
                }
                if (l != 0) {
                    char s[20];
                    fprintf(cstdio, "Количество слов: '%s' равно %d\n", masst, l);
                    cout << "Количество слова: " << masst << " равно=" << l << endl;
                    l = 0;
                }
            }
            masst[j] = ' ';
            j = 0;
        }
        else {
            masst[j] = mass[i];
            j++;
        }
    }
    delete[] masst;
    fclose(cstdio);
    delete[] mass;
}

void check_memory() {//проверка утечек 
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    _CrtDumpMemoryLeaks();
}

int checkNumber() {//проверка корректности целого числа
    int k;
    cin >> k;
    while (cin.fail() || k > 3 || 1 > k) {//Если число не от 1 до 3 и символьное, то...
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "\nНеккоректное число, повторите ввод(Ввести нужно число от 1 до 3): ";
        cin >> k;  //ввод нового числа
    }
    return k;
}

int main() {
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    while (1) {
        cout << "Введите 1-чтобы найти слово с помощью <fstream>; 2-чтобы найти слово с помощью <cstdio>; 3-завершить программу" << endl;
        int d = checkNumber();//проверка ввода числа, для выбора варианта(от 1 до 3)
        switch (d) {
        case(1): 
            open_fstream("file.txt");//открытие file.txt и запись в поток с помощью библиотеки <fstream> и поиск слова в тексте, возврат кол-ва найденных слов
            break;
        case(2):
            open_cstdio("file.txt");//открытие file.txt и запись в поток с помощью библиотеки <cstdio> и поиск слова в тексте, возврат кол-ва найденных слов
            break;
        case(3):
            return 0;//прекращение программы
            break;
        }
        check_memory();//проверка утечек памяти
    }
}
