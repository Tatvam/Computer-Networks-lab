#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <sys/types.h> 
#include <string.h> 
#include <pthread.h>
#include <dirent.h>


int sock_fd;  
struct addrinfo hints, *servinfo;
int rv;
int main(int argc, char *argv[]){

    // Extacting the host name from url provided
    //---------------------------------------------------------------
    char fip[100]={0};
    int i;
    for(i = 0;i<strlen(argv[1]);i++){
        if(argv[1][i]=='/'){
            break;
        }
    }
  //  printf("%d\n",i);
   // printf("%d\n",strlen(argv[1]));
    char first[100]= {0};
    char second[100] = {0};
    if(i!=strlen(argv[1])){
        strncpy(first,argv[1],i);
        strcpy(second,argv[1]+i);
    }
    else{
        strcpy(first,argv[1]);
        sprintf(second,"/");
    }
    printf("%s\n",first);
    printf("%s\n",second);
    fflush(stdout);
    //---------------------------------------------------------------------

    // Find IP Address of the site using DNS lookup through getaddrinfo
    // --------------------------------------------------------------------
    if(argc!=2){
        perror("Enter the hostname");
    }
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // use AF_INET6 to force IPv6
    hints.ai_socktype = SOCK_STREAM;
    
    if ((rv = getaddrinfo(first, "80", &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }
    struct sockaddr_in * p = (struct sockaddr_in *)(servinfo->ai_addr);
    char str[100];
    inet_ntop(AF_INET, &(p->sin_addr), str, INET_ADDRSTRLEN);
    printf("%s\n",str);
    freeaddrinfo(servinfo); // all done with this structure
    // ---------------------------------------------------------------------

    // Connect to the web server
    //----------------------------------------------------------------------
    
    sock_fd = socket(AF_INET,servinfo->ai_socktype,servinfo->ai_protocol);
    printf("%d\n",sock_fd);
    if(connect(sock_fd,servinfo->ai_addr,servinfo->ai_addrlen)<0){
        perror("Connection Failed");
    }
    //-----------------------------------------------------------------------

    //GET Request
    //------------------------------------------------------------------------
    char header_get[1000]={0};
    sprintf(header_get,"GET %s HTTP/1.1\r\nHost: %s\r\n Content-Type: text/html \r\n",second,str);
    printf("%s\n",header_get);
    send(sock_fd,header_get,strlen(header_get),0);
     int recvl;
     char buffer[1000]={0};
    while(recvl > 0){
    recvl = recv(sock_fd,buffer,sizeof(buffer),0);
    buffer[recvl]='\0';
    printf("%s",buffer);
    }
   // -------------------------------------------------------------------------- 

   // POST Request
   //---------------------------------------------------------------------------
//    char header_post[1000]={0};
//    char *poststr = "hello=world\r\n";
//    sprintf(header_post,
//         "POST %s HTTP/1.1\r\n"
//         "HOST: %s\r\n"
//         "Content-type: application/x-www-form-urlencoded\r\n"
// 		"Content-length: %ld\r\n\r\n"
//         "Cookie"
//         "%s",second,str,strlen(poststr),poststr);

//     send(sock_fd,header_post,strlen(header_post),0);
//     bzero(buffer,1000);
//     while(recvl > 0){
//     recvl = recv(sock_fd,buffer,sizeof(buffer),0);
//     buffer[recvl]='\0';
//     printf("%s",buffer);
//     }
//     freeaddrinfo(servinfo);
}
