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

		/**
			\brief Confort Constructor
			\param Number The number of the reference to instanciate
			\return An new reference object 
		*/
		Reference(int Number);

		/**
			\brief Confort Constructor
			\param Number Number of the reference to instanciate
			\param URL_link The link to the web page of the reference
			\param tagNames an Array of all the tags to parse
			\post
			\return the index of the corresponding two-gram in the matrix
		*/
		// Reference(int Number, string URL_link, vector<string> tagNames);

		/**
			\brief Confort Constructor, used in case if we want to copy a referene=ce for any reason
			\param Number Number of the reference to instanciate
			\param URL_link The link to the web page of the reference
			\param tagNames an Array of all the tags to parse
			\param tagList 
			\post 
			\return the index of the corresponding two - gram in the matrix
		*/
		Reference(int Number, const string& URL_link, const vector<string>& tagNames);

		/**
			\brief Copy constructor
		*/
		Reference(const Reference& copy);

		/**
			\brief Destructor of the class
			\post All the Tags of the Array are deleted
		*/
		~Reference();

		//Methods

		/**
			\brief this method add a tag to a reference
		*/
		void AddTag(Tag * tag = nullptr, string tagName = nullptr);

		/**
			\brief this methid delete a tag of a reference
		*/
		void DelTag(Tag* tag = nullptr, string tagName = nullptr);
		
		
		vector<Tag*> getTags() const;

		int getReferenceNumber();
};

