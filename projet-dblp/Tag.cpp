#include "Tag.h"

Tag::Tag(string name_tag)
{
	this->name_tag = name_tag;

	// zeroes in the 2-gram matrix

	for (int row=0; row < CHAR_NUMBER; row++) {
		for (int col=0; col < CHAR_NUMBER; col++) {
			two_gram_matrix[row][col];
		}
	}
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
