#include "all.h"
void ls_util(struct stat info,struct dirent* name)
{
    struct passwd *pw = getpwuid(info.st_uid);
    char date[150];
    strftime(date,100,"%h %d %H %M",localtime(&(info.st_ctime)));
    struct group *grp = getgrgid(info.st_gid);
    int d = S_ISDIR(info.st_mode);
    printf((d) ? "d" : "-");
    printf((info.st_mode & S_IRUSR) ? "r":"-");
    printf((info.st_mode & S_IWUSR) ? "w":"-");
    printf((info.st_mode & S_IXUSR) ? "x":"-");
    printf((info.st_mode & S_IRGRP) ? "r":"-");
    printf((info.st_mode & S_IWGRP) ? "w":"-");
    printf((info.st_mode & S_IXGRP) ? "x":"-");
    printf((info.st_mode & S_IROTH) ? "r":"-");
    printf((info.st_mode & S_IWOTH) ? "w":"-");
    printf((info.st_mode & S_IXOTH) ? "x":"-");
    printf(" %d",(int)info.st_nlink);
    printf(" %s",pw->pw_name);
    printf(" %s",grp->gr_name);
    printf(" %8d",(int)info.st_size);
    printf(" %s",date);
    if(d) printf(blue);
    printf(" %s",name->d_name);
    printf(reset);
    printf("\n");
}
int ls(char **args)
{
    int l=0,a=0,dir_cnt=0;
    DIR* dir;
    struct dirent *name;
    struct stat info;
    for (int i = 1; args[i] != NULL; i++)
    {
        if(!strcmp(args[i],"-a")) a=1;
        else if(!strcmp(args[i],"-l")) l=1;
        else if(!strcmp(args[i],"-la") || !strcmp(args[i],"-al")) 
        {
            a=1;
            l=1;
        }
        else if(strcmp(" ",args[i])) dir_cnt++;
    }
    int single=0;
    if(!dir_cnt)
    {
        single=1;
        dir_cnt=1;
    }
    if(!strcmp(args[0],"l")) a=l=1;
    char** dir_names = (char**)malloc(dir_cnt*sizeof(char*));
    int j=0;
    for (int i = 1; args[i]!=NULL; i++)
    {
        if(strcmp(args[i],"-l") && strcmp(args[i],"-la") && strcmp(args[i],"-al") && strcmp(args[i],"-a"))
        dir_names[j++]=args[i];
    }
    if(single)
    {
        dir_names[0]=".";
    }
    int i=0;
    while(i<dir_cnt)
    {
        dir=opendir(dir_names[i]);
        if(dir==NULL)
        {
            fprintf(stderr, "%s No such file or directory\n",dir_names[i++]);
            continue;
        }
        printf(green "%s\n" reset,dir_names[i]);
        while((name = readdir(dir)) != NULL)
        {
            char buff[600];
            sprintf(buff,"%s/%s",dir_names[i],name->d_name);
            stat(buff,&info);
            if(!l && a)
            {
                if(S_ISDIR(info.st_mode)) printf(blue);
                printf("%s\n" reset,name->d_name);
            }
            else if(a && l)
            {
                ls_util(info,name);
            }
            else if(!a && !l)
            {
                if(name->d_name[0] !=  '.')
                {
                    if(S_ISDIR(info.st_mode)) printf(blue);
                    printf("%s\n" reset,name->d_name);
                }
            }
            else
            {
                if(name->d_name[0] != '.')
                ls_util(info,name);
            }
        }
        i++;
    }
    closedir(dir);
    return 1;
}