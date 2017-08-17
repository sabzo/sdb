#include "../lib/sdb.h"
int main(int argc, char **argv) {
  if (argc != 2) 
    error("usage: sdb <program name>");
   
  /* Initialize SDB */
  char *prog = argv[1];
  /* Fork and get process ID */
  pid_t child; 

  if ((child = fork()) == 0) {
    //child process
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) {
      perror("PTRACE_TRACEME");
      exit(-1);
    }
    execl(prog, prog, NULL);
  } 
  else if (child >= 1) {
   // parent procesis 
   int status;
   unsigned int counter = 0;
   
   printf("SDB started\n");
   while(1) {
      waitpid(child, &status, 0);
	  if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
	    counter++;
	    // execute child process instruction
        if (ptrace(PTRACE_SINGLESTEP, child, NULL, NULL) == -1) {
              perror("ptrace_cont");
              exit(-1);
        }
          // printf("ret code: %d\n", i);
      } else if (WIFEXITED(status)) {
        printf("executed %u instructions\n", counter);
        exit(0);
      }

     // printf("Counter: %d\n", counter);
  }
  printf("executed %u instructions\n", counter);
}

return 0;
}
