#pragma once

#pragma once
#ifndef CUSTOM_STRING_HEADER
#define CUSTOM_STRING_HEADER




class String
{
public:
	String();
	String(const char* _str);
	String(const String& _other);
	String(const double _str);
	~String();

public:
	size_t Length() const;
	char& CharacterAt(size_t _index);
	const char& CharacterAt(size_t _index) const;

	bool EqualTo(const String& _other) const;

	String& Append(const String& _str);
	String& Prepend(const String& _str);

	const char* CStr() const;

	String& ToLower();
	String& ToUpper();

	size_t Find(const String& _str);
	size_t Find(size_t _startIndex, const String& _str);

	String& Replace(const String& _find, const String& _replace);

	String& ReadFromConsole();
	String& WriteToConsole();
	static void WriteInColor(unsigned short colorCode, String outputStr);
	static void WriteInColor(unsigned short colorCode, double outputdouble);
	const String& WriteToConsole() const;

public:
	bool operator==(const String& _other);
	bool operator!=(const String& _other);
	bool operator<(const String& _other);

	String& operator=(const String& _str);

	char& operator[](size_t _index);
	const char& operator[](size_t _index) const;

private:
	char* str;
};

#endif