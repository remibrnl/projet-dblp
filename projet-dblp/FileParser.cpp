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

vector<Reference*>* FileParser::parseFile(int limit, const vector<string>& tagNames)
{
	vector<Reference*>* references = new vector<Reference*>;

	ifstream fileStream;

	fileStream.open(path_to_file);

	if (fileStream.is_open()) {

		Reference* current_ref = new Reference(0);
		int i_reference = 1;

		while (!fileStream.eof()) {
			string line;
			
			getline(fileStream, line);

			if (line.empty()) break;

			if (line.find(REFERENCE_BEGIN_TAG) != string::npos) {
				// debut nouvelle reference

				if (current_ref == nullptr) current_ref = new Reference(i_reference);

				continue;
			}
			else if (line.find(REFERENCE_END_TAG) != string::npos) {
				// fin reference

				references->push_back(current_ref);
				current_ref = nullptr;

				i_reference++;

				continue;
			}

			for (auto tag : tagNames) {

				if (line.find(tag) != string::npos) {
					current_ref->AddTag(new Tag(tag, line), tag);

					continue;
				}
			}
		}
	}
	fileStream.close();
	
	return references;
}