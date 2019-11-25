#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string>
#include<iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <cstring>

#define clear() printf("\033[H\033[J") //to clear screen

using namespace std;

#include "list.h"
#include "cursor_handle.h"


    vector<pair<string, char>> list(char* str,char d) {            //function definition begin
    clear();        //clear terminal
    vector<pair<string, char>> filename;
    DIR *mydir;
    struct dirent **myfile;
    struct stat mystat;
    char buf[512];
    struct passwd *pw;
    struct group  *gr;

    int total_files = scandir(str, &myfile, NULL, alphasort);

    for(int i=0; i<total_files; i++) {


        string name = myfile[i]->d_name;
        stat(name.c_str(), &mystat);

        string strTemp(str);    //concatenate path to string
        strTemp = strTemp+"/"+name;

        cout << name<<"  ";     //filename

        cout<< mystat.st_size<<"    ";       //file size

        pw = getpwuid(mystat.st_uid);
        gr = getgrgid(mystat.st_gid);

        cout << pw->pw_name << " " << gr->gr_name << " ";   //ownername nd groupname

        char d= (S_ISDIR(mystat.st_mode)) ? 'd' : '-';
        filename.push_back(make_pair(strTemp, d));

        char ur= (mystat.st_mode & S_IRUSR) ? 'r' : '-';
        char  uw= (mystat.st_mode & S_IWUSR) ? 'w' : '-';
        char ue = (mystat.st_mode & S_IXUSR) ? 'x' : '-';

        char gr= (mystat.st_mode & S_IRGRP) ? 'r' : '-';
        char gw= (mystat.st_mode & S_IWGRP) ? 'w' : '-';
        char ge = (mystat.st_mode & S_IXGRP) ? 'x' : '-';

        char oread = (mystat.st_mode & S_IROTH) ? 'r' : '-';
        char ow = (mystat.st_mode & S_IWOTH) ? 'w' : '-';
        char oe = (mystat.st_mode & S_IXOTH) ? 'x' : '-';
        
        cout << d;                          //print whether it is directory or file
        cout << ur << uw << ue;
        cout << gr << gw << ge;
        cout << oread << ow << oe<<"   ";

        cout << ctime(&mystat.st_mtime);    //print time
    }
    return filename;   
}
