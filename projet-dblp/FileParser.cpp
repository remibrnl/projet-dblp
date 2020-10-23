#include "FileParser.h"

FileParser::FileParser(string path_to_file)
{
	this->path_to_file = path_to_file;
}

FileParser::FileParser(const FileParser& copy)
{
	this->path_to_file = copy.path_to_file;
}

string FileParser::getPath()
{
	return path_to_file;
}

void FileParser::setPath(string path_to_file)
{
	this->path_to_file = path_to_file;
}

vector<Reference>& FileParser::parseFile(int numberToCreate)
{
	vector<Reference> references_vect;

	// open file
	ifstream input_stream(path_to_file);

	if (!input_stream) {
		if (!input_stream) std::cout << "EXCEPTION FSTREAM A FAIRE : le fichier n'a pas été ouvert correctement" << std::endl;

		// pas fini
	}
}
