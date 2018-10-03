#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <conio.h>
#include <iomanip>
#include <windows.h>
using namespace std;
#define DICT_SIZE 2376434
#define maxLengthOfWord 50


// Words separation using dictionary
string addSpaces(const string text, const set<string> dict) {

	string result, tmp, theLongestWord;


	for (int i = 0; i < text.length() - maxLengthOfWord; ++i) {

		tmp.clear();
		theLongestWord.clear();

		for (int j = i; j < i + maxLengthOfWord; ++j) {
			tmp += text[j];

			// Поиск слов в словаре (!=)
			if (dict.find(tmp) != dict.end() && tmp.length() >= theLongestWord.length())
				theLongestWord = tmp;

			//cout << tmp << endl;
		}
		result += theLongestWord;
		result += " ";
		tmp.clear();
		i += theLongestWord.length();
		if (theLongestWord.length() >= 1) i--;
		//cout << "Next pos = " << i+1 << endl;

	}

	return result;
}



// Загрузка словаря из файла
void loadDict(set <string> &dict, char *fileName) {

	int t_b, t_e;
	t_b = GetTickCount();
	cout << "Loading of dictionary has started" << endl;
	std::ifstream fin;
	fin.open(fileName);


	string tmp_string;
	for (int i = 0; i < DICT_SIZE; ++i) {

		fin >> tmp_string;
		dict.insert(tmp_string);

		if (i % (DICT_SIZE / 100) == 0)
			cout << "\r" << std::setprecision(3) << std::fixed << std::setw(3) << (i * 100) / DICT_SIZE + 1 << "%";
	}

	cout << endl << "Loading of dictionary has finished:  ";
	fin.close();
	t_e = GetTickCount();
	cout << (t_e - t_b) << "Ms" << endl;
}


// Загрузка строки без пробелов из файла
void loadEncryptedText(string &text, char *fileName) {

	std::ifstream fin;
	fin.open(fileName);
	fin >> text;
	fin.close();
}



void main() {

	setlocale(LC_ALL, "russian");

	string text;
	set<string> dict;

	loadDict(dict, "russian_dictionary.txt");
	loadEncryptedText(text, "decrypted_2.txt");
	cout << "Everything is ready." << endl;
	dict.insert("баурджан");
	dict.insert("момышулы");

	cout << addSpaces(text, dict);
	
	_getch();
}