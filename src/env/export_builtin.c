/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guillem Barulls <Guillem Barulls>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:39:26 by Guillem Barulls   #+#    #+#             */
/*   Updated: 2025/02/25 17:31:01 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*change_null(char *content, char *str)
{
	if (!content)
		return (" ");
	return (str);
}

void	export_list_builtin(t_env *data)
{
	t_var	*current;

	current = data->head;
	while (current->next)
	{
		if (!ft_strcmp(current->type, "env")
			|| !ft_strcmp(current->type, "exp"))
			printf("declare -x %s%s%s%s\n", current->var_name,
		  			change_null(current->content, "=\""),
		  			change_null(current->content, current->content),
		  			change_null(current->content, "\""));
		current = current->next;
	}
}
