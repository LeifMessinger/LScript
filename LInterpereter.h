#include<iostream>
#include<vector>
#include<map>
namespace L{
	typedef std::vector<std::string> Sentence;	//Used by the compiler, but also a common phrase I use to describe procedures
	class Word;	//Forward declarations
	class Dictionary;
	class Instance;
	class Word{
		public:
			virtual Word* evaluate(Instance& instance);
			virtual ~Word(){}	//Virtual classes should have virtual destructors
	};
	class Dictionary : public std::map<std::string,Word*>{
		public:
			bool deleteAfterwards = false;
			~Dictionary();
	};
	class Instance{
		private:
			//init()
		public:
			Instance();
			//Instance(std::istream&); Just call init, then call readFrom
			Dictionary dic;	//Gets cleared and deleted when dic gets destroyed. Holy cow, that sounds wrong
			Sentence sentence;
			size_t index = 0;
			
			//readFrom(std::istream);	Do this later, I'm tired
			void pushWord(std::string word); 	//Pushes a single word onto the stack
			//In theory, the entire program should be able to run off this one function
	};
}