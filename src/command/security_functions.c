/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:43:16 by patri             #+#    #+#             */
/*   Updated: 2025/04/08 17:04:36 by pamanzan         ###   ########.fr       */
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

void	free_list(t_env	*data)
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
		if(current->type)
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

void	error_msg(char *str, int flag)
{
	if (flag == 0)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else if (flag == 1)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command NOT found\n", 2);
	}
	else if (flag == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Perimssion denied\n", 2);
	}
}
