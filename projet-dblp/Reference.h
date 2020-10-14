#pragma once

#include <string>

#ifndef TAG_H
#define TAG_H
#include "tag.h"

#endif 


class Reference
{
	private:
		int referenceNumber;
		Tag** tags;

	public:
		//Constructeurs et destructeurs
		Reference(int Number);
		Reference(int Number, Tag** tagList);
		~Reference();

		//Methods
		void AddTag(Tag* tag);
		void DelTag(Tag* tag);
		void DelTag(std::string tagName);

};

