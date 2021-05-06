#include<iostream>
#include"LInterpereter.h"
#include<regex>
//First we define our language Words
class QuitWord : public L::Word{
	virtual Word* evaluate(L::Instance& instance){
		std::cout << "QUIT";
		return nullptr;
	}
};
//Next Word is print

int main(){	//Pipe in a .l file
	L::Instance instance;
	instance.dic.emplace("quit", new QuitWord());

	std::regex wordGetter("\\w+");
	for(std::string line; std::getline(std::cin,line);){
		//Todo: split lines by either periods or semicolons
		std::smatch matcher;
		while(std::regex_search(line,matcher,wordGetter)){	//for each word token
			for(std::string word : matcher){
				std::cout << word << " ";	//Prints each word once
			}
			std::cout << std::endl;
			line = matcher.suffix().str();	//Apparently this is how you keep searching through a string
		}
	}
}