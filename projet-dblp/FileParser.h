#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Reference.h";

using namespace std;

class FileParser
{
	//TODO : test
	private:
		string path_to_file;
		vector<Tag*> parseArray;

	public:
		FileParser(string path, int limit, vector<string*> tagNames);

};

