/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:17:54 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/02/25 17:35:23 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_list_builtin(t_env *data)
{
	t_var	*current;

	current = data->head;
	while (current->next)
	{
		if (!ft_strcmp(current->type, "env"))
			printf("%s=%s\n", current->var_name, current->content);
		current = current->next;
	}
}
