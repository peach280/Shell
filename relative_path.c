#include "all.h"
char* process_dir(char* curdir)
{
    char* res=NULL;
    if(!strcmp(curdir,home))
        res="~";
    else
    {
        int h = strlen(home);
        int c = strlen(curdir);
        if(c<h)
        {
            res=curdir;
        }
        else
        {
            res=(char*)malloc(sizeof(char)*(c-h+2));
            res[0]='~';
            int i=0,j=1;
            while(curdir[i]==home[i])
            {
                i++;
            }
            while(curdir[i]!='\0')
            {
                res[j]=curdir[i];
                i++;
                j++;
            }
            res[j]='\0';
        }
    }
    return res;
}