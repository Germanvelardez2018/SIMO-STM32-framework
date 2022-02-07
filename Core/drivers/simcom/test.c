#include "string.h"
#include "stdlib.h"
#include "stdio.h"



#define CMD_OK                  "OK\r\n"
#define LEN_CMD_OK               4
#define IS_EQUAL                 0



static int __get_equal(char* string1, char* string2)
{
    int ret = 0; 

    char buf[200];
    sprintf(buf,"comparar %s con %s \r\n",string1,string2);
    printf("%s",buf);
    ret = (  strncmp(string1,string2,strlen(string2)) == IS_EQUAL)?1:0;

    return ret;
}


int main(void)
{
    #define MSG         "ESTE ES EL MENSAJE OK\r\n"


    char    msg[] = MSG;

    int index = strlen(MSG);
    int ret =__get_equal( &msg[index-LEN_CMD_OK],  CMD_OK);


    if( ret == 1){
        printf("los string son iguales \r\n");

    }
    else{
        printf("los string no son iguales \r\n");
    }

    char end[]= "len 6";

    printf("%s tiene len %d \r\n",end,strlen(end));

    return 0;
}