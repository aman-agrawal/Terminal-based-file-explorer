#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string>
#include <iostream>
#include <string>
#define maxvalue 100

#include "cwd.h"
using namespace std;
	string mycwd() {

	char cwd[maxvalue];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {

       string ans=cwd;
       return ans;
   } else {
       
		return "error";
   }
}

