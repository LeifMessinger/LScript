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
			void init();
		public:
			//Variables
			Dictionary dic;	//Gets cleared and deleted when dic gets destroyed. Holy cow, that sounds wrong
			Sentence sentence;
			size_t index = 0;

			//Constructors
			Instance();
			Instance(std::istream&);

			//Methods
			void stdInit();	//Makes words like "print" and "quit"
			void readFrom(std::istream&);
			void pushWord(std::string word); 	//Pushes a single word onto the stack
			//In theory, the entire program should be able to run off this one function
	};
}
