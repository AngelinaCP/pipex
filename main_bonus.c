#include "pipex.h"

int	create_pipes(t_arg *fdp)
{
	fdp->i = 0;
	while (fdp->i < fdp->num_argc - 1)
	{
		if (pipe(fdp[fdp->i].pp) == -1)
		{
			perror("Error with creating pipe\n");
			return (1);
		}
		fdp->i++;
	}
	return (0);
}

int	find_path(char **envp, int argc, t_arg *fdp)
{
	fdp->count = 0;
	if (argc < 5)
	{
		perror("Not enough arguments");
		return (-1);
	}
	while (envp[fdp->count])
	{
		if ((ft_strncmp("PATH=", envp[fdp->count], 5)) == 0)
			break ;
		fdp->count++;
	}
	return (fdp->count);
}

int	fork_and_child(t_arg *fdp, char **argv, char **envp)
{
	int	pid;

	while (fdp->i < fdp->num_argc - 1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error with creating process\n");
			return (1);
		}
		if (child_and_prnt_wait(pid, fdp, argv, envp))
			return (2);
		fdp->i++;
	}
	return (0);
}

int	exec_process(int argc, char **argv, char **envp, t_arg *fdp)
{
	if (create_pipes(fdp))
		return (1);
	fdp->i = 0;
	if (fork_and_child(fdp, argv, envp))
		return (2);
	return (parent_process(fdp, argv, envp, argc));
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	*fdp;

	fdp = (t_arg *) malloc(sizeof(t_arg) * argc);
	fdp->num_argc = argc - 3;
	if (find_path(envp, argc, fdp) == -1)
		return (1);
	if (argc < 5)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(EXIT_FAILURE);
	}
	if (!(ft_strcmp("here_doc", argv[1])))
	{
		if (argc < 6)
		{
			write(2, "Wrong number of arguments\n", 26);
			exit(EXIT_FAILURE);
		}
		fdp->flag = 1;
		fdp->num_argc = argc - 3;
	}
	if (exec_process(argc, argv, envp, fdp))
		return (2);
	free (fdp);
}
