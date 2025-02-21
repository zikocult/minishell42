/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:40:22 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/02/20 20:20:28 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_var	*env_prev_search(t_env *data, char *str)
{
	t_var	*current;

	current = data->head;
	if (!ft_strcmp(current->var_name, str))
		return (current);
	while (current->next)
	{
		if (!ft_strcmp(current->next->var_name, str))
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	unset_builtin(t_env *data, char *str)
{
	t_var	*del_node;
	t_var	*current;

	current = env_prev_search(data, str);
	if (current)
	{
		if (current == data->head &&
			ft_strcmp(current->next->var_name, str))
			del_node = current;
		else
		{
			del_node = current->next;
			current->next = current->next->next;
		}
		if (del_node == data->head)
			data->head = del_node->next;
		free(del_node->type);
		free(del_node->content);
		free(del_node->var_name);
		free(del_node);
	}
}
