#include "all.h"
int bg_cnt=0;
char bg_proc_name[100][100];
void sig_int_handler(int signum)
{
    int state;
    pid_t pid = waitpid(-1,&state,WNOHANG);
    if(pid != -1)
    {
        if(!WIFSIGNALED(state))
        {
            for (int i = 0; i < bg_cnt; i++)
            {
                if(pid==bg[i])
                {
                    printf("\n[%d] + %d done\t%s\n",i+1,pid,bg_proc_name[i]);
                    bg[i]=-1;
                    bg_cnt--;
                    break;
                }
            }
            
        }
    }
}
int proc_launch(char **args)
{
    int bgs=0;
    for (int i = 0; args[i]!=NULL ; i++)
    {
        int len = strlen(args[i]);
        if(args[i][len-1]== '&')
        {
            bgs=1;
            args[i][len-1] = '\0';
            if(args[i][len-2]== ' ') args[i][len-2] = '\0';
        }
    }
    pid_t pid = fork(),wpid;
    int state;
    if(pid==-1)
    {
        perror("err");
    }
    else if(!pid)
    {
        if(execvp(args[0],args)==-1) perror("err");
        exit(EXIT_FAILURE);
    }
    else
    {
        if(!bgs)
        {
            wpid=waitpid(pid,&state,WUNTRACED);
            while(1)
            {
                if(!WIFEXITED(state) && !WIFSIGNALED(state))
                {
                    wpid=waitpid(pid,&state,WUNTRACED);
                    continue;
                }
                break;
            }
        }
        else
        {
            bg[bg_cnt]=pid;
            strcpy(bg_proc_name[bg_cnt++],args[0]);
            printf("[%d] %d\n",bg_cnt,pid);
            signal(SIGCHLD,sig_int_handler);
            bgs=0;
        }
    }
    return 1;
}