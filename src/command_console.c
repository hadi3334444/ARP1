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
        int fd,fd2; 
        char * send = "/tmp/myfifo";
        mkfifo(send, 0666);
        char * send2 = "/tmp/myfifo3";
        mkfifo(send2, 0666);
        char inpt[80];
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
                    strncpy(inpt,"Vx++",10);
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
                    //fd = open(send, O_WRONLY); 
                    strncpy(inpt,"Vx--",10);
                    write(fd, inpt, strlen(inpt)+1); 
                    //close(fd);

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
                    //fd2 = open(send2, O_WRONLY); 
                    strncpy(inpt,"Vz++",10);
                    write(fd2, inpt, strlen(inpt)+1); 
                    //close(fd2);
                    
                    mvprintw(LINES - 1, 1, "Vertical Speed Increased");
                    refresh();
                    sleep(1);
                    for(int j = 0; j < COLS; j++) {
                        mvaddch(LINES - 1, j, ' ');
                    }
                }

                // Vz-- button pressed
                else if(check_button_pressed(vz_decr_btn, &event)) {
                    //fd2 = open(send2, O_WRONLY); 
                    strncpy(inpt,"Vz--",10);
                    write(fd2, inpt, strlen(inpt)+1); 
                    //close(fd2);
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
        close(fd);
        close(fd2);
    }    
    // Terminate
    endwin();
    return 0;
}
