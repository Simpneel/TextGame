#include "String.h"
#include <ostream>
#include <Windows.h>
#include <charconv>

String::String() {
	str = new char[1] {'\0'};						//Initialise a new string  
}

String::String(const char* _str) {					//Initialising a new string using a character array input
	size_t strLength = strlen(_str) + 1;
	str = new char[strLength];
	strncpy(str, _str, strLength);
}

String::String(const float _str) {
	char cVal[128] {};
	std::to_chars(std::begin(cVal), std::end(cVal), _str);
	size_t strLength = strlen(cVal) + 1;
	str = new char[strLength];
	strncpy(str, cVal, strLength);
}

String::String(const String& _other) : str(nullptr) //Initialising a new string using another string var 
{
	size_t _strLen = _other.Length() + 1;
	str = new char[_strLen];
	strncpy(str, _other.str, _strLen);
}

String::~String() {									//Deconstructor
	delete[] str;
}

size_t String::Length() const {						//Uses the strlen command from cstring to get the length of a given char* 

	return strlen(str);
}

char& String::CharacterAt(size_t _index) {			//Returns the character at a given index(_index)
	if (_index > Length()) {
		_index = Length();
	}
	return str[_index];
}

const char& String::CharacterAt(size_t _index) const {//Overloading of the CharacterAt() function above
	if (_index > Length()) {
		_index = Length();
	}
	return str[_index];
}

bool String::EqualTo(const String& _other) const {	//Checks if two strings, str (the string we use EqualTo with) and _other (the string given to function) are exactly the same	
	size_t strEqual = strcmp(str, _other.str);      //It will return false for differences in capitalisation as well as extra whitespaces
	if (strEqual < 0 || strEqual > 0) {
		return false;
	}
	else {
		return true;
	}
}

String& String::Append(const String& _str) {		//Using strncpy and strncat from cstring, takes a string input 
	size_t newLen = Length() + _str.Length() + 1;	//and enters it into the back of the current existing string
	char* strCopy = new char[newLen] {};			//and returns the same 
	strncpy(strCopy, str, Length());
	strncat(strCopy, _str.str, _str.Length());
	delete[] str;
	str = strCopy;
	return *this;
}

String& String::Prepend(const String& _str) {		//Using the same concept as append above, takes a string input
	size_t newLen = Length() + _str.Length() + 1;	//but enters it into the start of the current string instead
	char* strCopy = new char[newLen] {};			//by swapping which values get entered into the strCopy var first
	strncpy(strCopy, _str.str, _str.Length());
	strncat(strCopy, str, Length());
	delete[] str;
	str = strCopy;
	return *this;
}

const char* String::CStr() const {				//Returns a given char* as a String variable
	return str;
}

String& String::ToLower() {							//Returns the string with all characters in lowercase
	for (size_t i = 0; i < strlen(str); i += 1) {
		str[i] = tolower(str[i]);
	}
	return *this;
}

String& String::ToUpper() {							//Returns the string with all characters in uppercase
	for (size_t i = 0; i < strlen(str); i += 1) {
		str[i] = toupper(str[i]);
	}
	return*this;
}

size_t String::Find(const String& _str) {			//Searches for a given substring in the main string using strstr, and returns the starting index of the substring. Returns -1 if it isn't found
	char* strIndexLocation = strstr(str, _str.str);
	if (strIndexLocation == NULL) {
		return -1;
	}
	else {
		size_t finalIndexVal = strIndexLocation - str;
		return finalIndexVal;
	}
}

size_t String::Find(size_t _startIndex, const String& _str) {			//Overloading of Find function, with the additional input of a starting index, Search will start only after the given index and will do the same search
	char* strIndexLocation = strstr(str + _startIndex, _str.str);
	if (strIndexLocation == NULL) {
		return -1;
	}
	else {
		size_t finalIndexVal = strIndexLocation - str;
		return finalIndexVal;
	}
}

