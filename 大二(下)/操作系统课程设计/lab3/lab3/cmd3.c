#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int i;
    char str[1024]={};
    printf("argc: %d\n", argc);
    for(i = 1; i < argc; i++)
    {
	strcat(str, argv[i]); 
    }
    printf("result: %s\n", str);
    return 0;
}
