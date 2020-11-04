#include "Tag.h"
//This constructor is created more for the tests than the real code
Tag::Tag()
{
	name_tag = "None";
	element_to_parse = "None";
	for (int col = 0; col < CHAR_NUMBER*CHAR_NUMBER; col++) {
		two_gram_matrix[col] = 0;
	}
}

Tag::Tag(string name_tag)
{
	this->name_tag = name_tag;

	// zeroes in the 2-gram matrix

	for (int col = 0; col < CHAR_NUMBER*CHAR_NUMBER; col++) {
		two_gram_matrix[col] = 0;
	}
}

Tag::Tag(string name_tag, string sentence_to_parse)
{
	this->name_tag = name_tag;

	this->element_to_parse = sentence_to_parse;
	// initiate the 2-gram matrix

	for (int col = 0; col < CHAR_NUMBER*CHAR_NUMBER; col++) {
		two_gram_matrix[col] = 0;
	}

	generateTwoGramMatrix(sentence_to_parse);
}

Tag::Tag(const Tag& copy)
{
	name_tag = copy.name_tag;
	element_to_parse = copy.element_to_parse;

	// matrix copy

	int size = CHAR_NUMBER * CHAR_NUMBER;

	for (int i = 0; i < size; i++) {
		two_gram_matrix[i] = copy.two_gram_matrix[i];
	}

}

string Tag::getName()
{
	return this->name_tag;
}

string Tag::getSentence()
{
	return this->element_to_parse;
}

int Tag::indexesTwoGram(std::string twogram)
{
	char leftc = twogram.at(0);
	char rightc = twogram.at(1);

	int index = 0;
	// indices matrices
	// espace 0
	// a-z 1-26
	// 0-9 27-37

	// caractère left

	// espace
	if (leftc == 32) {
		index += 0;
	}
	// majuscules
	else if (leftc >= 65 && leftc <= 90) {
		index += ( leftc - 64) * 37;
	}
	// minuscules
	else if (leftc >= 97 && leftc <= 122) {
		index += (leftc - 96) * 37;
	}
	// chiffres
	else if (leftc >= 48 && leftc <= 57) {
		index += (leftc - 21) * 37;
	}
	
	// caractère right

	if (rightc == 32) {
		index += 0;
	}
	// majuscules
	else if (rightc >= 65 && rightc <= 90) {
		index += rightc - 64;
	}
	// minuscules
	else if (rightc >= 97 && rightc <= 122) {
		index += rightc - 96;
	}
	// chiffres
	else if (rightc >= 48 && rightc <= 57) {
		index += rightc - 21;
	}
	return index;
}

void Tag::generateTwoGramMatrix(string toParse)
{
	vector<string> twogramList;
	string twoGram = "";
	int firstLetter = 0;
	int secondLetter = 1;

	while (secondLetter < this->element_to_parse.size()) {
		//We build the actual twogram..
		twoGram.push_back(element_to_parse.at(firstLetter));
		twoGram.push_back(element_to_parse.at(secondLetter));

		//.. to temporary store it in an array
		twogramList.push_back(twoGram);

		//and we reinitialize the string for the next twogram
		twoGram = "";
		firstLetter++;
		secondLetter++;
	}
	
	int indexToIncrement = 0;
	for (int i = 0; i < twogramList.size(); i++) {

		
		indexToIncrement = indexesTwoGram(twogramList.at(i));
		cout << twogramList.at(i) << ",";

		two_gram_matrix[indexToIncrement] += 1;
	}
}
