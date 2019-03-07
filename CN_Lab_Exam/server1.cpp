// Server side C/C++ program to demonstrate Socket programming 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<time.h> 
#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include <unistd.h> 
#include<bits/stdc++.h>

using namespace std;

#define PORT 8081

// void func(int* new_socket)
// {
// 	int valread;
// 	char buffer[1024] = {0};
// 	char chunk[1024] = {0};
// 	char f[10000];
// 	memset(f,'\0',sizeof(f));
// 	char *hello = "Hello from Server";
// 	mydir = opendir(".");
// 	while((myfile = readdir(mydir)) != NULL)
//     {
//        //strcpy(t,myfile->d_name);
//        strcat(f,myfile->d_name);
//        char s[] = "  ";
//        strcat(f,s);
//         //printf(" %s\n", myfile->d_name);
//     }
//     closedir(mydir);
// 	send(*new_socket , f , strlen(f) , 0 ); 
//    // printf("Hello\n");
//    // fflush(stdout);
// 	valread = read( *new_socket , buffer, 1024); 
// 	printf("%s\n",buffer );
// 	buffer[valread]='\0';
// 	sleep(1); 
	
// 	//fflush(stdout);
// 	printf("Hello message sent\n"); 

//     FILE *fptr; 

// 	char filename[100]; 
// 	char c;
// 	strcpy(filename,buffer); 

// 	//printf("Enter the filename to open \n"); 
// 	//scanf("%s", filename); 

// 	// Open file 
// 	fptr = fopen(filename, "r"); 
// 	if (fptr == NULL) 
// 	{ 
// 		printf("Cannot open file \n"); 
// 		exit(0); 
// 	} 

// 	// Read contents from file
// 	int len,n,m; 
// 	 do{
// 	 	//chunk[len] = '\0';
// 	 	n = fread(chunk, 1, sizeof(chunk), fptr);
// 	 	if(n){
// 	 	m =send(*new_socket , chunk, sizeof(chunk) , 0 );
// 	 	}
// 	 	else{
// 	 	m = 0;
// 	 	}
// 	 	printf("%s\n",chunk);
        	
//         	//sleep(2);
// 	}while(n>0 && n==m);

// 	fclose(fptr); 

// 	return;

// }
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
int partition (vector<int> &arr, int low, int high) 
{ 
    int pivot = arr[high];  
    int i = (low - 1);  
  
    for (int j = low; j <= high- 1; j++) 
    { 
       
        if (arr[j] <= pivot) 
        { 
            i++;    
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
  

void quicksort(vector<int> &arr, int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(arr, low, high); 
  
        quicksort(arr, low, pi - 1); 
        quicksort(arr, pi + 1, high); 
    } 
} 


int main(int argc, char const *argv[]) 
{ 
		int server_fd, new_socket, valread; 
		struct sockaddr_in address; 
		int opt = 1; 
		int addrlen = sizeof(address); 
		char buffer[1024] = {0}; 
		char *hello = "Hello from server"; 
		
		// Creating socket file descriptor 
		if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
		{ 
			perror("socket failed"); 
			exit(EXIT_FAILURE); 
		} 
		
		// Forcefully attaching socket to the port 8080 
		if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
													&opt, sizeof(opt))) 
		{ 
			perror("setsockopt"); 
			exit(EXIT_FAILURE); 
		} 
		address.sin_family = AF_INET; 
		address.sin_addr.s_addr = INADDR_ANY; 
		address.sin_port = htons( PORT ); 
		
		// Forcefully attaching socket to the port 8080 
		if (bind(server_fd, (struct sockaddr *)&address, 
									sizeof(address))<0) 
		{ 
			perror("bind failed"); 
			exit(EXIT_FAILURE); 
		}
		if (listen(server_fd, 3) < 0) 
		{ 
			perror("listen"); 
			exit(EXIT_FAILURE); 
		} 
		
		int test = (new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0;

		if (test) 
		{ 
			perror("accept"); 
			exit(EXIT_FAILURE); 
		} 
		else 
		{
			int ACK;
			if(recv(new_socket,&ACK, sizeof(int),0)<0){
				perror("Client not responding");
				return 0;
			}else{
				if(send(new_socket,&ACK,sizeof(ACK),0)<0){
					perror("Crash");
				}else{
					cout<<"ACK send"<<endl;
				}
			}
            char buffer[1000];
            int recv;
			if((recv = read(new_socket,buffer,1000)) != 0){
                // send ACK
                char ACK[] = "Data recieved";
                //send(new_socket, ACK, sizeof(ACK), 0);
            }else{
                perror("Data not send");
                return -1;
            }

            char* token = strtok(buffer, " "); 
            // Keep printing tokens while one of the 
            // delimiters present in str[].
            vector<int> arr; 
            while (token != NULL) { 
                arr.push_back(atoi(token));
                token = strtok(NULL, " "); 
            } 

            // Quick sort
			
            quicksort(arr, 0, arr.size()-1);
			for(int i = 0;i<arr.size();i++){
				cout<<arr[i]<<endl;
			}
            int m = arr.size();
            int i = 0;
            while(m--){
				send(new_socket, &arr[i], sizeof(int), 0);
				i++;
            }

            
			//pthread_join(thread_id, NULL); 
		}
		return 0; 
	}

	
