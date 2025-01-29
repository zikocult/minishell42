/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:37:06 by Guillem Bar       #+#    #+#             */
/*   Updated: 2025/01/29 11:29:30 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	process_token(char *start, char *end, int *mode, t_parse *data)
{
	char	*token;

	token = ft_strndup(start, end - start);
	if (*mode == 1)
		data->infile = token;
	else if (*mode == 2)
		data->outfile = token;
	else if (*mode == 3)
		data->a_infile = token;
	else if (*mode == 4)
		data->a_outfile = token;
	else if (!data->command)
		data->command = token;
	else
	{
		append_parameter(&data->parameter, token);
		free(token);
	}
	if (*mode >= 1 && *mode <= 4)
		*mode = 0;
}

char	*handle_special_char(char *end, int *mode, t_parse *data)
{
	if (*end == '|')
		add_node(data);
	else if (*end == '<')
	{
		if (*(end + 1) == '<')
		{
			*mode = 3;
			end++;
		}
		else
			*mode = 1;
	}
	else if (*end == '>')
	{
		if (*(end + 1) == '>')
		{
			*mode = 4;
			end++;
		}
		else
			*mode = 2;
	}
	return (end);
}

static bool	between_quotes(char **end, int *in_quotes)
{
	if (**end == '"')
	{
		*in_quotes = !(*in_quotes);
		(*end)++;
		return (true);
	}
	return (false);
}

void	parse_token(char *cmd_buff, t_parse *data)
{
	char	*start;
	char	*end;
	int		mode;

	start = cmd_buff;
	end = cmd_buff;
	mode = 0;
	while (*end)
	{
		if (between_quotes(&end, &data->in_quotes))
			continue ;
		if (!data->in_quotes && (*end == ' ' || *end == '|' || *end == '<'
				|| *end == '>'))
		{
			if (start != end)
				process_token(start, end, &mode, data);
			end = handle_special_char(end, &mode, data);
			start = end + 1;
		}
		end++;
	}
	if (start != end)
		process_token(start, end, &mode, data);
	add_node(data);
}
