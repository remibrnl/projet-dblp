#pragma once
#include <vector>
#include <string>

#define CHAR_NUMBER 36

using namespace std;

class Tag
{
private:
	string name_tag;
	string element_to_parse;
	int two_gram_matrix[CHAR_NUMBER][CHAR_NUMBER];
public:
	Tag();
	Tag(string name_tag);

	string getName();
	void indexesTwoGram(int &coordX, int &coordY,string twogram);
	int generateTwoGramMatrix(string toParse);

};

