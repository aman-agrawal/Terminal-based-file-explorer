 #include<stdio.h>
#include <iostream>
#include<termios.h>
//#define cursorforward(x) printf("\033[%dC", (x))
//#define cursorbackward(x) printf("\033[%dD", (x))
//#define cursorup(y) printf("\033[%dA", (y))
//#define cursordown(y) printf("\033[%dB", (y))

//#define KEY_ESCAPE  0x001b
//#define KEY_ENTER   0x000a
//#define KEY_UP      0x0105
//#define KEY_DOWN    0x0106
//#define KEY_LEFT    0x0107
//#define KEY_RIGHT   0x0108



#include "cursor_handle.h"

void mov(int x,int y)
{
	printf("\033[%d;%dH",x,y) ;

}




int cursor_handle(int &x, int &y)
{
	printf("\033[%d;%dH",x,y) ; // going to x row y column
	char c;
	while(1)
{		c=getchar();
	if(c==65 && x>1) {
		//cursorup
		x--;
		mov(x,y);
	}

	else if(c==66) {
		//cursordown
		x++;
		mov(x,y);
	}		
		
	else if(c==68) {
		//cursorbackward
		return 3;
	}
	else if(c==67) {
		//cursorforward
		return 4;
	}
	else if(c==10) {
		//enter key is tapped
		return 1;
	}
	else if(c=='h'|| c=='H') {
		//home key is pressed
		return 2;
	}
	else if(c==127) {
		//backspace key is pressed
		return 5;
	}
	else if(c==':') {
		//colon is pressed
		return 6;
	}

	return -1;
		
}

}