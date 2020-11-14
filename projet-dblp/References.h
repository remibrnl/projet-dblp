#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <omp.h>
#include <fstream>
#include <fstream>
#include <algorithm>
#include <codecvt>

#define CHAR_NUMBER 37
#define TOTAL_CHAR_NUMBER 1369
#define REFERENCE_BEGIN_TAG "<ref>"
#define REFERENCE_END_TAG "</ref>"

using namespace std;

class References
{
private:
	int size = 0;
	vector<string> tags_names;
	vector<vector<uint8_t[TOTAL_CHAR_NUMBER]>> two_gram_array;

	void parse_file(const string& file_path);
	void generatetwogram(const string& tag, const string& line);

public:

	void parse_all(vector<string> files_paths);

	References(vector<string> tags_names);
	References(const References& copy);
	References& operator=(const References& copy);
	~References();
};

