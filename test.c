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
	int fd_pipe[3][2];
	int i;
	char *argv[3] = {"cat", "-e", 0};

	fd = open("test.c", O_RDONLY);
	out = open("test1.txt", O_WRONLY | O_CREAT | O_TRUNC, 00774);
	i = 0;
	while ( i < 3)
	{
		pipe(fd_pipe[i]);
		i++;
	}

	pid = fork();

	if (pid)
	{
		wait(0);
		pid = fork();
		if (pid)
		{
			wait(0);
			close(fd_pipe[1][1]);
			dup2(fd_pipe[1][0], 0);
			dup2(out, 1);
			close(fd_pipe[1][0]);
			execve("/bin/cat", argv, NULL);
		}
		if (!pid)
		{
			close(fd_pipe[1][0]);
			close((fd_pipe[0][1]));
			dup2(fd_pipe[0][0], 0);
			close(fd_pipe[0][0]);
			dup2(fd_pipe[1][1], 1);
			close(fd_pipe[1][1]);
			execve("/bin/cat", argv, NULL);
		}
	}
	if (!pid)
	{
		close(fd_pipe[0][0]);
		dup2(fd, 0);
		dup2(fd_pipe[0][1], 1);
		close(fd_pipe[0][1]);
		execve("/bin/cat", argv, NULL);
	}
	return  (0);
}