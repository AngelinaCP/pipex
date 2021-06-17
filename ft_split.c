/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelena <ddelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:39:30 by ddelena           #+#    #+#             */
/*   Updated: 2021/04/30 00:33:45 by ddelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

static int	ft_count_words(const char *s, char c)
{
	int	count;

	count = 0;
	if (s == NULL)
		return (0);
	if (*s != c)
		count = 1;
	while (*s)
	{
		if (*s++ == c && *s != c)
			count++;
	}
	if (*(--s) == c)
		count--;
	return (count);
}

static char	**ft_spl(char **out, const char *s, char c)
{
	int		i;
	int		j;

	j = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++; 
		i = 0;
		while (*s && *s != c && i++ >= 0)
			s++;
		if (i == 0)
			break ;
		out[j] = malloc(i + 1);
		s -= i;
		i = 0;
		while (*s && *s != c)
			out[j][i++] = (char)*s++;
		out[j++][i] = 0;
	}
	out[j] = 0;
	return (out);
}

char	**ft_split(char const *s, char c)
{
	char	**out;

	out = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (out == NULL)
		return (NULL);
	if (s == NULL)
	{
		out[0] = "\0";
		return (out);
	}
	out = ft_spl(out, s, c);
	return (out);
}
