#include "FileParser.h"
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

FileParser::FileParser(string path, int limit, vector<string*> tagNames)
{
	ifstream fileStream;

	fileStream.open(path);

	if (fileStream.is_open()) {
		while (!fileStream.eof()) {
			string line;
			getline(fileStream, line);
			if (line.empty()) break;

			for (auto it = begin(tagNames); it != end(tagNames); ++it) {
				if (line.find(**it) != string::npos) {
					parseArray.push_back(new Tag(**it, line));
				}
				else break;
			}
		}
	}
	fileStream.close();
	
}