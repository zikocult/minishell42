/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:43:16 by patri             #+#    #+#             */
/*   Updated: 2025/01/11 08:55:41 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	free_list(t_env	*data)
{
	t_var	*current;
	t_var	*next_node;

	current = data->head;
	while (current->next)
	{
		next_node = current->next;
		free(current->content);
		free(current->var_name);
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
