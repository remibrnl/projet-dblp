#include "References.h"

void References::parse_file(const string& file_path)
{
	ifstream fileStream;

	fileStream.open(file_path);

	// pas sur
	fileStream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	if (fileStream.is_open()) {

		// Reference* current_ref = new Reference(0);
		// int i_reference = 1;
		bool opened_reference = false;

		while (!fileStream.eof()) {
			string line;

			fileStream >> line;

			//getline(fileStream, line);

			if (line.empty()) break;

			if (line.find(REFERENCE_BEGIN_TAG) != string::npos) {
				// debut nouvelle reference

				if (opened_reference) throw exception("Reference markup read exception");

				// open reference
				opened_reference = true;

				// if (current_ref == nullptr) current_ref = new Reference(i_reference);
				

				continue;
			}
			else if (line.find(REFERENCE_END_TAG) != string::npos) {
				// fin reference

				//references->push_back(current_ref);
				//current_ref = nullptr;



				// close reference
				opened_reference = false;
				//i_reference++;

				continue;
			}

			int i_tag = 0;

			size_t firstPos;
			size_t lastPos;

			for (string tag : tags_names) {

				if (line.find(tag) != string::npos) {
					//current_ref->AddTag(new Tag(tag, line), tag);

					two_gram_array[i_tag].push_back(generate_matrix(line));

					if (regex_match(line, regex(("<.+>.+")))) {
						firstPos = line.find_first_of('>') + 1;
						lastPos = line.find_last_of("<");
						line.substr(firstPos, lastPos - firstPos);

						two_gram_array[i_tag].push_back(generate_matrix(line.substr(firstPos, lastPos - firstPos)));
					}
					else {
						two_gram_array[i_tag].push_back(generate_matrix(line));
					}

					continue;
				}
				i_tag++;
			}
		}
	}
	fileStream.close();
}

uint8_t* References::generate_matrix(const string& line) const
{
	uint8_t matrix[TOTAL_CHAR_NUMBER];

	

	

	vector<string> twogramList;
	string twoGram = "";
	int firstLetter = 0;
	int secondLetter = 1;

	while (line.size()) {
		//We build the actual twogram..
		twoGram.push_back(line.at(firstLetter));
		twoGram.push_back(line.at(secondLetter));

		//.. to temporary store it in an array
		twogramList.push_back(twoGram);

		//and we reinitialize the string for the next twogram
		twoGram.clear();
		// twogram = "";
		firstLetter++;
		secondLetter++;
	}

	int indexToIncrement = 0;

	// à paralléliser faire attention aux conflits sur two_gram_matrix[indexToIncrement]


	int i;

	//#pragma omp parallel
	{
		//#pragma omp for private(i,indexToIncrement)
		for (i = 0; i < twogramList.size(); i++) {

			indexToIncrement = indexes_two_gram(twogramList.at(i));

			if (indexToIncrement == -1) continue;

			//#pragma omp critical
			{
				matrix[indexToIncrement] += 1;
			}
		}
	}
	//cout << endl;

	return matrix;
}

int References::indexes_two_gram(const string& two_gram) const
{
	char leftc = two_gram.at(0);
	char rightc = two_gram.at(1);

	int index = 0;
	// indices matrices
	// espace 0
	// a-z 1-26
	// 0-9 27-37

	// caractère left

	// espace
	if (leftc == 32) {
		index += 0;
	}
	// majuscules
	else if (leftc >= 65 && leftc <= 90) {
		index += (leftc - 64) * 37;
	}
	// minuscules
	else if (leftc >= 97 && leftc <= 122) {
		index += (leftc - 96) * 37;
	}
	// chiffres
	else if (leftc >= 48 && leftc <= 57) {
		index += (leftc - 21) * 37;
	}

	// caractère right

	if (rightc == 32) {
		index += 0;
	}
	// majuscules
	else if (rightc >= 65 && rightc <= 90) {
		index += rightc - 64;
	}
	// minuscules
	else if (rightc >= 97 && rightc <= 122) {
		index += rightc - 96;
	}
	// chiffres
	else if (rightc >= 48 && rightc <= 57) {
		index += rightc - 21;
	}
	else {
		index = -1;
	}

	return index;
}


References::References(vector<string> tags_names)
{
	this->tags_names = tags_names;
	two_gram_array.resize(tags_names.size());
}

void References::parse_all(vector<string> files_paths)
{
    #pragma omp parallel for num_threads(files.size())
    for (int i = 0; i < files_paths.size(); i++) {
        cout << "thread:" << omp_get_thread_num() << " iteration:" << i << " started." << endl;
        try {
            output_refs.push_back(files[i].parseFile(0, tags));
        }
        catch (const exception& e) {
            cout << "Exception : " << e.what();
        }
        cout << "thread:" << omp_get_thread_num() << " iteration:" << i << " done." << endl;
    }
}
