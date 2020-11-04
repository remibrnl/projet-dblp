// projet-dblp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Tag.h"
#include "FileParser.h"

int main(int argc, char* argv[])
{
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

    string url = "test_parser.txt";

    FileParser fileParser(url);

    vector<Reference*>* refs;

    vector<string> tags;

    tags.push_back("author");
    tags.push_back("title");

    refs = fileParser.parseFile(0, tags);

    int* matrix;

    for (auto ref : *refs) {
        auto ref_tags = ref->getTags();
        for (auto tag : ref_tags) {
            
            tag->getTwoGramMatrix();

            cout << endl;
       }
    }

    //std::cout << left << "," << right << std::endl;
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
