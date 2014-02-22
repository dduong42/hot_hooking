#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libinject/ptrace_injector.h"
#define ADDR_HEADER (void *)0x400000
#define ADDR_WRITE (void *)0x600ab0

/*
** This programs shows how we can hook a function
** on a process that is running, using ptrace.
** In this example we will hook the function write
*/

char payload[] =
"\x57\x56\x52\xb8\x01\x00\x00\x00"
"\xbf\x01\x00\x00\x00"
"\x48\x8d\x35\x12\x00\x00\x00"
"\xba\x09\x00\x00\x00\x0f\x05"
"\xb8\x01\x00\x00\x00\x5a\x5e\x5f\x0f\x05\xc3"
"Hooked !\n";

int main(int ac, char **av)
{
	int pid;
	void *ret_mmap;
	struct user_regs_struct regs;
	long saved_header;

	if (ac != 2)
	{
		fprintf(stderr, "Usage: %s [pid]\n");
		return (1);
	}
	pid = atoi(av[1]);
	if (ptrace(PTRACE_ATTACH, pid, 0, 0) < 0)
	{
		perror("ptrace attach");
		return (1);
	}
	waitpid(pid, 0 , 0);
	if (ptrace(PTRACE_GETREGS, pid, &regs, &regs) < 0)
	{
		perror("ptrace getregs");
		exit(1);
	}
	if ((saved_header = ptrace(PTRACE_PEEKTEXT, pid, ADDR_HEADER, 0)) == -1)
	{
		perror("ptrace peektext");
		exit(1);
	}
	ret_mmap = inject_payload(pid, sizeof(payload) - 1, ADDR_HEADER, payload);
	copy_into_mem(pid, 8, ADDR_WRITE, (void *)&ret_mmap);
	copy_into_mem(pid, 2, ADDR_HEADER, (void *)&saved_header);
	if (ptrace(PTRACE_SETREGS, pid, &regs, &regs) < 0)
	{
		perror("ptrace getregs");
		exit(1);
	}
	if (ptrace(PTRACE_DETACH, pid, 0, 0) < 0)
	{
		perror("ptrace detach");
		return (1);
	}
	return (0);
}