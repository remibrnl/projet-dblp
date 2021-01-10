#include "FileParser.h"

#pragma warning(disable : 4996)

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

vector<Reference*>* FileParser::parseFile(const vector<string>& tagNames, int &i_reference, bool no_ref_tag)
{
	// verif no_ref_tag
	if (no_ref_tag && (tagNames.size() > 1)) {
		throw new exception("more than 1 tag with no_ref_tag true exception");
	}

	vector<Reference*>* references = new vector<Reference*>;

	ifstream fileStream;

	fileStream.open(path_to_file);

	fileStream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	if (fileStream.is_open()) {

		string line;
		Reference* current_ref = nullptr;

		// just one tag per lines without ref tags
		if (no_ref_tag) {

			string single_tag_name = tagNames[0];

			while (getline(fileStream, line)) {
				
				current_ref = new Reference(i_reference);

				current_ref->AddTag(new Tag(single_tag_name, line), single_tag_name);

				references->push_back(current_ref);

				i_reference++;
			}
		}
		// with <ref> and </ref> tags
		else {
			
			bool opened_reference = false;
			
			current_ref = new Reference(i_reference);
			i_reference++;

			while (getline(fileStream, line)) {

				if (line.empty()) break;

				if (line.find(REFERENCE_BEGIN_TAG) != string::npos) {
					// debut nouvelle reference

					if (opened_reference) throw exception("Reference markup read exception");

					// open reference
					opened_reference = true;

					if (current_ref == nullptr) current_ref = new Reference(i_reference);

					continue;
				}
				else if (line.find(REFERENCE_END_TAG) != string::npos) {
					// fin reference

					references->push_back(current_ref);
					current_ref = nullptr;

					// close reference
					opened_reference = false;
					i_reference++;

					continue;
				}

				for (string tag : tagNames) {

					if (line.find(tag) != string::npos) {
						current_ref->AddTag(new Tag(tag, line), tag);

						continue;
					}
				}

			}
		}
	}

	fileStream.close();
	
	return references;
}