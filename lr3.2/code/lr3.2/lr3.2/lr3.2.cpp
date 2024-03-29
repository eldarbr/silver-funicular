﻿#include <iostream>
#include <fstream>
using namespace std;

// НАХОЖДЕНИЕ ДЛИНЫ СТРОКИ
int get_str_length(char a[]) {
    int length = 0;
    char last_read = a[0];
    while (last_read != '\0') {
        length += 1;
        last_read = a[length];
    }
    return length;
}

// ВЫВОД СТРОКИ С ПОДЧЕРКИВАНИЕМ СИМВОЛОВ ПО ИНДЕКСАМ
void print_with_highlights(char str[], int highlights[]) {
    int length = get_str_length(str);
    for (int i = 0; i < length; i++) {
        if (highlights[i]==1) {
            cout << "\x1b[4m" << str[i] << "\x1b[0m";
        }
        else {
            cout << str[i];
        }
    }
    cout << endl;
}

// ПОИСК ПОВТОРЯЮЩИХСЯ СИМВОЛОВ
void find_duplicated_chars(char str1[], char str2[]) {
    int max_len = get_str_length(str1);
    int min_len = get_str_length(str2);
    if (get_str_length(str2) > max_len) {
        max_len = get_str_length(str2);
        min_len = get_str_length(str1);
    }
    int num = 0;
    int *dup = new int[max_len];
    for (int i = 0; i < max_len; i++) {
        dup[i] = 0;
        if (i >= min_len) {
            dup[i] = 0;
        } else
        if (str1[i] == str2[i]) {
            dup[i] = 1;
            num++;
        }
    }

    cout << "всего дупликатов: " << num << endl;
    print_with_highlights(str1, dup);
    print_with_highlights(str2, dup);
}

// ПОИСК ЗАДАННОГО СЛОВА В СТРОКАХ
int count_word_matches(char target_word[], char s[]) {
    int num = 0;            // КОЛИЧЕСТВО ЗАДАННОГО СЛОВА В СТРОКЕ
    bool match = true;          
    int start = 0;          
    for (int i = 0;i < get_str_length(s)+1; i++) {
        //cout << s[i] << endl;
        if (s[i] == ' ' || s[i] == '\0') {
            //cout << i << " " << start << " " << match << " probel" << endl;
            if (target_word[i - start] != '\0') match = false;
            if (match) num++;
            start = i+1;
            match = true;
        }
        else if (match && s[i] != target_word[i - start]) {
            match = false; 
            //cout << "no match" << endl;
        }
        //cout << i << " " << start << " " << match << endl;
    }
    return num;
}

// СРАВНЕНИЕ ДВУХ СТРОК ПО НАЛИЧИЮ ЗАДАННОГО СЛОВА
void words_statistics(char target_word[], char s1[], char s2[]) {
    int word_matches1 = count_word_matches(target_word, s1);
    int word_matches2 = count_word_matches(target_word, s2);
    if (word_matches1 == word_matches2)
        cout << "количество заданного слова в первой строке и второй строке одинаково: "
        << word_matches1 << endl;    
    else if (word_matches1 > word_matches2) 
        cout << "в первой строке заданное слово повторяется больше раз: "
        << word_matches1 << " против " << word_matches2 << endl;
    else 
        cout << "во второй строке заданное слово повторяется больше раз: "
        << word_matches2 << " против " << word_matches1 << endl;
}

//const string filename = ".txt";
//const string filename = "corr_test_0.txt";
const string filename = "corr_test_1.txt";
//const string filename = "corr_test_2.txt";
//const string filename = "incorr_test_0.txt";
//const string filename = "incorr_test_1.txt";

int main()
{
    setlocale(LC_ALL, "RUS");

    /* char target_word[] = "home";
     char s1[] = "home home home mouse home mouse car home home";
     char s2[] = "home house car mouse";*/

    char target_word[500];      // ЗАДАННОЕ СЛОВО
    char s1[500];               // ПЕРВАЯ СТРОКА
    char s2[500];               // ВТОРАЯ СТРОКА

    ifstream f1;                // СОЗДАНИЕ ОБЪЕКТА КЛАССА ifstream
    f1.open(filename);          // СВЯЗЫВАНИЕ ОБЪЕКТА С ФАЙЛОМ
    if (f1.is_open()) {
        cout << "Файл найден." << endl;
        f1.getline(target_word, 59);    // ЧТЕНИЕ ПЕРВОЙ СТРОКИ ИЗ ФАЙЛА
        f1.getline(s1, 500);            // ЧТЕНИЕ ВТОРОЙ СТРОКИ ИЗ ФАЙЛА
        f1.getline(s2, 500);            // ЧТЕНИЕ ТРЕТЬЕЙ СТРОКИ ИЗ ФАЙЛА
    }
    else {
        cout << "Файл не найден! Введите данные вручную:" << endl;
        cin.getline(target_word, 59);   // ЧТЕНИЕ ПЕРВОЙ СТРОКИ
        cin.getline(s1, 500);           // ЧТЕНИЕ ВТОРОЙ СТРОКИ
        cin.getline(s2, 500);           // ЧТЕНИЕ ТРЕТЬЕЙ СТРОКИ
    }
    if (target_word[0] == '\0') {
        cout << "Ошибка! Слово не получено!" << endl;
        return 1;
    }
    else if (target_word[0] == ' ') {
        cout << "Ошибка! Слово не должно начинаться с пробела!" << endl;
        return 2;
    }
    else {
        find_duplicated_chars(s1, s2);      // ПОИСК ПОВТОРЯБЩИХСЯ СИМВОЛОВ
        words_statistics(target_word, s1, s2);  // ПОИСК ЗАДАННОГО СЛОВА В СТРОКАХ
    }
    return 0;
}
