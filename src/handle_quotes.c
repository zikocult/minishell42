/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:09:45 by patri             #+#    #+#             */
/*   Updated: 2025/01/23 16:20:02 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_quotes_general(t_parse *state, t_env *data, char *cmd_buff)
{
	if (cmd_buff[state->i] == '\'' || cmd_buff[state->len] == '\'')
		handle_squotes(state, cmd_buff);
	else if (cmd_buff[state->i] == '\"' || cmd_buff[state->len] == '\"')
		handle_dquotes(state, data, cmd_buff);
	else
		without_quotes(state, data, cmd_buff);
}

void	handle_squotes(t_parse *state, char *cmd_buff)
{
	char	*start; 

	start = cmd_buff;
	if (start[state->i] == '\'' && start[state->len] == '\'') 
	{
		state->i++;
		state->len--;
	}
	while (start[state->i] && (start[state->i] != '\'' && start[state->len] != '\''))
		state->new_cmdbuff[state->j++] = &start[state->i++];
	if (start[state->i] == '\'')
		state->i++;
	if (start[state->len] == '\'')
		state->len--;
}

void	handle_dquotes(t_parse *state, t_env *data, char *cmd_buff)
{
	char	*var_value;
	int		k;
	char	*start;

	start = cmd_buff;
	if (start[state->i] == '\"' && start[state->len] == '\"') 
	{
		state->i++;
		state->len--;
	}
	while (start[state->i] && start[state->i] != '\"')
	{
		if (start[state->i] == '$')
		{
			state->i++;
			var_value = expand_variable(&start[state->i], data);
			k = 0;
			while (var_value[k])
				state->new_cmdbuff[state->j++] = &var_value[k++];
			while (start[state->i] && (ft_isalnum(start[state->i]
					) || (start[state->i] == '_')))
					state->i++;
		}	
		else
			state->new_cmdbuff[state->j++] = &start[state->i++];
	}
	if (start[state->i] == '\"')
		state->i++;
	if (start[state->len] == '\"')
		state->len--;
}

void	without_quotes(t_parse *state, t_env *data, char *cmd_buff)
{
	char	*var_value;
	int		k;

	while (cmd_buff[state->i])
	{
		if (cmd_buff[state->i] == '$')
		{
			state->i++;
			var_value = expand_variable(&cmd_buff[state->i], data);
			k = 0;
			while (var_value[k])
				state->new_cmdbuff[state->j++] = &var_value[k++];
			while (cmd_buff[state->i] && (ft_isalnum(cmd_buff[state->i])
					|| (cmd_buff[state->i] == '_')))
				state->i++;
		}
		else
			state->new_cmdbuff[state->j++] = &cmd_buff[state->i++];
	}
}

void	clean_quotes(t_parse *state, char c, char *cmd_buff)
{
	char	*start; 

	start = cmd_buff;
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
}
