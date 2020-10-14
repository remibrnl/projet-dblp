#include "Tag.h"

Tag::Tag(string name_tag)
{
	this->name_tag = name_tag;
	
	// initialisation de la matrix 2-gram
	two_gram_matrix = vector<vector<int>>(36, vector<int>(36));
}
