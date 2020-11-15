#include <string>
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <fstream>
using namespace std;
string time() {
	char str[26];
	time_t result = time(NULL);
	ctime_s(str, sizeof str, &result);

	return str;
}
int main()
{
	string path = "log.txt";
	setlocale(LC_ALL, "Russian");
	string start_line, final_line, command, test_offset;
	char symbol;
	int offset;
	bool key;
	ofstream fout(path, ios_base::app);
	fout << "INFO : The program started : " << time();
	do {//цикл ввода значения сдвига(будет работать пока пользователь не введет число корректно)
		key = true;
		cout << "Введите велечину сдвига: ";
		//cin >> test_offset;
		getline(cin, test_offset);
		for (int i = 0; i < test_offset.length(); i++) {
			if ((!isdigit(test_offset[i])) and (test_offset[i] != '-')) {
				key = false;
				cout << "Должно быть введено только число. Попробуйте еще раз." << endl;
				fout << "WARNING : The user entered an invalid offset value : " << time();
				break;
			}
		}
	} while (!key);


	offset = atoi(test_offset.c_str());
	do {//цикл ввода команды
		cout << "Введите a для кодирования или b для расшифровки: ";

		getline(cin, command);

		if (command == "b") {
			offset *= -1;
		}
		else if (command != "a") {
			cout << "Команда введена некорректно. Попробуйте еще раз." << endl;
			fout << "WARNING : The user entered an invalid command : " << time();
		}
	} while ((command != "a") and (command != "b"));
	cout << "Введите предложение(нелатинские символы не будут зашифрованы или расшифрованы): ";
	getline(cin, start_line);
	cout << endl;

	final_line.resize(start_line.length());
	for (int i = 0; i < start_line.length(); i++) {//цикл, который проходит все символы введенной строки и сдвигает символы латиницы в соответствии с UNICODE
		if ((start_line[i] > 96) and (start_line[i] < 123)) {
			symbol = start_line[i] += offset;
			symbol = char(97 + (26 * (1 - (symbol / 97))) + ((symbol - 97) % 26));
			final_line[i] = symbol;
		}
		else if ((start_line[i] > 64) and (start_line[i] < 91)) {
			symbol = start_line[i] += offset;
			symbol = char(64 + (26 * (1 - (symbol / 64))) + ((symbol - 64) % 26));
			final_line[i] = symbol;
		}

		else {
			final_line[i] = start_line[i];//если символы не латинские, то они сохраняются 
		}
	}
	cout << "Результат: " << final_line;//вывод результата
	if (command == "a") {
		fout << "INFO : Message successfully encoded : " << time();
	}
	else {
		fout << "INFO : Message successfully decoded : " << time();
	}
	fout << "INFO : The program completed : " << time();
	fout << endl;
	fout.close();
}