#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>
#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n);
int main(int argc, char **argv, char **envp);
char	**ft_split(char const *s, char c);
char 	*ft_strjoin(char const *s1, char const *s2, char const *s3);


#endif
