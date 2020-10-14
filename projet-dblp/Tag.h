#pragma once
#include <vector>
#include <string>

using namespace std;

class Tag
{
private:
	string name_tag;
	string element_to_parse;
	vector<vector<int>> two_gram_matrix;
public:
	Tag(string name_tag);
};

