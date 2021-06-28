#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include "pipex.h"
#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int main(int argc, char **argv)
{
	char *buf;
	int i;
	int fd_pipe[2];
	int fd_out;
	if (argc < 3)
		exit (-1);
	char *cat[3] = {"/bin/cat", "-e", 0};
	fd_out = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	int pid;
	pipe(fd_pipe);
	pid = fork();
	wait(0);
	if (!pid)
	{
		close(fd_pipe[0]);
		while (ft_strncmp(buf, argv[1], ft_strlen(argv[1])))
		{
			if(get_next_line(0, &buf) && ft_strncmp(buf, argv[1], ft_strlen(argv[1])))
			{
				write(fd_pipe[1], buf, ft_strlen(buf));
				write(fd_pipe[1], "\n", 1);
			}
			free(buf);
		}
		return (0);
	}
	close(fd_pipe[1]);
	dup2(fd_pipe[0], 0);
	dup2(fd_out, 1);
	execve(cat[0], cat, NULL);
	return (0);
}