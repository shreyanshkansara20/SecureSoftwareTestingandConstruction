/*
 * adder.c - a minimal CGI program that adds two numbers together
 */
/* $begin adder */
#include "csapp.h"
#include<limits.h>


int main(void) {
    char *buf, *p, *method_name;
    char method[MAXLINE], uri[MAXLINE], version[MAXLINE], arg[MAXLINE];
    char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
    int n1=0, n2=0;

   // if (strcasecmp(getenv("METHOD_NAME"),"GET") == 0){   
 if ((buf = getenv("QUERY_STRING")) != NULL) 
    {   
	    p = strchr(buf, '&');
	    *p = '\0';
        strcpy(arg1, buf);
	    strcpy(arg2, p+1);
	    n1 = atoi(arg1);
	    n2 = atoi(arg2);
    }


   // }
  //  else if (strcasecmp(getenv("METHOD_NAME"),"POST") == 0)
    // {
    //     sscanf(getenv("ARG"), "%s", arg);
    //     p=strchr(arg,'&');
    //     *p='\0';
    //     strcpy(arg1,arg);
    //     strcpy(arg2,p+1);
    //     n1=atoi(arg1);
    //     n2=atoi(arg2);
    //     printf("n1=%d&n2=%d\n\n",n1,n2);
        
    // }

    /* Make the response body */
   
    sprintf(content, "Welcome to add.com: ");
    sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
    int sum =(n1/2) + (n2/2);

    if((n1>0 && n2>0 && sum>=(INT_MAX/2)) || (n2<0 && n1<0 && sum<=(INT_MIN/2))){
            printf("Integer Overflow Detected!!!");
            exit(0);
    }
    else
    {
    sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>", 
	    content, n1, n2, n1 + n2);
    }
    sprintf(content, "%sThanks for visiting!\r\n", content);

    printf("Content-length: %d\r\n", (int)strlen(content));
    
    
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);
    exit(0);
}
/* $end adder */
