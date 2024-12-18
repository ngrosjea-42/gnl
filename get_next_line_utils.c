/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrosjea <ngrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:35:07 by ngrosjea          #+#    #+#             */
/*   Updated: 2024/12/17 13:33:40 by ngrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2, int size)
{
	char	*result;
	int		len_fin;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = NULL;
	len_fin = 0;
	if (s1)
		len_fin = ft_strlen(s1);
	len_fin += size;
	result = malloc(sizeof(char) * len_fin + 1);
	if (!result)
		return (free(s1), NULL);
	while (s1 && s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (j < size)
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}
