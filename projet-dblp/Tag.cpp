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

void Tag::indexesTwoGram(int& leftid, int& rightid, std::string twogram)
{
	char leftc = twogram.at(0);
	char rightc = twogram.at(1);

	// indices matrices
	// espace 0
	// a-z 1-26
	// 0-9 27-37

	// caractère left

	// espace
	if (leftc == 32) {
		leftid = 0;
	}
	// majuscules
	else if (leftc >= 65 && leftc <= 90) {
		leftid = leftc - 64;
	}
	// minuscules
	else if (leftc >= 97 && leftc <= 122) {
		leftid = leftc - 96;
	}
	// chiffres
	else if (leftc >= 48 && leftc <= 57) {
		leftid = leftc - 21;
	}
	
	// caractère right

	if (rightc == 32) {
		rightid = 0;
	}
	// majuscules
	else if (rightc >= 65 && rightc <= 90) {
		rightid = rightc - 64;
	}
	// minuscules
	else if (rightc >= 97 && rightc <= 122) {
		rightid = rightc - 96;
	}
	// chiffres
	else if (rightc >= 48 && rightc <= 57) {
		leftid = rightc - 21;
	}

}
