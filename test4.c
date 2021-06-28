#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include "pipex.h"
#include "get_next_line.h"

int find_path(char **envp, int argc)
{
	int	count;

	count = 0;
	if (argc < 5)
	{
		perror("Not enough arguments");
		return (-1);
	}
	while (envp[count])
	{
		if ((ft_strncmp("PATH=", envp[count], 5)) == 0)
			break;
		count++;
	}
	return (count);
}

void	do_execve(char **envp, char **argv, int i, int count)
{
	char *path;
	char **dv;
	char **cmd1;
	char *str;
	int		j;

	j = 0;
	path = envp[count] + 5;
	dv = ft_split(path, ':');
	cmd1 = ft_split(argv[2 + i], ' ');
	while (dv[j])
	{
		str = ft_strjoin3(dv[j], "/", cmd1[0]);
		execve(str, cmd1, envp);
		j++;
		//doesn't free when is executed
		free(str);
	}
}

int main(int argc, char **argv, char **envp)
{
	int count;

	char *buf;
	int i;
	int fdp[2];
	int fdp2[2];
	int	fd;
	char **arg[2];
	int pid;
	int	pid2;
	//print here_doc
	count = find_path(envp, argc);
	if (count == -1)
		return (1);
	fd = open(argv[5], O_WRONLY | O_CREAT | O_TRUNC, 00774);
	if (fd < 0)
	{
		perror(argv[5]);
		return (5);
	}
	if ((argc == 6 && ft_strncmp(argv[1], "here_doc", 8)) == 0)
	{
		if (pipe(fdp) == -1)
			return (1);
		if (pipe(fdp2) == -1)
			return (1);
		pid = fork();
		if (pid)
			pid2 = fork();
		if (pid < 0)
			return (3);
		char c;
		if (pid == 0)
		{
			close(fdp[0]);
			while (ft_strncmp(buf, argv[2], ft_strlen(argv[2])))
			{
				//		write(1, "> ", 2);
				if (get_next_line(0, &buf) && (ft_strncmp(buf, argv[2], ft_strlen(argv[2]))))
				{
					write(fdp[1], &buf, ft_strlen(buf));
					write(fdp[1], "\n", 1);
				}
				free(buf);
			}
			return (0);
		}
		else if (pid2 == 0)
		{

			do_execve(envp, argv, 1, count);
			perror("child");
			return (0);
		}
		//O_APPEND
		waitpid(pid, NULL, 0);
		waitpid(pid2, NULL, 0);
		close(fdp[1]);
		dup2(fdp[0], STDIN);
		dup2(fd, STDOUT);
		do_execve(envp, argv, 2, count);
		perror("parent");
		return (6);
	}
}