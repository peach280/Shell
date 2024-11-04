#include "all.h"
void sig_handler(int signum)
{
    exit(EXIT_SUCCESS);
}
int main()
{
    char *inp;
    memset(bg,-1,sizeof(bg));
    char *host;
    char *curdir = (char*)malloc(sizeof(char));
    char* curr = (char*)malloc(250*sizeof(char));
    int len = readlink("/proc/self/exe",curr,250);
    if(len<0)
    {
        getcwd(home,250);
    } 
    else
    {
        int i;
        for (i = len; curr[i] != '/'; i--)
        {
            curr[i]='\0';
        }
        curr[i]='\0';
        strcpy(home,curr);
        char temp[26];
        strcpy(temp,"cd ~");
        char **args;
        args = tokenize(temp,DELIM);
        execute(args);
        free(args);
    }
    int f=1;
    do
    {
        signal(SIGINT,sig_handler);
        struct passwd *pwd;
        char* user;
        pwd = getpwuid((getuid()));
        if(pwd!=NULL)
        {
            user=pwd->pw_name;
        }
        gethostname(host,300);
        getcwd(curdir,300);
        printf(cyan "<%s@%s:%s>" reset ,user,host,process_dir(curdir));
        inp=get_input();
        char **commands = tokenize(inp,";");
        for (int i = 0; commands[i] != NULL && f; i++)
        {
            char **args = tokenize(inp,DELIM);
            f=execute(args);
            free(args);
        }
        free(inp);
        free(commands);
    } while (f);
    return 0;
}