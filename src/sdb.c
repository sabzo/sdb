#include "../lib/sdb.h"
int main(int argc, char **argv) {
  if (argc != 2) 
    error("usage: sdb <program name>");
   
  /* Initialize SDB */
  char *prog = argv[1];
  /* Fork and get process ID */
  pid_t pid; 

  if ((pid = fork()) == 0) {
    //child process
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) 
      perror("Unable to start ptrace");
      execl(prog, prog, NULL);
  } 
  else if (pid >= 1) {
   // parent procesis 
   int status;
   unsigned int counter = 0;
   
   printf("SDB started\n");
   while(1) {
      waitpid(pid, &status, 0);
	  if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
	    counter++;
	    // execute child process instruction
        if (ptrace(PTRACE_CONT, pid, NULL, NULL) == -1) {
              perror("ptrace_cont");
              exit(-1);
          }
          // printf("ret code: %d\n", i);
      } else if (WIFEXITED(status)) 
        error("Process finished\n");

      printf("ptrace ret: %d\n", i);
      printf("Counter: %d\n", counter);
  }
  printf("executed %u instructions\n", counter);
}

return 0;
}
