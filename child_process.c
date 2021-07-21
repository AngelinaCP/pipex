#include "pipex.h"

void	child_limiter(t_arg *fdp, char **argv)
{
	char	*buf;

	buf = NULL;
	close(fdp[fdp->i].pp[0]);
	while (ft_strcmp(buf, argv[2]))
	{
		if (get_next_line(0, &buf) && ft_strncmp(buf, argv[2],
				ft_strlen(argv[2])))
		{
			write(fdp[fdp->i].pp[1], buf, ft_strlen(buf));
			write(fdp[fdp->i].pp[1], "\n", 1);
		}
		free(buf);
	}
}

void	child_first_fd(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror(argv[1]);
		exit(2);
	}
	if (dup2(fd, STDIN) < 0)
		perror("Couldn't read from the file");
}

void	child_mult_pipes(t_arg *fdp)
{
	if (fdp->i != 0)
	{
		close(fdp[fdp->i - 1].pp[1]);
		if (dup2(fdp[fdp->i - 1].pp[0], STDIN) < 0)
			perror("Couldn't read from the pipe");
		close(fdp[fdp->i - 1].pp[0]);
	}
	if (dup2(fdp[fdp->i].pp[1], STDOUT) < 0)
		perror("Couldn't write to the pipe");
	close(fdp[fdp->i].pp[0]);
	close(fdp [fdp->i].pp[1]);
}

int	child_exec(t_arg *fdp, char **envp, char **argv)
{
	if (fdp->flag == 1 && fdp->i > 0)
	{
		do_execve(envp, argv, fdp->i + 1, fdp);
		perror("child");
	}
	else if (fdp->flag != 1)
	{
		do_execve(envp, argv, fdp->i, fdp);
		perror("child");
	}
	return (1);
}

int	child_and_prnt_wait(int pid, t_arg *fdp, char **argv, char **envp)
{
	if (pid == 0)
	{
		if (fdp->i == 0)
		{
			if (fdp->flag == 1)
				child_limiter(fdp, argv);
			else
				child_first_fd(argv);
		}
		child_mult_pipes(fdp);
		return (child_exec(fdp, envp, argv));
	}
	else
	{
		wait(0);
		close((fdp[fdp->i].pp[1]));
		if (fdp->i)
			close(fdp[fdp->i - 1].pp[0]);
	}
	return (0);
}
