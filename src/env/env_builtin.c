/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:17:54 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/02/19 19:05:00 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_builtin(t_env *data)
{
	t_var	*current;

	current = data->head_env;
	while (current->next)
	{
		printf("%s=%s\n", current->var_name, current->content);
		current = current->next;
	}
}

void	var_builtin(t_env *data)
{
	t_var	*current;

	current = data->head;
	while (current != data->head_env && current->next)
	{
		printf("%s=%s\n", current->var_name, current->content);
		current = current->next;
	}
}

void	add_elem(t_env *data, char *name, char *content)
{
	t_var	*new_node;

	new_node = env_search(data, name);
	if (!new_node)
	{
		new_node = (t_var *)malloc(sizeof(t_var));
		if (!new_node)
			return ;
		new_node->var_name = ft_strdup(name);
		new_node->content = ft_strdup(content);
		new_node->next = data->head;
		data->head = new_node;
	}
	else
	{
		free(new_node->content);
		new_node->content = ft_strdup(content);
	}
}
