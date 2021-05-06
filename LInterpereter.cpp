#include<iostream>
#include"LInterpereter.h"	//Should include vector and map
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
L::Instance::Instance(){
	dic.deleteAfterwards = true;	//We want this thing to delete the Words when the program is done.
}
void L::Instance::pushWord(std::string word){
	
}