/* $begin tinymain */
/*
 * tiny.c - A simple, iterative HTTP/1.0 Web server that uses the 
 *     GET method to serve static and dynamic content.
 */
#include "csapp.h"
#include<pthread.h>

//int flag=0;
void doit(int fd);
void read_requesthdrs(rio_t *rp);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs);
void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg);


struct ThreadArgs{
    int client_sock;
};

void *ThreadMain(void *threadargs){
    int client_sock;
    pthread_detach(pthread_self());
    client_sock = ((struct ThreadArgs *) threadargs) -> client_sock;
    doit(client_sock);
    Close(client_sock);
    free(threadargs);
    return;
}
int main(int argc, char **argv) 
{
    int listenfd, connfd, port, clientlen;
    struct sockaddr_in clientaddr;
    pthread_t threadID;
    struct ThreadArgs *threadargs;

    /* Check command line args */
    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(1);
    }
    port = atoi(argv[1]);

    listenfd = Open_listenfd(port);
    while (1) {
	    clientlen = sizeof(clientaddr);
	    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); //line:netp:tiny:accept
        threadargs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs)); 
        threadargs -> client_sock = connfd;

        pthread_create(&threadID, NULL, ThreadMain, (void *) threadargs);
    }
}


/* $end tinymain */

/*
 * doit - handle one HTTP request/response transaction
 */
/* $begin doit */
void doit(int fd) 
{
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE], arg[MAXLINE], arg1[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;
  
    /* Read request line and headers */
    Rio_readinitb(&rio, fd);
    Rio_readlineb(&rio, buf, MAXLINE);   
                        //line:netp:doit:readrequest
    sscanf(buf, "%s %s %s", method, uri, version);       //line:netp:doit:parserequest
    printf("%d",strlen(uri));
     setenv("METHOD_NAME", method, 1);

    if ((strcasecmp(method, "POST") == 0) && (strcasecmp(uri, "/cgi-bin/adder") == 0)){
        Rio_readlineb(&rio, arg, MAXLINE);
        strcpy(filename, ".");
        strcat(filename, uri);
        serve_dynamic(fd,filename,arg);                                                  //For taking arguments input
        //setenv("ARG",arg,1);
        //printf(getenv("ARG"));
    }
            
    
    
    if (strcasecmp(method, "GET") && strcasecmp(method,"POST")) {                     //line:netp:doit:beginrequesterr
       clienterror(fd, method, "501", "Not Implemented",
                "Tiny does not implement this method");
        return;
    }                                                                                 //line:netp:doit:endrequesterr
    read_requesthdrs(&rio);                                                           //line:netp:doit:readrequesthdrs
    
    /* Parse URI from GET request */
     if (strstr(uri,"cgi-bin") == NULL && strstr(uri, "../"))
        {
	
        clienterror(fd, uri, "403", "Forbidden","File Traversal Detected! Program ends here");     //File Traversal            
        return;
        }
    if (strstr(uri,"cgi-bin") && strstr(uri, "../"))
        {
	
        clienterror(fd, uri, "403", "Forbidden","Command Injection Detected!");                    //Commmand Injection            
        return;
        }
    
    if(strlen(uri) >= 8096)
    {   
        strncpy(arg1,"DONT DO THAT",12);

        clienterror(fd, arg1,"403", "Forbidden", "Buffer Overflow Detected!!");                  //Buffer Overflow
        //printf("Buffer Overflow Detected!");
        //exit(0);
        //flag=1;
        return;
    } 
    if (strstr(uri,"cgi-bin") || strstr(uri,".gif") || strstr(uri,".jpg") || strstr(uri,"README") || strstr(uri,".html") || strstr(uri,".ico") || uri[strlen(uri)-1] == '/')
    {
        is_static = parse_uri(uri, filename, cgiargs); 
                                               //line:netp:doit:staticcheck
        if (stat(filename, &sbuf) < 0) {                     //line:netp:doit:beginnotfound
	        clienterror(fd, filename, "404", "Not found",
		    "Tiny couldn't find this file");
	        return;
        }                                                      //line:netp:doit:endnotfound

        if (is_static) { /* Serve static content */          
	    if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) { //line:netp:doit:readable
	        clienterror(fd, filename, "403", "Forbidden",
			"Tiny couldn't read the file");
	        return;
	    }
	    serve_static(fd, filename, sbuf.st_size);        //line:netp:doit:servestatic
        }   
        else 
        { /* Serve dynamic content */
	        if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) 
            { //line:netp:doit:executable
	            clienterror(fd, filename, "403", "Forbidden",
			    "Tiny couldn't run the CGI program");
	            return;
            }
            serve_dynamic(fd, filename, cgiargs);                   //line:netp:doit:servedynamic
                                                        
        }

    }
    else{
        clienterror(fd, uri, "403", "Forbidden",
                "You are not allowed to execute this file!!");
        //flag=1;
        return;
    }
}
/* $end doit */

