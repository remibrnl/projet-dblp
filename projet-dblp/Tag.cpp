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

void Tag::indexesTwoGram(int &coordX, int &coordY, std::string twogram)
{
	coordX = twogram.at(0);
	coordY = twogram.at(1);

	int index = 0;


	switch (coordX) {
	case 'a':
		break;
	case 'b':
		index +=1;
		break;
	case 'c':
		index +=2;
		break;
	case 'd':
		index +=3;
		break;
	case 'e':
		index +=4;
		break;
	case 'f':
		index +=5;
		break;
	case 'g':
		index +=6;
		break;
	case 'h':
		index +=7;
		break;
	case 'i':
		index +=8;
		break;
	case 'j':
		index +=9;
		break;
	case 'k':
		index +=10;
		break;
	case 'l':
		index +=11;
		break;
	case 'm':
		index +=12;
		break;
	case 'n':
		index +=13;
		break;
	case 'o':
		index +=14;
		break;
	case 'p':
		index +=15;
		break;
	case 'q':
		index +=16;
		break;
	case 'r':
		index +=17;
		break;
	case 's':
		index +=18;
		break;
	case 't':
		index +=19;
		break;
	case 'u':
		index +=20;
		break;
	case 'v':
		index +=21;
		break;
	case 'w':
		index +=22;
		break;
	case 'x':
		index +=23;
		break;
	case 'y':
		index +=24;
		break;
	case 'z':
		index +=25;
		break;
	case ' ':
		index +=26;
		break;
	case '0':
		index +=27;
		break;
	case '1':
		index +=28;
		break;
	case '2':
		index +=29;
		break;
	case '3':
		index +=30;
		break;
	case '4':
		index +=31;
		break;
	case '5':
		index +=32;
		break;
	case '6':
		index +=33;
		break;
	case '7':
		index +=34;
		break;
	case '8':
		index +=35;
		break;
	case '9':
		index +=36;
		break;
	}

	switch (secondletter) {
	case 'a':
		break;
	case 'b':
		index += 1;
		break;
	case 'c':
		index += 2;
		break;
	case 'd':
		index += 3;
		break;
	case 'e':
		index += 4;
		break;
	case 'f':
		index += 5;
		break;
	case 'g':
		index += 6;
		break;
	case 'h':
		index += 7;
		break;
	case 'i':
		index += 8;
		break;
	case 'j':
		index += 9;
		break;
	case 'k':
		index += 10;
		break;
	case 'l':
		index += 11;
		break;
	case 'm':
		index += 12;
		break;
	case 'n':
		index += 13;
		break;
	case 'o':
		index += 14;
		break;
	case 'p':
		index += 15;
		break;
	case 'q':
		index += 16;
		break;
	case 'r':
		index += 17;
		break;
	case 's':
		index += 18;
		break;
	case 't':
		index += 19;
		break;
	case 'u':
		index += 20;
		break;
	case 'v':
		index += 21;
		break;
	case 'w':
		index += 22;
		break;
	case 'x':
		index += 23;
		break;
	case 'y':
		index += 24;
		break;
	case 'z':
		index += 25;
		break;
	case ' ':
		index += 26;
		break;
	case '0':
		index += 27;
		break;
	case '1':
		index += 28;
		break;
	case '2':
		index += 29;
		break;
	case '3':
		index += 30;
		break;
	case '4':
		index += 31;
		break;
	case '5':
		index += 32;
		break;
	case '6':
		index += 33;
		break;
	case '7':
		index += 34;
		break;
	case '8':
		index += 35;
		break;
	case '9':
		index += 36;
		break;
	}
	return index;
}
