#include "textparser.h"

TextParser::TextParser(){
	
	/* Unneeded unless using wordbankBlock
	dictionary.open("words.txt");
	if(!dictionary.is_open()) {
		std::cout << "Error, word bank file cannot be found!\n";
	}else{
		insertwordtobank();
	}
	*/
}
TextParser::~TextParser(){
	file.close();
	dictionary.close();
}
//reusing code from lab1
void tolowercase(std::string &a){
	
	std::transform(a.begin(),a.end(),a.begin(), ::tolower);
}
void reverseString(std::string &input){
	int n = input.size();
	for( int i = 0; i < n / 2; i++){
		std::swap(input[i], input[n-i-1]);
	}
}

void reverseStringRange(std::string &input, int a, int b){
	int size = (b - a)/2;
	
	for(int i = 0; i < size/2; i++){
		std::swap(input[a + i], input[b - i]);
	}
}
//gets rid of punctuations
void unPunctuator(std::string &input){
	long unsigned int i = 0;
	while(i < input.size()){
		if(ispunct(input[i])){
			if(input[i] != '-'){
				input.erase(i,1);
				if(i > 0){
					i--;
				}
			}else{
				i++;
			}
		}else{
			i++;
		}
	}
}
//WIP
void TextParser::lineblock(){
	std::string s;
	while(file){
		
		std::getline(file, s);
		//std::cout << s;
		int a = 0, b = 0;
		int size = s.size();
		
		for(int i = 0; i < size; i++){
			
			if(ispunct(s[i])){
			if(s[i] != '\'' && s[i] != ',' && s[i] != '-'){
				std::cout << "Punc found at, " << i << std::endl;
				if((i - 1) > 0){
				if(s[i] == ' '){
					a = i;
				}}
			}}
			if(isupper(s[i])){
				
				std::cout << "Upper found at, " << i << std::endl;
				if(i + 2 < size){
					
					std::cout << "Good Upper found at, " << i << std::endl;
					if(isupper(s[i+2]) && isblank(s[i+1])){
						std::cout << "Reversing by capitalization seperation\n";
						b = i;
						reverseStringRange(s, a, b);
					}
				}else if(i >= size - 1){
						//std::cout << "Reversing by end string\n";
						//b = i;
						//reverseStringRange(s,a,b);
				}
			}
			
		}
		
	}
	
	std::cout << "Printing: " << s << "end print\n";
}
void TextParser::QueueToText(std::string newFile){
	std::ofstream outputFile;
	
	outputFile.open(newFile, std::ofstream::out | std::ofstream::trunc);
	
	int size = words.GetSize();
	
	for(int i = 0; i < size; i++){
		outputFile << words.front() << " ";
		words.push(words.front());
		words.pop();
	}
	
	outputFile.close();
}
void TextParser::PrintOriginalFile(){
	std::ifstream ifile(filename);
	std::string s;
	while(ifile){
		std::getline(ifile,s);
		std::cout << s << std::endl;
	}
	ifile.close();
}
//deprecated, not needed to be used.
void TextParser::insertwordtobank(){
	//putting all of the words into the dictionary
	//all words should be lowercase
	//AND it should have no puncutation marks
	while(dictionary){
		std::string word;
		std::getline(dictionary, word);
		tolowercase(word);
		wordBank.insert(word);
		
	}
}
void TextParser::emptystack(){
	
	int size = words_to_fix.GetSize();
	for(int i = 0; i < size; i++){
		//fixes the word
		std::string s = words_to_fix.top();
		reverseString(s);
		
		//add to queue
		//std::cout << "Fixed word: " << s << std::endl;
		words.push(s);
		
		//removes from stack
		words_to_fix.pop();
	}
	
}

//WIP and probably not going to be used
void TextParser::wordbankBlock(){
	if(!file.is_open()) return;
	
	while(file){
		
		std::string word;
		
		file >> word;
		std::string raw;
		raw = word;
		unPunctuator(raw);
		tolowercase(raw);
		
		if(wordBank.find(raw) != wordBank.end())
		{
			emptystack();
			words.push(word);
			
		}else{
			words_to_fix.push(word);
			
		}
	}
}

void TextParser::wordblock(){
	//access file
	//run through each word
	//each input goes into a text node in the queue
	if(!file.is_open()) return;
	bool reverseSearch = false;
	 
	while(file){
		std::string word;
		file >> word;
		
		
		switch(reverseSearch)
		{
		case true:	//This case happens second
		
		
			//This case assumes that every word ahead is a reversed word
			//and it will look at the last character of each word onwards
			//if final character is an uppercase, then 
			//this will likely mean its been reversed
			if(isupper(word.back())){
				
				words_to_fix.push(word);
				file>>word;
				//If the FIRST character is a capital of the NEXT word
				if(isupper(word.front())){
				//	std::cout << "reverse check ending\n";
					emptystack();
					words.push(word);
					reverseSearch = false;
				}else{
					words_to_fix.push(word);
				}
				

			}else{
				words_to_fix.push(word);
				
			}
		break;
		case false:		//look at this one first
		
		//if the first character of a word is a 
		//puncutation, very likely the start of a sentence
			if(ispunct(word.front()) && word.front() != ',' && word.front() != '\''){
				reverseSearch = true;	
				//std::cout << "starting reverse checking\n";
				words_to_fix.push(word);
			}else{
				words.push(word);
			}
		break;
		}
		
		
	}
}
std::map<std::string, int> TextParser::GetWordFrequency(){
	int n = words.GetSize();
	std::map<std::string, int> brick;
	
	//loops through the queue pushing the value of the front and popping it
	for(int i = 0; i < n; i++){
		std::string fixed = words.front();
		unPunctuator(fixed);
		tolowercase(fixed);
		
		brick[fixed] += 1;
		words.push(words.front());
		words.pop();
	}
	return brick;
	
}
void TextParser::PrintFixedFile(){
	int n = words.GetSize();
	int count = 1;
	for(int i = 0; i < n; i++){
		std::cout << words.front() << " ";
		if(count % 15 == 0) std::cout << std::endl;
		count++;
		words.push(words.front());
		words.pop();
	}
}
std::set<std::string> TextParser::GetUniqueWords(){
	int n = words.GetSize();
	std::set<std::string> brick;
	for(int i = 0; i < n; i++){
		std::string fixed = words.front();
		unPunctuator(fixed);
		tolowercase(fixed);
		
		brick.insert(fixed);
		words.push(words.front());
		words.pop();
	}
	/*
	 * for(auto iter : GetWordFrequency()){
	 * 		brick.insert(iter.first);
	 * }
	 * 
	 */
	return brick;
}

void TextParser::SetFile(std::string s){
	filename = s;
}

bool TextParser::init(){
/*
 * Steps:
 * Access file for dictionary and sample file
 * Put words from sample file into a queue
 * 		check each word by reversing them, and 
 * 		comparing them to the dictionary
 * 			If yes, put all subsequent words into a stack with their fixed order
 * 				Also mark it for the beginning of the reversed sentence
 * 			If no, mark as end for reversed sentence.
 * 		
 * */

	//check if file is open
	words.clear();
	std::cout << filename << std::endl;
	file.open(filename);
	if(!file.is_open()){
		std::cout << "Error, sample file cannot be found!\n";
		return false;
	}
	
	
	std::cout << "Starting line block\n";
	//wordbankBlock();
	//lineblock();
	wordblock();


	
	file.close();
	
	return true;
}

Queue<std::string>* TextParser::GetQueueHandle(){
	return &words;
}
