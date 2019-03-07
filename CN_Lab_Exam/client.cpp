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
//#include<bits/stdc++.h>

using namespace std;
pthread_mutex_t lock;

struct threads{
    int sock_fd;
    vector<int> result;
};
typedef struct threads threads;

int n = 0;
static int count = 0;
static int l = 0;
// /pthread_mutex_t lock;


void* func(void* datas){
    ifstream ifile; 
    ifile.open("output.txt");
    int part = n/3;

    threads *data = (threads *)datas;
    int sock = data->sock_fd;
    char buffer[1000];
    string number;
    int pt = 0;
    int ACK = 1;
    while(1){
        if(send(sock,&ACK,sizeof(int),0) < 0){
            perror("ACK not send");
        }
        else{
            int ACK;
            if(recv(sock,&ACK,sizeof(ACK),0)<0){
                perror("server not responding");
                return NULL;
            }else{
                cout<<"ACK Recieved"<<endl;
                break;
            }
        }
    }
    // code for sending data to server
      //cout<<part<<endl;
    pthread_mutex_lock(&lock);
    if(count == 0){
        pt  = n/3;
        while(part && ifile >> number ){
                //cout<<number<<endl;
                char num[100];
                number+=" ";
                strcpy(num, number.c_str());
                strcat(buffer,num);
                part--;
            }
        }else if(count == 1){
            while(part && ifile >> number){
                part--;
            }
            pt  = n/3;
            part = n/3;
            while(part && ifile >> number){
                //cout<<number<<endl;
                char num[100];
                number+=" ";
                strcpy(num, number.c_str());
                strcat(buffer,num);
                part--;
            }
        }else if(count == 2){
              while(part && ifile >> number){
                part--;
            }
            part = n/3;
            while(part && ifile >> number){
                part--;
            }
            pt  = n-2*n/3;
            part = n-2*n/3;
            while(part && ifile >> number){
                //cout<<number<<endl;
                number+=" ";
                char num[100];
                strcpy(num, number.c_str());
                strcat(buffer,num);
                part--;
            }
        }
    count++;
    pthread_mutex_unlock(&lock);
   // printf("%s\n",buffer);
    send(sock, buffer, sizeof(buffer), 0);
   // cout<<"hi"<<endl;
    int rec = 0;
    int i = 0;
    data->result.resize(pt);
   // cout<<pt<<"hi"<<endl;
    while((rec = recv(sock,&data->result[i],sizeof(100),0)!=0)){
       // cout<<data.result[i]<<endl;
        i++;
    }
    l++;
    return NULL;

}

vector<int> mergeTwo(vector<int>& A, vector<int>& B) 
{ 
    // Get sizes of vectors 
    int m = A.size(); 
    int n = B.size(); 
  
    // Vector for storing Result 
    vector<int> D; 
    D.reserve(m + n); 
  
    int i = 0, j = 0; 
    while (i < m && j < n) { 
  
        if (A[i] <= B[j])  
            D.push_back(A[i++]); 
        else
            D.push_back(B[j++]); 
    } 
  
    // B has exhausted 
    while (i < m)  
        D.push_back(A[i++]); 
      
    // A has exhausted 
    while (j < n)  
        D.push_back(B[j++]);     
    
    return D; 
} 

int main(){
    //char *s = "Hello from server";
    int no;
    printf("Enter the total Numbers you want to sort");
    scanf("%d",&no);
    n = no;
    srand(time(0));

    std::ofstream out("output.txt");
	 while(no--){
	 	int num;
        num = rand()%1000;
        string s = to_string(num)+'\n';
        out << s;
        cout<<s;
	}  
    out.close();
    vector<struct sockaddr_in>  sockinfo(3);
    //vector<int> sock_fd(3);
    vector<int> port(3);
    vector<pthread_t> thread(3);
    port[0] = 8080;
    port[1] = 8081;
    port[2] = 8082;
    threads data[3];
    for(int i = 0;i<3;i++){

        if((data[i].sock_fd = socket(AF_INET,SOCK_STREAM,0)) < 0){
            perror("socket failed"); 
            exit(EXIT_FAILURE); 
        }

        sockinfo[i].sin_family = AF_INET;
        sockinfo[i].sin_port = htons(port[i]);
        inet_aton("127.0.0.1",&(sockinfo[i].sin_addr));
        memset(&(sockinfo[i].sin_zero),'\0',8);


        if(connect(data[i].sock_fd,(struct sockaddr *)&(sockinfo[i]),sizeof(sockinfo[i]))<0){
                perror("Failed");
            exit(EXIT_FAILURE);
        }
        pthread_mutex_init(&lock, NULL);
		pthread_create(&thread[i], NULL, &func, (void *)&data[i]);

    }
    for(int i = 0;i<3;i++){
        pthread_join(thread[i],NULL);
    }
    for(int i = 0;i<data[0].result.size();i++){
        cout<<data[0].result[i]<<endl;
    }
    vector<int> ans = mergeTwo(data[0].result, data[1].result);
    ans = mergeTwo(ans,data[2].result);

    cout<<"-------------------------------------------------"<<endl;
    cout<<"---------------Sorted Array-----------------------"<<endl;
    for(int i = 0;i<ans.size();i++){
        cout<<ans[i]<<endl;
    }
    
}
