#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	char	*path;
	int		i;
	char	**dv;
	char	**cmd1;
	int		fd;

	i = 0;
	if (argc != 5)
		perror("Not enough arguments");
	while (envp[i])
	{
		if ((ft_strncmp("PATH=", envp[i], 5)) == 0)
			break;
		i++;
	}
	int fdp[2];
	if (pipe(fdp) == -1)
		return (1);
	int pid;

	pid = fork();
	if (pid < 0)
		return (2);
	if (pid)
	{
		wait(0);
		fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 00774);
		if (fd < 0)
		{
			perror(argv[4]);
			exit(2);
		}
		if (dup2(fd, STDOUT) < 0)
			perror("TEXT");
		if (dup2(fdp[0], STDIN) < 0)
			perror("TEXT");
		 close(fdp[0]);
		 close(fdp[1]);
		path = envp[i] + 5;
		dv = ft_split(path, ':');
		cmd1 = ft_split(argv[3], ' ');
		int j = 0;
		char *str;

		while (dv[j])
		{
			str = ft_strjoin(dv[j], "/", cmd1[0]);
			execve(str, cmd1, envp);
			j++;
			free(str);
		}
		perror("parent");
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			perror(argv[1]);
			exit(2);
		}
		if (dup2(fd, STDIN) < 0)
			perror("TEXT");
		if (dup2(fdp[1], STDOUT) < 0)
			perror("ERROR");
		close(fdp[0]);
		close(fdp[1]);
				
		path = envp[i] + 5;

		dv = ft_split(path, ':');//seg
		cmd1 = ft_split(argv[2], ' ');
		int j = 0;
		char *str;
		while (dv[j])
		{
			str = ft_strjoin(dv[j], "/", cmd1[0]);
			execve(str, cmd1, envp);
			j++;
			free(str);
		}
		perror("child");
	}
}