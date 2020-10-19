#include "Reference.h"

Reference::Reference(int number) {
	this->referenceNumber = number;
}

Reference::Reference(int Number, vector<string>  tagNames, int namesArraySize)
{
	//Give the reference a Number
	this->referenceNumber = Number;

	//Give to the string array the names of the tag we want to parse, and create the tags objects
	for (int i = 0; i < namesArraySize; i++) {
		this->tagNames.push_back(tagNames[i]);
		tags.push_back(new Tag(tagNames[i]));
	};
}

Reference::Reference(int Number, vector<string> tagNames, int namesArraySize, vector<Tag*> tagList)
{
	//Give the reference a Number
	this->referenceNumber = Number;

	//Give to the string array the names of the tag we want to parse, and create the tags objects
	for (int i = 0; i < namesArraySize; i++) {
		this->tagNames[i] = tagNames[i];
	};
}

Reference::~Reference()
{
	for (int i = 0; i < tagNames.size(); i++)
	{
		delete tags[i];
	}
}

void Reference::AddTag(Tag * tag = nullptr, string tagName = nullptr)
{
	if (tag) {
		this->tags.push_back(tag);
		return;
	}
	else if (!tagName.empty()) {
		this->tags.push_back(new Tag(tagName));
		return;
	}
}

void Reference::DelTag(Tag * tag = nullptr, string tagName = nullptr)
{
	if (tag) {
		for (int i = 0; i < this->tagNames.size(); i++) {
			if (this->tags.at(i)->getName.compare(tag->getName()) == 0) {
				delete tags.at[i]; // Peut etre que la suppression se fait mal
				tags.erase(tags.begin() + i);
			}
		}
	}

	if (!tagName.empty())
	{
		for (int i = 0; i < this->tagNames.size(); i++) {
			if (this->tags.at(i)->getName.compare(tagName) == 0) {
				delete tags.at[i];
				tags.erase(tags.begin() + i);
			}
		}
	}
}






;