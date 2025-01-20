/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:37:35 by pamanzan          #+#    #+#             */
/*   Updated: 2025/01/20 18:58:23 by gbaruls-         ###   ########.fr       */
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

char	**parse_token(char *command_buff, t_env *data, t_parse *state)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	if (!data)
		return (NULL);
	state->infile = NULL;
	state->outfile = NULL;
	state->symbol = '\0';
	state->new_cmbuff = (char **)malloc(count_cmds(command_buff, state) + 1);
	if (!state)
		// LIMPIAR BIEN TODO
		return (NULL);
	while (command_buff[i])
	{
		if (command_buff[i] == '>')
		{
			// Malloc del tamano de len
			// recorrer desde j hasta i guardando el resultado
			j = i;
			len = 0;
			state->symbol = '>';
		}
		if (command_buff[i] == '<')
		{

		}
		if (command_buff[i] == '|')
		{
	
		}
		i++;
	}
	if (state->symbol)
	{

	}
	return (state->new_cmbuff);
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (count);
}
