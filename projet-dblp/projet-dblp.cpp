// projet-dblp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include <vector>
#include <chrono>
#include "Tag.h"
#include "FileParser.h"
#include "Reference.h"
#include "FastMapCalculs.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[], char *envp[])
{
    // COMMAND LINE READING

    // command:
    // ./prog.exe -t <list of tags>  -f <paths of files> -o <output bitmap>

    vector<string> tags;
    char* files_directory = nullptr;
    char* output_path = nullptr;
    bool no_ref_tag = false;

    bool reading[3] = {false, false, false};
    // 0     1      2
    // tags, files, output_path

    for (int i = 1; argv[i] != NULL; ++i) {
        // tags
        if (strcmp(argv[i], "-t") == 0) {
            reading[0] = true;

            reading[1] = false;
            reading[2] = false;

            continue;
        }
        

        // files
        if (strcmp(argv[i], "-f") == 0) {
            reading[1] = true;

            reading[0] = false;
            reading[2] = false;

            continue;
        }


        // output bitmap
        if (strcmp(argv[i], "-o") == 0) {
            reading[2] = true;

            reading[0] = false;
            reading[1] = false;

            continue;
        }

        // tags reading
        if (reading[0]) {
            tags.push_back(argv[i]);

            continue;
        }

        // files readings
        if (reading[1]) {
            files_directory = argv[i];

            continue;
        }

        // output bitmap reading
        if (reading[2]) {

            output_path = argv[i];

            continue;
        }
    }

    // error command parameters check
    if (tags.empty() || !files_directory || !output_path) {
        cout << "Error in command line argument." << endl;
        cout << "Usage:" << endl;
        cout << argv[0] << " -t <list of tags>  -f <directory of files> -o <output bitmap>" << endl;

        ::exit(EXIT_FAILURE);
    }

    // check no tag option
    // no ref tag = 1 tag only
    if (tags.size() == 1) {
        no_ref_tag = true;
    }

    // print options
    cout << "files_directory: " << files_directory << endl;
    cout << "output_path: " << output_path << endl;
    for (Tag tag : tags) {
        cout << "tags: " << tag.getName() << endl;
    }
    cout << "no_ref_tag: " << no_ref_tag << endl;
    cout << "max_threads: " << omp_get_max_threads() << endl << endl;


    // PARSING REFERENCES
    
    const chrono::steady_clock::time_point parsing_time_begin = chrono::steady_clock::now();

    // iterate files in the provided directory and create fileparser objects
    vector<FileParser> files;

    for (const auto& file : fs::directory_iterator(files_directory)) {
        files.emplace_back(FileParser(static_cast<string>(file.path().string())));
    }


    vector<vector<Reference*>*> output_refs;
	
    int i_reference = 0;

    #pragma omp parallel for shared(i_reference) num_threads(omp_get_max_threads())
    for (int i = 0; i < static_cast<int>(files.size()); i++) {
        cout << "thread:" << omp_get_thread_num() << " file:" << i << " started." << endl;
        try {
            output_refs.push_back(files[i].parseFile(tags, i_reference, no_ref_tag));
        }
        catch (const exception& e) {
            cerr << "Exception : " << e.what();
        }
        cout << "thread:" << omp_get_thread_num() << " file:" << i << " done." << endl;
    }

    const chrono::steady_clock::time_point parsing_time_end = chrono::steady_clock::now();
    cout << "parsing time elapsed: " << chrono::duration_cast<chrono::milliseconds> (parsing_time_end - parsing_time_begin).count() << "ms" << endl;


    // COMPUTE COORDINATES

    const chrono::steady_clock::time_point fastmap_time_begin = chrono::steady_clock::now();

    cout << "start coordinates computing." << endl;

    for (string Tag : tags) {
        cout << "La balise HTML parsee est :"<< Tag << endl;

        //Calculate the FastMap Reductions

        try {
            FastMapCalculs::calculateCoord(output_refs, 100000, Tag);
        }
        catch (const exception& e) {
            cerr << "Exception : " << e.what() << endl;
        }

        //Generate BitMap
        //The method to generate the bitmap
    }
    

    cout << "end coordinates computing." << endl;

    const chrono::steady_clock::time_point fastmap_time_end = chrono::steady_clock::now();
    cout << "coordinates computing time elapsed: " << chrono::duration_cast<chrono::milliseconds> (fastmap_time_end - fastmap_time_begin).count() << "ms" << endl;

    FastMapCalculs::printCoords();

    /*
    for (auto file : output_refs) {
        for (auto ref : *file) {
            
            for (auto tag : ref->getTags()) {
                tag->getTwoGramMatrix();
                cout << endl;
                //cout << tag->getSentence() << endl;
            }
            

            cout << ref->getReferenceNumber() << "  ";
        }
    }
    */

    ::exit(EXIT_SUCCESS);
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
