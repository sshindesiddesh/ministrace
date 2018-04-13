#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int do_child(int argc, char **argv);
int do_trace(pid_t child);
int wait_for_syscall(pid_t child);
