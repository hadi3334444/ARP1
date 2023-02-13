#include "./../include/command_utilities.h"

#include <stdio.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    // Utility variable to avoid trigger resize event on launch
    int first_resize = TRUE;

    // Initialize User Interface 
    init_console_ui();
    
    // Infinite loop
    while(TRUE)
	{	
        // Get mouse/resize commands in non-blocking mode...
        int cmd = getch();
        //file descriptors for the named pipes
	int fd,fd2; 
	//named pipe
        char * send = "/tmp/myfifo";
        mkfifo(send, 0666);
        //named pipe
	char * send2 = "/tmp/myfifo3";
        mkfifo(send2, 0666);
        char inpt[80];
        //open pipes for writing 
	fd = open(send, O_WRONLY);
        fd2 = open(send2, O_WRONLY);
        // If user resizes screen, re-draw UI
        if(cmd == KEY_RESIZE) {
            if(first_resize) {
                first_resize = FALSE;
            }
            else {
                reset_console_ui();
            }
        }
        // Else if mouse has been pressed
        else if(cmd == KEY_MOUSE) {

            // Check which button has been pressed...
            if(getmouse(&event) == OK) {

                // Vx++ button pressed
                if(check_button_pressed(vx_incr_btn, &event)){ 
                    //put Vx++ into input variable
		    strncpy(inpt,"Vx++",10);
                    //writing input to the first named pipe
		    write(fd, inpt, strlen(inpt)+1); 
                    
                    mvprintw(LINES - 1, 1, "Horizontal Speed Increased");
                    //refresh();
                    sleep(1);
                    for(int j = 0; j < COLS; j++) {
                        mvaddch(LINES - 1, j, ' ');
                    }
                }

                // Vx-- button pressed
                else if(check_button_pressed(vx_decr_btn, &event)) {
                    // put Vx-- into input variable
                    strncpy(inpt,"Vx--",10);
                    //writing input to the first named pipe
                    write(fd, inpt, strlen(inpt)+1); 

                    mvprintw(LINES - 1, 1, "Horizontal Speed Decreased");
                    refresh();
                    sleep(1);
                    for(int j = 0; j < COLS; j++) {
                        mvaddch(LINES - 1, j, ' ');
                    }
                }

                // Vx stop button pressed
                else if(check_button_pressed(vx_stp_button, &event)) {
                    mvprintw(LINES - 1, 1, "Horizontal Motor Stopped");
                    refresh();
                    sleep(1);
                    for(int j = 0; j < COLS; j++) {
                        mvaddch(LINES - 1, j, ' ');
                    }
                }

                // Vz++ button pressed
                else if(check_button_pressed(vz_incr_btn, &event)) {
                    //put Vz++ into input variable
                    strncpy(inpt,"Vz++",10);
                    //writing input to the second named pipe
                    write(fd2, inpt, strlen(inpt)+1); 
                    
                    mvprintw(LINES - 1, 1, "Vertical Speed Increased");
                    refresh();
                    sleep(1);
                    for(int j = 0; j < COLS; j++) {
                        mvaddch(LINES - 1, j, ' ');
                    }
                }

                // Vz-- button pressed
                else if(check_button_pressed(vz_decr_btn, &event)) {
                    //put Vz-- into input variable
                    strncpy(inpt,"Vz--",10);
                    //writing input to the second named pipe
                    write(fd2, inpt, strlen(inpt)+1); 
                    
                    mvprintw(LINES - 1, 1, "Vertical Speed Decreased");
                    refresh();
                    sleep(1);
                    for(int j = 0; j < COLS; j++) {
                        mvaddch(LINES - 1, j, ' ');
                    }
                }

                // Vz stop button pressed
                else if(check_button_pressed(vz_stp_button, &event)) {
                    mvprintw(LINES - 1, 1, "Vertical Motor Stopped");
                    refresh();
                    sleep(1);
                    for(int j = 0; j < COLS; j++) {
                        mvaddch(LINES - 1, j, ' ');
                    }
                }
            }
        }

        refresh();
	//closing file descriptors associated with the named pipes
        close(fd);
        close(fd2);
    }    
    // Terminate
    endwin();
    return 0;
}
