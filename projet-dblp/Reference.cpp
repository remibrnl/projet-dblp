#include "Reference.h"

Reference::Reference(int number) {
	this->referenceNumber = number;
	tags = new Tag*;
};