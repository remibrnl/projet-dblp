#pragma once
#include <vector>
#include <string>
#include <iostream>

#define CHAR_NUMBER 37

using namespace std;

class Tag
{
private:
	string name_tag;
	string element_to_parse;
	int two_gram_matrix[CHAR_NUMBER*CHAR_NUMBER];
public:
	Tag();
	Tag(string name_tag);
	Tag(string name_tag, string sentence_to_parse);

	/**
	Getter on the name of the Tag
	*/
	string getName();

	/**
	Getter on the sentence we want to parse
	*/
	string getSentence();

	/**
	This methode take as parameter a two-gram like: "ar" , "F4", " r" or "aA"
	It returns an index of the column number in the matrix, corresponding to the two-gram 
	*/
	int indexesTwoGram(string twogram);

	void generateTwoGramMatrix(string toParse);

};

