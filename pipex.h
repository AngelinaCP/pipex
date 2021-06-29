#ifndef PIPEX_H
# define PIPEX_H

# define STDOUT 1
# define STDIN 0
# include <stddef.h>
# include <stdlib.h>

typedef struct s_arg
{
	int	pp[2];
	int count;
	int	flag;
} t_arg ;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int 	main(int argc, char **argv, char **envp);
//int main(int argc, char **argv);
char	**ft_split(char const *s, char c);
char 	*ft_strjoin3(char const *s1, char const *s2, char const *s3);


#endif
