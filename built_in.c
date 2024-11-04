#include "all.h"
int cd(char ** args)
{
    if(args[1]==NULL) 
    {
        chdir(home);
    }
    else
    {
        if(!strcmp(args[1],"~")) chdir(home);
        else
        {
            if(chdir(args[1])) perror("err");
        }
    }
    return 1;
}
int pwd()
{
    char* buff = (char*)malloc(200*sizeof(char));
    getcwd(buff,200);
    printf("%s\n",buff);
    free(buff);
    return 1;
}
int echo(char** args)
{
    for (int i = 1; args[i] != NULL; i++)
    {
        printf("%s ",args[i]);
    }
    printf("\n");
    return 1;
}
int execute(char **args)
{
    if(args[0]==NULL)
    {
        return 1;
    }
    if(!strcmp(args[0],"cd"))
    {
        return cd(args);
    }
    if(!strcmp(args[0],"pwd"))
    {
        return pwd();
    }
    if(!strcmp(args[0],"echo"))
    {
        return echo(args);
    }
    else if (!strcmp("pinfo", args[0])) 
    {
        return pinfo(args);
    } 
    else if (!strcmp("ls", args[0]) || !strcmp("l", args[0])) 
    {
        return ls(args);
    } 
    else if (!strcmp("exit", args[0]) || !strcmp("EXIT", args[0])) 
    {
        return 0;
    }
    return proc_launch(args);

}