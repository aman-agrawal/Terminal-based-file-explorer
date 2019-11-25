#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include<iostream>
#include <vector>
#include<string>
#include<stack>
#include<termios.h>
#include<string.h>
#include<fstream>

// include all header files for user defined functions
#include "list.h"
#include "cursor_handle.h"
#include"keyboard.h"
#include"pathtrim.h"
#define maxpath 10000

string mycwd();
void copyfile(string,string);
void createfile(string,string);
void createdir(string,string);
void renamefile(string,string);
void movefile(string,string);
int deletefile(string);
int deletedir(string);
void go_to(string);

//


using namespace std;
#define clear2() printf("\033[H\033[J") //to clear screen

string sonu=".";

int x=1,y=1;
vector<pair<string, char>> filename;

string mycwd() {

    char cwd[1000];
   if (getcwd(cwd, sizeof(cwd)) != NULL)
   {
        string ans=cwd;
       return ans;
   }
   else
    return "error";
}



void copyfile(string a,string b){       //copy files

    ifstream f1;
    f1.open(a);

    if(!f1){
        cout<<"error in read file";
        return;
    }
    ofstream f2;
    f2.open(b);


    if(!f2){
        cout<<"error";
        return;
    }

    char line[80];

    while(f1.good()) {
        f1.getline(line, 80);
        f2 << line;
        f2 << endl;
    }
    f1.close();
    f2.close();
}

void createfile(string a,string b)   //create file
{
    string name;
    string x;
    if(b==".")
        x=sonu+"/"+a;
    else
        x=sonu+"/"+b+"/"+a;

    ofstream f(x);
    f.close();
    cout << "file Created successfully";

}

void createdir(string a,string b)   //create file
{
    string name;
    string x;
    if(b==".")
        x=sonu+"/"+a;
    else
        x=sonu+"/"+b+"/"+a;
    int y= mkdir(x.c_str(),0777);
    if(y==-1)
        cout<<"error, directory not created";
    else
        cout << "directory Created successfully";
}


void renamefile(string a,string b)      //rename file
{
    string a1=sonu+"/"+a;
    string b1=sonu+"/"+b;
    int result= (!rename(a1.c_str(),b1.c_str()))  || (!rename(a.c_str(),b.c_str())) ; //converting string into const char*
    if (result == 1)
         cout<<"File successfully renamed";
    else
        cout<<"wrong input";
}

void movefile(string a,string b)      //rename file
{
    copyfile(a,b);
    deletefile(a);
}

int deletefile(string a)      //delete file
{
    string soni=sonu+"/"+a;
    int result= (!remove(a.c_str())) || (!remove(soni.c_str()));
    return result;
}

int deletedir(string dirpath)
{
    DIR *dir;
    struct dirent *data;
    char path[maxpath];

    const char *dirname=dirpath.c_str();

    dir = opendir(dirname);
    if (dir == NULL)
        return 0;   //wrong input

    while ((data = readdir(dir)) != NULL) {
        if (strcmp(data->d_name, ".") && strcmp(data->d_name, "..")) {
            snprintf(path, (size_t) maxpath, "%s/%s", dirname, data->d_name);
            if (data->d_type == DT_DIR) {
                char* path1= (char*)path;      //converting const char* into char*
                string dirpath1(path1);    //converting char* into string
                deletedir(dirpath1);
            }
            remove(path);
        }
    }
    remove(dirname) ; 
    closedir(dir);
    return 1;
}

void go_to(string a)
{
    list((char*)a.c_str(),1); 
        x=1;y=1;
    mov(x,y);       
}

