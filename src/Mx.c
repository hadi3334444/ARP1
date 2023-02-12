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
    int fd1,fd2; 
    char * receiveM = "/tmp/myfifo1"; 
    mkfifo(receiveM, 0666); 
    char * send = "/tmp/myfifo5";
    mkfifo(send,0666);
    float x=0.0,z=0.0;
    char str1[80]; 
while(1)
{     
    fd1 = open(receiveM,O_RDONLY);
    
    if(read(fd1, str1, strlen(str1))==-1)
        perror("read");
    close(fd1);
    if(strcmp(str1,"Vx--")==0 && x>0)
    {
        x-=0.1;
        printf("Horizontal speed is %f\n",x);
        //fd2 = open(send,O_WRONLY);
        //if(write(fd2,str1,strlen(str1)+1)==-1)
            //perror("write");
        //close(fd2);
    }
    else if(strcmp(str1,"Vx++")==0)
    {
        x+=0.1;
        printf("Horizontal speed is %f\n",x);
        //fd2 = open(send,O_WRONLY);
        //if(write(fd2,str1,strlen(str1)+1)==-1)
            //perror("write");
        //close(fd2);
    }
    else if(strcmp(str1,"Vz--")==0 && z>0)
    {
        z-=0.1;
        printf("Vertical speed is %f\n",z);
        //fd2 = open(send,O_WRONLY);
        //if(write(fd2,str1,strlen(str1)+1)==-1)
            //perror("write");
        //close(fd2);
    }
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
