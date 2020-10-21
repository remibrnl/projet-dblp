#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Reference.h";

using namespace std;

class FileParser
{
	private:
		string path_to_file;

	public:
		FileParser();
		FileParser(string path);

		string getPath();
		string setPath();

		Reference* createReference();
		vector<Reference> parseFile(int numberToCreate = -1);

};

