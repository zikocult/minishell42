/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:17:54 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/02/18 18:26:27 by gbaruls-         ###   ########.fr       */
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
	data->tail->var_name = ft_strdup(name);
	data->tail->content = ft_strdup(content);
	insert_blank_node(data);
}
