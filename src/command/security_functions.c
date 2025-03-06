/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:43:16 by patri             #+#    #+#             */
/*   Updated: 2025/03/06 18:23:07 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_memory(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	malloc_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	free_list(t_env *data)
{
	t_var	*current;
	t_var	*next_node;

	current = data->head;
	while (current->next)
	{
		next_node = current->next;
		if (current->content)
			free(current->content);
		if (current->var_name)
			free(current->var_name);
		if (current->type)
			free(current->type);
		if (current)
			free(current);
		current = next_node;
	}
	free(data->tail);
	data->head = NULL;
	data->tail = NULL;
}

char	*if_notstr(char *str)
{
	if (!str)
		return (NULL);
	return (str);
}

void	free_main(char *command_buff, t_env *data)
{
	if (data->heredoc_delimeter)
	{
		free(data->heredoc_delimeter);
		data->heredoc_delimeter = NULL;
	}
	free(command_buff);
}
