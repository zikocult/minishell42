/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:34:40 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/02/25 17:35:14 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	new_node1(t_env *data, char *name, char *content, char *type)
{
	t_var	*new_node;

	new_node = (t_var *)malloc(sizeof(t_var));
	if (!new_node)
		return ;
	new_node->type = ft_strdup(type);
	new_node->var_name = ft_strdup(name);
	if (content)
		new_node->content = ft_strdup(content);
	else
		new_node->content = NULL;
	data->last_node->next = new_node;
	new_node->next = data->tail;
	data->last_node = new_node;
}

static void	new_node2(t_env *data, char *name, char *content, char *type)
{
	t_var	*new_node;

	new_node = (t_var *)malloc(sizeof(t_var));
	if (!new_node)
		return ;
	new_node->type = ft_strdup(type);
	new_node->var_name = ft_strdup(name);
	if (content)
		new_node->content = ft_strdup(content);
	else
		new_node->content = NULL;
	new_node->next = data->head;
	data->head = new_node;
	data->last_node = new_node;
}

void	add_elem(t_env *data, char *name, char *content, char *type)
{
	t_var	*new_node;

	if (data->head != data->tail)
	{
		new_node = env_search(data, name);
		if (!new_node)
			new_node1(data, name, content, type);
		else
		{
			if (content)
			{
				free(new_node->content);
				new_node->content = ft_strdup(content);
			}
			else
			{
				if (new_node->content)
					free(new_node->content);
			}
			free(new_node->type);
			new_node->type = ft_strdup(type);
		}
	}
	else
		new_node2(data, name, content, type);
}
