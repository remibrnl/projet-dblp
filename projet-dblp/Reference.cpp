#include "Reference.h"

Reference::Reference(int number) {
	this->referenceNumber = number;
}


Reference::Reference(const Reference& copy)
{
	referenceNumber = copy.referenceNumber;
	link_to_reference = copy.link_to_reference;
	tagNames = copy.tagNames;
	tags = copy.tags;
}
Reference::Reference(int Number, string URL_link, vector<string>  tagNames)
{
	//Give the reference a Number
	this->referenceNumber = Number;

	//as wished we keep the link to the DBLP reference
	this->link_to_reference = URL_link;

	//Give to the string array the names of the tag we want to parse, and create the tags objects
	for (int i = 0; i < tagNames.size(); i++) {
		this->tagNames.push_back(tagNames[i]);
		tags.push_back(new Tag(tagNames[i]));
	};
}

Reference::Reference(int Number, string URL_link, vector<string> tagNames, vector<Tag*> tagList)
{
	//Give the reference a Number
	this->referenceNumber = Number;

	//as wished we keep the link to the DBLP reference
	this->link_to_reference = URL_link;

	//Give to the string array the names of the tag we want to parse, and create the tags objects
	for (int i = 0; i < tagNames.size(); i++) {
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

void Reference::AddTag(Tag * tag, string tagName)
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

void Reference::DelTag(Tag * tag, string tagName)
{
	if (tag) {
		for (int i = 0; i < this->tagNames.size(); i++) {
			if (this->tags.at(i)->getName().compare(tag->getName()) == 0) {
				delete &tags.at(i); // Peut etre que la suppression se fait mal
				tags.erase(tags.begin() + i);
			}
		}
	}

	if (!tagName.empty())
	{
		for (int i = 0; i < this->tagNames.size(); i++) {
			if (this->tags.at(i)->getName().compare(tagName) == 0) {
				delete tags.at(i);
				tags.erase(tags.begin() + i);
			}
		}
	}
}






;