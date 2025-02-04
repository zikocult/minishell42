/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_remove_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:16:05 by Guillem Bar       #+#    #+#             */
/*   Updated: 2025/02/04 15:42:31 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

// static void	remove_double_quotes(char **str)
// {
// 	char	*src;
// 	char	*dst;
//
// 	if (!str || !(*str))
// 		return ;
// 	src = *str;
// 	dst = *str;
// 	while (*src)
// 	{
// 		if (*src != '"')
// 			*dst++ = *src;
// 		src++;
// 	}
// 	*dst = '\0';
// }

static size_t	calculate_new_length(const char *str)
{
	size_t	new_len;

	new_len = 0;
	while (*str)
	{
		if (*str != '"')
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
		if (*str != '"')
			*dst++ = *str;
		str++;
	}
	// *dst = '\0';
	return (temp);
}

static void	remove_double_quotes(char **str)
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

void	remove_quotes_from_par(t_par *current)
{
	while (current)
	{
		remove_double_quotes(&current->command);
		remove_double_quotes(&current->parameter);
		current = current->next;
	}
}
