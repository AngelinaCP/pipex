#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include "pipex.h"
#include "get_next_line.h"

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
	cmd1 = ft_split(argv[3 + i], ' ');
	while (dv[j])
	{
		str = ft_strjoin3(dv[j], "/", cmd1[0]);
		execve(str, cmd1, envp);
		j++;
		//doesn't free when is executed
		free(str);
	}
}

void child_process(char **argv, int i, int fdp[][2])
{
	int	fd;
	char *buf;

	if (i == 0)
	{
		//write(2, "ll\n", 3);
		buf = NULL;
		close(fdp[i][0]);
		while(ft_strncmp(buf, argv[2], ft_strlen(argv[2])))
		{
			if(get_next_line(0, &buf) && ft_strncmp(buf, argv[2], ft_strlen(argv[2])))
			{
				write(fdp[i][1], buf, ft_strlen(buf));
				write(fdp[i][1], "\n", 1);
			}
			free(buf);
		}
	}
	if (i != 0)
	{
	//	write(1, "ac", 2);
		close(fdp[i - 1][1]);
		if (dup2(fdp[i - 1][0], STDIN) < 0)
			perror("Couldn't read from the pipe1");
		close(fdp[i - 1][0]);
		if (dup2(fdp[i][1], STDOUT) < 0)
			perror("Couldn't write to the pipe1");
		close(fdp[i][0]);
		close(fdp[i][1]);
	}
}

//void parent_process(char **argv, int argc, int fdp[][2], int num_argc)
//{
//	int fd;
//
//	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 00774);
//	if (fd < 0)
//	{
//		perror(argv[4]);
//		exit(2);
//	}
//	if (dup2(fd, STDOUT) < 0)
//		perror("Couldn't read from the file");
//	//changed num-argc - 2
//	if (dup2(fdp[num_argc - 1][0], STDIN) < 0)
//		perror("Couldn't read from the pipe2");
//	close(fdp[num_argc - 2][1]);
//	close(fdp[num_argc - 2][0]);
//}

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

int exec_process(int argc, char **argv, int count, char **envp, int num_argc)
{
	int 	fdp[num_argc][2];
	int 	pid;
	int	i;

	i = 0;
	while (i < num_argc)
	{
		if (pipe(fdp[i]) == -1)
		{
			perror("Error with creating pipe\n");
			return (1);
		}
		i++;
	}
	i = 0;
//	if (do_fork(i, argv, count, envp, argc))
//		return (2);
//	return (0);
	while (i != num_argc - 1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error with creating process\n");
			return (2);
		}
		if (pid == 0)
		{
			child_process(argv, i, fdp);
			if (i > 0)
			{
				do_execve(envp, argv, i, count);
				perror("child");
				return (3);
			}
			return (1);
		}
		else
		{
			wait(0);
			close((fdp[i][1]));
//			if (i)
//				close(fdp[i - 1][0]);
		}
		i++;
	}
	int fd;

	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 00774);
	if (fd < 0)
	{
		perror(argv[4]);
		exit(2);
	}
	if (dup2(fd, STDOUT) < 0)
		perror("Couldn't read from the file");
	if (dup2(fdp[num_argc - 2][0], STDIN) < 0)
		perror("Couldn't read from the pipe2");
	close(fdp[num_argc - 2][1]);
	close(fdp[num_argc - 2][0]);
//	parent_process(argv, argc, fdp, num_argc);
	do_execve(envp, argv, i, count);
	perror("parent");
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	int		i;
	int		count;
	t_list	var;
	int		num_argc;

	num_argc = argc - 4;
	i = 0;
	count = find_path(envp, argc);
	if (count == -1)
		return (1);
	if (argc < 6 && !ft_strncmp(argv[1], "here_doc", 8))
	{
		write(1, "Not enough arguments!\n", 22);
		exit(EXIT_FAILURE);
	}
	if (exec_process(argc, argv, count, envp, num_argc))
		return (2);
	//segfault ./a.out
	//seeking in current directory
	//initialize fds
	//посмотри права доступа функцией access()

}