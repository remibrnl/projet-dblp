#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <regex>

#define CHAR_NUMBER 37

using namespace std;

class Tag
{
private:
	string name_tag;
	string element_to_parse;
	int two_gram_matrix[CHAR_NUMBER*CHAR_NUMBER];
public:

	/**
		\brief Default constructor, used for tests
		\post The two Strings are initialized to nullptr. The Matrix is filled with 0
		\return A new Tag object
	*/
	Tag();

	/**
		\brief Comfort constructor
		\param name_tag Name of the tag to parse
		\post The tag object is initialized with the sentence to parse to nullptr. The matrix is filled with 0
		\return A new Tag object
	*/
	Tag(string name_tag);

	/**
		\brief Comfort constructor
		\param name_tag Name of the tag to parse
		\param sentence_to_parse Name of the sentence to parse
		\post The matrix is filled with 0
		\return A new Tag object
	*/
	Tag(string name_tag, string sentence_to_parse);

	/**
		\brief Copy constructor
	*/
	Tag(const Tag& copy);

	/**	
		\brief Getter on the name of the Tag
		\return The name of the tag parsed
	*/
	string getName();

	/**
		\brief Getter on the sentence we want to parse
		\post pVECArray is copied, the user have to disalocate the object if he dynamically did
		\return A new CMatrix object
	*/
	string getSentence();

	/**
		\brief Getter on the sentence we want to parse
		\param nColumnNumber Number of columns
		\post the index returned is an index between 0 and 1369, considering the mtrix is on a single line
		\return the index of the corresponding two-gram in the matrix

		This methode take as parameter a two-gram like: "ar" , "F4", " r" or "aA"
		It returns an index of the column number in the matrix, corresponding to the two-gram
	*/
	int indexesTwoGram(string twogram);

	/**
		\brief The method wich instantiate the matrix of the corresponding two-grams of a sentence
		\param toParse the sentence we want to parse 
		\post The values in the matrix have changed corresponding to the number of occurences of a two-gram in the sentence
	*/
	void generateTwoGramMatrix(string toParse);

};

