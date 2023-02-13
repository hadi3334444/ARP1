#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    //two file descriptors for reading and writing
    int fd1,fd2; 
    //first named pipe
    char * receiveM = "/tmp/myfifo1"; 
    mkfifo(receiveM, 0666); 
    //second named pipe 
    char * send = "/tmp/myfifo5";
    mkfifo(send,0666);
    float x=0.0,z=0.0;
    char str1[80]; 
while(1)
{     
    //opening the first named pipe in file descriptor fd1
    fd1 = open(receiveM,O_RDONLY);
    
    //reading
    if(read(fd1, str1, strlen(str1))==-1)
        perror("read");
    //closing file descriptor
    close(fd1);
    //if Vx-- is received then decrease the Horizontal velocity
    if(strcmp(str1,"Vx--")==0 && x>0)
    {
        x-=0.1;
        printf("Horizontal speed is %f\n",x);
        //fd2 = open(send,O_WRONLY);
        //if(write(fd2,str1,strlen(str1)+1)==-1)
            //perror("write");
        //close(fd2);
    }
    //if Vx++ is written the Horizontal velocity should be increased
    else if(strcmp(str1,"Vx++")==0)
    {
        x+=0.1;
        printf("Horizontal speed is %f\n",x);
        //fd2 = open(send,O_WRONLY);
        //if(write(fd2,str1,strlen(str1)+1)==-1)
            //perror("write");
        //close(fd2);
    }
    //if Vz-- is received then decrease the vertical velocity
    else if(strcmp(str1,"Vz--")==0 && z>0)
    {
        z-=0.1;
        printf("Vertical speed is %f\n",z);
        //fd2 = open(send,O_WRONLY);
        //if(write(fd2,str1,strlen(str1)+1)==-1)
            //perror("write");
        //close(fd2);
    }
    //if Vz++ is received then increase the vertical velocity
    else if(strcmp(str1,"Vz++")==0)
    {
        z+=0.1;
        printf("Vertical speed is %f\n",z);
        //fd2 = open(send,O_WRONLY);
        //if(write(fd2,str1,strlen(str1)+1)==-1)
            //perror("write");
        //close(fd2);
    }
    refresh();
    sleep(1); 
}

return 0;
}
