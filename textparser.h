#include <fstream>
#include <string>
#include <set>
#include <map>
#include <cctype>
#include <algorithm>
#include <iostream>
#include "queue.h"
#include "stack.h"

#pragma once

//The purpose of this class is to tokenize the words
//Have a struct for the print, scanning text, and  

struct Text{
	std::string print;
//Word that is stripped of punctuations
//this is to print the words as a unique word
	std::string raw;
};

class TextParser{
	
private:
	std::ifstream file;

//after some inspection
//words from this word bank are capitalized normally if its a proper noun
//i.e. Adam although 
	std::ifstream dictionary;
	
	//all words should be lowercase
	std::set<std::string> wordBank;
	Queue<std::string> words;
	Stack<std::string> words_to_fix;
	std::string filename;

	void insertwordtobank();

	void wordbankBlock();
	void wordblock();
	void lineblock();

	void emptystack();

public:
	TextParser();
	void SetFile(std::string);
	void PrintOriginalFile();
	void PrintFixedFile();
	void QueueToText();
	~TextParser();
	std::set<std::string> GetUniqueWords();
	std::map<std::string, int> GetWordFrequency();
//insert all of the words in the txt into the set 
//for this project, we can reverse the words as we're going 
//through the sample text file and see if they match the set or not
//but this would be slower whenever the sample text file
//is greater than the dictionary
	bool init();
	Queue<std::string>* GetQueueHandle();
};
