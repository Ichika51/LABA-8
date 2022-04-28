#include <iostream>
#include <fstream>
using namespace std;

bool example(const char* filename){
    ifstream is(filename); 
    // если файл не открыт
    if (!is) {
        cout << "Ошибка открытия файла" << endl;
        return false;
    }
    char str[100]; // буфер для чтения строки
    cout << "Текст из файла: " << endl;
    while (is){ // до is нулевого будет делать
        is.getline(str, 100); // прочитать строку из файла в буфер str
        cout << str << endl; // вывести на экран
    }

    is.close(); 

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

char* get_string(int*len) {//ввод слова, которое нужно найти в тексте
    bool dlina = false;
    cout << "Введите слово, количество которого вы хотите найти в тексте(максимум 4 символа в тексте): " << endl;
    while (dlina == false) {
        char* stroka = (char*)malloc(4 * sizeof(char));
        int len = 0;
        int capacity = 1;
        char c = getchar();
        while (c != '\n') {
            stroka[len++] = c;
            if (len >= capacity) {
                capacity *= 2;
                stroka = (char*)realloc(stroka, capacity * sizeof(char));
            }
            c = getchar();
        }
        stroka[len] = '\0';
        if (len > 4) {
            free(stroka);
            cout << "\nТы ввёл слишком длинное слово(максимум 4 символа). Попробуй ещё раз:\n";

        }
        if (len <= 4) {
            char* vvod = (char*)malloc(len*sizeof(char)+1);
            for (int i = 0;i < len;i++) {
                vvod[i] = stroka[i];
            }
            vvod[len] = '\0';
            free(stroka);
            return vvod;
        }
    }
}

int main(){
    setlocale(LC_ALL, "RUS");
    int len = 0;
    char* str=get_string(&len);
    example("c:\\file.txt");

    free(str);
    check_memory();
    return 0;
}