String& String::Replace(const String& _find, const String& _replace) {  //Replaces every instance of a given substring in the main string 
	int findLen = _find.Length();
	int replaceLen = _replace.Length();
	int replaceCount = 0;
	for (size_t i = 0; (Find(i, _find) != -1); i += Find(i, _find) + 1) {
		replaceCount++;
	}
	size_t newLen = Length() + ((replaceLen - findLen) * replaceCount) + 1;
	char* newStr = new char[newLen] {};
	int findIndex = Find(_find);
	int strCounter = 0;
	if (findIndex == -1 || _find.Length() == 0) {
		return *this;
	}
	else {
		if (findIndex == 0) {
			strncpy(newStr, _replace.str, replaceLen);
			strCounter += findLen;
		}
		else {
			strncpy(newStr, str, findIndex);
			strCounter += findIndex;
		}
		while (strCounter <= Length()) {
			findIndex = Find(strCounter, _find);
			if (strCounter == findIndex) {
				strncat(newStr, _replace.str, replaceLen);
				strCounter += findLen;
			}
			else if (findIndex != -1) {
				strncat(newStr, str + strCounter, findIndex - strCounter);
				strCounter = findIndex;
			}
			else {
				break;
			}
		}
		if ((strCounter < Length())) {
			strncat(newStr, str + strCounter, Length() - strCounter);
			strCounter += Length() - strCounter;
		}
	}
	delete[] str;
	str = newStr;
	return *this;
}

String& String::ReadFromConsole()				//Takes user given input from the console using cin.get and returns it as a string
{
	//Jared's code for ReadFromConsole
	std::istream::sentry fetcher(std::cin);
	if (!fetcher) {
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		return *this;
	}
	std::streamsize bufferedText = std::cin.rdbuf()->in_avail();
	char* newStr = new char[bufferedText];
	std::cin.rdbuf()->sgetn(newStr, bufferedText);
	newStr[bufferedText - 1] = '\0';
	delete[] str;
	this->str = newStr;
	return *this;

	//My code for ReadFromConsole
	//int x = 50;								
	//char* readInput = new char[x];
	//std::cin.get(readInput, x);
	//for (int i = 0; i <= x; i++) {
	//	if (isblank(readInput[i])) {
	//		x--;
	//	}
	//}
	//std::cin.ignore(x,'\n');					//Tells system to ignore all extra characters after newLine i.e. after user hits enter
	//delete[] str;
	//str = readInput;
	//return *this;
}

String& String::WriteToConsole()				//Prints a string in console
{
	std::cout << str;
	return *this;
}

void String::WriteInColor(unsigned short colorCode, String outputStr) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, colorCode);
	outputStr.WriteToConsole();
	SetConsoleTextAttribute(hcon, 07);
	return void();
}

void String::WriteInColor(unsigned short colorCode, float outputFloat) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, colorCode);
	std::cout << outputFloat;
	SetConsoleTextAttribute(hcon, 07);
	return void();
}

const String& String::WriteToConsole() const {
	std::cout << str;
	return *this;
}

bool String::operator==(const String& _other) {
	return EqualTo(_other);
}

bool String::operator!=(const String& _other) {
	return !(EqualTo(_other));
}

bool String::operator<(const String& _other) {
	if (EqualTo(_other)) {
		return false;
	}
	else {
		int i = 0;
		while (i < Length() && i < _other.Length()) {
			int ascii1 = str[i];
			int ascii2 = _other[i];
			std::cout << ascii1;
			std::cout << ascii2;

			if (ascii1 < ascii2) {
				return true;
				break;
			}
			else if (ascii1 == ascii2) {
				i++;
			}
			else {
				return false;
				break;
			}
		}
	}
}

std::ostream& operator<<(std::ostream& os, String const& m) {
	return os << m.WriteToConsole();
}

String& String::operator=(const String& _other)
{
	if (this == &_other) {
		return *this;
	}
	delete[] str;
	size_t strLen = strlen(_other.str) + 1;
	str = new char[strLen];
	strncpy(str, _other.str, strLen);
	return *this;
}

char& String::operator[](size_t _index)
{
	return CharacterAt(_index);
}

const char& String::operator[](size_t _index) const
{
	return CharacterAt(_index);
}
