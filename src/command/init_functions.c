/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 09:23:05 by patri             #+#    #+#             */
/*   Updated: 2025/02/06 16:34:33 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	init_parse_state(t_parse *state, char *command_buff)
// {
// 	char	*new_cmbuff;
//
// 	state->len = ft_strlen(command_buff) - 1;
// 	new_cmbuff = malloc(1000);
// 	if (!new_cmbuff)
// 		malloc_error("error de malloc en el parseo, new_cmbuff");
// 	/* state->new_cmbuff[0] = new_cmbuff; */
// 	state->i = 0;
// 	state->j = 0;
// }
//
// bool	init_state(char *command_buff, t_parse *state)
// {
// 	state->infile = NULL;
// 	state->outfile = NULL;
// 	state->symbol = '\0';
// 	state->new_cmdbuff = (char *)malloc(count_cmds(command_buff, state) + 1);
// 	if (!state->new_cmdbuff)
// 	{
// 		free_memory(state->new_cmdbuff); //esto lo he puesto yo :>
// 		return (0);
// 	}
// 	return (1);
// }

void	init_list(t_env *data, char **env)
{
	t_var	*new_node;
	int		i;

	i = 0;
	while (env[i])
	{
		new_node = create_node(env[i]);
		if (!new_node)
		{
			free_list(data);
			return ;
		}
		if (!data->head)
		{
			data->head = new_node;
			data->tail = new_node;
		}
		else
		{
			data->tail->next = new_node;
			data->tail = new_node;
		}
		i++;
	}
	insert_blank_node(data);
}
