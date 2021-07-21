#ifndef PIPEX_H
# define PIPEX_H

# define STDOUT 1
# define STDIN 0
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <time.h>
# include <stdlib.h>

typedef struct s_arg
{
	int	pp[2];
	int count;
	int	flag;
	int i;
	int num_argc;
} t_arg ;

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int 	main(int argc, char **argv, char **envp);
char	**ft_split(char const *s, char c);
int 	child_and_prnt_wait(int pid, t_arg *fdp, char **argv, char **envp);
void	do_execve(char **envp, char **argv, int i, t_arg *fdp);
int 	fork_and_child(t_arg *fdp, char **argv, char **envp);
int 	child_and_prnt_wait(int pid, t_arg *fdp, char **argv, char **envp);
int 	parent_process(t_arg *fdp, char **argv, char **envp, int argc);
char 	*ft_strjoin(char const *s1, char const *s2);
int	get_next_line(int fd, char **line);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strcpy(char *dest, char *src);

#endif
