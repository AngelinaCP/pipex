#include "get_next_line.h"

//size_t	ft_strlen(const char *str)
//{
//	int	i;
//
//	i = 0;
//	while (str[i])
//	{
//		i++;
//	}
//	return (i);
//}

char 	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return ((char *)str);
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
