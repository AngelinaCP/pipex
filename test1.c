#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM 2

int main(int argc, char **argv)
{
	int pids[NUM];
	int pipes[NUM + 1][2];
	int i;
	for (i = 0; i < NUM + 1; i++)
	{
		if (pipe(pipes[i]) == -1)
			return (1);
	}
	for (i = 0; i < NUM; i++)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			int j;
			for (j = 0; j < NUM; j++)
			{
				if (i != j)
					//open pipes[0][0]
					close(pipes[j][0]);
				if (i + 1 != j)
					//open pipes[1][0]
					close(pipes[j][1]);
			}
			int x;
			//pipes[0][0]
			if (read(pipes[i][0], &x, sizeof(int)) == -1)
				return (3);
			printf("Got: %d\n", x);
			x++;
			//write[1][1]
			if (write(pipes[i + 1][1], &x, sizeof(int)) == -1)
				return (4);
			printf("Send %d\n", x);
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			return (0);
		}
	}

	//parent process
	int	j;
	for (j = 0; j < NUM; j++)
	{
		if (j != NUM)
			close(pipes[j][0]);
		if (j != 0)
			close(pipes[j][1]);
	}
	int y = 5;
	if (write(pipes[0][1], &y, sizeof(int)))
		return (4);
	if (read(pipes[NUM][0], &y, sizeof(int)))
		return (5);
	close (pipes[0][1]);
	close (pipes[NUM][0]);

	for(i = 0; i < NUM; i++)
		wait (NULL);
	return (0);
}