/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelena <ddelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 04:45:14 by ddelena           #+#    #+#             */
/*   Updated: 2021/04/24 05:03:57 by ddelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

//char 	*ft_strjoin(char const *s1, char const *s2)
//{
//	char	*str;
//	int		i;
//	int		j;
//
//	i = 0;
//	j = 0;
//	if (!s1 || !s2)
//		return (NULL);
//	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
//	if (str == NULL)
//		return (NULL);
//	while (s1[i])
//	{
//		str[i] = s1[i];
//		i++;
//	}
//	while (s2[j])
//	{
//		str[i] = s2[j];
//		j++;
//		i++;
//	}
//	str[i] = '\0';
//	return ((char *)str);
//}

#include <stdio.h>

char 	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!s1 || !s2 || !s3)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
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
	while (s3[k])
	{
		str[i] = s3[k];
		i++;
		k++;
	}
	str[i] = '\0';
	return (str);
}
