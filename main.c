#include"LInterpereter.h"
#include <stdio.h>	//Already included in LInterpereter, but it's still good to have
int main(){
	L_evalIO(stdin, stdout);
	return 0;
}
