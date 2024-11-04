#include "all.h"
char *get_input() 
{
    char *input = NULL;
    size_t size = 0;
    getline(&input, &size, stdin);
    return input;
}
char** tokenize(char* inp,char* delim)
{
    int mx=100;
    char **res = (char**)malloc(mx*sizeof(char*));
    if(res==NULL)
    {
        printf("err:Allocation error\n");
        return res;
    }
    char* token = strtok(inp,delim);
    int i ;
    for (i= 0; token!=NULL; i++)
    {
        if(i==mx)
        {
            mx+=100;
            char **new_res=realloc(res,mx);
            if(!new_res)
            {
                printf("err:Allocation error\n");
                free(res);
                break;
            }
        }
        res[i]=token;
        token=strtok(NULL,delim);
    }
    res[i]=NULL;
    return res;
}