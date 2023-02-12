#include "./../include/inspection_utilities.h"

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

    // End-effector coordinates
    float ee_x, ee_y;

    // Initialize User Interface 
    init_console_ui();

    char * receiveMx = "/tmp/myfif";
    mkfifo(receiveMx, 0666);
    char str1[10];
    int fd1;
    // Infinite loop
    while(TRUE)
	{
        fd1=open(receiveMx,O_RDONLY);
        if(read(fd1, str1, strlen(str1))==-1)
            perror("read");
        
        // Get mouse/resize commands in non-blocking mode...
        int cmd = getch();

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

                // STOP button pressed
                if(check_button_pressed(stp_button, &event)) {
                    mvprintw(LINES - 1, 1, "STP button pressed");
                    refresh();
                    sleep(1);
                    for(int j = 0; j < COLS; j++) {
                        mvaddch(LINES - 1, j, ' ');
                    }
                }

                // RESET button pressed
                else if(check_button_pressed(rst_button, &event)) {
                    mvprintw(LINES - 1, 1, "RST button pressed");
                    refresh();
                    sleep(1);
                    for(int j = 0; j < COLS; j++) {
                        mvaddch(LINES - 1, j, ' ');
                    }
                }
            }
        }
        
        if(strcmp(str1,"Vx++")==0)
            ee_x++;
        else if(strcmp(str1,"Vx--")==0)
            ee_x--;
        else if(strcmp(str1,"Vz++")==0)
            ee_y++;
        else if(strcmp(str1,"Vz--")==0)
            ee_y--;
        // To be commented in final version...
        //switch ()
        //{
            //case 1:
                //ee_x++;
                //break;
            //case 2:
                //ee_x--;
                //break;
            //case 3:
                //ee_y++;
                //break;
            //case 4:
                //ee_y--;
                //break;
            //default:
                //break;
        //}
        
        // Update UI
        update_console_ui(&ee_x, &ee_y);
	}

    // Terminate
    endwin();
    return 0;
}
