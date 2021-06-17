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
	int		fd1;

	i = 0;
	if (argc != 5)
		printf("ERROR\n");
	while (envp[i])
	{
		if (ft_strncmp("PATH:", envp[i], 5))
			break;
		i++;
	}

	//NEW FUNCTION
	int fdp[2];
	if (pipe(fdp) == -1)
		return (1);
	int pid;

	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
	{
		//fd[1]
		if ((fd = open(argv[1], O_RDONLY) == -1))
		{
			printf("input file reror\n");
			exit(2);
		}
		close(fdp[0]);
		dup2(fd, STDIN_FILENO);
		close (fd);
		if (dup2(fdp[1], STDOUT_FILENO))
			printf("blabla");
		close(fdp[1]);
		path = envp[i] + 5;
		dv = ft_split(path, ':');
		cmd1 = ft_split(argv[2], ' ');
		int j = 0;
		char *str;
		while (dv[j])
		{
			str = ft_strjoin(dv[j], "/", cmd1[0]);
			execv(str, cmd1);
			j++;
			free(str);
		}
		close(fdp[1]);
	}
//	else
	{
		//fd[0]

		if ((fd = open(argv[4], O_WRONLY) == -1)) {
			printf("blablabla\n");
			exit(2);
		}
			waitpid(pid, NULL, 0);
//		wait(NULL);
		write(2, "abc\n", 4);
		close(fdp[1]);
		dup2(fdp[0], STDIN_FILENO);
		close (fd);
		if (dup2(fd, STDOUT_FILENO))
			printf("blabla");
		close(fdp[0]);
		path = envp[i] + 5;
		dv = ft_split(path, ':');
		cmd1 = ft_split(argv[2], ' ');
		int j = 0;
		char *str;
		while (dv[j])
		{
			str = ft_strjoin(dv[j], "/", cmd1[1]);
			execv(str, cmd1);
			j++;
			free(str);
		}
	}
}