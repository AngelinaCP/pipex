#include <stdio.h>

int main(void)
{
	printf("Uiii!!\n");
	return (0);
}

void do_fork(int i, int num_argc, char **argv, int count, char **envp)
{
	int 	fdp[num_argc][2];
	int 	pid[num_argc + 1];

	while (i < num_argc - 1)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("Error with creating process\n");
			return (2);
		}
		if (pid[i] == 0)
		{
			child_process(argv, i, num_argc, fdp);
			do_execve(envp, argv, i, count);
			perror("child");
			return (3);
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
}
//int	do_fork(int i, int num_argc, char **argv, int count, char **envp, char argc)
//{
//	int 	fdp[num_argc][2];
//	int 	pid[num_argc + 1];
//
//	while (i < num_argc - 1)
//	{
//		pid[i] = fork();
//		if (pid[i] == -1)
//		{
//			perror("Error with creating process\n");
//			return (1);
//		}
//		if (pid[i] == 0)
//		{
//			child_process(argv, i, num_argc, fdp);
//			do_execve(envp, argv, i, count);
//			perror("child");
//			return (2);
//		}
//		else
//		{
//			wait(0);
//			close((fdp[i][1]));
//			if (i)
//				close(fdp[i - 1][0]);
//		}
//		i++;
//	}
//	parent_process(argv, argc, num_argc, fdp);
//	do_execve(envp, argv, i, count);
//	perror("parent");
//	return (0);
//}