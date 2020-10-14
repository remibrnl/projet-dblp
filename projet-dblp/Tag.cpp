#include "Tag.h"

Tag::Tag(string name_tag)
{
	this->name_tag = name_tag;

	// zeroes in the 2-gram matrix

	for (int row; row < CHAR_NUMBER; row++) {
		for (int col; col < CHAR_NUMBER; col++) {
			two_gram_matrix[row][col];
		}
	}
}
