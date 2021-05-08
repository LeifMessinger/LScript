#include<iostream>
#include"LInterpereter.h"	//Should include vector and map
#include<regex>
L::Word* L::Word::evaluate(Instance& instance){	//I said it would be elegent, I didn't say it would be fast or efficient.
	//We make sentence a reference because we want to be able to do stuff to it
	//Index is the index of the current word, so if it was at the start it would be 0
	
	//Can return nullptr, and can return an actual word function/variable/namespace that needs to be deleted
	return nullptr;
}
L::Dictionary::~Dictionary(){
	if(!deleteAfterwards) return;
	for (std::map<std::string,Word*>::iterator it = std::map<std::string,Word*>::begin(); it != std::map<std::string,Word*>::end(); it++){
		delete (it->second);
	}
}
void L::Instance::init(){
	dic.deleteAfterwards = true;	//We want this thing to delete the Words when the program is done.
}
//STD Definitions
//First we define print
class PrintWord : public L::Word{
        virtual Word* evaluate(L::Instance& instance){
                std::cout << "QUIT";
                return nullptr;
        }
};
//Next we define quit
class QuitWord : public L::Word{
        virtual Word* evaluate(L::Instance& instance){
                std::cout << "PRINT";	//Find a way to break from the program
                return nullptr;
        }
};

void L::Instance::stdInit(){
	//Emplace the quit keyword into the map
	dic.emplace("print", new PrintWord());
	dic.emplace("quit", new QuitWord());
}
L::Instance::Instance(){
	init();
}
L::Instance::Instance(std::istream& st){
	init();		//dic.deleteAfterwards = true
	stdInit();	//Include things like "print" and "quit"
	readFrom(st);
}
void L::Instance::readFrom(std::istream& st){
	std::regex wordGetter("\\S+");
        for(std::string line; std::getline(st,line);){
                //Todo: split lines by either periods or semicolons
                std::smatch matcher;
                while(std::regex_search(line,matcher,wordGetter)){      //for each word token
                        for(std::string capturingGroup : matcher){ //This thing loops through each capturing group
                                this->pushWord(capturingGroup);
                        }
                        line = matcher.suffix().str();  //Apparently this is how you keep searching through a string
                }
		//std::cout << "Evaluating:" << std::endl;
		this->evaluate();
        }
}
void L::Instance::pushWord(std::string word){
	wordStack.push_back(word);
}
void L::Instance::evaluate(){
	/*for(L::Sentence::const_iterator it = wordStack.cbegin(); it != wordStack.cend(); it++){
		std::cout << (*it) << " ";
	}*/	//Print stack
	for(size_t i = 0; i < wordStack.size(); i++){
		std::map<std::string, L::Word*>::iterator word = dic.find(wordStack[it]);
		Word* result;
		if(word != dic.end()){
			result = word->second->evaluate(*this);
		}
		if(result != nullptr){
			//The word did something and has returned a value
			//I have to consider not literally returning a word after my evaluate function
		}
	}
	std::cout << std::endl;
	wordStack.clear();
}
