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
			for (string tag : tags_names) {

				if (line.find(tag) != string::npos) {
					//current_ref->AddTag(new Tag(tag, line), tag);

					two_gram_array[i_tag] = ;

					continue;
				}
				i_tag++;
			}
		}
	}
	fileStream.close();
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

References::References()
{
}
