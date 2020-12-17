#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <codecvt>
#include "Reference.h"

#define REFERENCE_BEGIN_TAG "<ref>"
#define REFERENCE_END_TAG "</ref>"

using namespace std;

class FileParser
{
	private:
		string path_to_file;
		//iostream input_stream;

	public:
		FileParser(string path_to_file);
		FileParser(const FileParser& copy);

		string getPath();
		void setPath(string path_to_file);

		// pas sur ??
		// Reference& create_reference(iostream file);

		vector<Reference*>* parseFile(const vector<string>& tagNames, int& i_reference, bool no_ref_tag);

};

