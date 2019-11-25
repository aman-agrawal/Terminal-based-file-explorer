#include<iostream>
#include<string>

#include"pathtrim.h"

string trim1(string largepath)
{
   int len=largepath.size(),i,countt=0,j,k=0,flag=0;
    char d2=largepath[len-2];
    char d1=largepath[len-1];

    if(d1=='.' && d2=='.')
    {
        for(i=len-1;i>=0;i--)
        {
            if(flag==1)
                break;
            if(largepath[i]=='/')
            {
                countt++;
            }
            if(countt==2)
            {
                j=i-1;
                flag=1;
                break;
            }
        }
    }
    if(countt==2)
       return largepath.substr(0,j+1);
}