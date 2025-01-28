/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:24:41 by Guillem Bar       #+#    #+#             */
/*   Updated: 2025/01/28 10:50:01 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*ptr;
	size_t	len;

	i = 0;
	if (n < ft_strlen(s))
		len = n;
	else
		len = ft_strlen(s);
	ptr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	while (s[i] && i < n)
	{
		ptr[i] = (char)s[i];
		i++;
	}
	return (ptr);
}

char	*ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(dst);
	while (src[i] != '\0')
	{
		dst[len] = src[i];
		i++;
		len++;
	}
	dst[len] = '\0';
	return (dst);
}

void	append_parameter(char **parameter, const char *token)
{
	size_t	len;
	char	*temp;

	if (*parameter)
	{
		len = ft_strlen(*parameter) + ft_strlen(token) + 2;
		temp = (char *)malloc(len);
		if (temp)
		{
			ft_strcpy(temp, *parameter);
			ft_strcat(temp, " ");
			ft_strcat(temp, token);
			free(*parameter);
			*parameter = temp;
		}
	}
	else
	{
		*parameter = ft_strdup(token);
	}
}
