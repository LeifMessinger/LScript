#include<iostream>
#include<regex>
namespace L{
	class Word{
		void operator()(){	//I said it would be elegent, I didn't say it would be fast or efficient.
			//I know this goes against everything L stands for,
			//but hopefully after this is done nobody has to do an operator overload again,
			//or at least it will be the only thing they ever do.
		}
	};
	typedef std::vector<Word*> Sentence;	//Used by the compiler, but also a common phrase I use to describe procedures
	class Type : public Word{
		//Types are variable types which also double as namespaces
	};
	class Variable : public Word{
		
	};
	class Operator : public Word{
		
	};
	class Dictionary : public std::map<std::string,Word*>{
		public:
			bool deleteAfterwards = false;
			~Dictionary(){
				if(!deleteAfterwards) return;
				for (std::map<std::string,Word*>::iterator it = std::map<std::string,Word*>::begin(); it != std::map<std::string,Word*>::end(); it++){
					delete (it->second);
				}
			}
	};
	//Next basically make a std::vector<Word> and a std::queue<Word>
}

//First we define our language Words
class QuitWord : public L::Word{
	void operator()(){
		std::cout << "QUIT";
	}
};
//Next Word is print

int main(){	//Pipe in a .l file

	L::Dictionary dic;	//Gets cleared and deleted when dic gets destroyed. Holy cow, that sounds wrong
	dic.deleteAfterwards = true;	//We want this thing to delete the Words when the program is done.
	dic.emplace("quit", new QuitWord());

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