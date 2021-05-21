#include<iostream>
#include"LInterpereter.h"	//Should include vector and map
#include<regex>
void L::Operator::evaluate(Instance& instance){
	//This is a sample operator, so nothing happens
	return;
}void L::Variable::evaluate(Instance& instance){
	instance.variableQueue.push(instance);	//Queue uses push, I checked
	return;
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
        virtual void evaluate(L::Instance& instance){
                for(size_t i = 1; i < instance.wordStack.size(); i++){
			std::cout << (instance.wordStack[i]) << " ";
		}	//Print stack
		instance.wordStack.clear();
        }
};
//Next we define quit
class QuitOperator : public L::Operator{
        virtual void evaluate(L::Instance& instance){
                std::cout << "QUIT";	//Find a way to break from the program
        }
};

void L::Instance::stdInit(){
	//Emplace the quit keyword into the map
	dic.emplace("print", new PrintOperator());
	dic.emplace("quit", new QuitOperator());
}
void L::Instance::pushWord(const std::string& word){
	std::map<std::string, L::Operator*>::iterator operatorDefinition = instance.dic.find(instance.wordStack[i]);
	if(operatorDefinition != instance.dic.end()){	//Word has been defined
		operatorStack.push((*operatorDefinition));	// *operatorDefinition should still be a Operator*
	}else{
	//elseif(!isNaN(word)){
		//Word is a constant number, so you push that value onto the stack
	//}else{
		//Word wasn't defined, which means it is undefined
		//We make a variable object
		L::Operator* var = new L::Variable();
		dic.emplace(word,var);
		operatorStack.push(var);	//It will get greedy and take the first variable it sees, so either use a 
	}
	evaluate(*this);	//Attempt to eval after each word
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
        }
}
void L::Instance::evaluate(Instance& instance){	//Not really recursive
	/*for(L::Sentence::const_iterator it = wordStack.cbegin(); it != wordStack.cend(); it++){
		std::cout << (*it) << " ";
	}*/	//Print stack
	std::cout << std::endl;
	instance.wordStack.clear();
}
