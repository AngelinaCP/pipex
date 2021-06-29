#include "pipex.h"

void	do_execve(char **envp, char **argv, int i, t_arg *fdp)
{
	char *path;
	char **dv;
	char **cmd1;
	char *str;
	char	*str2;
	int		j;

	j = 0;
	path = envp[fdp->count] + 5;
	dv = ft_split(path, ':');
	cmd1 = ft_split(argv[2 + i], ' ');
	while (dv[j])
	{
		str = ft_strjoin(dv[j], "/");
		str2 = ft_strjoin(str, cmd1[0]);
		execve(str2, cmd1, envp);
		j++;
		free(str);
		free(str2);
	}
	free (dv);
	free (cmd1);
}

int parent_process(t_arg *fdp, char **argv, char **envp, int argc)
{
	int fd;

	if (fdp->flag == 1)
		fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 00774);
	else
		fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 00774);
	if (fd < 0)
	{
		perror(argv[4]);
		exit(2);
	}
	if (dup2(fd, STDOUT) < 0)
		perror("Couldn't read from the file");
	if (dup2(fdp[fdp->num_argc - 2].pp[0], STDIN) < 0)
		perror("Couldn't read from the pipe2");
	close(fdp[fdp->num_argc - 2].pp[1]);
	close(fdp[fdp->num_argc - 2].pp[0]);
	do_execve(envp, argv, fdp->i, fdp);
	perror("parent");
	return (0);
}