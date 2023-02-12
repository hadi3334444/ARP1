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
int fd1, fd2;
char * receiveM1 = "/tmp/myfifo"; 
mkfifo(receiveM1, 0666); 
char * sendMx = "/tmp/myfifo1";
mkfifo(sendMx, 0666);
float x = 0.0;
char str1[MAX_LENGTH];
char str2[MAX_LENGTH] = "vx"; 

while (1) {
    fd1 = open(receiveM1, O_RDONLY);
    int bytes_read = read(fd1, str1, MAX_LENGTH);
    close(fd1);

    if (bytes_read > 0) {
        strcpy(str2, str1);
    }

    if (strcmp(str2, "Vx++") == 0) {
        x += 0.1;
        printf("Horizontal speed is %f\n", x);
        fd2 = open(sendMx, O_WRONLY);
        write(fd2, str2, strlen(str2) + 1);
        close(fd2);
    } 
    else if (strcmp(str2, "Vx--") == 0 && x > 0) {
        x -= 0.1;
        printf("Horizontal speed is %f\n", x);
        fd2 = open(sendMx, O_WRONLY);
        write(fd2, str2, strlen(str2) + 1);
        close(fd2);
    }
    sleep(1);
}       

return 0;




}

