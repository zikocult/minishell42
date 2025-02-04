/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_remove_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:16:05 by Guillem Bar       #+#    #+#             */
/*   Updated: 2025/02/04 10:23:35 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static void	trim_quotes(char **str, size_t start, size_t end)
{
	char	*new_str;

	new_str = (char *)malloc(end - start + 2);
	if (!new_str)
		return ;
	ft_strncpy(new_str, *str + start, end - start + 1);
	new_str[end - start + 1] = '\0';
	free(*str);
	*str = new_str;
}

static void	remove_double_quotes(char **str)
{
	size_t	len;
	size_t	start;
	size_t	end;

	if (!str || !(*str))
		return ;
	len = strlen(*str);
	start = 0;
	end = len - 1;
	if ((*str)[start] == '"')
		start++;
	if ((*str)[end] == '"')
		end--;
	if (start > end)
	{
		free(*str);
		*str = NULL;
		return ;
	}
	trim_quotes(str, start, end);
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
