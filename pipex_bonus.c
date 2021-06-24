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
	int		num_argc;
	int		j;
	int		count;

	i = 0;
	count = 0;
	num_argc = argc - 3;
	int 	pid[num_argc + 1];
//segfault ./a.out
	if (argc < 5)
	{
		perror("Not enough arguments");
		return (1);
	}
	while (envp[count])
	{
		if ((ft_strncmp("PATH=", envp[count], 5)) == 0)
			break;
		count++;
	}
	//creating pipes
	int fdp[num_argc + 1][2];

	i = 0;
	while (i < num_argc - 1)
	{
		if (pipe(fdp[i]) == -1)
		{
			perror("Error with creating pipe\n");
			return (2);
		}
		i++;
	}
	i = 0;
	printf("nargc=%d\n", num_argc);
	//creating process
	while (i < num_argc - 1)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("Error with creating process\n");
			return (3);
		}
		printf("i = %d pid=%d\n", i, pid[i]);
		// write(2, "blabla\n", 7);
		if (pid[i] == 0)
		{
			if (i == 0)
			{
				fd = open(argv[1], O_RDONLY);
				if (fd < 0) {
					perror(argv[1]);
					exit(2);
				}
				if(dup2(fd, STDIN) < 0)
				perror("Couldn't read from the file");
			}
			// j = 0;
			// while (j < num_argc + 1)
			// {
			// 	if (i == 0)
			// 		close(fdp[i][0]);
			// 	if (i != j)
			// 		close(fdp[j][1]);
			// 	if (i != j)
			// 		close(fdp[j][0]);
			// 	j++;
			// }
			if (i != 0)
			{
				if (dup2(fdp[i - 1][0], STDIN) < 0)
					perror("Couldn't write to the pipe");
				close(fdp[i - 1][0]);
				close(fdp[i - 1][1]);
				
			}
			// close(fdp[i][0]);
			// if (i != num_argc)
			// 	close(fdp[i][0]);
//			if (i != num_argc - 1)
			{
			if (dup2(fdp[i][1], STDOUT) < 0)
				perror("Couldn't read from the pipe");
			}


			j = 0;
			close(fdp[i][0]);
			close(fdp[i][1]);
			path = envp[count] + 5;
			dv = ft_split(path, ':');
			cmd1 = ft_split(argv[2 + i], ' ');
			int j = 0;
			char *str;
			// printf("run=%d %s\n", num_argc, argv[2 + i]);
			write(2, "runcmnd\n", 8);
			while (dv[j])
			{
				str = ft_strjoin(dv[j], "/", cmd1[0]);
				execve(str, cmd1, envp);
				j++;
				free(str);
			}
			perror("child");
			return (0);
		}
		
		else
		{
			wait(0);
			write(2, "dogdal\n", 7);
		}
		i++;
	}
	// i = 0;
	// while (i < num_argc - 1)
	// {
	// 	wait(NULL);
	// 	i++;
	// }
	//return 0;
	// j = 0;
	// while (j < num_argc + 1)
	// {
	// 	if (j != num_argc)
	// 		close (fdp[j][0]);
	// 	if (j != 0)
	// 		close(fdp[j][1]);
	// 	j++;
	// }
	write(2, "dogd22\n", 7);
	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 00774);
	if (fd < 0)
	{
		perror(argv[4]);
		exit(2);
	}
	if (dup2(fd, STDOUT) < 0)
		perror("Couldn't read from the file");
	//add
	if (dup2(fdp[num_argc - 2][0], STDIN) < 0)
		perror("Couldn't read from the pipe");
	close(fdp[num_argc - 2][1]);
	close(fdp[num_argc - 2][0]);
	path = envp[count] + 5;
	dv = ft_split(path, ':');
	cmd1 = ft_split(argv[i + 2], ' ');
	int k = 0;
	char *str;
	while (dv[k])
	{
		str = ft_strjoin(dv[k], "/", cmd1[0]);
		execve(str, cmd1, envp);
		k++;
		free(str);
	}
	perror("parent");
}
