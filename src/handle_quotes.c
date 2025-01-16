/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:09:45 by patri             #+#    #+#             */
/*   Updated: 2025/01/16 18:29:01 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_quotes_general(t_parse_state *state, t_env *data)
{
	int		len;
	
	len = ft_strlen(state->cmbuff) - 1;
	if (state->cmbuff[0] == '\'' || state->cmbuff[len] == '\'')
		handle_squotes(state);
	else if (state->cmbuff[0] == '\"' || state->cmbuff[len] == '\"')
 	{
		state->i++;
		handle_dquotes(state, data);
	}
	else
		without_quotes(state, data);
}

void	handle_squotes(t_parse_state *state)
{
	int		len;
	char	*start; 

	start = state->cmbuff;
	len = ft_strlen(state->cmbuff) - 1;
	if (start[0] != '\'' && start[len] == '\'')
		printf("Aqui llamamos a HereDoc y salimos\n");
	else if (start[0] == '\'' && start[len] != '\'')
		printf("Aqui llamamos a HereDoc y salimos patata\n");
	else if (start[0] == '\'' && start[len] == '\'')
	{
		state->i++;
		len = len - 1;
	}
	while (start[state->i] && (start[state->i] != '\'' && start[len] != '\''))	
		state->new_cmbuff[state->j++] = start[state->i++];
	if (start[state->i] == '\'')
		state->i++;
}

void	handle_dquotes(t_parse_state *state, t_env *data)
{
	char	*var_value;
	int		k;
	int		len;
	char	*start;

	len = ft_strlen(state->cmbuff) - 1;
	start = state->cmbuff;
	if (start[0] != '\"' && start[len] == '\"')
		printf("Aqui llamamos a HereDoc y salimos\n");
	else if (start[0] == '\"' && start[len] != '\"')
		printf("Aqui llamamos a HereDoc y salimos patata\n");
	else if (start[0] == '\"' && start[len] == '\"')
	{
		while (start[state->i] && start[state->i] != '\"')
		{
			if (start[state->i] == '$')
			{
				state->i++;
				var_value = expand_variable(&start[state->i], data);
				if (var_value && var_value != NULL)
				{
					k = 0;
					while (var_value[k])
						state->new_cmbuff[state->j++] = var_value[k++];
				}
				while (start[state->i] && (
						ft_isalnum(start[state->i]
						) || (start[state->i] == '_')))
					state->i++;
			}
			else
				state->new_cmbuff[state->j++] = start[state->i++];
		}
	}
	if (start[state->i] == '\"')
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
