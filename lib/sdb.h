#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <errno.h>

void error(char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

typedef struct sdb {
  char *prog;
  pid_t *pid;
  void (*init)(char *prog);
  void (*run) (char *args);
  struct debugger *this;
} _sdb;

void _new(char *prog);
 
_sdb sdb;
