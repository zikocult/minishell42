/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_buff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:29:00 by Guillem Bar       #+#    #+#             */
/*   Updated: 2025/02/03 18:50:58 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static bool	check_parse_error(char c, int count)
{
	if ((c == '<' || c == '>') && count >= 3)
	{
		printf("minishell: parse_error %c\n", c);
		return (false);
	}
	if (c == '|' && count >= 2)
	{
		printf("minishell: parse_error |\n");
		return (false);
	}
	return (true);
}

static bool	check_pipe_error(char *cmd_buff, int i)
{
	bool	test;

	test = false;
	while (cmd_buff[i + 1] != '|' && cmd_buff[i + 1] && test == false)
	{
		if (cmd_buff[i + 1] != ' ')
			test = true;
		i++;
	}
	if (test == false)
	{
		printf("minishell: parse_error |\n");
		return (false);
	}
	return (true);
}

static void	update_count_and_last_char(char c, char *last_char, int *count)
{
	if (c == *last_char)
		(*count)++;
	else
	{
		*count = 1;
		*last_char = c;
	}
}

static bool	check_consecutive_redirections(char *cmd_buff)
{
	int		i;
	bool	empty_space;
	bool	in_single_quotes;
	bool	in_double_quotes;

	i = 0;
	empty_space = false;
	in_single_quotes = false;
	in_double_quotes = false;
	while (cmd_buff[i])
	{
		if (cmd_buff[i] == '\'')
			in_single_quotes = !in_single_quotes;
		if (cmd_buff[i] == '"')
			in_double_quotes = !in_double_quotes;
		if ((!in_single_quotes || !in_double_quotes) && (cmd_buff[i] == '<' || cmd_buff[i] == '>'))
		{
			i++;
			if (cmd_buff[i] == ' ')
				empty_space = true;
			while (cmd_buff[i] == ' ')
				i++;
			if (empty_space && (cmd_buff[i] == '<' || cmd_buff[i] == '>'))
			{
				printf("minishell: parse_error '%c'\n", cmd_buff[i]);
				return (false);
			}
			empty_space = false;
		}
		else
			i++;
	}
	return (true);
}

bool	validate_cmdbuff(char *cmd_buff)
{
	int		i;
	int		count;
	char	last_char;

	if (!check_consecutive_redirections(cmd_buff))
		return (false);
	init_vars(&i, &count, &last_char);
	while (cmd_buff[i])
	{
		jump_single_quotes(cmd_buff, &i);
		jump_double_quotes(cmd_buff, &i);
		if (cmd_buff[i] == '<' || cmd_buff[i] == '>' || cmd_buff[i] == '|')
		{
			update_count_and_last_char(cmd_buff[i], &last_char, &count);
			if (!check_parse_error(cmd_buff[i], count))
				return (false);
			if (!check_pipe_error(cmd_buff, i))
				return (false);
		}
		else
			validation_reset(&count, &last_char);
		i++;
	}
	return (true);
}
