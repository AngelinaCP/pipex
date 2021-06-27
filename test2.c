#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
	char *argv[2] = {"/Users/ddelena/Documents/pipex/pipex/file1", 0};
	execve("/Users/ddelena/Documents/pipex/pipex/file1", argv, NULL);
	perror("file1");
	return (0);
}