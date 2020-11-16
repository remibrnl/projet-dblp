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
	// size : number of references
	int size = 0;

	// names of processed tags
	vector<string> tags_names;

	// array of array of matrixes
	// a subarray represents a tag with its matrixes of two gram
	vector<vector<uint8_t*>> two_gram_array;

	// parse a file from a given path
	void parse_file(const string& file_path);

	// return a 2-gram matrix from a given line
	uint8_t* generate_matrix(const string& line) const;

	// return indexe for a given two_gram string
	int indexes_two_gram(const string& two_gram) const;

public:

	// generate all matrixses for given paths
	void parse_all(vector<string> files_paths);

	// give the tags to process
	References(vector<string> tags_names);

	// TODO

	References(const References& copy);
	References& operator=(const References& copy);
	~References();
};

