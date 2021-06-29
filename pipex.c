#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include "pipex.h"

void child_process1(int fdp[2], char **argv)
{
	int fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror(argv[1]);
		exit(1);
	}
	if (dup2(fd, STDIN) < 0)
		perror("Couldn't read from the file");
	if (dup2(fdp[1], STDOUT) < 0)
		perror("Couldn't write to the pipe");
	close(fdp[0]);
	close(fdp[1]);
}

void parent_process1(int fdp[2], char **argv)
{
	int fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 00774);
	if (fd < 0)
	{
		perror(argv[4]);
		exit(2);
	}
	if (dup2(fd, STDOUT) < 0)
		perror("Couldn't write to the file");
	if (dup2(fdp[0], STDIN) < 0)
		perror("Couldn't read from the pipe");
	close (fd);
	close(fdp[0]);
	close(fdp[1]);
}


void execute_process(char **envp, char *argv, int i)
{
	char	*path;
	char 	**dv;
	char	**cmd;
	int 	j;
	char 	*str;
	char 	*str2;

	j = 0;
	path = envp[i] + 5;
	dv = ft_split(path, ':');
	cmd = ft_split(argv, ' ');
	while (dv[j])
	{
		str = ft_strjoin(dv[j], "/");
		str2 = ft_strjoin(str, cmd[0]);
		execve(str2, cmd, envp);
		j++;
		free(str);
		free(str2);
	}
}

int fork_proc(char **argv, char **envp, int i)
{
	int	pid;
	int fdp[2];

	if (pipe(fdp) == -1)
		return (2);
	pid = fork();
	if (pid < 0)
	{
		perror("Couldn't create a process");
		return (1);
	}
	if (pid)
	{
		wait(0);
		parent_process1(fdp, argv);
		execute_process(envp, argv[3], i);
		perror("father");
	}
	else
	{
		child_process1(fdp, argv);
		execute_process(envp, argv[2], i);
		perror("child");
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	int		i;

	i = 0;
	if (argc != 5)
	{
		write(2, "Wrong number of arguments\n", 26);
		return (1);
	}

	while (envp[i])
	{
		if ((ft_strncmp("PATH=", envp[i], 5)) == 0)
			break;
		i++;
	}
	if (fork_proc(argv, envp, i))
		return (3);
	return (0);
}