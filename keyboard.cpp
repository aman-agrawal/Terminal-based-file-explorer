#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <iostream>
#include <string>

#include"keyboard.h"
using namespace std;

struct termios initial_settings;
struct termios new_settings;

void off_keyboard()
{
tcgetattr(0,&initial_settings);
new_settings = initial_settings;
new_settings.c_lflag &= ~ICANON;
new_settings.c_lflag &= ~ECHO;
tcsetattr(0, TCSANOW, &new_settings);
}
void on_keyboard()
{
tcsetattr(0, TCSANOW, &initial_settings);
}