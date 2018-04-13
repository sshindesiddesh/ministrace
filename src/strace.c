#include <strace.h>

int waitforsyscall(pid_t pid)
{
	int status;

	while (1) {
		ptrace(PTRACE_SYSCALL, pid, 0, 0);
		waitpid(pid, &status, 0);
		if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80)
			return 0;
		if (WIFEXITED(status))
			return 1;
	}
	return 1;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Program to be straced not present\n");
		return 0;
	}

	pid_t pid = fork();

	if (pid == 0) {

		char *exec_args[argc];

		memcpy(exec_args, argv + 1, (argc - 1) * sizeof(char *));
		exec_args[argc - 1] = NULL;
		ptrace(PTRACE_TRACEME);
		kill(getpid(), SIGSTOP);
		execvp(exec_args[0], exec_args);
	} else {

		int status, syscall, retval;

		waitpid(pid, &status, 0);
		ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);
		while (1) {
			if (waitforsyscall(pid) != 0)
				break;
			syscall = ptrace(PTRACE_PEEKUSER, pid,
				sizeof(long)*ORIG_RAX);
			fprintf(stderr, "syscall - %d returned ", syscall);
			if (waitforsyscall(pid) != 0)
				break;
			retval = ptrace(PTRACE_PEEKUSER, pid,
				sizeof(long)*ORIG_RAX);
			fprintf(stderr, "%d\n", retval);
		}
	}
	return 0;
}
