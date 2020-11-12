// projet-dblp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Tag.h"
#include "FileParser.h"
#include "Reference.h"
#include <time.h>

int main(int argc, char* argv[], char *envp[])
{
    // command:
    // ./prog.exe -t <list of tags>  -f <paths of files> -o <output bitmap>
    
    vector<string> tags;
    vector<FileParser> files;
    char* output_path = nullptr;

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

        if (reading[0]) {
            tags.push_back(argv[i]);

            continue;
        }
        if (reading[1]) {
            files.push_back(FileParser(argv[i]));

            continue;
        }
        if (reading[2]) {

            output_path = argv[i];

            continue;
        }
    }

    // error verification
    if (tags.empty() || files.empty() || !output_path) {
        cout << "Error in command line argument." << endl;
        cout << "Usage:" << endl;
        cout << argv[0] << " -t <list of tags>  -f <paths of files> -o <output bitmap>" << endl;

        ::exit(EXIT_FAILURE);
    }

    

    /* std::vector<Tag> tag_list;

    for (int i = 0; i < argc; i++) {
        Tag current(argv[i]);
        tag_list.push_back(current);

    std::cout << "Hello World!\n";
}

    Tag test();*/
    /*
    Tag testtag("author", "<author>Nicolas est un giga PD</author>");

    string teststr = "AA";
	string toParse = "Le test se Fait bIeN";
    int left = 0;
    int right = 0;
    */

    //string url = "test_parser.txt";

    //FileParser fileParser(url);

    //vector<Reference*>* refs;

    

    //tags.push_back("author");
    //tags.push_back("title");

    //refs = fileParser.parseFile(0, tags);

    

    

    /*
    files.push_back(FileParser("test_parser_1.txt"));
    files.push_back(FileParser("test_parser_2.txt"));
    files.push_back(FileParser("test_parser_3.txt"));
    files.push_back(FileParser("test_parser_4.txt"));
    files.push_back(FileParser("test_parser_5.txt"));
    files.push_back(FileParser("test_parser_6.txt"));
    files.push_back(FileParser("test_parser_7.txt"));
    files.push_back(FileParser("test_parser_8.txt"));
    */

    vector<vector<Reference*>*> output_refs;

    #pragma omp parallel for num_threads(files.size())
    for (int i = 0; i < files.size(); i++) {
        cout << "thread:" << omp_get_thread_num() << " iteration:" << i << " started." << endl;
        output_refs.push_back(files[i].parseFile(0, tags));
        cout << "thread:" << omp_get_thread_num() << " iteration:" << i << " done." << endl;
    }




    /*for (auto ref : *refs) {
        auto ref_tags = ref->getTags();
        for (auto tag : ref_tags) {
            
            //tag->getTwoGramMatrix();

            cout << endl;
       }
    }*/

	cout << "time elapsed:" << clock();
   
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
