#include "get_next_line.h"

char	*next_line(char **start_l, char **line)
{
	char		*ptr2;

	ptr2 = NULL;
	if (*start_l)
	{
		ptr2 = ft_strchr(*start_l, '\n');
		if (ptr2)
		{
			*ptr2 = '\0';
			ptr2++;
			*line = ft_strdup(*start_l);
			ft_strcpy(*start_l, ptr2);
		}
		else
		{
			*line = ft_strdup(*start_l);
			free(*start_l);
			start_l = NULL;
		}
	}
	else
		*line = ((char *)malloc((BUFFER_SIZE + 1) * sizeof(char)));
	return (ptr2);
}

char	*find_n(char **p, char **start_l, char **line, char *buf)
{
	char		*copy;

	*p = ft_strchr(buf, '\n');
	if (*p)
	{
		**p = '\0';
		*start_l = ft_strdup(++(*p));
	}
	copy = *line;
	*line = ft_strjoin(*line, buf);
	free(copy);
	copy = NULL;
	return (*p);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	int			count;
	static char	*start_l;
	char		*p;

	if (fd < 0 || BUFFER_SIZE < 1 || !line || read(fd, 0, 0) < 0)
		return (-1);
	buf = (char *)malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
	p = next_line(&start_l, line);
	count = 1;
	while (!p && count != 0)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count == -1)
			return (-1);
		buf[count] = '\0';
		find_n(&p, &start_l, line, buf);
	}
	free(buf);
	if (count == 0)
	{
		start_l = NULL;
		return (0);
	}
	return (1);
}
