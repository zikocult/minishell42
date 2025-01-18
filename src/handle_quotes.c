/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:09:45 by patri             #+#    #+#             */
/*   Updated: 2025/01/18 13:31:22 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_quotes_general(t_parse_state *state, t_env *data)
{
	if (state->cmbuff[state->i] == '\'' || state->cmbuff[state->len] == '\'')
		handle_squotes(state);
	else if (state->cmbuff[state->i] == '\"' || state->cmbuff[state->len] == '\"')
		handle_dquotes(state, data);
	else
		without_quotes(state, data);
}

void	handle_squotes(t_parse_state *state)
{
	char	*start; 

	start = state->cmbuff;
	while (start[state->i] && (start[state->i] != '\'' && start[state->len] != '\''))
		state->new_cmbuff[state->j++] = start[state->i++];
	if (start[state->i] == '\'')
		state->i++;
	if (start[state->len] == '\'')
		state->len--;
}

void	handle_dquotes(t_parse_state *state, t_env *data)
{
	char	*var_value;
	int		k;
	char	*start;

	start = state->cmbuff;
	while (start[state->i] && start[state->i] != '\"')
	{
		if (start[state->i] == '$')
		{
			state->i++;
			var_value = expand_variable(&start[state->i], data);
			k = 0;
			while (var_value[k])
				state->new_cmbuff[state->j++] = var_value[k++];
			while (start[state->i] && (ft_isalnum(start[state->i]
					) || (start[state->i] == '_')))
					state->i++;
		}	
		else
			state->new_cmbuff[state->j++] = start[state->i++];
	}
	if (start[state->i] == '\"')
		state->i++;
	if (start[state->len] == '\"')
		state->len--;
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
			k = 0;
			while (var_value[k])
				state->new_cmbuff[state->j++] = var_value[k++];
			while (state->cmbuff[state->i] && (
					ft_isalnum(state->cmbuff[state->i]
					) || (state->cmbuff[state->i] == '_')))
				state->i++;
		}
		else
			state->new_cmbuff[state->j++] = state->cmbuff[state->i++];
	}
}

void	clean_quotes(t_parse_state *state, char c)
{
	char	*start; 

	start = state->cmbuff;
	if (start[state->i] != c && start[state->len] == c)
	{
		printf("Sintax error\n");
		state->len--;
		return ;
	}
	else if (start[state->i] == c && start[state->len] != c)
	{
		state->i++;
		printf("Sintax error patata\n");
		return ;
	}
	else if (start[state->i] == c && start[state->len] == c) 
	{
		state->i++;
		state->len--;
	}
}
