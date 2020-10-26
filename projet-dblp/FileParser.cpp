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

vector<Reference>& FileParser::parseFile(int numberToCreate, vector<Tag> tags_list)
{
	vector<Reference> references_vect;

	// open file
	ifstream input_stream(path_to_file);

	if (!input_stream) {
		if (!input_stream.is_open()) std::cout << "EXCEPTION FSTREAM A FAIRE : le fichier n'a pas été ouvert correctement" << std::endl;

		int i = 0;

		// on veut parcour les références une par une
		while (true) {
			// creation d'une référence
			Reference reference(i);

			// lecture des différents tags ?
			for (Tag tag : tags_list) {

				Tag* new_tag = new Tag(tag);

				// lire les balises puis envoyer les string dans new_tag.genereatetwogrammatrix


				reference.AddTag(new_tag);
			}

		}
	}

	input_stream.close();
}
