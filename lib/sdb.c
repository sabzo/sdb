#include <sdb.h>
/* Initialize SDB by acepting progname*/
_sdb sdb;
void _init(char *prog) {
  sdb.prog = prog;
}
/* Run Debugger with optinal arguments for prog */
void _run(char *args) {
    if ((sdb.pid = fork()) == 0) {
        //child process
        if (ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) 
          perror("Unable to start ptrace");
          execl(prog, prog, NULL);
      } 
      else if (sdb.pid >= 1) {
       // parent procesis 
       int status;
       unsigned int counter = 0;
       
       printf("SDB started\n");
       while(1) {
          waitpid(sdb.pid, &status, 0);
          if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
            counter++;
            // execute child process instruction
            if (ptrace(PTRACE_CONT, sdb.pid, NULL, NULL) == -1) {
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
}


