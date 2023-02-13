#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LENGTH 80

bool is_empty(char str[]) {
return str[0] == '\0';
}

int main(int argc, char const *argv[])
{
//two file descriptors for reading and writing
int fd1, fd2;
//first named pipe
char * receiveM2 = "/tmp/myfifo3"; 
mkfifo(receiveM2, 0666); 
//second named pipe 
char * sendMx = "/tmp/myfifo1";
mkfifo(sendMx, 0666);
//Horizontal speed
float z = 0.0;
//strings for reading and writing
char str1[MAX_LENGTH];
char str2[MAX_LENGTH] = "vz"; 

while (1) {
    //opening the first named pipe in file descriptor fd1
    fd1 = open(receiveM2, O_RDONLY);
    //reading
    int bytes_read = read(fd1, str1, MAX_LENGTH);
    //closing file descriptor
    close(fd1);
    /*check if data is read and put str1 into str2 
    to increase the velocity till we receive the next input*/
    if (bytes_read > 0) {
        strcpy(str2, str1);
    }

    //if Vx+ is pressed then increase the velocity otherwise we have to decrease the velocity
    if (strcmp(str2, "Vz++") == 0) {
        z += 0.1;
        printf("Vertical speed is %f\n", z);
	//openning the second named pipe to write
        fd2 = open(sendMx, O_WRONLY);
        write(fd2, str2, strlen(str2) + 1);
        close(fd2);
    } 
    //if Vx- is pressed the velocity should be decreased
    else if (strcmp(str2, "Vz--") == 0 && z > 0) {
        z -= 0.1;
        printf("Vertical speed is %f\n", z);
	//openning the second named pipe to write
        fd2 = open(sendMx, O_WRONLY);
        write(fd2, str2, strlen(str2) + 1);
        close(fd2);
    }
    //wait for one second 
    sleep(1);
}       

return 0;




}

