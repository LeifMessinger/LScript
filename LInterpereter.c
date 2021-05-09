//In C, instead of cin and cout, you got stdin and stdout (And stderr)
//They are pointers to files. They are also known as FILE structs
//You just gotta read a bunch of documentation to find out how to work with files

//We are going to do a character-by-character interpereter.
//It basically only helps me, because all the interpereter knows is what is in the stack before it crashes

//Anyways, before I begin, I want to decide a couple things

//1. Do I use stdin always, or do I try to have a FILE parameter on all my functions?
//2. Is the stack just a character buffer, or do I make some sort of custom linked list of character buffers or whatever
//3. How the hell am I supposed to make a map in C? I don't want to do associated arrays.
//4. How is this call stack supposed to work. With recursion?

//Decided things
//The interpereter has 3 main eval stages
//1. The character loop
//The character loop basically only concerns the parentheses balancing and when it is time to compile.
//Once it compiles, it can send the whole string buffer to the second level compier
//2. Sentence breakdown
//Sentences get their words looked up and thrown onto a stack.
//This can be a single stage and the word stage can cover the rest.
//3. Word evaluation
//Let each word run an eval function on the word stack.
//This can be still be done with recursion, or an actual stack, or both.
//After a single pass, the word stack should have the remnants of the evaluation.
//Those can get pushed onto the front or back of the sentence it belongs to.
//I'm thinking, for simplicity, that remnant stack gets converted back into a string, like how it was before the sentence stage.
//Or it can get pushed into the next word loop as is.

//Todo: Make a basic fgetc loop
#include <stdio.h>	//FILE, fgetc, fputc, printf, scanf, stdin, stdout, stderr
#include <stdlib.h> 	//calloc
void L_evalIO(FILE* input, FILE* output){
	char* buffer = calloc(sizeof(char),2047);	//Reserve a bunch of space
	//Calloc makes it so I don't have to put that null character on the end
	for(int c = fgetc(input), i = 0; c != EOF; c = fgetc(input), ++i){	//First loop buffers characters into a string
		buffer[i] = (char)c;
	}
	printf("%s",buffer);
}
