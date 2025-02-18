/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:17:54 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/02/18 23:36:05 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_builtin(t_env *data)
{
	t_var	*current;

	current = data->head;
	while (current->next)
	{
		printf("%s=%s\n", current->var_name, current->content);
		current = current->next;
	}
}

void	add_elem(t_env *data, char *name, char *content)
{
	t_var	*new_node;

	if (!env_search(data, name))
	{
		new_node = (t_var *)malloc(sizeof(t_var));
		if (!new_node)
			return ;
		new_node->var_name = ft_strdup(name);
		new_node->content = ft_strdup(content);
		new_node->next = data->head;
		data->head = new_node;
	}
}
