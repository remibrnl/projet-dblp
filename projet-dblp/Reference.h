#pragma once

#include <string>
#include <vector>

#ifndef TAG_H
#define TAG_H
#include "tag.h"

#endif 


class Reference
{
	private:
		int referenceNumber;
		string link_to_reference;
		vector<string> tagNames;
		vector<Tag*> tags;

	public:
		//Constructeurs et destructeurs
		Reference(int Number);
		Reference(int Number, string URL_link, vector<string> tagNames, int namesArraySize);
		Reference(int Number, string URL_link, vector<string> tagNames, int namesArraySize, vector<Tag*> tagList);
		~Reference();

		//Methods
		void AddTag(Tag * tag = nullptr, string tagName = nullptr);
		void DelTag(Tag* tag = nullptr, string tagName = nullptr);
		

};

