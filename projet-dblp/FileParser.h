#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Reference.h";

using namespace std;

class FileParser
{
	private:
		string path_to_file;
		//iostream input_stream;

	public:
		FileParser();
		FileParser(string path_to_file);
		FileParser(const FileParser& copy);

		string getPath();
		void setPath(string path_to_file);

		// pas sur ??
		Reference& create_reference(iostream file);

		vector<Reference*>* parseFile(string path, int limit, vector<string*> tagNames);

};

