#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<map>
namespace L{
	//enum VariableType {UNDEFINED, STRING, INT, FLOAT, STRUCT, OPERATOR};	I'm doing the unique coding style, "We'll cross that bridge when we come to it"
	class Operator;	//Forward declarations
	class Dictionary;
	class Instance;
	class Operator{
		public:
			virtual void evaluate(Instance& instance);
			virtual ~Operator(){}	//Virtual classes should have virtual destructors
	};
	class Variable : public Operator{
		public:
			std::string data;
			void evaluate(Instance& instance) override;
	};
	class Dictionary : public std::map<std::string,Operator*>{	//Stores definitions
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
			std::stack<std::Operator> operatorStack;
			std::queue<std::Operator> variableQueue;
			size_t index = 0;

			//Constructors
			Instance();
			Instance(std::string);		//Instantly starts crunching from string
			Instance(std::istream&);	//Instantly starts crunching from input stream

			//Methods
			void stdInit();	//Makes words like "print" and "quit"
			void readFrom(std::istream&);
			void pushWord(std::string word);	//Pushes a single word onto the stack
			static void evaluate(Instance&);	//I should probably change the name of this function
			//In theory, the entire program should be able to run off this one function
	};
}
