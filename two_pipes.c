#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
	int fd;
	int out;
	int pid;
	int fd_pipe[2];
	int i;
	char *argv[3] = {"cat", "-e", 0};

	fd = open("test.c", O_RDONLY);
	out = open("test1.txt", O_WRONLY | O_CREAT | O_TRUNC, 00774);
	i = 0;

	pipe(fd_pipe);

	pid = fork();

	if (pid)
	{
		wait(0);
		int fd_file1[2];
		pipe(fd_file1);
		close(fd_pipe[1]);
		pid = fork();
		if (pid)
		{
			wait(0);
			close(fd_file1[1]);
			dup2(fd_file1[0], 0);
			dup2(out, 1);
			close(fd_file1[0]);
			execve("/bin/cat", argv, NULL);
		}
		if (!pid)
		{
			close(fd_pipe[1]);
			dup2(fd_pipe[0], 0);
			dup2(fd_file1[1], 1);
			close(fd_pipe[0]);
			execve("/bin/cat", argv, NULL);
		}
	}
	if (!pid)
	{
		close(fd_pipe[0]);
		dup2(fd, 0);
		dup2(fd_pipe[1], 1);
		close(fd_pipe[1]);
		execve("/bin/cat", argv, NULL);
	}
	return  (0);
}