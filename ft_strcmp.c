#include "pipex.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1)
		return (1);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
