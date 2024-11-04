#include "all.h"
int pinfo(char** argv)
{
   
    char proc[400],info[500],exec[500],sym[500];
    strcpy(proc,"/proc/");
    strcat(proc, (argv[1]) ? argv[1]:"self");
    strcpy(info,proc);
    strcat(info,"/stat");
    int file_desc = open(info,O_RDONLY); 
    if(file_desc==-1)
    {
        perror("err");
        return 1;
    }
    char buff[3000],**res;
    read(file_desc,buff,3000);
    res=tokenize(buff,DELIM);
    close(file_desc);
    printf("PID-----%s\n",res[0]);
    printf("Process Status-----%s\n",res[2]);
    printf("Virtual Memory-----%s\n",res[22]);
    strcpy(sym,proc);
    strcat(sym,"/exe");
    int length = readlink(sym,exec,500); 
    if(length<0) 
    {
        strcpy(exec,"Invalid link\n");
    }
    exec[length]='\0';
    printf("Executable Path----%s\n",process_dir(exec));
    free(res);
    return 1;

}