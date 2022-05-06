#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <windows.h>

using namespace std;

int open_fstream(const char* filename,char*vvod,int*len){
    ifstream input(filename);
    if (!input) {// если файл не откроется, то ошибка
        cout << "Ошибка открытия файла" << endl;
        return false;
    }
    char ch;
    int Count = 0;
    while (input >> noskipws >> ch) {//цикл, чтобы узнать, кол-во элементов в массиве
        Count++; 
    }
    cout << "Count = " << Count << endl;
    input.close();
    char* mass = new char[Count+1];
    ifstream file(filename);
    for (int i = 0; i < Count; i++) {
        file >> noskipws >> mass[i];         //запись строк из файла в массив
        mass[Count] = '\0';
    }
    cout << mass << endl;
    int k = 0;
    int l = 0;
    for (int i = 0;i < Count;i++) {//перебор строки из файла
        int j = 0;
        while (vvod[j] == mass[i]) {//сравнение элементов двух массивов
            k++;j++;i++;
        }
        if (k >= *len) { //если счетчик набрал кол-во элементов из слова, то поиск удачный
            k = 0;
            l++;
        }
        if (vvod[j] != mass[i]) {//если элементы массивов не равны, то обнуление счетчика
            i = i - j;
            j = 0;k = 0;
        }
    }
    input.close();
    delete[] mass;
    return l;
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

char* get_string(int *len) {//ввод слова, которое нужно найти в тексте
    bool dlina = false;
    cout << "Введите слово, количество которого вы хотите найти в тексте(максимум 4 символа в тексте): " << endl;
    while (dlina == false) {
        char* stroka = (char*)malloc(4 * sizeof(char));
        int h = 0;
        int capacity = 1;
        char c = getchar();
        while (c != '\n') {
            stroka[h++] = c;
            if (h >= capacity) {
                capacity *= 2;
                stroka = (char*)realloc(stroka, capacity * sizeof(char));
            }
            c = getchar();
        }
        stroka[h] = '\0';
        if (h > 4) {
            free(stroka);
            cout << "\nТы ввёл слишком длинное слово(максимум 4 символа). Попробуй ещё раз:\n";
        }
        *len = h;
        if (h <= 4) {     //проверка, чтобы введенное слово было не больше 4-х символов
            char* vvod = (char*)malloc(*len*sizeof(char)+1);
            for (int i = 0;i < h;i++) {
                vvod[i] = stroka[i];
            }
            vvod[h] = '\0';
            free(stroka);
            return vvod;
        }
    }
}

int open_cstdio(const char* filename, char* vvod, int* len) {
    FILE* ptrFile = fopen(filename, "r");
    if (!ptrFile) {    // если файл не открыт, то выводит ошибку
        cout << "Ошибка открытия файла" << endl;
        return false;
    }
    char ch;
    int Count = 0;
    while ((ch = getc(ptrFile)) != EOF) { //Подсчет кол-ва элементов в файле для создания массива
        Count++;
    }
    cout << "Count = " << Count << endl;
    fclose(ptrFile);
    FILE* ptr = fopen(filename, "r");
    char* mass = new char[Count + 1];
    for (int i = 0; i < Count; i++) {
        char c = fgetc(ptrFile);
        mass[i]=c;//Запись в массив файла
        mass[Count] = '\0';
    }
    cout << mass << endl;
    int k = 0;
    int l = 0;
    for (int i = 0;i < Count;i++) {//перебор массива
        int j = 0;
        while (vvod[j] == mass[i]) {//если символы из текста равны символам из слова, то k++
            k++;j++;i++;            
        }
        if (k >= *len) {//если k больше или равен кол-ву символов в слове, то l++
            k = 0;
            l++;
        }
        if (vvod[j] != mass[i]) {//если символ из текста не равен символу из слова, то k=0
            i = i - j;
            j = 0;k = 0;
        }
    }
    fclose(ptr);
    delete[] mass;
    return l;
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

int main(){
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int len = 0;
    char* str=get_string(&len);//получение слова, которое нужно найти в тексте, масимум 4 символа
    cout << "Введите 1-чтобы найти слово с помощью <fstream>; 2-чтобы найти слово с помощью <cstdio>; 3-завершить программу" << endl;
    int d = checkNumber();//проверка ввода числа, для выбора варианта(от 1 до 3)
    int l;
    switch (d) {
    case(1):l = open_fstream("c:\\file.txt", str, &len);//открытие file.txt и запись в поток с помощью библиотеки <fstream> и поиск слова в тексте, возврат кол-ва найденных слов
        cout << "Количество слов '" << str << "' в тексте = " << l << endl;
        break;
    case(2):l = open_cstdio("c:\\file.txt", str, &len);//открытие file.txt и запись в поток с помощью библиотеки <cstdio> и поиск слова в тексте, возврат кол-ва найденных слов
        cout << "Количество слов '" << str << "' в тексте = " << l << endl;
        break;
    case(3):
        break;
    }
    free(str);//очистка массива
    check_memory();//проверка утечек памяти
    return 0;
}
