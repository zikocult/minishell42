/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:09:45 by patri             #+#    #+#             */
/*   Updated: 2025/01/09 17:47:05 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_quotes_general(t_parse_state *state, t_env *data)
{
	if (state->cmbuff[state->i] == '\'')
	{
		state->i++;
		handle_squotes(state);
	}
	else if (state->cmbuff[state->i] == '\"')
	{
		state->i++;
		handle_dquotes(state, data);
	}
	else
		without_quotes(state, data);
}

void	handle_squotes(t_parse_state *state)
{
	while (state->cmbuff[state->i] && state->cmbuff[state->i] != '\'')
		state->new_cmbuff[state->j++] = state->cmbuff[state->i++];
	if (state->cmbuff[state->i] == '\'')
		state->i++;
}

void	handle_dquotes(t_parse_state *state, t_env *data)
{
	char	*var_value;
	int		k;

	while (state->cmbuff[state->i] && state->cmbuff[state->i] != '\"')
	{
		if (state->cmbuff[state->i] == '$')
		{
			state->i++;
			var_value = expand_variable(&state->cmbuff[state->i], data);

			if (var_value && var_value != NULL)
			{
				k = 0;
				while (var_value[k])
					state->new_cmbuff[state->j++] = var_value[k++];
			}
	
			while (state->cmbuff[state->i] && (
					ft_isalnum(state->cmbuff[state->i]
					) || (state->cmbuff[state->i] == '_')))
				state->i++;
		}
		else
			state->new_cmbuff[state->j++] = state->cmbuff[state->i++];

	}
	if (state->cmbuff[state->i] == '\"')
		state->i++;
}

void	without_quotes(t_parse_state *state, t_env *data)
{
	char	*var_value;
	int		k;

	while (state->cmbuff[state->i])
	{
		if (state->cmbuff[state->i] == '$')
		{
			state->i++;
			var_value = expand_variable(&state->cmbuff[state->i], data);

			if (var_value && var_value != NULL)
			{
				k = 0;
				while (var_value[k])
					state->new_cmbuff[state->j++] = var_value[k++];
			}
	
			while (state->cmbuff[state->i] && (
					ft_isalnum(state->cmbuff[state->i]
					) || (state->cmbuff[state->i] == '_')))
				state->i++;
		}
		else
			state->new_cmbuff[state->j++] = state->cmbuff[state->i++];

	}

}
