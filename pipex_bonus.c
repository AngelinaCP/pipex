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
	//for bonus1 argv[2 + i]
	//for bonus2 argv[3 + i]
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

//buf = NULL;
//close(fdp[i][0]);
//while(ft_strncmp(buf, argv[2], ft_strlen(argv[2])))
//{
//if(get_next_line(0, &buf) && ft_strncmp(buf, argv[2], ft_strlen(argv[2])))
//{
//write(fdp[i][1], buf, ft_strlen(buf));
//write(fdp[i][1], "\n", 1);
//}
//free(buf);

int exec_process(int argc, char **argv, int count, char **envp, int num_argc)
{
	int 	fdp[num_argc][2];
	int 	pid;
	int	i;
	int fd;

	i = 0;
	//changed: -1 added
	while (i < num_argc - 1)
	{
		if (pipe(fdp[i]) == -1)
		{
			perror("Error with creating pipe\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < num_argc - 1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error with creating process\n");
			return (2);
		}
		if (pid == 0)
		{
			int	fd;
			char *buf;

			if (i == 0) {
//				fd = open(argv[1], O_RDONLY);
//				if (fd < 0)
//				{
//					perror(argv[1]);
//					exit(2);
//				}
//				if (dup2(fd, STDIN) < 0)
//					perror("Couldn't read from the file");
//					//bonus2
//				else
//				{
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
//				}
			}
			if (i != 0)
			{
				close(fdp[i - 1][1]);
				if (dup2(fdp[i - 1][0], STDIN) < 0)
					perror("Couldn't read from the pipe1");
				close(fdp[i - 1][0]);
			}
			if (dup2(fdp[i][1], STDOUT) < 0)
				perror("Couldn't write to the pipe1");
			close(fdp[i][0]);
			close(fdp[i][1]);
			//if (i > 0) for bonus2 // add flag
			if (i > 0)
			{
				do_execve(envp, argv, i, count);
				perror("child");
			}
			return (3);
		}
		else
		{
			wait(0);
			close((fdp[i][1]));
			if (i)
				close(fdp[i - 1][0]);
		}
		i++;
	}
//	int fd;

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
	do_execve(envp, argv, i, count);
	perror("parent");
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	int		i;
	int		count;

	int		num_argc;

	num_argc = argc - 3;
	i = 0;
	count = find_path(envp, argc);
	if (count == -1)
		return (1);
	if (argc < 5)
	{
		perror("Not enough arguments");
		exit(EXIT_FAILURE);
	}
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (argc < 6)
		{
			perror("Not enough arguments");
			exit(EXIT_FAILURE);
		}
		num_argc = argc - 4;
	}
	if (exec_process(argc, argv, count, envp, num_argc))
		return (2);
	//segfault ./a.out
	//seeking in current directory
	//initialize fds
	//посмотри права доступа функцией access()

}