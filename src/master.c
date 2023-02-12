#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int spawn(const char * program, char * arg_list[]) {

  pid_t child_pid = fork();

  if(child_pid < 0) {
    perror("Error while forking...");
    return 1;
  }

  else if(child_pid != 0) {
    return child_pid;
  }

  else {
    if(execvp (program, arg_list) == 0);
    perror("Exec failed");
    return 1;
  }
}

int main() {

  char * arg_list_command[] = { "/usr/bin/konsole", "-e", "./bin/command", NULL };
  char * arg_list_inspection[] = { "/usr/bin/konsole", "-e", "./bin/inspection", NULL };
  char * arg_list_M1[] = { "/usr/bin/konsole", "-e", "./bin/M1", NULL };
  char * arg_list_M2[] = { "/usr/bin/konsole", "-e", "./bin/M2", NULL };
  char * arg_list_Mx[] = { "/usr/bin/konsole", "-e", "./bin/Mx", NULL };

  pid_t pid_cmd = spawn("/usr/bin/konsole", arg_list_command);
  pid_t pid_insp = spawn("/usr/bin/konsole", arg_list_inspection);
  pid_t pid_M1 = spawn("/usr/bin/konsole", arg_list_M1);
  pid_t pid_M2 = spawn("/usr/bin/konsole", arg_list_M2);
  pid_t pid_Mx = spawn("/usr/bin/konsole", arg_list_Mx);

  int status;
  waitpid(pid_cmd, &status, 0);
  waitpid(pid_insp, &status, 0);
  waitpid(pid_M1, &status, 0);
  waitpid(pid_M2, &status, 0);
  waitpid(pid_Mx, &status, 0);
  
  printf ("Main program exiting with status %d\n", status);
  return 0;
}

