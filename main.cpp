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
#define maxLengthOfWord 30


// Words separation using dictionary
string cutWordsRecursively(const string &text, const set<string> &dict, int firstPosition, int depth) {

	string tmp, theLongestWord;
	tmp.clear();
	theLongestWord.clear();

	// TO DO
	/*
	Надо добавить метрику для того, чтобы не было много коротких слов
	Учитывать глубину рекурсии
	*/

	for (int i = firstPosition; i < text.length() + maxLengthOfWord; ++i) {
		tmp += text[i];

		if (dict.find(tmp) != dict.end() &&					/// Если слово найдено
			tmp.length() > theLongestWord.length()) {		/// и оно не пустое
															/// и за ним идут depth - 1 слов 
			//cout << tmp << endl;
			if (depth > 0) {
				string nextWord = cutWordsRecursively(text, dict, firstPosition + tmp.length(), depth - 1);
				//cout << depth << "  " << nextWord <<  "   " << tmp << "   " << theLongestWord << endl;
				if (nextWord.length() != 0) {

					theLongestWord = tmp;
				}
			}
			else return string("EOR"); // END OF RECURTION
		}
	}

	return string(theLongestWord);
}


// Words separation using dictionary
string addSpaces(const string &text, const set<string> &dict) {

	string result, word;
	vector<string> words;


	// Идём по всему тексту
	int i = 0;
	while (i < text.length() - maxLengthOfWord) {

		//	cout << endl << "Position of i: " << i << endl;
		word = cutWordsRecursively(text, dict, i, 8);
		cout << word << endl;
		i += word.length();
		if (word.length() == 0)
			i++;
		words.push_back(word);
	}


	for (int i = 0; i < words.size(); ++i) {
		result += words[i] + " ";
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
	cout << "Everything is ready:" << endl << endl;
	dict.insert("баурджан");
	dict.insert("момышулы");
	dict.insert("панфилов");
	dict.insert("панфилова");
	dict.insert("волоколамское");
	dict.insert("волоколамскому");
	cout << addSpaces(text, dict);

	_getch();
}