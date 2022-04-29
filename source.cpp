#include <iostream>
#include <fstream>
using namespace std;

bool example(const char* filename,char*vvod,int*len){
    bool first=false;
    bool second = false;
    ifstream input("c:\\file.txt");
    // если файл не открыт
    if (!input) {
        cout << "Ошибка открытия файла" << endl;
        return false;
    }
    char ch;
    int Count = 0;
    while (input >> ch) {
        Count++;
    }
    cout << "Букв в файле : " << Count << endl;
    input.close();
    char* mass = new char[Count+1];
    ifstream file("c:\\file.txt");
    for (int i = 0; i < Count; i++) {
        file >> noskipws >> mass[i];
        mass[Count] = '\0';
    }
    cout << mass << endl;
    int k = 0;
    int l = 0;
    for (int i = 0;i < 100;i++) {//перебор строки из файла
        int j = 0;
        while (vvod[j] == mass[i]) {
            k++;j++;i++;
        }
        if (k >= *len) {          //**********************************************
            k = 0;
            l++;
        }
        if (vvod[j] != mass[i]) {
            i = i - j;
            j = 0;k = 0;
        }
    }
    cout << "Слов найдено: " << l << endl;
    input.close();
    delete[] mass;
    return true;
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
        if (h <= 4) {
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

int main(){
    setlocale(LC_ALL, "RUS");
    int len = 0;
    char* str=get_string(&len);
    example("c:\\file.txt",str,&len);
    free(str);
    check_memory();
    return 0;
}