/*
 * read_requesthdrs - read and parse HTTP request headers
 */
/* $begin read_requesthdrs */
void read_requesthdrs(rio_t *rp) 
{
    char buf[MAXLINE];

    Rio_readlineb(rp, buf, MAXLINE);
    while(strcmp(buf, "\r\n")) {
                                   //line:netp:readhdrs:checkterm
	Rio_readlineb(rp, buf, MAXLINE);
	printf("%s", buf);
    }
    return;
}
/* $end read_requesthdrs */

/*
 * parse_uri - parse URI into filename and CGI args
 *             return 0 if dynamic content, 1 if static
 */
/* $begin parse_uri */
int parse_uri(char *uri, char *filename, char *cgiargs) 
{
    char *ptr;

    if (!strstr(uri, "cgi-bin")) {  
                                                /* Static content */ //line:netp:parseuri:isstatic
	strcpy(cgiargs, "");                             //line:netp:parseuri:clearcgi
	strcpy(filename, ".");                           //line:netp:parseuri:beginconvert1
	strcat(filename, uri);
	
	                           			                //line:netp:parseuri:endconvert1
	if (uri[strlen(uri)-1] == '/') 
        strcat(filename, "home.html");                   //line:netp:parseuri:appenddefault
        return 1;                                               //line:netp:parseuri:slashcheck


    }
    else {  /* Dynamic content */                        //line:netp:parseuri:isdynamic
	ptr = index(uri, '?');                           //line:netp:parseuri:beginextract
	if (ptr) {
	    strcpy(cgiargs, ptr+1);
	    *ptr = '\0';
	}
	else 
	    strcpy(cgiargs, "");                         //line:netp:parseuri:endextract
	strcpy(filename, ".");                           //line:netp:parseuri:beginconvert2
	strcat(filename, uri);                           //line:netp:parseuri:endconvert2
	return 0;
    }
}
/* $end parse_uri */

/*
 * serve_static - copy a file back to the client 
 */
/* $begin serve_static */
void serve_static(int fd, char *filename, int filesize) 
{
    int srcfd;
    char *srcp, filetype[MAXLINE], buf[MAXBUF];
 
    /* Send response headers to client */
    get_filetype(filename, filetype);       //line:netp:servestatic:getfiletype
    sprintf(buf, "HTTP/1.0 200 OK\r\n");    //line:netp:servestatic:beginserve
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
    Rio_writen(fd, buf, strlen(buf));       //line:netp:servestatic:endserve

    /* Send response body to client */
    srcfd = Open(filename, O_RDONLY, 0);    //line:netp:servestatic:open
    srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);//line:netp:servestatic:mmap
    Close(srcfd);                           //line:netp:servestatic:close
    Rio_writen(fd, srcp, filesize);         //line:netp:servestatic:write
    Munmap(srcp, filesize);                 //line:netp:servestatic:munmap
}

/*
 * get_filetype - derive file type from file name
 */
void get_filetype(char *filename, char *filetype) 
{
    if (strstr(filename, ".html"))
	strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
	strcpy(filetype, "image/gif");
    else if (strstr(filename, ".jpg"))
	strcpy(filetype, "image/jpeg");
    else
	strcpy(filetype, "text/plain");
}  
/* $end serve_static */

/*
 * serve_dynamic - run a CGI program on behalf of the client
 */
/* $begin serve_dynamic */
void serve_dynamic(int fd, char *filename, char *cgiargs) 
{
    char buf[MAXLINE], *emptylist[] = { NULL }, method[MAXLINE], uri[MAXLINE], version[MAXLINE];

    /* Return first part of HTTP response */
    sprintf(buf, "HTTP/1.0 200 OK\r\n"); 
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Server: Tiny Web Server\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sscanf(buf, "%s %s %s", method, uri, version);
           //line:netp:doit:parserequest
    //printf("%s", method);
    
  
    if (Fork() == 0) { /* child */ //line:netp:servedynamic:fork
	/* Real server would set all CGI vars here */
    
	setenv("QUERY_STRING", cgiargs, 1); //line:netp:servedynamic:setenv
    //setenv("METHOD_NAME", method, 1);
	Dup2(fd, STDOUT_FILENO);         /* Redirect stdout to client */ //line:netp:servedynamic:dup2
	Execve(filename, emptylist, environ); /* Run CGI program */ //line:netp:servedynamic:execve
    }
    Wait(NULL); /* Parent waits for and reaps child */ //line:netp:servedynamic:wait
}
/* $end serve_dynamic */

/*
 * clienterror - returns an error message to the client
 */
/* $begin clienterror */
void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg) 
{
    char buf[MAXLINE], body[MAXBUF];

    /* Build the HTTP response body */
    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s<h1 style=\"color:red;\">%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p><h1>%s:\r\n", body, longmsg);
    sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

    /* Print the HTTP response */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
    
    
}
/* $end clienterror */
