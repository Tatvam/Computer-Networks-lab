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


int sockfd;  
struct addrinfo hints, *servinfo;
int rv;
int main(int argc, char *argv[]){
    // Find IP Address of the site using DNS lookup through getaddrinfo
    // --------------------------------------------------------------------
    if(argc!=2){
        perror("Enter the hostname");
    }
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // use AF_INET6 to force IPv6
    hints.ai_socktype = SOCK_STREAM;
    
    if ((rv = getaddrinfo(argv[1], "http", &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }
    struct sockaddr_in * p = (struct sockaddr_in *)(servinfo->ai_addr);
    char str[100];
    inet_ntop(AF_INET, &(p->sin_addr), str, INET_ADDRSTRLEN);
    printf("%s",str);
    freeaddrinfo(servinfo); // all done with this structure
    // ---------------------------------------------------------------------




    
}