/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_remove_quotes2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:41:12 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/02/06 16:16:08 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	calculate_new_length(const char *str)
{
	size_t	new_len;

	new_len = 0;
	while (*str)
	{
		if (*str != '\'')
			new_len++;
		str++;
	}
	return (new_len);
}

static char	*create_new_string(const char *str, size_t new_len)
{
	char	*temp;
	char	*dst;

	temp = (char *)ft_calloc(new_len + 1, sizeof(char));
	dst = temp;
	if (!temp)
		return (NULL);
	while (*str)
	{
		if (*str != '\'')
			*dst++ = *str;
		str++;
	}
	return (temp);
}

void	remove_single_quotes(char **str)
{
	size_t	new_len;
	char	*new_str;

	if (!str || !(*str))
		return ;
	new_len = calculate_new_length(*str);
	new_str = create_new_string(*str, new_len);
	if (!new_str)
		return ;
	free(*str);
	*str = new_str;
}
