#ifndef EXCEPTIONS
#define EXCEPTIONS
#include<exception>
#include<iostream>
#include<string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class TextToEnumConversionError:public exception
{
public:
	const char* what() const noexcept override
	{
		return "Error: Inputted text does not match the expected values";
	}
};

class EnumNotFound:public exception
{
public:
	const char* what() const noexcept override
	{
		return "Error: Enum value not found";
	}
};

class InvalidChoice:public exception
{
public:
	const char* what() const noexcept override
	{
		return "Error: Invalid choice";
	}
};

class FileNotOpened :public exception
{
private:
	const char* fileName;
	char* error;
public:
	FileNotOpened(string fileName)
	{
		this->fileName = fileName.c_str();
		
		error = new char[92]; //file name needs to be less than 50 characters(92 - 41 - 1)
	}

	~FileNotOpened()
	{
		delete[] error;
	}

	const char* what() const noexcept override
	{
		strcpy_s(error, sizeof error, "Error: the following file did not open: ");
		strcat_s(error,sizeof error, fileName);
		return error;
	}
};
#endif