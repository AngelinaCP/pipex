#include "pipex.h"

size_t	ft_strlen1(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*d;
	int		length;
	int		i;

	i = 0;
	length = ft_strlen(s1);
	d = (char *)malloc(sizeof(char) * (length + 1));
	if (d == 0)
		return (NULL);
	while (i < length)
	{
		d[i] = s1[i];
		i++;
	}
	d[i] = 0;
	return (d);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
