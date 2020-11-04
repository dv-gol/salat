﻿#include <stdio.h>
#include <locale>

#define ENG 26
#define RUS 32

void encrypt(int n)
{
    FILE* fp1, * fp2;
    fopen_s(&fp1, "input.txt", "r");// открытие файла
    fopen_s(&fp2, "output.txt", "w");
    int flag;
    char c;
    c = getc(fp1);// посимвольный ввод
    while (!feof(fp1))//проверка конца файла
    {
        flag = 0; //обработан ли текущий символ
        if (c >= 'A' && c <= 'Z') //проверка принадлежности вводимых данных на принадлежность к английскому алфавиту верхнего регистра
        {
            c = c + (n % ENG); //Остаток от деления  берем для того, чтобы при n >= ENG убрать лишний "проход"
            if (c > 'Z') c = 'A' + (c - 'Z') - 1; //шифрование
            fprintf(fp2, "%c", c); // если считанный символ не буква,то он записывает без изменений
            flag = 1;
        }
        if (c >= 'a' && c <= 'z') //проверка принадлежности вводимых данных на принадлежность к английскому алфавиту нижнего регистра
        {
            c = c + (n % ENG);
            if (c > 'z') c = 'a' + (c - 'z') - 1; //шифрование
            fprintf(fp2, "%c", c);
            flag = 1;
        }
        if (c >= 'А' && c <= 'Я') //проверка принадлежности вводимых данных на принадлежность к русскому алфавиту верхнего регистра
        {
            c = c + (n % RUS);
            if (c > 'Я') c = 'А' + (c - 'Я') - 1;
            fprintf(fp2, "%c", c);
            flag = 1;
        }
        if (c >= 'а' && c <= 'я') //проверка принадлежности вводимых данных на принадлежность к русскому алфавиту нижнего регистра
        {
            c = c + (n % RUS);
            if (c > 'я') c = 'а' + (c - 'я') - 1;
            fprintf(fp2, "%c", c);
            flag = 1;
        }
        if (!flag) fprintf(fp2, "%c", c);
        c = getc(fp1);
    }
    fclose(fp1);
    fclose(fp2);
}

void decipher(int n)
{
    FILE* fp1, * fp2;
    fopen_s(&fp1, "output.txt", "r");
    fopen_s(&fp2, "123.txt", "w");
    int flag;
    char c;
    c = getc(fp1);
    while (!feof(fp1))
    {
        flag = 0;
        if (c >= 'A' && c <= 'Z')
        {
            c = c - (n % ENG);
            if (c < 'A') c = 'Z' - ('A' - c) + 1;
            fprintf(fp2, "%c", c);
            flag = 1;
        }
        if (c >= 'a' && c <= 'z')
        {
            c = c - (n % ENG);
            if (c < 'a') c = 'z' - ('a' - c) + 1;
            fprintf(fp2, "%c", c);
            flag = 1;
        }
        if (c >= 'А' && c <= 'Я')
        {
            c = c - (n % RUS);
            if (c < 'А') c = 'Я' - ('А' - c) + 1;
            fprintf(fp2, "%c", c);
            flag = 1;
        }
        if (c >= 'а' && c <= 'я')
        {
            c = c - (n % RUS);
            if (c < 'а') c = 'я' - ('а' - c) + 1;
            fprintf(fp2, "%c", c);
            flag = 1;
        }
        if (!flag) fprintf(fp2, "%c", c);
        c = getc(fp1);
    }
    fclose(fp1); //закрытие файла
    fclose(fp2);
}

int main()
{
    setlocale(LC_ALL, "Russian"); //возможность отображения русских символов в консоли
    int n;
    printf("Введите натуральное n: ");
    scanf_s("%d", &n);
    getchar(); //нужен для того, чтобы поймать символ клавиши ENTER, нажатой при вводе числа n
    if (n < 1) return 0;
    printf("Чтобы зашифровать текст введите a, расшифровать b: ");
    char c;
    scanf_s("%c", &c, 1);
    if (c == 'a') encrypt(n);
    if (c == 'b') decipher(n);
    return 0;
}
