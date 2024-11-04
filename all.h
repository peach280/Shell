#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#define DELIM " \t\n\r\a"
#define reset "\033[0m"
#define cyan "\033[36m"
#define blue "\033[34m"
#define red "\033[31m"
#define green "\x1b[32m"
char home[300];
int bg[150];
char *get_input();
int proc_launch(char **args);
int cd(char ** args);
int pwd();
int echo(char** args);
int pinfo(char **argv);
char *process_dir(char *curdir);
char**tokenize(char *input,char* delim);
int execute(char ** args);
int ls(char** args);