int main(int argc, char* argv[])
{
	clear2();		//to clear terminal
	string hmd=mycwd();

	stack<string>l;
	stack<string>r;
	l.push(string(argv[1]));
	while(r.empty()!=1)
    			{r.pop();}

	filename = list(argv[1],1);	//to print ls 
    x=1;y=1;
    mov(x,y);
    off_keyboard();
    while(1) {
    	int i = cursor_handle(x, y);
    if(i==1)
    {
		//enter key is tapped

    	//f status
    	if(filename[x-1].second != 'd')
    	{
			system(("xdg-open " + filename[x-1].first).c_str());
    	}
		
    
    	//d status
    	else
    	{
            sonu=sonu+"/"+filename[x-1].first;

    	const char *ye = filename[x-1].first.c_str();
    	char* z= (char*)ye; 		//converting const char* into char*
    	string largepath(z);	//converting char* into string

    	int len=largepath.size();
    	if(largepath[len-1]=='.' && largepath[len-2]=='.')
    	{
    		if(largepath!=hmd)
    		{
    			string trimpath=trim1(largepath);
    			char *trimstring = (char*)trimpath.c_str();

    			l.push(trimpath);	///////push into l stack
    			while(r.empty()!=1)
    			{r.pop();}
    			filename= list(trimstring, filename[x-1].second);
    		}
    		else
    		{
    			// when .. is pressed and we r in home directory
    			filename = list(argv[1],1);	//to print ls

    		}
            x=1;y=1;
            mov(x,y);

    	}
    	else
    	{	
    		l.push(largepath);	///////push into l stack
    		while(r.empty()!=1)
    			{r.pop();}
    		filename=list(z, filename[x-1].second);	//refer line 67 for z
                x=1;y=1;
            mov(x,y);
    	}
    	}
    		
    	
    }

    if(i==2)
    {
    	//home key is tapped
    	filename = list(argv[1], filename[x-1].second);	//to print home directory 	
        x=1;y=1;
            mov(x,y);
    }

   
    if(i==3)
    {
    	//left key is pressed
    	if(l.empty()==0)
    	{string pl=l.top();
    	l.pop();
    	r.push(pl);
    	string pll=l.top();
    	const char *o1 = pll.c_str();
    	char* o11= (char*)o1;
    	filename=list(o11, filename[x-1].second);
        x=1;y=1;
            mov(x,y);
    	}

    }
   
    if(i==4)
    {
    	//right key is pressed
    	if(r.empty()==0)
    	{string pr=r.top();
    	const char *o2 = pr.c_str();
    	char* o22= (char*)o2;

    	r.pop();
    	l.push(pr);
    	filename=list(o22, filename[x-1].second);
        x=1;y=1;
        mov(x,y);
    	}
    }

    if(i==5)
    {	//backspace key is pressed
    	const char *y4 = filename[x-1].first.c_str();
    	char* z2= (char*)y4; 		//converting const char* into char*
    	string originalpath(z2);	//converting char* into string
    	string parentpath=originalpath.substr(0, originalpath.find_last_of("\\/"));
    	parentpath=originalpath.substr(0, parentpath.find_last_of("\\/"));

    	const char *o3 = parentpath.c_str();

    	char* parentpointer= (char*)o3;
    	filename = list(parentpointer, filename[x-1].second);
        x=1;y=1;
            mov(x,y);
    }

    if(i==6)
    {
    	//colon is pressed

    	on_keyboard();
        x=28,y=1;
    	mov(x,y);
    	printf("\033[27;1H");
    	cout<<"*******************************************"<<endl<<"enter command : ";
        vector<string> v;
            string s1 ;
            getline(cin,s1);
            auto i = s1.begin() ;
            string::iterator start = s1.begin() ;

            if(s1[0]==27)
                {
                    //escape is pressed
                     x=1,y=1;
                     mov(x,y);
                    printf("\033[27;1H");
                    cout<<"                                                           "<<endl;
                    cout<<"                                                           "<<endl;
                    cout<<"                                                           ";
                }  
        else{

        while(i!= s1.end())
        {
            if(*i == ' ')
            {
                string s2(start, i) ;
                v.push_back(s2) ;
                start = ++i ;
            }
            else 
                i++ ;
        }
        string s2(start,i) ;
        v.push_back(s2) ;
        if(v[0]=="copy")
        {
            int vectorsize1=v.size();
            int vectorsize2=vectorsize1-2;
            int i=1;
            while(vectorsize2--)
            {   copyfile(sonu+"/"+v[i],v[vectorsize1-1]+"/"+v[i]);
                i++;
            }
            cout << "all file(s) Copied done successfully";
        }
        else if(v[0]=="create_file")
        {
            createfile(v[1],v[2]);
        }
        else if(v[0]=="create_dir")
        {
            createdir(v[1],v[2]);
        }
        else if(v[0]=="move")
        {
            int vectorsize1=v.size();
            int vectorsize2=vectorsize1-2;
            int i=1;
            while(vectorsize2--)
            {   movefile(v[i],v[vectorsize1-1]+v[i]);
                i++;
            }
            cout << "all file(s) moved successfully";
        }
        else if(v[0]=="rename")
        {
            renamefile(v[1],v[2]);
        }
        else if(v[0]=="delete_file")
        {
            int result=deletefile(v[1]);
            if (result == 1)
                cout<<"File successfully deleted";
            else
                cout<<"wrong input";
        }
        else if(v[0]=="delete_dir")
        {
            int result=deletedir(v[1]);
            if(result==0)
                cout<<"wrong input";
            else
                cout<<"directory successfully deleted";
        }
        else if(v[0]=="goto")
        {
            go_to(v[1]);
        }
      }
    	
      }  
    }	
    
}