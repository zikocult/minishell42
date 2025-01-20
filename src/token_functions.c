/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:37:35 by pamanzan          #+#    #+#             */
/*   Updated: 2025/01/20 17:31:36 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**parse_token(char *command_buff, t_env *data, t_parse *state)
{
	char			**args;

	state = malloc(sizeof(t_parse));
	if (data)
		printf("patata\n");
	if (!state)
		malloc_error("error de malloc en el parseo, state struct");
	init_parse_state(state, command_buff);
	/* clean_quotes(state, '\'', command_buff); */
	/* clean_quotes(state, '\"', command_buff); */
	/* handle_quotes_general(state, data, command_buff); */
	while (command_buff[state->i])
		state->new_cmbuff[state->j++] = &command_buff[state->i++];
	state->new_cmbuff[state->j] = NULL;
	args = ft_split(state->new_cmbuff[0], ' ');
	free(state);
	return (args);

	/* state = malloc(sizeof(t_parse_state)); */
	/* if (!state) */
	/* 	malloc_error("error de malloc en el parseo, state struct"); */
	/* init_parse_state(state, command_buff); */


}

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (count);
}
