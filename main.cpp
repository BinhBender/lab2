#include <iostream>
#include <string>
#include <iomanip>
#include "queue.h"
#include "stack.h"
#include "textparser.h"
#include <fstream>
#include <set>
#include <map>


void ProgramStart();
void printUniqueWords(std::set<std::string>&);
void printWordFrequency(const std::map<std::string, int>);

int main(){
	
	/*
	TextParser tp;
	
	//std::cout << "finding file";
	tp.SetFile("I_have_a_dream_mixed.txt");
	//std::cout << "Starting init";
	tp.init();
	
	
	
	Queue<std::string>* q = tp.GetQueueHandle();
	
	int size = q->GetSize();
	for(int i = 0; i < size - 1; i++){
		std::cout << q->front() << " ";
		q->pop(); 
		
	}

	*/
	
	int userinput = 0;
	std::cout << "+++++++++Welcome to the program+++++++++\n";
	std::cout << "Description\n" << std::setw(5) << " " << "\nThis program works inputting sample files that \nhave sentences with linguistic units that are reversed. The output of this function will be their fixed version and a histogram of all the words\n";
	
	
	
	bool keepRunning = true;
	while(keepRunning){
				
		std::cout << "=====Main Menu=====\n\nPress 1 to start, 2 to end\n";
		std::cin >> userinput;
		
		switch(userinput){
			
			case 1:
				ProgramStart();
			
			break;
			case 2:
				keepRunning = false;
			break;
			
		}
	}
	
	
	std::cout << "\nSad to see you go, but alas, goodbye.\n";
	return 0;
	
}
void printResults(TextParser& tp){
	//amalgamation of all print functions
	std::cout << "\n\nOriginal Text:\n";
	tp.PrintOriginalFile();
	
	std::cout << "\n\nFixed Text:\n";
	tp.PrintFixedFile();
			
			
	std::set<std::string> unique = tp.GetUniqueWords();
	printUniqueWords(unique);
	std::cout << std::endl;
	printWordFrequency(tp.GetWordFrequency());

	std::cout << "\nWhat do you want to name the output?\nInput: ";
	std::string newFile;
	std::cin >> newFile;
	tp.QueueToText(newFile.append(".txt"));

	std::cout << "saving in " << newFile << "...\n";
	
}
void ProgramStart(){
	TextParser tp;
	std::string file1 = "I_have_a_dream_mixed.txt";
	std::string file2 = "RomeoAndJuliet.txt";
	bool keepLooping = true;
	int input;
	

	while(keepLooping){
		bool nopick = true;
		std::cout << "\nPick one of the files\n";
		std::cout << "1 - \"I_have_a_dream_mixed.txt\"\n";
		std::cout << "2 - \"RomeoAndJuliet.txt\"\n";
		std::cout << "3 - Exit\nAwating Input: ";
		std::cin >> input;
		switch(input){
			case 1://file1
				tp.SetFile(file1);
				tp.init();
				nopick = false;
			break;
			case 2://file2
				tp.SetFile(file2);
				tp.init();
				nopick = false;
			break;
			case 3://exit
				keepLooping = false;
				
				nopick = true;
			break;
			default:
			std::cout << "Invalid input, please use the available options\n";
			
			
			
		}
		//this is for printing the results
		//should only appear if the user 
		//picked an option
		if(!nopick){
			printResults(tp);
		}
	}
}



void printUniqueWords(std::set<std::string> &setinput){
	
	std::cout << "\n\nThere are " << setinput.size() << " unique words in the text";
	
}

void printWordFrequency(const std::map<std::string, int> mapinput){
	int maxsize = mapinput.size();
	std::cout << "Out of " << maxsize << " words:\n";
	int count = 1;
	for(auto value : mapinput){
		std::cout << std::setw(20) << std::left << value.first << ":" << std::right << std::setw(4) << value.second << "| ";
		
		//std::cout << std::setprecision(2) << " making up " << (double(value.second) / maxsize) << "% of all the words";
		if(count % 4 == 0) std::cout << std::endl;
		count++;
	}
	
}
