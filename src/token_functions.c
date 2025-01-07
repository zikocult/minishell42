/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:37:35 by pamanzan          #+#    #+#             */
/*   Updated: 2025/01/07 10:29:33 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**parse_token(char *command_buff, t_env_vars *env)
{
	char			**args;
	t_parse_state	*state;

	state = malloc(sizeof(t_parse_state));
	if (!state)
		malloc_error("error de malloc en el parseo, state struct");
	init_parse_state(state, command_buff);
	while (state->cmbuff[state->i])
	{
		handle_quotes_general(state, env);
		state->new_cmbuff[state->j++] = state->cmbuff[state->i++];
	}
	state->new_cmbuff[state->j] = '\0';
	args = ft_split(state->new_cmbuff, ' ');
//	free(state->new_cmbuff);
	free(state);
	return (args);
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (count);
}
