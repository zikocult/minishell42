/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:37:35 by pamanzan          #+#    #+#             */
/*   Updated: 2025/01/21 18:14:18 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	**parse_token(char *command_buff, t_env *data, t_parse *state)
// {
// 	char			**args;
//
// 	if (data)
// 		printf("patata\n");
// 	state = malloc(sizeof(t_parse));
// 	if (!state)
// 		malloc_error("error de malloc en el parseo, state struct");
// 	// init_parse_state(state, command_buff);
// 	/* clean_quotes(state, '\'', command_buff); */
// 	/* clean_quotes(state, '\"', command_buff); */
// 	/* handle_quotes_general(state, data, command_buff); */
// 	while (command_buff[state->i])
// 		state->new_cmbuff[state->j++] = &command_buff[state->i++];
// 	state->new_cmbuff[state->j] = NULL;
// 	args = ft_split(state->new_cmbuff[0], ' ');
// 	free(state);
// 	return (args);
//
// 	/* state = malloc(sizeof(t_parse_state)); */
// 	/* if (!state) */
// 	/* 	malloc_error("error de malloc en el parseo, state struct"); */
// 	/* init_parse_state(state, command_buff); */
// }
//
//
// int	count_args(char **args)
// {
// 	int	count;
//
// 	count = 0;
// 	while (args[count] != NULL)
// 		count++;
// 	return (count);
// }

int	count_cmds(char *cmd_buff, t_parse *state)
{
	int	len;
	int	i;

	len = 1;
	i = 0;
	while (cmd_buff[i])
	{
		if (cmd_buff[i] == '|')
			len++;
		i++;
	}
	return (len);
}

char	*parse_buff(int i, int j, char *cmd_buff)
{
	char	*temp_buff;
	int		k;

	k = 0;
	temp_buff = malloc((i - j + 1) * sizeof(char));
	while (j < i)
	{
		temp_buff[k] = cmd_buff[j];
		k++;
		j++;
	}
	temp_buff[k] = '\0';
	return (temp_buff);
}

char	**parse_token(char *command_buff, t_env *data, t_parse *state)
{
	int		i;
	int		j;
	int		k;
	bool	parse;

	i = 0;
	j = 0;
	k = 0;
	parse = false;
	if (!data)
		return (NULL);
	if (!init_state(command_buff, state))
		return (NULL);
	while (command_buff[i] && parse == false)
	{
		if (command_buff[i] == '>')
		{
			state->new_cmdbuff[k] = parse_buff(i, j, command_buff);
			j = i + 1;
			parse = true;
			state->symbol = '>';
		}
		if (command_buff[i] == '<')
		{
			state->infile = parse_buff(i, j, command_buff);
			j = i + 1;
			state->symbol = '<';
		}
		if (command_buff[i] == '|')
		{
			state->new_cmdbuff[k] = parse_buff(i, j, command_buff);
			j = i + 1;
			k++;
			state->symbol = '|';
		}
		i++;
	}
	if (state->symbol)
	{
		if (state->symbol == '>')

	}
	else
	{
		// Si no hay nada significa que todo command_buff es una orden,
		// hay que copiar la linea entera.
	}
	return (state->new_cmbuff);
}
